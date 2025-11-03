# !/usr/bin/env bash

#set -euo pipefail
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BASE_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
source "$BASE_DIR/common/lib.sh"
source "$BASE_DIR/common/versions.sh" 2>/dev/null || true

# -------- Arg parse --------
PREFIX=""
BIN_DIR=""
CONF_DIR=""
# ---------------------------
while [[ $# -gt 0 ]]; do
  case "$1" in
    --prefix) PREFIX="$2"; shift 2;;
    --bin-dir) BIN_DIR="$2"; shift 2;;
    --conf-dir) CONF_DIR="$2"; shift 2;;
    *) err "Unknown argument: $1"; exit 1;;
  esac
done
TOOL_CHAIN_DIR="${PREFIX}/toolchains"


info "Starting macOS native installation…"
echo "    Installation prefix: ${PREFIX}"
info "Looking for prerequisites…"
# Prerequisite: xcode-select --install, check via `xcode-select -v`
if command -v xcode-select >/dev/null 2>&1; then
    XCODE_VERSION="$(xcode-select -v 2>/dev/null | sed -En 's/.*version[[:space:]]+([0-9.]+).*/\1/p' | sed 's/\.$//')"
    : "${XCODE_VERSION:=unknown}"
    info "Xcode Command Line Tools are detected (version: ${XCODE_VERSION})."
else
    err "Xcode Command Line Tools not found, which is essential for building. Please install them first:"
    err "  xcode-select --install"
    exit 1
fi

# prerequisite: CMake
if ! command -v cmake >/dev/null 2>&1; then
    err "CMake not found, which is essential for building. Please install it first (e.g., via Homebrew):"
    err "  brew install cmake"
    exit 1
else
    CMAKE_VERSION="$(cmake --version | head -n1 | awk '{print $3}')"
    info "CMake is detected (version: ${CMAKE_VERSION})."
fi

BREW_BIN="/opt/homebrew/bin/brew"
[ -x "$BREW_BIN" ] || BREW_BIN="/usr/local/bin/brew"
BREW_PREFIX="$($BREW_BIN --prefix)"


need_cmd() { command -v "$1" >/dev/null 2>&1 || MISSING+=("$1"); }
MISSING=()
need_cmd qt@5
need_cmd xerces-c
need_cmd expat
need_cmd autoconf
need_cmd automake
need_cmd gsl
need_cmd libtool || need_cmd glibtoolize
need_cmd pkg-config


