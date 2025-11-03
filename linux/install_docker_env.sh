#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BASE_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
source "$BASE_DIR/common/lib.sh"

# -------- Defaults --------
OS=""
PREFIX="${PREFIX:-$HOME/.local/share/gemse}"
BIN_DIR="${BIN_DIR:-$HOME/.local/bin}"
CONF_DIR="${CONF_DIR:-$HOME/.config/gemse}"
IMAGE="docker://ramirezdiego/gemse_env:latest"
RUNTIME=""
# --------------------------

# -------- Arg parse --------
while [[ $# -gt 0 ]]; do
  case "$1" in
    --os) OS="$2"; shift 2;;
    --prefix) PREFIX="$2"; shift 2;;
    --bin-dir) BIN_DIR="$2"; shift 2;;
    --conf-dir) CONF_DIR="$2"; shift 2;;
    --image) IMAGE="$2"; shift 2;;
    --runtime) RUNTIME="$2"; shift 2;;
    *) err "Unknown arg: $1"; exit 1;;
  esac
done
# --------------------------

mkdir -p "$PREFIX" "$BIN_DIR" "$CONF_DIR"

[[ -z "${RUNTIME:-}" ]] && RUNTIME="$(detect_runtime)"
info "Container runtime: ${RUNTIME:-none}"
info "IMAGE: $IMAGE"
info "PREFIX: $PREFIX"
info "BIN_DIR: $BIN_DIR"
info "CONF_DIR: $CONF_DIR"

# Pull image (best-effort)
if [[ -n "${RUNTIME:-}" ]]; then
  info "Pulling GeMSE_environment docker image from ${IMAGE}"
  case "$RUNTIME" in
    docker|podman)
      "$RUNTIME" pull "$IMAGE" || true
      ok "Image pulled (or already present)."
      ;;
    apptainer|singularity)
      # Apptainer "pull" to images dir could go here if you prefer local .sif
      :
      ;;
  esac
fi

WRAP="$BIN_DIR/gemse"
cat > "$WRAP" <<'EOF'
#!/usr/bin/env bash
set -euo pipefail

# User-overridable defaults
RUNTIME="${RUNTIME:-}"
IMAGE="${IMAGE:-docker://ramirezdiego/gemse_env:latest}"
WORKDIR="${WORKDIR:-$PWD}"

# Try to detect runtime if not provided
detect_runtime() {
  for r in docker podman apptainer singularity; do
    command -v "$r" >/dev/null 2>&1 && { echo "$r"; return; }
  done
  echo ""
}

[[ -z "$RUNTIME" ]] && RUNTIME="$(detect_runtime)"
if [[ -z "$RUNTIME" ]]; then
  echo "[gemse] ERROR: No container runtime found (docker/podman/apptainer/singularity)." >&2
  exit 1
fi

# X11 DISPLAY defaults
DISPLAY="${DISPLAY:-:0}"
XSOCK="/tmp/.X11-unix"
XAUTH_MOUNT=""
# If using Xorg with xhost local:root, this is enough. For Wayland/Xwayland, DISPLAY still points to :0
# Optionally, users can do: xhost +local:root

# Common mounts
BASIC_MOUNTS=(
  -v "$PWD":"$WORKDIR":Z
)
# X11 socket if present
if [[ -d "$XSOCK" ]]; then
  BASIC_MOUNTS+=( -v "$XSOCK":"$XSOCK":rw,Z )
fi

# /dev/dri if present (for OpenGL accel on Linux)
GPU_ARGS=()
if [[ -d /dev/dri ]]; then
  GPU_ARGS+=( --device=/dev/dri )
fi

# Extra groups (video) if available (docker only accepts numeric gid or name if present)
GROUP_ARGS=()
if getent group video >/dev/null 2>&1; then
  GROUP_ARGS+=( --group-add video )
fi

IPC_ARGS=( --ipc=host )

# Environment
ENV_ARGS=(
  -e DISPLAY="$DISPLAY"
  -e QT_X11_NO_MITSHM=1
)

# SELinux relabel note: we used ':Z' on bind mounts

case "$RUNTIME" in
  docker|podman)
    exec "$RUNTIME" run --rm -it \
      "${ENV_ARGS[@]}" \
      "${GPU_ARGS[@]}" \
      "${GROUP_ARGS[@]}" \
      "${IPC_ARGS[@]}" \
      "${BASIC_MOUNTS[@]}" \
      -w "$WORKDIR" \
      --name gemse_env \
      "$IMAGE" \
      /bin/bash
    ;;
  apptainer|singularity)
    # Apptainer/Singularity execution
    exec "$RUNTIME" exec \
      --env DISPLAY="$DISPLAY",QT_X11_NO_MITSHM=1 \
      --bind "$PWD:$WORKDIR" \
      "$IMAGE" /bin/bash
    ;;
  *)
    echo "[gemse] Unsupported runtime: $RUNTIME" >&2
    exit 1
    ;;
esac
EOF

chmod +x "$WRAP"
ok "Created launcher: $WRAP"
echo
info "Usage:"
echo "  $WRAP"
echo
ok "Container-based GeMSE launcher is ready."
