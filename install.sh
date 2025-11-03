#!/usr/bin/env bash


set -euo pipefail

APP_NAME="gemse"
IMAGE_TAG_DEFAULT="docker://ramirezdiego/gemse_env:latest"

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/common/lib.sh"


OS="$(uname -s)"


# Welcome message
printf "%s\n" "=========================================================================="
printf "%s\n" "               Welcome to GeMSE toolkit installation!"
printf "%s\n" "=========================================================================="
cat <<'EOF'
GeMSE_toolkit is the unified software framework under development for the
Germanium Material and meteorite Screening Experiment (GeMSE), designed for
low-background gamma-ray spectroscopy data analysis and simulation.

⚠️  Note: v0.1.0-alpha is a structural pre-release, consolidating repositories
    and establishing layout before the unified toolkit interface.
EOF
echo



info "OS detected:"
case "$OS" in
  Darwin) 
    echo "    - macOS";;
  Linux)  echo "    - Linux";;
  *) err "Unsupported OS: $OS"; exit 1;;
esac


# gemse command check
if command -v "${APP_NAME}" >/dev/null 2>&1; then
  err "A previous installation of GeMSE environment detected (command '${APP_NAME}' exists)."
  err "Please remove it before proceeding."
  exit 1
fi

# --- Installation scope selection ---
echo
info "Please select installation location of GeMSE environment"
read -r -p "    System wide (1) or local (2) installation: " install_choice
case "${install_choice:-2}" in
  1)
    PREFIX="/opt/GeMSE_toolkit"
    BIN_LINK="/usr/local/bin/${APP_NAME}"
    USE_SUDO="sudo"
    ;;
  2|*)
    PREFIX="$HOME/.local/share/gemse"
    mkdir -p "$HOME/.local/bin"
    BIN_LINK="$HOME/.local/bin/${APP_NAME}"
    USE_SUDO=""
    ;;
esac
info "GeMSE environment will be installed in: $PREFIX"

IMAGES_DIR="${PREFIX}/images"
VENV_DIR="${PREFIX}/gemse_venv"
BIN_DIR="${PREFIX}/bin"
CONF_DIR="${PREFIX}/config"


# --- Handle previous installation ---
if [[ -d "$PREFIX" ]]; then
  info "Previous installation detected at ${PREFIX}"
  read -r -p "    Do you want to remove it and continue? (y/n): " keep_remove_previous
  case "${keep_remove_previous:-n}" in
    y|Y )
      info "Removing previous installation…"
      ${USE_SUDO} rm -rf "${PREFIX}"
      ;;
    n|N )
      info "Installation aborted."
      exit 0
      ;;
    * )
      err "Invalid choice. Installation aborted."
      exit 1
      ;;
  esac
fi

# Prepare directories
mkdir -p "${IMAGES_DIR}" "${BIN_DIR}" "${CONF_DIR}"
mkdir -p "$(dirname "${BIN_LINK}")"

# --- gemse_venv (for CLI) ---
if [ ! -d "${VENV_DIR}" ]; then
  info "Creating Python virtual environment at: ${VENV_DIR}"
  python3 -m venv "${VENV_DIR}"
fi

# Always upgrade pip and install/update gemse package
echo "Installing/Updating GeMSE package in the virtual environment…"
"${VENV_DIR}/bin/python" -m pip install --upgrade pip
# Install gemse package (from current directory) In the future 
"${VENV_DIR}/bin/python" -m pip install . 

# Copy utils
announce "Copying utility scripts…"
CPP_DIR="${PREFIX}/cpp"
JUPYTER_DIR="${PREFIX}/jupyter"
GEMSE_PYANA="${BIN_DIR}/gemse_pyana"

mkdir -p "${CPP_DIR}" "${JUPYTER_DIR}" "${GEMSE_PYANA}"
cp -r ${SCRIPT_DIR}/cpp/* "${CPP_DIR}/"
cp -r ${SCRIPT_DIR}/jupyter/* "${JUPYTER_DIR}/"
cp -r ${SCRIPT_DIR}/python/gemsepyana/* "${GEMSE_PYANA}/"
ok "Utility scripts copied."

# --- Build environment (container/native vs.) ---
bash "$SCRIPT_DIR/common/create-env.sh" \
  --os "$OS" \
  --prefix "$PREFIX" \
  --bin-dir "$BIN_DIR" \
  --conf-dir "$CONF_DIR" \
  --image "$IMAGE_TAG_DEFAULT"

# --- one entry point launcher ---
LAUNCHER="${BIN_DIR}/${APP_NAME}"
cat > "${LAUNCHER}" <<'EOF'
#!/usr/bin/env bash
set -euo pipefail

# Calls gemse from the venv, passing all args.
# PREFIX, VENV and possible runtime.conf are read here.

PREFIX="${PREFIX_OVERRIDE:-$HOME/.local/share/gemse}"
VENV_DIR="${VENV_OVERRIDE:-${PREFIX}/gemse_venv}"
CONF_FILE="${CONF_OVERRIDE:-${CONF_DIR}/runtime.conf}"

# if runtime.conf exists, source it (RUNTIME, IMAGE, SIF, etc. can be defined)
if [ -f "$CONF_FILE" ]; then
  # shellcheck disable=SC1090
  . "$CONF_FILE"
fi

# Python CLI (from venv)
exec "${VENV_DIR}/bin/python" -m gemse "$@"
EOF

# Make the launcher executable
chmod +x "${LAUNCHER}"

# Optional: symlink (to be in user PATH)
ln -sfn "${LAUNCHER}" "${BIN_LINK}"




ok "GeMSE environment installation finished."
