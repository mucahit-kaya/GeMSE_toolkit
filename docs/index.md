# GeMSE_toolkit — Handbook (v0.1, draft)

> **Purpose:** This handbook is a **practical user guide** to simplify daily work with scattered modules within the unified monorepo. First a notebook, then a documentation site. The goal is to quickly transform the information gathered here into a **MkDocs Material** site.

---

## 0. Quick Start (TL;DR)

```bash
# 1) Clone the repository
git clone https://github.com/mucahit-kaya/GeMSE_toolkit
cd GeMSE_toolkit

# 2) Open the default docker environment (interactive shell)
docker pull ramirezdiego/gemse_env:latest
docker run -it --rm \
  -v "$PWD":/work \
  -w /work \
  ramirezdiego/gemse_env:latest \
  /bin/bash

# 3) Typical workflow examples
```

More information about docker environment usage is [here](run-environment.md).

---

## 1. Repository Map and Roles

```
GeMSE_toolkit/
├─ containers/
│  ├─ environment/           # Docker & Singularity recipes
│  └─ ...
├─ cpp/
│  ├─ gemse-analysis/        # C++ analysis code
│  ├─ gemse-mc/              # Geant4-based simulations
│  └─ gemse-root-scripts/    # ROOT macros / utility tools
├─ python/
│  └─ gemsepyana/            # Python analysis package
├─ jupyter/
│  └─ gemse-notebooks/       # Experimental notebooks and examples
├─ docs/                     # MkDocs content
├─ scripts/                  # CLI helpers for repetitive tasks
├─ LICENSE
└─ README.md
```

> **Note:** Subtrees were imported with `git subtree --squash`. Each folder focuses on its own domain; for cross-usage, refer to the **playbooks** sections in this handbook.

---

## 2. GeMSE_environment : Running the Analysis & Simulation Environment
More detailed instructions are available [here](run-environment.md).
### 2.1 Docker

```bash
# Pull the image
docker pull ramirezdiego/gemse_env:latest

# Run container
docker run -it --rm \
  -v "$PWD":/work \
  -w /work \
  ramirezdiego/gemse_env:latest \
  /bin/bash
```
For interactive docker usage, see [here](run-environment.md).

**Tips**

* For X11/ROOT graphical windows, XQuartz/Xorg is required on Mac/Linux.
* Inside the container:
```bash
# For Analysis tools (ROOT + BAT):
source /opt/GeMSE/setup.sh

# For Simulation tools (Geant4):
source /opt/GeMSE/geant4_setup.sh
```

### 2.2 Apptainer/Singularity (Recommended)
Some scripts are especially written for Singularity usage. For regular Linux users, it is recommended to use Singularity/Apptainer instead of Docker.
Please refer to [here](run-environment.md) for detailed instructions.

---

## 3. Code Building & Execution Playbooks

### 3.1 C++ Analysis (gemse-analysis)

```bash
cd cpp/gemse-analysis
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
./build/bin/<tool-name> --help
```

**Common Issues**

* `libstdc++` version conflicts → Build inside container.
* ROOT not found → `thisroot.sh` not sourced.

### 3.2 ROOT Scripts (gemse-root-scripts)

```bash
cd cpp/gemse-root-scripts
root -l scripts/energy_resolution.cxx
# or
root -l 'scripts/make_rootfile_spectrum.cxx("input.dat","out.root")'
```

### 3.3 Geant4 Simulations (gemse-mc)

```bash
cd cpp/gemse-mc
cmake -S . -B build -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_BUILD_MULTITHREADED=ON
cmake --build build -j
./build/bin/gemse-mc --help
```

### 3.4 Python Analysis (gemsepyana)

```bash
cd python/gemsepyana
pip install -e .
pytest -q   # if tests exist
python -m gemsepyana --help
```

### 3.5 Jupyter Notebooks

```bash
jupyter lab --notebook-dir=jupyter/gemse-notebooks --ip=0.0.0.0 --allow-root
```

---
## 4. How to Analyze a Spectrum:
Follow these steps to analyze a GeMSE spectrum using the integrated tools:

1. **Prepare your data**: Ensure your spectrum data is in the correct format (e.g., ROOT file).

2. **Load the data**: Use the provided Python scripts or Jupyter notebooks to load your spectrum data.

3. **Perform analysis**: Utilize the analysis functions available in the `gemsepyana` package to process your spectrum.

4. **Visualize results**: Generate plots and visualizations to interpret your analysis results.

5. **Save outputs**: Export your results in the desired format (e.g., figures, tables).
For detailed step-by-step instructions, refer to: [Analyzing a Spectrum](analyze-spectrum.md).

---

## 5. Roadmap Notes

* `gemse` unified CLI
* Config schema validation (pydantic/cerberus)
* Small reference data package and automated smoke tests

---

### Appendix: PR Checklist

* [ ] Updated README/Handbook steps
* [ ] Code formatting/lint passed
* [ ] Tests/smoke tests passed
* [ ] License headers correct
* [ ] Changelog updated