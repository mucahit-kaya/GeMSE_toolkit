GeMSE_toolkit/
  docs/                     # user guide, developer guide
  examples/
  data-registry/            # small example data + schema, hashes with README
  containers/
    environment/                 # base image + variants (CPU/GPU/minimal) for python analysis, CLI, pipelines; fetched from GeMSE_environment
  cpp/
    gemse-root-scripts/       # ROOT/BAT based tools; originally from GeMSE_ROOT_scripts
    gemse-analysis/          # C++ spectral analysis library; originally from GeMSE_analysis
  jupyter-notebooks/      
    analysis/               # Collection of notebooks to look into raw and processed CAEN MCA data; fetched from GeMSE_notebooks
  python/
    gemse-core/             # IO, schema, logging, config, common utils
    gemse-analyses/         # spectral analysis, CB fit, efficiency, etc. (API)
    gemse-cli/              # `gemse` command; plug-in discovery
  LICENSE
  README.md

