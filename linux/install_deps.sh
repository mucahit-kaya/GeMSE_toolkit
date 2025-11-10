#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BASE_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
source "$BASE_DIR/common/lib.sh"

PKM=""
if command -v dnf >/dev/null; then
  PKM=dnf
elif command -v apt-get >/dev/null; then
  PKM=apt
fi


info "Installing dependencies using ${PKM}…"
case "$PKM" in
  dnf)
    sudo dnf -y install \
      git curl wget ca-certificates \
      tar bzip2 xz unzip \
      cmake gcc gcc-c++ make git \
      qt5-qtbase-devel qt5-qttools-devel  qt5-qt3d-devel \
      mesa-libGL-devel mesa-libGLU-devel \
      libX11-devel libXext-devel libXrender-devel libXrandr-devel libXmu-devel libXi-devel \
      xerces-c-devel expat-devel zlib-devel
      which pkgconf \
      mesa-libGL mesa-libGLU libX11 libXext libXrender libXrandr libXmu libXi \
      xauth xorg-x11-xauth \
      # optional container runtimes (isteğe bağlı):
      docker podman apptainer || true
    ;;
  apt)
    sudo apt-get update
    sudo apt-get -y install \
      git curl wget ca-certificates \
      tar bzip2 xz-utils unzip \
      build-essential cmake pkg-config \
      libgl1 libglu1-mesa libx11-6 libxext6 libxrender1 libxrandr2 libxmu6 libxi6 \
      xauth libexpat libexpat1-dev\
      docker.io podman apptainer || true
    ;;
  *)
    echo "[deps] Unknown package manager; please install dependencies manually." >&2
    exit 0
    ;;
esac

