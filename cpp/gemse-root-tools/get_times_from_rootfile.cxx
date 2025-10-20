#include "macros.h"

// ----------------------------------------------------
// (11 Oct 2022) Get Times (durations) from ROOT files
// ----------------------------------------------------

int main(int argc, char *argv[]) {
    
    // argc should be 2 for correct execution
    if ( argc != 2 ) {
        
        // We print argv[0] assuming it is the program name
        std::cout<<"usage: "<< argv[0] <<" <spectrum_file.root>"<< std::endl;
        return 1;
    }
    
    TString FileName = argv[1];

    double t_real;
    double t_live;
    
    // read parameters from file
    t_real = getreal(FileName);
    t_live = getlive(FileName);

    if (t_real != 0) {
	 std::cout<< "# t_real in s" << std::endl;
	 std::cout<< t_real << std::endl;
         // return t_real; 
    }
    
    if (t_live != 0) {
	 std::cout<< "# t_live in s" << std::endl;
         std::cout<< t_live << std::endl;
        // return t_live;
    }

    return 0;
}