if [ ${#MISSING[@]} -ne 0 ]; then
    err "The following required build tools are missing: ${MISSING[*]}"
    err "These will be installed with Homebrew."
    brew install "${MISSING[@]}"
fi



mkdir -p "${TOOL_CHAIN_DIR}"
info "Toolchains (ROOT, Geant4, etc.) will be installed under: ${TOOL_CHAIN_DIR}"

JOBS="$(sysctl -n hw.ncpu 2>/dev/null || echo 4)"
info "Using ${JOBS} parallel jobs for building."
cd "${TOOL_CHAIN_DIR}"


# ROOT installation
announce "Installing ROOT"
ROOT_DIR="${TOOL_CHAIN_DIR}/root"
echo "    ROOT version: ${ROOT_VERSION?}"
curl -LO https://root.cern/download/root_v${ROOT_VERSION}.macos-13.7-arm64-clang150.tar.gz # Download ROOT precompiled for macOS ARM64 -> Fix later: maybe add x86_64 support

tar xzf root_v${ROOT_VERSION}.macos-13.7-arm64-clang150.tar.gz -C "${TOOL_CHAIN_DIR}"
rm -f root_v${ROOT_VERSION}.macos-13.7-arm64-clang150.tar.gz
export DYLD_LIBRARY_PATH=""
source root/bin/thisroot.sh # BAT installer needs to find ROOT
ok "ROOT ${ROOT_VERSION} installed."


# ===== Geant4 installation (macOS + Qt5) =====
announce "Installing Geant4 (Qt5)"
echo "    Geant4 version: ${GEANT4_VERSION?}"

BREW_PREFIX="$(brew --prefix 2>/dev/null || true)"
if [ -z "$BREW_PREFIX" ]; then
  if [ -d /opt/homebrew ]; then BREW_PREFIX=/opt/homebrew
  else BREW_PREFIX=/usr/local
  fi
fi

QT5_PREFIX="$(brew --prefix qt@5 2>/dev/null || echo "${BREW_PREFIX}/opt/qt@5")"
XERCES_PREFIX="$(brew --prefix xerces-c 2>/dev/null || echo "${BREW_PREFIX}/opt/xerces-c")"

G4_INSTALL_DIR="${TOOL_CHAIN_DIR}/geant4/${GEANT4_VERSION}"
G4_TARBALL="geant4-${GEANT4_VERSION}.tar.gz"
G4_SRC_DIR="${TOOL_CHAIN_DIR}/geant4-${GEANT4_VERSION}"
G4_BUILD_DIR="${TOOL_CHAIN_DIR}/geant4-${GEANT4_VERSION}-build"   # <— build dir

curl -fL -o "${TOOL_CHAIN_DIR}/${G4_TARBALL}" \
  "https://gitlab.cern.ch/geant4/geant4/-/archive/${GEANT4_VERSION}/${G4_TARBALL}"
tar xzf "${TOOL_CHAIN_DIR}/${G4_TARBALL}" -C "${TOOL_CHAIN_DIR}"
mkdir -p "${G4_BUILD_DIR}" "${G4_INSTALL_DIR}"

# CMake configuration
CMAKE_PREFIX_PATH="${QT5_PREFIX};${XERCES_PREFIX}"
QT5_CMAKE_DIR="${QT5_PREFIX}/lib/cmake/Qt5"


cmake -S "${G4_SRC_DIR}" -B "${G4_BUILD_DIR}" \
  -DCMAKE_INSTALL_PREFIX="${G4_INSTALL_DIR}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_CXX_STANDARD=17 \
  -DCMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}" \
  -DCMAKE_POLICY_DEFAULT_CMP0135=NEW \
  -DBUILD_SHARED_LIBS=ON \
  -DGEANT4_BUILD_MULTITHREADED=ON \
  -DGEANT4_BUILD_STORE_TRAJECTORY=ON \
  -DGEANT4_INSTALL_DATA=ON \
  -DGEANT4_INSTALL_EXAMPLES=ON \
  -DGEANT4_USE_QT=ON \
  -DGEANT4_USE_QT_QT6=OFF \
  -DQt5_DIR="${QT5_CMAKE_DIR}" \
  -DGEANT4_USE_OPENGL=ON \
  -DGEANT4_USE_OPENGL_X11=OFF \
  -DGEANT4_USE_GDML=ON \
  -DXercesC_ROOT="${XERCES_PREFIX}" \
  -DGEANT4_USE_SYSTEM_ZLIB=ON \
  -DGEANT4_USE_SYSTEM_EXPAT=ON


cmake --build "${G4_BUILD_DIR}" -j"${JOBS}"
cmake --install "${G4_BUILD_DIR}"
ln -sfn "${G4_INSTALL_DIR}" "${TOOL_CHAIN_DIR}/geant4/current"
# Cleanup
rm -f "${TOOL_CHAIN_DIR}/${G4_TARBALL}"
rm -rf "${G4_BUILD_DIR}" "${G4_SRC_DIR}"
ok "Geant4 ${GEANT4_VERSION} installed with Qt5 at ${G4_INSTALL_DIR}"



# Installing assimp, tetgen, BAT
cd ${TOOL_CHAIN_DIR}
announce "Installing assimp"
ASSIMP_INSTALL_DIR="${TOOL_CHAIN_DIR}/assimp"
git clone https://github.com/assimp/assimp.git # From official repo -> just for testing, use our fork later if needed
cd ${ASSIMP_INSTALL_DIR}
cmake CMakeLists.txt
cmake --build . -j"${JOBS}"
ok "assimp installed."


announce "Installing tetgen"
cd ${TOOL_CHAIN_DIR}
TETGEN_DIR="${TOOL_CHAIN_DIR}/tetgen"
git clone https://github.com/christopherpoole/tetgen.git
cd ${TETGEN_DIR}
# Source code compile
clang++ -std=c++11 -O3 -fPIC -c tetgen.cxx predicates.cxx -Wno-deprecated-declarations
# Static library
ar rcs libtetgen.a tetgen.o predicates.o
# Dynamic library
clang++ -dynamiclib -o libtetgen.dylib tetgen.o predicates.o \
  -install_name @rpath/libtetgen.dylib
# Regular directory structure if needed
# mkdir -p include lib
# cp -f tetgen.h include/
# mv -f libtetgen.* lib/
# Symlink for consistency with Linux installations
ln -sf libtetgen.dylib lib/tetlib.so
make -j"${JOBS}"
ok "tetgen installed."


cd "${TOOL_CHAIN_DIR}"
announce "Installing BAT"
# ===== BAT installation (macOS) =====
# 0) Homebrew  and libtool check
if ! command -v brew >/dev/null 2>&1; then
    echo "[!] Homebrew yok. Kur: /bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
    exit 1
fi
# Find brew location and libtool prefix
BREW_BIN="$(command -v brew)"
BREW_PREFIX="$("$BREW_BIN" --prefix)"

# Is libtool installed?
if ! "$BREW_BIN" list --versions libtool >/dev/null 2>&1; then
    echo "[*] Installing libtool via Homebrew…"
    "$BREW_BIN" install libtool
fi

# exact glibtoolize and glibtool paths
GLIBTOOLIZE_PATH="$("$BREW_BIN" --prefix libtool)/bin/glibtoolize"
GLIBTOOL_PATH="$("$BREW_BIN" --prefix libtool)/bin/glibtool"

# Check paths
if [ ! -x "$GLIBTOOLIZE_PATH" ]; then
    if command -v glibtoolize >/dev/null 2>&1; then
        GLIBTOOLIZE_PATH="$(command -v glibtoolize)"
    elif command -v libtoolize >/dev/null 2>&1; then
        # fallback to libtoolize
        GLIBTOOLIZE_PATH="$(command -v libtoolize)"
    else
        echo "[!] glibtoolize/libtoolize not found. Is Brew libtool installed? Try again:"
        echo "    $BREW_BIN install libtool"
        exit 1
    fi
fi

# 1) Environment variables
: "${ACLOCAL_PATH:=}"
export ACLOCAL_PATH="${ACLOCAL_PATH:+${ACLOCAL_PATH}:}${BREW_PREFIX}/share/aclocal"
export LIBTOOL="$GLIBTOOL_PATH"
export LIBTOOLIZE="$GLIBTOOLIZE_PATH"

# 2) Source code clone
BAT_VERSION="v0.9.4.1"
BAT_DIR="${TOOL_CHAIN_DIR}/bat"
rm -rf "${BAT_DIR}"
git clone https://github.com/bat/bat.git
cd "${BAT_DIR}"

# 3) throw() fix for C++11 compatibility
cp BAT/BCMath.h BAT/BCMath.h.bak
find BAT -name '*.h' -print0 \
    | xargs -0 sed -i.bak -E 's/\)\s*throw\s*\([^)]*\)/) noexcept(false)/g'

grep -Rn "throw *\(" BAT || echo "All throw(...) clauses fixed."

# 4) Fix for ROOT::Math::Util::ToString issue in BCIntegrate.cxx
echo "[*] Fixing ROOT::Math::Util::ToString compatibility issue..."
cat > /tmp/bcintegrate_patch.sed << 'EOF'
# Replace ToString usage with std::to_string
s/using ROOT::Math::Util::ToString;//g
s/ToString(\([^)]*\))/std::to_string(\1)/g
EOF

if [ -f "src/BCIntegrate.cxx" ]; then
    sed -i.bak -f /tmp/bcintegrate_patch.sed src/BCIntegrate.cxx
    echo "[*] BCIntegrate.cxx patched for ROOT 6 compatibility"
fi

rm -f /tmp/bcintegrate_patch.sed

# 5) Autotools fixes
mkdir -p m4 bat-install

sed -i.bak \
    -e 's/\<AM_CONFIG_HEADER\>/AC_CONFIG_HEADERS/g' \
    -e 's/\<AM_PROG_LIBTOOL\>/LT_INIT/g' \
    -e 's/^AC_OUTPUT(.*)$/AC_OUTPUT/' \
    configure.ac || true

grep -q 'AC_PROG_RANLIB' configure.ac || \
    awk '{
        print $0;
        if ($0 ~ /AC_PROG_CC/ && !p) { print "AC_PROG_RANLIB"; print "AC_PROG_AR"; p=1 }
    }' configure.ac > configure.ac.tmp && mv configure.ac.tmp configure.ac

# 6) Run Autotools
"$LIBTOOLIZE" --force --copy
aclocal -I m4 -I "$BREW_PREFIX/share/aclocal"
autoreconf -fvi

# 7) Cleanup
make -C src clean 2>/dev/null || true
rm -f src/libBAT_rdict.cxx src/libBAT_rdict.cxx.tmp 2>/dev/null || true

# 8) Configure ve build
./configure --prefix="${BAT_DIR}/bat-install" \
    --with-rootsys="$(root-config --prefix)" \
    --disable-static

make -j"$JOBS"
make install

ok "BAT installed."