GeMSE_toolkit/
  docs/                     # user guide, developer guide
  examples/
  data-registry/            # small example data + schema, hashes with README
  containers/
    docker/                 # base image + variants (CPU/GPU/minimal)
    apptainer/              # Apptainer/Singularity recipe (derived from Docker)
  pipelines/
    hpge_material_screening/
    hpge_resolution/
    radon_chamber/
  python/
    gemse-core/             # IO, schema, logging, config, common utils
    gemse-analyses/         # spectral analysis, CB fit, efficiency, etc. (API)
    gemse-cli/              # `gemse` command; plug-in discovery
  cpp/
    gemse-root-tools/       # ROOT/BAT based tools
  ci/
    github/                 # CI workflows
  LICENSE
  README.md

