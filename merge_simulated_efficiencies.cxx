#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TH1F.h>

#include <iostream>

// --------------------------------
// main program
// --------------------------------

int main(int argc, char *argv[]) {
    
    // argc should be > 3 for correct execution
    if ( argc < 3 ) {
        
        // We print argv[0] assuming it is the program name
        std::cout<<"usage: "<< argv[0] <<" <simulated_efficiencies1.root> <simulated_efficiencies2.root> ... <simulated_efficiencies_merged>" << std::endl;
        return 1;
    }
    
    // name of output file
    TString FileName_out = argv[argc-1];
    
    // create TChain for all trees
    TChain* chain = new TChain("tree");
   
    // loop over all files
    for (int i=0; i<argc-2; ++i) {
        
        TString FileName = argv[i+1];
        chain->Add(FileName);
    
    }
    
    // merge chain into single file
    chain->Merge(FileName_out+".root");

    // plot efficiencies
    // TCanvas* c = new TCanvas("c");
    // chain->Draw("efficiency:energy","","*");
    // 
    //chain->Draw("energy:efficiency:efficiency_err","","goff");
    //TGraphErrors * g = new TGraphErrors (chain->GetEntries(),chain->GetV1(),chain->GetV2(),0,chain->GetV3());
    //g->Draw("ap");
    //c->SaveAs(FileName_out+".pdf");
    

    // more fun plots (Seb Okt 14, 2024)
    //    
    // plot efficiencies
    TCanvas* c = new TCanvas("c");
    chain->Draw("energy:efficiency:efficiency_err","","goff");
    TGraphErrors * g = new TGraphErrors (chain->GetEntries(),chain->GetV1(),chain->GetV2(),0,chain->GetV3());
    g->Draw("ap");
    gPad->Update();
    g->GetXaxis()->SetTitle("energy [keV]");
    g->GetYaxis()->SetTitle("efficiency [1]");
    c->SaveAs(FileName_out+"_eff.pdf");
    //
    TCanvas* c2 = new TCanvas("c2");
    chain->Draw("energy:eff_BR:efficiency_err/efficiency*eff_BR","","goff");
    TGraphErrors * g2 = new TGraphErrors (chain->GetEntries(),chain->GetV1(),chain->GetV2(),0,chain->GetV3());
    g2->Draw("ap");
    gPad->Update();
    g2->GetXaxis()->SetTitle("energy [keV]");
    g2->GetYaxis()->SetTitle("eff_BR [1]");
    c2->SaveAs(FileName_out+"_effBR.pdf");


}





