#!/usr/bin/env bash
set -euo pipefail

PKM=""
if command -v dnf >/dev/null; then
  PKM=dnf
elif command -v apt-get >/dev/null; then
  PKM=apt
fi

case "$PKM" in
  dnf)
    sudo dnf -y install \
      git curl wget ca-certificates \
      tar bzip2 xz unzip \
      make gcc gcc-c++ cmake \
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
      xauth \
      docker.io podman apptainer || true
    ;;
  *)
    echo "[deps] Unknown package manager; please install dependencies manually." >&2
    exit 0
    ;;
esac
