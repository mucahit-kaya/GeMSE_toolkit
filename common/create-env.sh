#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BASE_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
source "$BASE_DIR/common/lib.sh"

# -------- Arg parse --------
OS=""
PREFIX=""
BIN_DIR=""
CONF_DIR=""
IMAGE=""
MODE=""
# ---------------------------

while [[ $# -gt 0 ]]; do
  case "$1" in
    --os) OS="$2"; shift 2;;
    --prefix) PREFIX="$2"; shift 2;;
    --bin-dir) BIN_DIR="$2"; shift 2;;
    --conf-dir) CONF_DIR="$2"; shift 2;;
    --image) IMAGE="$2"; shift 2;;
    *) err "Unknown arg: $1"; exit 1;;
  esac
done

[[ -z "$OS" ]] && OS="$(detect_os)"
[[ -z "${IMAGE:-}" ]] && IMAGE="docker://ramirezdiego/gemse_env:latest"

info "OS=$OS"
info "PREFIX=$PREFIX"
info "BIN_DIR=$BIN_DIR  CONF_DIR=$CONF_DIR"
info "IMAGE=$IMAGE"

case "$OS" in
  Darwin)
    echo
    info "macOS detected. Containers not suitable for Geant4/ROOT visualization (/dev/dri absent; no native Singularity)."
    echo "   → Native source installation will be performed (OpenGL ready, slower build)."
    echo
    info "Building environment from source…"
    bash "$BASE_DIR/macos/macos_install.sh" --prefix "$PREFIX" --bin-dir "$BIN_DIR" --conf-dir "$CONF_DIR"
    bash "$BASE_DIR/macos/macos_post_setup.sh" --prefix "$PREFIX"
    ok "macOS native toolchain ready."
    ;;

  Linux)
    # Runtime detection (docker > podman > apptainer > singularity)
    RUNTIME="$(detect_runtime)"
    if [[ -z "$RUNTIME" ]]; then
      err "No container runtime found. Install Docker/Podman or Apptainer/Singularity."
      exit 1
    fi
    info "Detected runtime: $RUNTIME"

    # Dependencies (don't forget to check within the distro)
    info "Installing dependencies…"
    bash "$BASE_DIR/linux/install_deps.sh" --prefix "$PREFIX" || true

    # Installation mode selection
    echo
    info "Select installation mode:"
    echo "  1) Source build (native installation from source; slower but flexible)"
    echo "  2) Container-based (Docker/Podman or Apptainer/Singularity; faster setup)"
    read -r -p "Choose 1 or 2 [default 2]: " MODE
    case "$MODE" in
      1)
        info "Building environment from source…"
        bash "$BASE_DIR/linux/install_source.sh" --prefix "$PREFIX" --bin-dir "$BIN_DIR" --conf-dir "$CONF_DIR"
        bash "$BASE_DIR/linux/post_setup.sh" --prefix "$PREFIX"
        ;;
      2)
        info "Setting up container-based environment…"
        if [[ "$RUNTIME" == "docker" || "$RUNTIME" == "podman" ]]; then
          bash "$BASE_DIR/linux/install_docker_env.sh" \
            --runtime "$RUNTIME" --image "$IMAGE" --prefix "$PREFIX" --bin-dir "$BIN_DIR" --conf-dir "$CONF_DIR"
        elif [[ "$RUNTIME" == "apptainer" || "$RUNTIME" == "singularity" ]]; then
          bash "$BASE_DIR/linux/install_apptainer_env.sh" \
            --runtime "$RUNTIME" --image "$IMAGE" --prefix "$PREFIX" --images-dir "$PREFIX/images" --bin-dir "$BIN_DIR" --conf-dir "$CONF_DIR"
        else
          err "Unsupported runtime: $RUNTIME"
          exit 1
        fi
        ;;
      *)
        err "Unknown MODE: $MODE (use 'source' or 'docker')"
        exit 1
        ;;
    esac
    ok "Linux env ready."
    ;;

  *)
    err "Unsupported OS: $OS"
    exit 1
    ;;
esac