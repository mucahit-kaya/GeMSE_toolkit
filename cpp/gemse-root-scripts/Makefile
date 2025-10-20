###################################################################
# This Makefile was created using the bat-project script.
# bat-project is part of Bayesian Analysis Toolkit (BAT).
# BAT can be downloaded from http://mpp.mpg.de/bat
###################################################################
#
# Run 'make' to compile the program and 'make clean' to remove
# all compiled parts and 'clean' the directory.
#
# You might need to adjust the CXXFLAGS and LIBS based on
# the BAT installation on your system. Consult the gmake manual
# for details.
#
###################################################################

# compiler and flags
CXX          = g++
CXXFLAGS     = -g -O2 -Wall -fPIC -Wno-deprecated 
LD           = /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ld
LDFLAGS      = -g -O2 

# ----------------------------------------------------------------------
# The following definitions rely on the script bat-config being
# available in $PATH. If BAT is not installed in the standard system
# directories, update $PATH accordingly.

CXXFLAGS += `bat-config --cflags`
LIBS := `bat-config --libs`

# List of all classes (models) used in the program
# Add classes to the end. Backslash indicates continuation
# on the next line
CXXSRCS_all      = \
	calibrate_spectrum.cxx energy_calibration.cxx energy_resolution.cxx make_rootfile_list.cxx make_rootfile_spectrum.cxx make_spectrum_list.cxx plot_rate.cxx add_spectra.cxx integral_rate.cxx merge_simulated_efficiencies.cxx merge_simulated_efficiencies_adjustTl208BR.cxx get_times_from_rootfile.cxx get_efficiencies_from_rootfile.cxx make_rootfile_from_compass_rootfile.cxx print_informations_root_tree.cxx energy_calibration_manual.cxx energy_resolution_manual.cxx energy_resolution_prefit.cxx merge_simulated_efficiencies_solid_angle_estimate.cxx

CXXSRCS1      = \
    calibrate_spectrum.cxx 
CXXSRCS2      = \
	energy_calibration.cxx
CXXSRCS3      = \
	energy_resolution.cxx
CXXSRCS4      = \
	make_rootfile_list.cxx
CXXSRCS5      = \
    make_rootfile_spectrum.cxx
CXXSRCS6     = \
	make_spectrum_list.cxx
CXXSRCS7      = \
	plot_rate.cxx
CXXSRCS8      = \
	add_spectra.cxx
CXXSRCS9      = \
	integral_rate.cxx
CXXSRCS10      = \
	merge_simulated_efficiencies.cxx
CXXSRCS11      = \
	get_times_from_rootfile.cxx
CXXSRCS12      = \
	merge_simulated_efficiencies_solid_angle_estimate.cxx
CXXSRCS13      = \
	energy_resolution_prefit.cxx
CXXSRCS14      = \
    get_calibration_function.cxx
CXXSRCS15      = \
	get_efficiencies_from_rootfile.cxx
CXXSRCS16      = \
	make_rootfile_from_compass_rootfile.cxx
CXXSRCS17      = \
    print_informations_root_tree.cxx
CXXSRCS18      = \
    energy_calibration_manual.cxx
CXXSRCS19      = \
    energy_resolution_manual.cxx
CXXSRCS20      = \
	merge_simulated_efficiencies_adjustTl208BR.cxx

# ----------------------------------------------------------------------
# don't change lines below unless you know what you're doing
#
CXXOBJS_all      = $(patsubst %.cxx,%.o,$(CXXSRCS_all))

CXXOBJS1      = $(patsubst %.cxx,%.o,$(CXXSRCS1))
CXXOBJS2      = $(patsubst %.cxx,%.o,$(CXXSRCS2))
CXXOBJS3      = $(patsubst %.cxx,%.o,$(CXXSRCS3))
CXXOBJS4      = $(patsubst %.cxx,%.o,$(CXXSRCS4))
CXXOBJS5      = $(patsubst %.cxx,%.o,$(CXXSRCS5))
CXXOBJS6      = $(patsubst %.cxx,%.o,$(CXXSRCS6))
CXXOBJS7      = $(patsubst %.cxx,%.o,$(CXXSRCS7))
CXXOBJS8      = $(patsubst %.cxx,%.o,$(CXXSRCS8))
CXXOBJS9      = $(patsubst %.cxx,%.o,$(CXXSRCS9))
CXXOBJS10      = $(patsubst %.cxx,%.o,$(CXXSRCS10))
CXXOBJS11      = $(patsubst %.cxx,%.o,$(CXXSRCS11))
CXXOBJS12      = $(patsubst %.cxx,%.o,$(CXXSRCS12))
CXXOBJS13      = $(patsubst %.cxx,%.o,$(CXXSRCS13))
CXXOBJS14      = $(patsubst %.cxx,%.o,$(CXXSRCS14))
CXXOBJS15      = $(patsubst %.cxx,%.o,$(CXXSRCS15))
CXXOBJS16      = $(patsubst %.cxx,%.o,$(CXXSRCS16))
CXXOBJS17      = $(patsubst %.cxx,%.o,$(CXXSRCS17))
CXXOBJS18      = $(patsubst %.cxx,%.o,$(CXXSRCS18))
CXXOBJS19      = $(patsubst %.cxx,%.o,$(CXXSRCS19))
CXXOBJS20      = $(patsubst %.cxx,%.o,$(CXXSRCS20))

MYPROGS_all     = \
	calibrate_spectrum energy_calibration energy_resolution make_rootfile_list make_rootfile_spectrum make_spectrum_list plot_rate add_spectra integral_rate merge_simulated_efficiencies merge_simulated_efficiencies_adjustTl208BR get_times_from_rootfile get_efficiencies_from_rootfile get_calibration_function make_rootfile_from_compass_rootfile print_informations_root_tree energy_calibration_manual energy_resolution_manual energy_resolution_prefit merge_simulated_efficiencies_solid_angle_estimate

