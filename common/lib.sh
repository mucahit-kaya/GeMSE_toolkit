#!/usr/bin/env bash
set -euo pipefail

# Colors & logging (graceful fallback)
if command -v tput >/dev/null 2>&1 && [[ ${TERM:-} != "dumb" ]]; then
  BOLD=$(tput bold); RESET=$(tput sgr0)
  RED=$(tput setaf 1); GRN=$(tput setaf 2); CYN=$(tput setaf 6)
else
  BOLD=""; RESET=""; RED=""; GRN=""; CYN=""
fi

info() { printf "%s[*]%s %s\n" "$CYN" "$RESET" "$*"; }
ok()   { printf "%s[ok]%s %s\n"  "$GRN" "$RESET" "$*"; }
err()  { printf "%s[!]%s %s\n"   "$RED" "$RESET" "$*" 1>&2; }

detect_os() { uname -s; }

# docker > podman > apptainer > singularity sırası
detect_runtime() {
  if command -v docker >/dev/null 2>&1; then echo docker; return; fi
  if command -v podman >/dev/null 2>&1; then echo podman; return; fi
  if command -v apptainer >/dev/null 2>&1; then echo apptainer; return; fi
  if command -v singularity >/dev/null 2>&1; then echo singularity; return; fi
  echo ""
}

confirm() {
  local q="${1:-Proceed?}"; read -r -p "$q (y/n): " a
  [[ "${a:-n}" =~ ^[Yy]$ ]]
}


function announce {
    echo
    echo "#######################################################################################"
    echo "## $1       ("`date -u`")"
    echo
}
