#include "macros.h"

// ----------------------------------------------------
// (26 Apr 2023) Print informations stored in ROOT Tree
// ----------------------------------------------------

int main(int argc, char *argv[]) {
    
    // argc should be 2 for correct execution
    if ( argc != 2 ) {
        
        // We print argv[0] assuming it is the program name
        std::cout<<"usage: "<< argv[0] <<" <XYZ.txt.root>"<< std::endl;
        return 1;
    }

    std::cout<<"Now trying to read: "<< argv[1] << std::endl;
    
    TString FileName = argv[1];

    int res = print_info_root_file(FileName=FileName);

    return res;
}
