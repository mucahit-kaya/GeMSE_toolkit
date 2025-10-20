make_rootfile_spectrum
======
Converts an ASCII spectrum of CAEN DT5781A to a ROOT file. First line in ASCII file must be real time, second line live time
## Usage
```
./make_rootfile_spectrum <spectrum_file.txt>
```
## Output
* spectrum_file.txt.root 
    * TH1D "hist": spectrum
    * TVectorD "t_live": live time
    * TVectorD "t_real": real time


energy_calibration
======
Fits the peaks in a spectrum with a Gauss+Pol1. The peak position vs. energy is then fitted with a Pol2 to get the energy calibration. 

Requires a **parameters txt file** (see „example_parameters_calibration.txt“) with the following content:
* spectrum file name: name of spectrum **ROOT** file

For every peak
* fitrange low (ADC channels): lower limit of fit range
* fitrange high (ADC channels): upper limit of fit range
* counts: start parameter for number of counts in peak
* mean (ADC channels): start parameter for peak position 
* sigma (ADC channels): start parameter for peak standard deviation
* constant : start parameter for constant
* slope: start parameter for slope
* energy (keV): literature value of peak energy

## Usage
```
./energy_calibration <parameters_calibration.txt>
```
## Output	
* spectrum_file.txt.root_calibration_fits.root
    * TCanvas "c1"
        * TH1D "hist": original (uncalibrated) spectrum 
        * TF1 "fitFunction": fit for every peak
* spectrum_file.txt.root_calibration_function.root
    * TCanvas "c2" 
        * TGraphErrors "Graph": peak position vs energy 
        * TF1 "fitFunction": Pol2 fit to "Graph"


calibrate_spectrum
======
calibrates a **spectrum txt file** with a calibration function
## Usage
```
./calibrate_spectrum <spectrum_file.txt> <calibration_function.root>
```
## Output
* spectrum_file.txt_calibrated.root
    * TH1D "hist": calibrated spectrum 
    * TVectorD "t_live": live time 
    * TVectorD "t_real": real time


energy_resolution
======
Fits the peaks in a **calibrated** spectrum with Gauss+Pol1. The peaks' standard deviation vs energy is then fitted with a function sqrt(p0+p1*x+p2*x^2) to get the energy resolution as function of energy.

Requires a **parameters txt file** (see „example_parameters_resolution.txt“) with the following content:
* spectrum file name: name of spectrum **ROOT** file

For every peak
* fitrange low (keV): lower limit of fit range
* fitrange high (keV): upper limit of fit range
* counts: start parameter for number of counts in peak
* mean (keV): start parameter for peak position 
* sigma (keV): start parameter for peak standard deviation
* constant : start parameter for constant
* slope: start parameter for slope

## Usage
```
./energy_resolution <parameters_resolution.txt>
```
## Output	
* spectrum_file.txt.root_resolution_fits.root
    * TCanvas "c1"
        * TH1D "hist": calibrated spectrum 
        * TF1 "fitFunction": fit for every peak
* spectrum_file.txt.root_resolution_function.root
    * TCanvas "c2" 
        * TGraphErrors "Graph": resolution vs energy 
        * TF1 "fitFunction": fit to "Graph" with sqrt(p0+p1*x+p2*x^2)


make_rootfile_list
======
Converts a list file (ASCII format) of CAEN DT5781A into a ROOT file
## Usage
```
./make_rootfile_list <list_file.dat> <calibration_function.root>
```
the second argument is optional
## Output
* list_file.dat.root
    * TTree "dataTree"
        * TBranch "energy": energy in keV (only if calibration function was specified)
        * TBranch "pulseheight": pulseheight in ADC channels
        * TBranch "extras": extra information about pileup, deadtime or saturation
        * TBranch "time": timestamp in 10ns units

make_spectrum_list
======
Produces a spectrum from a list file  
## Usage
```
./make_spectrum_list <arguments> 
```
arguments:

```--file <list_file.root>``` specifies the list filename

```--energy``` use the energy calibration

```--t_min <t0> --t_max <t1>``` select time range [t0,t1]

## Output
* list_file.dat.root_(calibrated)_time_t0-t1.root
    * TH1D "hist": (calibrated) spectrum
    * TVectorD "t_live": live time 
    * TVectorD "t_real": real time

plot_rate
======
Produces a rate vs. time plot from list file
## Usage
```
./plot_rate <arguments> 
```
arguments:

``` --file <list_file.root>``` specifies the list filename

```--energy``` use the energy calibration

```--range_min <r0> --range_max <r1>``` select pulseheight/energy range [r0,r1]

```--binwidth <binwidth>``` specify bin width (s)

## Output
* list_file.dat.root_rate_energy/pulseheight_r0-r1.root
    * TH1D "hist": rate vs. time histogram

add_spectra
======
Adds up two or more spectra 
## Usage
```
./add_spectra <spectrum1.root> <spectrum2.root> ... <results_filename> 
```

## Output
* results_filename.root
    * TH1D "hist": sum of spectrum1, spectrum2, ...
    * TVectorD "t_live": summed up live time 
    * TVectorD "t_real": summed up real time

integral_rate
======
Calculates the integral rate in a certain energy range 
## Usage
```
./integral_rate <spectrum.root> <E_min> <E_max> 
```

## Output
* spectrum_integral_rate_E_min-E_max.pdf

merge_simulated_efficiencies
======
merges the results of several simulated efficiencies into a single file 
## Usage
```
./merge_simulated_efficiencies <simulated_efficiencies1.root> <simulated_efficiencies2.root> ... <simulated_efficiencies_merged> 
```

## Output
* simulated_efficiencies_merged.pdf
* simulated_efficiencies_merged.root

macros.h
======
contains all macros which are used by the other scripts
