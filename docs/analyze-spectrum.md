# How to Analyze a Spectrum
This library suitable for analyzing GeMSE spectra provides several integrated tools to facilitate the process. It was built for esspecially GeMSE data that comes from CAEN MCA devices, but can be adapted for other similar spectral data formats.

### Measurement Folder Structure
The analysis workflow typically involves the following data structure:
```
measurement/
├── .compass/               # Configuration file for Compass data acquisition software, measurement metadata
├── CONFIG                   # Other configuration files for CAEN MCA settings.
└── DAQ/                     # Raw data folders for several runs from CAEN MCA.
    └── run_<number>/       # Individual run folders.
        ├── FILTERED         # Filtered spectrum data folder.
        ├── RAW              # Raw spectrum data folder.
            ├── DataR_CH0@DT5781A_793_run_<number>.root # Raw spectrum file for channel 0
            ├── DataR_CH1@DT5781A_793_run_<number>.root # Raw spectrum file for channel 1
        └── UNFILTERED       # Unfiltered spectrum data folder.
```


Follow these steps to analyze a GeMSE spectrum using the integrated tools:
- **Prepare your data**: Ensure your spectrum data is in the correct format (e.g., ROOT, CSV, txt file).

    To better organize your workspace, we recommend placing your data in a folder named `spectra/`. The `init_results_folder.sh` script will automatically create the necessary directory structure to accommodate the measurement that has different runs and store your analysis results.

