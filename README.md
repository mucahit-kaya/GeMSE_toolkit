# GeMSE_toolkit

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](./LICENSE)
[![Status: Alpha](https://img.shields.io/badge/status-alpha-orange.svg)](https://github.com/mucahit-kaya/GeMSE_toolkit/releases)

**GeMSE_toolkit** is the unified software framework under development for the **Germanium Material and meteorite Screening Experiment (GeMSE)**, designed for low-background gamma-ray spectroscopy data analysis and simulation.  
It brings together the previously separated analysis, simulation, preprocessing, and environment setup tools into a single, reproducible monorepo.

> ⚠️ **Note:** This version (`v0.1.0-alpha`) is a *structural pre-release*.  
> It is **not yet ready for direct use or deployment**.  
> The purpose of this stage is to consolidate the repositories and establish a consistent project layout before implementing the unified toolkit interface.

---

## Repository structure

The following existing GeMSE repositories have been integrated via `git subtree`:

| Source repository | Imported branch | Target path |
|--------------------|-----------------|--------------|
| [AG-Schumann/GeMSE_environment](https://github.com/AG-Schumann/GeMSE_environment) | `master` | `containers/environment/` |
| [AG-Schumann/GeMSE_ROOT_scripts](https://github.com/AG-Schumann/GeMSE_ROOT_scripts) | `compass` | `cpp/gemse-root-scripts/` |
| [AG-Schumann/GeMSE_analysis](https://github.com/AG-Schumann/GeMSE_analysis) | `master` | `cpp/gemse-analysis/` |
| [AG-Schumann/GeMSE_MC](https://github.com/AG-Schumann/GeMSE_MC) | `compass` | `cpp/gemse-mc/` |
| [AG-Schumann/GeMSE_notebooks](https://github.com/AG-Schumann/GeMSE_notebooks) | `main` | `jupyter/gemse-notebooks/` |
| [AG-Schumann/GeMSE_gemsepyana](https://github.com/AG-Schumann/GeMSE_gemsepyana) | `main` | `python/gemsepyana/` |

- Each module was imported using `git subtree --squash` to preserve logical history while keeping the monorepo lightweight.  
- Each subtree corresponds to a functional domain (analysis, simulation, environment, or visualization).

---

## Goal of the toolkit

The long-term goal of **GeMSE_toolkit** is to provide:

- A unified command-line interface (`gemse`) for all analysis and simulation pipelines.  
- Shared configuration and data schemas for reproducible workflows.  
- Portable container environments (Docker & Apptainer).  
- Consistent documentation, testing, and CI/CD integration.  
- Easy onboarding for new users and maintainers.

---

## Current status

- Repository structure defined and subtrees integrated.  
- Docker and Apptainer environments placed under `containers/`.  
- ⚠️ No functional integration yet — tools are still independent.  
- CLI, configuration unification, and CI pipelines are under development.

---

## 🔧 Development branch

Active development continues in  
 [`development` branch](https://github.com/mucahit-kaya/GeMSE_toolkit/tree/development)

Please use `main` only as a reference for the latest structural snapshot.

---

## Next steps

1. Implement unified `gemse` CLI to run analysis and simulation pipelines.  
2. Standardize configuration formats across all modules.  
3. Add automated tests and GitHub Actions CI workflows.  
4. Integrate example datasets and minimal working demos.  
5. Release `v0.1.0` once the toolkit reaches runnable stability.

---

## Contributors

- **Mücahit Kaya** — initial integration, monorepo setup  
- **AG Schumann Group (Uni Freiburg)** — original GeMSE repositories and analysis tools  

---

## 📄 License

The **GeMSE_toolkit** monorepo is distributed under the terms of the **GNU General Public License v3 (GPL-3.0)**,  
which governs all newly created integration code and documentation in this repository.

> ⚠️ **Important note on license inheritance:**  
> This monorepo integrates several upstream repositories with different or missing license declarations.  
> To remain transparent, the license status of each imported component is summarized below:

| Component | Source | Upstream License | Integrated Under |
|------------|---------|------------------|------------------|
| `containers/environment/` | GeMSE_environment | GPL-3.0 | GPL-3.0 |
| `cpp/gemse-mc/` | GeMSE_MC | GPL-3.0 | GPL-3.0 |
| `cpp/gemse-root-scripts/` | GeMSE_ROOT_scripts | *No license specified* | Temporarily GPL-3.0 until clarified |
| `cpp/gemse-analysis/` | GeMSE_analysis | *No license specified* | Temporarily GPL-3.0 until clarified |
| `jupyter/gemse-notebooks/` | GeMSE_notebooks | *No license specified* | Temporarily GPL-3.0 until clarified |
| `python/gemsepyana/` | GeMSE_gemsepyana | MIT | GPL-3.0-compatible |

**Interpretation:**
- MIT-licensed components are legally compatible with GPL-3.0 and can be redistributed under it.  
- GPL-3.0 components retain their original license.  
- Components without an explicit license remain under copyright by their original authors;  
  their inclusion here is provisional until explicit permission or license clarification is obtained.

All newly written integration scripts, documentation, and tooling in this repository  
are explicitly licensed under **GPL-3.0** unless otherwise noted.

---

### Citation

If you use GeMSE data or analysis methods, please cite the relevant GeMSE publications and tools as listed in the original repositories.

---

### Version

**Current version:** `v0.1.0-alpha`  
**Status:** Structural pre-release – not functional yet.