MYPROGS1     = \
        calibrate_spectrum
MYPROGS2     = \
	energy_calibration
MYPROGS3     = \
	energy_resolution
MYPROGS4     = \
	make_rootfile_list
MYPROGS5     = \
	make_rootfile_spectrum
MYPROGS6     = \
	make_spectrum_list
MYPROGS7     = \
	plot_rate
MYPROGS9     = \
	add_spectra
MYPROGS9     = \
	integral_rate
MYPROGS10     = \
	merge_simulated_efficiencies
MYPROGS11     = \
	get_times_from_rootfile
MYPROGS12      = \
	merge_simulated_efficiencies_solid_angle_estimate
MYPROGS13      = \
	energy_resolution_prefit
MYPROGS14      = \
	get_calibration_function
MYPROGS15      = \
	get_efficiencies_from_rootfile
MYPROGS16      = \
	make_rootfile_from_compass_rootfile
MYPROGS17      = \
	print_informations_root_tree
MYPROGS18      = \
	energy_calibration_manual
MYPROGS19      = \
    energy_resolution_manual
MYPROGS20     = \
	merge_simulated_efficiencies_adjustTl208BR


GARBAGE = $(CXXOBJS_all) *~ link.d $(MYPROGS_all)

# targets
all : calibrate_spectrum energy_calibration energy_resolution make_rootfile_list make_rootfile_spectrum make_spectrum_list plot_rate add_spectra integral_rate merge_simulated_efficiencies merge_simulated_efficiencies_adjustTl208BR get_times_from_rootfile get_efficiencies_from_rootfile get_calibration_function make_rootfile_from_compass_rootfile print_informations_root_tree energy_calibration_manual energy_resolution_manual energy_resolution_prefit merge_simulated_efficiencies_solid_angle_estimate

link.d : $(patsubst %.cxx,%.h,$(CXXSRCS_all))
	$(CXX) -MM $(CXXFLAGS) $(CXXSRCS_all) > link.d;

-include link.d

%.o : %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	rm -f $(GARBAGE)

calibrate_spectrum : $(CXXOBJS1)
	$(CXX) $(LDFLAGS) $(CXXOBJS1) $(LIBS) -o $@

energy_calibration : $(CXXOBJS2)
	$(CXX) $(LDFLAGS) $(CXXOBJS2) $(LIBS) -o $@

energy_resolution : $(CXXOBJS3)
	$(CXX) $(LDFLAGS) $(CXXOBJS3) $(LIBS) -o $@

make_rootfile_list : $(CXXOBJS4)
	$(CXX) $(LDFLAGS) $(CXXOBJS4) $(LIBS) -o $@

make_rootfile_spectrum : $(CXXOBJS5)
	$(CXX) $(LDFLAGS) $(CXXOBJS5) $(LIBS) -o $@

make_spectrum_list : $(CXXOBJS6)
	$(CXX) $(LDFLAGS) $(CXXOBJS6) $(LIBS) -o $@

plot_rate : $(CXXOBJS7)
	$(CXX) $(LDFLAGS) $(CXXOBJS7) $(LIBS) -o $@

add_spectra : $(CXXOBJS8)
	$(CXX) $(LDFLAGS) $(CXXOBJS8) $(LIBS) -o $@

integral_rate : $(CXXOBJS9)
	$(CXX) $(LDFLAGS) $(CXXOBJS9) $(LIBS) -o $@

merge_simulated_efficiencies : $(CXXOBJS10)
	$(CXX) $(LDFLAGS) $(CXXOBJS10) $(LIBS) -o $@

get_times_from_rootfile : $(CXXOBJS11)
	$(CXX) $(LDFLAGS) $(CXXOBJS11) $(LIBS) -o $@

merge_simulated_efficiencies_solid_angle_estimate : $(CXXOBJS12)
	$(CXX) $(LDFLAGS) $(CXXOBJS12) $(LIBS) -o $@

energy_resolution_prefit : $(CXXOBJS13)
	$(CXX) $(LDFLAGS) $(CXXOBJS13) $(LIBS) -o $@

get_calibration_function : $(CXXOBJS14)
	$(CXX) $(LDFLAGS) $(CXXOBJS14) $(LIBS) -o $@

get_efficiencies_from_rootfile : $(CXXOBJS15)
	$(CXX) $(LDFLAGS) $(CXXOBJS15) $(LIBS) -o $@
	
make_rootfile_from_compass_rootfile : $(CXXOBJS16)
	$(CXX) $(LDFLAGS) $(CXXOBJS16) $(LIBS) -o $@

print_informations_root_tree : $(CXXOBJS17)
	$(CXX) $(LDFLAGS) $(CXXOBJS17) $(LIBS) -o $@

energy_calibration_manual : $(CXXOBJS18)
	$(CXX) $(LDFLAGS) $(CXXOBJS18) $(LIBS) -o $@

energy_resolution_manual : $(CXXOBJS19)
	$(CXX) $(LDFLAGS) $(CXXOBJS19) $(LIBS) -o $@

merge_simulated_efficiencies_adjustTl208BR : $(CXXOBJS20)
	$(CXX) $(LDFLAGS) $(CXXOBJS20) $(LIBS) -o $@

print :
	@echo compiler  : $(CXX)
	@echo c++ srcs  : $(CXXSRCS_all)
	@echo c++ objs  : $(CXXOBJS_all)
	@echo c++ flags : $(CXXFLAGS)
	@echo libs      : $(LIBS)

