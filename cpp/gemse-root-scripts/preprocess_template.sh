#!/bin/bash

#####################################################################################
## This file should provide you with a preliminary understanding of how to use the
## tools in this repository and in what order. Although it is not exhaustive, it
## will give you an initial idea of what is possible.
##
## Sebastian, 31 May 2023
#####################################################################################

#####################################################################################
## NOTE FOR COMPASS-TYPE RAW DATA (Sebastian 31 May 2023)
##
## In case of the 'new' CoMPASS-generated raw data, that is put in a somewhat more 
## complicated folder hierachy '.../DAQ/run_XY/RAW/DataR_CH0@DT5781A_793_run_XY.root',
## I typically generate a separate folder, e.g. 'linked_files', where I put symlinks 
## 'ln -s <path_to_rawdata.root', that I then point at in the follwing.
#####################################################################################

# path to raw data:
GaFolder='<path_to_raw_data>'

# path to individual files
GaLFile0='<raw_data_file_1> (.txt or .root)'
GaLFile1='<raw_data_file_2> (.txt or .root)'
GaLFile2='<raw_data_file_3> (.txt or .root)'
#

# This last step defines, which files are processed:
GaLFiles=(${GaLFile0} ${GaLFile1} ${GaLFile2})
# OR: GaLFiles=(${GaLFile0} ${GaLFile1} ${GaLFile2} ${GaLFile3} ${GaLFile4} ${GaLFile5})
# OR: GaLFiles=(${GaLFile2})

## TODO: adopt for multiple time cuts
#######################
combine_spectra=1
do_root_stuff=1
do_annotation=0
#######################

TMIN=0 # in seconds
TMAX=0 # in seconds

# absolute path to calibration function (e.g., "<path_to_file>/DataR_CH0@DT5781A_793_run_1.root.root_spectrum_0-506968s.root_calibration_function.root")
GaCal='/home/sebastian/Computing/GeMSE/analysis_input_files/calibration/2023_05_10_meteorite23_0010_cal/manual_fits/DataR_CH0@DT5781A_793_run_1.root.root_spectrum_0-506968s.root_calibration_function.root'
# absolute path to background spectrum (e.g., "<path_to_bg_file>/2019-2020_combined_bkg_calibrated.root.root")
bg_spectrum='/home/sebastian/Computing/GeMSE/analysis_input_files/background/2019-2020_combined_background/2019-2020_combined_bkg_calibrated.root.root'

# absolute path to singuluarty image (e.g., "<path_to_image>/gemse_env.simg")
# find image here: https://github.com/AG-Schumann/GeMSE_environment 
container_image='/home/sebastian/Computing/GeMSE/singularity_containers/gemse_env.simg'

# absolute path to GeMSE_ROOT_scirpts (e.g., "<path>/GeMSE_ROOT_scripts")
pROOT='/home/sebastian/Computing/GeMSE/GeMSE_root_scripts/GeMSE_ROOT_scripts'

# path to python (uproot) script to do annotate generated spectra (e.g., "<path_to_python_script>/annotate_calibrated_histogram_uproot.py")
annotate_script='/home/sebastian/Computing/GeMSE/python_analysis/annotate_calibrated_histogram_uproot.py'

##########################################################################################
################# from here on the magic should happen ###################################
##########################################################################################

cdir=$(pwd)

if [ ${do_root_stuff} -eq 1 ]; then
  for GaLFile in "${GaLFiles[@]}"; do
     echo "... $GaLFile ..."
     if [ "${GaLFile##*.}" = "txt" ]
     then
       singularity exec ${container_image} ${pROOT}/make_rootfile_list ${GaFolder}/${GaLFile} ${GaCal}
     elif [ "${GaLFile##*.}" = "root" ]
     then
       echo "... processing .root file: $GaLFile ..."
       singularity exec ${container_image} ${pROOT}/make_rootfile_from_compass_rootfile ${GaFolder}/${GaLFile} ${GaCal}
     else
       echo "   ERROR file extension is neither .txt nor .root! BREAK."
       exit 1
     fi
     singularity exec ${container_image} ${pROOT}/plot_rate --file ${GaFolder}/${GaLFile}.root --energy
     singularity exec ${container_image} ${pROOT}/plot_rate --file ${GaFolder}/${GaLFile}.root --energy --range_min 340 --range_max 360 # (for Ra226 line)
     singularity exec ${container_image} ${pROOT}/plot_rate --file ${GaFolder}/${GaLFile}.root --energy --range_min 600 --range_max 620 # (for Ra226 line)
  
     singularity exec ${container_image} ${pROOT}/make_spectrum_list --file ${GaFolder}/${GaLFile}.root --t_min $TMIN --t_max $TMAX  # uncalibrated spectrum
     singularity exec ${container_image} ${pROOT}/make_spectrum_list --file ${GaFolder}/${GaLFile}.root --energy --t_min $TMIN --t_max $TMAX # calibrated spectrum

     if [ ${do_annotation} -eq 1 ]; then
       calibrated_spectrum=$(ls -rt ${GaFolder}/*spectrum_calibrated*.root | tail -n 1)
       singularity exec ${container_image} python ${annotate_script} --ifile=${calibrated_spectrum} --ofile=${GaFolder}/${GaLFile}_annotated_spectrum.pdf
     fi
  done
  echo "Loop done."
else
    echo "Skipping the following ROOT stuff (make_rootfile_list, plot_rate, make_spectrum_list)."
fi

calibrated_spectrum=$(ls -rt ${GaFolder}/*spectrum_calibrated*.root | tail -n 1)
echo ${calibrated_spectrum}

if [ ${combine_spectra} -eq 1 ]; then
    GaLcomb='combined_spectra'
    _calspecs=(${GaFolder}/*spectrum_calibrated*.root)
    calspecstring=""
    # we want to make sure that only the selected files (GaLFiles) are merged. Not all files that, e.g. in a previous step, were processed 
    for _cs in "${_calspecs[@]}"; do
        # Iterate over each string in the string_to_check array
        for _run in "${GaLFiles[@]}"; do
            # Check if the _run is present in *spectrum_calibrated*.root files
            if [[ "$_cs" == *"$_run"* ]]; then
                calspecstring+=" $_cs"
                break  # Break the inner loop if a match is found
            fi
        done
    done

    #echo "I will now merge the following files containing spectra: "
    #echo ${calspecstring}

    singularity exec ${container_image} ${pROOT}/add_spectra ${calspecstring} ${GaFolder}/${GaLcomb}
    if [ ${do_annotation} -eq 1 ]; then
      singularity exec ${container_image} python /home/sebastian/Computing/GeMSE/python_analysis/annotate_calibrated_histogram_uproot.py --ifile=${GaFolder}/${GaLcomb}.root --ofile=${GaFolder}/${GaLcomb}_annotated_spectrum.pdf
    fi
else
    echo "No combination of data."

fi

cd $cdir
