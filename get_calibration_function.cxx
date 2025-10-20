// #include "HPGe_Fit.h"
#include "macros.h"

// ----------------------------------------------------
// (13 Feb 2023) Get calibration function from ROOT
// ----------------------------------------------------

int main(int argc, char *argv[]) {

    // argc should be 2 for correct execution
    if ( argc != 2 ) {

        // We print argv[0] assuming it is the program name
        std::cout<<"usage: "<< argv[0] <<" <calibration_function.root>"<< std::endl;
        return 1;
    }


    TString fn_calfile = argv[1];

    TFile* File = TFile::Open(fn_calfile);
    
    if (!File) {
        
        std::cout << "###### ERROR: could not open " << fn_calfile << std::endl;
        return 0;
    }
    TCanvas* c = (TCanvas*) File->Get("c2");
    TGraphErrors* graph = (TGraphErrors*) c->GetPrimitive("Graph");
    TF1* fit = (TF1*) graph->GetFunction("fitFunction");
    
    TString exf1 = fit->GetExpFormula();
    //TString* exf2 = fit->GetExpFormula(Option_t option="P");
    TString exf2 = fit->GetExpFormula("P");
   
    std::cout<< "#formula: " << exf1 << std::endl;
    std::cout<< "#formulaP:" << exf2 << std::endl;

    File->Close();
    
    return 0;
    
}
