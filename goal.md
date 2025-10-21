GeMSE_toolkit/
  docs/                     # user guide, developer guide
  examples/
  data-registry/            # small example data + schema, hashes with README
  containers/
    gemse-environment/                 # base image + variants (CPU/GPU/minimal) for python analysis, CLI, pipelines; fetched from GeMSE_environment
  cpp/
    gemse-root-scripts/       # ROOT/BAT based tools; originally from GeMSE_ROOT_scripts
    gemse-analysis/          # C++ spectral analysis library; originally from GeMSE_analysis
    gemse-mc/                # Geant4-based MC simulation code; originally from GeMSE_MC
  jupyter/
    gemse-notebooks/               # Collection of notebooks to look into raw and processed CAEN MCA data; fetched from GeMSE_notebooks
  python/
    gemsepyana/       #  Collection of python tools for simple plotting/inspection of GeMSE spectra and data; fetched from GeMSE_gemsepyana
    gemse-core/             # IO, schema, logging, config, common utils
    gemse-cli/              # `gemse` command; plug-in discovery
  LICENSE
  README.md

