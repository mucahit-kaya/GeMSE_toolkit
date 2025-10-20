// #include "HPGe_Fit.h"
#include "macros.h"

// ----------------------------------------------------
// (14 Oct 2022) Get simulated efficiencies from ROOT files
// ----------------------------------------------------

int main(int argc, char *argv[]) {
    
    // argc should be 2 for correct execution
    if ( argc != 2 ) {
        
        // We print argv[0] assuming it is the program name
        std::cout<<"usage: "<< argv[0] <<" <spectrum_file.root>"<< std::endl;
        return 1;
    }
    
    TString fefficiency_name = argv[1];
    
    TFile* File = TFile::Open(fefficiency_name);
    
    if (!File) {
        std::cout << "##### ERROR: could not open " << fefficiency_name << std::endl;
        return 1;
    }
    
    std::cout << "#### Reading " << fefficiency_name << " ..." << std::endl;
    
    if (!File->GetListOfKeys()->Contains("tree")) {
        std::cout << "##### ERROR: no tree in file " << fefficiency_name << std::endl;
        return 1;
    }
    
    TTree* tree = (TTree*) File->Get("tree");
    
    double energy, efficiency, efficiency_err, eff_BR;
    
    tree->SetBranchAddress("energy",&energy);
    tree->SetBranchAddress("efficiency",&efficiency);
    tree->SetBranchAddress("efficiency_err",&efficiency_err);
    tree->SetBranchAddress("eff_BR",&eff_BR);
    
    int nEntries = tree->GetEntries();

    for (int i=0; i<nEntries; ++i) {
    	
        int Entry = tree->GetEntry(i);
        std::cout<< "#energy:" << energy << std::endl;
        std::cout<< "#efficiency:" << efficiency << std::endl;
        std::cout<< "#eff_err:" << efficiency_err << std::endl;
        std::cout<< "#eff_BR:" << eff_BR << std::endl;
    }
//    if (nEntries != 0) {
	 // std::cout<< "# t_real in s" << std::endl;
//	 std::cout<< nEntries << std::endl;
         // return t_real; 
//    }

    return 0;
}
