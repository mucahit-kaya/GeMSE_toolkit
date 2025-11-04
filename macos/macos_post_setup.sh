# !/bin/bash

# macOS specific post-installation steps
set -euo pipefail
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
    *) err "Unknown argument: $1"; exit 1;;
  esac
done

export PATH="/opt/homebrew/opt/qt@5/bin:$PATH"
export LDFLAGS="-L/opt/homebrew/opt/qt@5/lib"


ensure_path() {
  local file="$1"
  if [[ -f "$file" ]]; then
    if ! grep -qs 'export PATH="$HOME/.local/bin:$PATH"' "$file"; then
      printf '\nexport PATH="$HOME/.local/bin:$PATH"\n' >> "$file"
      info "$file updated with ~/.local/bin"
    fi
  fi
}
ensure_path "$HOME/.zprofile"
ensure_path "$HOME/.zshrc"
echo
info "PATH updated for macOS (zprofile/zshrc)."
info "Restart your terminal or run: source ~/.zprofile"



announce "Finalizing macOS post-installation steps"

SETUP="${PREFIX}/gemse_setup.sh"
SHELL_RC=""
if [ -n "${ZSH_VERSION-}" ]; then SHELL_RC="${HOME}/.zshrc"; fi
if [ -n "${BASH_VERSION-}" ]; then SHELL_RC="${HOME}/.bashrc"; fi
[ -z "$SHELL_RC" ] && SHELL_RC="${HOME}/.zshrc"

VENV_DIR_NAME="gemse_venv"
[ -d "${PREFIX}/venv" ] && VENV_DIR_NAME="venv"


cat > "${SETUP}" <<EOF
#!/usr/bin/env bash
# GeMSE environment setup script for macOS
# shellcheck shell=bash

echo "[GeMSE] Activating environment from: ${PREFIX}"

# Python virtual environment
if [ -f "${PREFIX}/${VENV_DIR_NAME}/bin/activate" ]; then
  # shellcheck disable=SC1091
  source "${PREFIX}/${VENV_DIR_NAME}/bin/activate"
  echo "[GeMSE] Python venv activated (${VENV_DIR_NAME}). Use 'deactivate' to exit."
else
  echo "[GeMSE] WARN: Python venv not found at ${PREFIX}/${VENV_DIR_NAME}. Skipping."
fi

# Common paths
export GEMSE_PREFIX="${PREFIX}"
export GEMSE_CONF_DIR="${PREFIX}/conf"
export GEMSE_TOOLCHAIN_DIR="${PREFIX}/toolchains"
export PATH="${PREFIX}/bin:\${PATH}"

# ---------- ROOT ----------
if [ -f "${PREFIX}/toolchains/root/bin/thisroot.sh" ]; then
  # shellcheck disable=SC1091
  export ROOTSYS="${PREFIX}/toolchains/root"
  source "${PREFIX}/toolchains/root/bin/thisroot.sh"
  echo "[GeMSE] ROOT initialized."
else
  echo "[GeMSE] WARN: ROOT not found at ${PREFIX}/toolchains/root."
fi

# ---------- Geant4 ----------
if [ -n "${GEANT4_VERSION-}" ] && [ -f "${PREFIX}/toolchains/geant4/${GEANT4_VERSION}/bin/geant4.sh" ]; then
  # shellcheck disable=SC1091
  source "${PREFIX}/toolchains/geant4/${GEANT4_VERSION}/bin/geant4.sh"
  # Eski/Make tabanlı sistemler için (varsa)
  if [ -f "${PREFIX}/toolchains/geant4/${GEANT4_VERSION}/share/Geant4/geant4make/geant4make.sh" ]; then
    # shellcheck disable=SC1091
    source "${PREFIX}/toolchains/geant4/${GEANT4_VERSION}/share/Geant4/geant4make/geant4make.sh"
  fi
  # Sets current directory as working directory for Geant4
  export G4WORKDIR="\$PWD"
  echo "[GeMSE] Geant4 initialized (version ${GEANT4_VERSION})."
else
  echo "[GeMSE] WARN: Geant4 not initialized; missing GEANT4_VERSION or geant4.sh."
fi

# ---------- Assimp ----------
export LD_LIBRARY_PATH="${PREFIX}/toolchains/assimp/bin:$LD_LIBRARY_PATH"
echo "[GeMSE] Assimp env loaded."


# ---------- BAT ----------
# Dynamic libs are managed via DYLD_* on macOS (SIP restricted in GUI apps)
export PATH="${PREFIX}/toolchains/bat/bat-install/bin:\${PATH}"
export DYLD_LIBRARY_PATH="${PREFIX}/toolchains/bat/bat-install/lib:\${DYLD_LIBRARY_PATH:-}"
export CPATH="${PREFIX}/toolchains/bat/bat-install/include:\${CPATH:-}"
export PKG_CONFIG_PATH="${PREFIX}/toolchains/bat/bat-install/lib/pkgconfig:\${PKG_CONFIG_PATH:-}"

# ---------- CMake/Cling path ----------
# For CMake find_package() calls
if command -v root-config >/dev/null 2>&1; then
  ROOT_PREFIX="\$(root-config --prefix 2>/dev/null)"
  if [ -n "\$ROOT_PREFIX" ]; then
    export CMAKE_PREFIX_PATH="\${ROOT_PREFIX}:\${CMAKE_PREFIX_PATH:-}"
  fi
fi
if [ -d "${PREFIX}/toolchains/geant4/${GEANT4_VERSION:-}/lib/cmake/Geant4" ]; then
  export CMAKE_PREFIX_PATH="${PREFIX}/toolchains/geant4/${GEANT4_VERSION}/lib/cmake/Geant4:\${CMAKE_PREFIX_PATH:-}"
fi
if [ -d "${PREFIX}/toolchains/bat/bat-install/lib/cmake" ]; then
  export CMAKE_PREFIX_PATH="${PREFIX}/toolchains/bat/bat-install/lib/cmake:\${CMAKE_PREFIX_PATH:-}"
fi

echo "[GeMSE] Environment ready."
EOF

chmod +x "${SETUP}"

# Add to shell initialization files
LINE="source \"${SETUP}\""
if ! grep -qsF "${LINE}" "${SHELL_RC}"; then
  printf '\n# GeMSE environment\n%s\n' "${LINE}" >> "${SHELL_RC}"
  echo "[*] Appended 'source ${SETUP}' to ${SHELL_RC}"
fi

# For current session
# shellcheck disable=SC1090
. "${SETUP}"

ok "Post-installation steps completed."
