#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
BASE_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
source "$BASE_DIR/common/lib.sh"
source "$BASE_DIR/common/versions.sh" 2>/dev/null || true

# -------- Arg parse --------
PREFIX=""
BIN_DIR=""
CONF_DIR=""
IMAGE=""
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

# Pulling GeMSE_env from docker
echo "Pulling GeMSE_env container image…"
docker pull ramirezdiego/gemse_env

# Pulling singularity/apptainer image -
echo "Building Singularity/Apptainer image…"
cd "$PREFIX/images"
#singularity build --tmpdir "${PREFIX}/images" gemse_env.simg docker://ramirezdiego/gemse_env:latest

# Creating container launcher script
cd $PREFIX
SETUP="${PREFIX}/gemse_env.sh"
cat > "$SETUP" <<EOF
#!/usr/bin/env bash
set -euo pipefail

PREFIX="$PREFIX"

# shellcheck disable=SC1091
source "\$PREFIX/gemse_venv/bin/activate"

xhost +SI:localuser:$(id -un)

RUNTIME="\${RUNTIME:-docker}"
IMAGE="\${IMAGE:-ramirezdiego/gemse_env:latest}"

docker run --rm -it \
  --user $(id -u):$(id -g) \
  -e DISPLAY="$DISPLAY" \
  -e XAUTHORITY=/tmp/.docker.xauth \
  -e QT_X11_NO_MITSHM=1 \
  -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
  -v "$PWD":/work:Z \
  -w /work \
  --device /dev/dri:/dev/dri \
  --ipc=host \
  ramirezdiego/gemse_env:latest \
  bash -lc 'source /opt/GeMSE/setup_sims.sh; exec bash'

EOF

chmod +x "$SETUP"
ok "Created launcher: $SETUP"
echo
info "Usage:"
echo "  $SETUP"
echo
ok "Container-based GeMSE launcher is ready."



