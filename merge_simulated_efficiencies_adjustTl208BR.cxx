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
    // chain->Merge(FileName_out+".root"); // dont save this chain, as we want to alter Tl208 BR, see below
    
    //////////////////////
    // Sebastian Sep 2024: At least in my past analyses, I did not account for the reduced 35.94% BR of Tl208 in the Th232/Th228 dacay chain.
    // Tl208 (as most isotopes) is simulated "stand-alone", i.e. not part of any chain. The BRs of the individual gammas is correct, however
    // when combining results from Tl208 and other isotopes in the Th228 chain, the reduced BR of Tl208 has to be taken into account.
    //
    // In order to avoid rerunning all the simulations, let's try to establish a flag 
    // which scales the **two affected** Tl208 lines (583.2 keV and 2614.5 keV) accordingly.
    /////////////////////

    double energy, efficiency, efficiency_err, eff_BR; // initial values from "old" chain
    double eff_BRstar; // modified number for "new" tree
    chain->SetBranchAddress("energy",&energy);
    chain->SetBranchAddress("efficiency",&efficiency);
    chain->SetBranchAddress("efficiency_err",&efficiency_err);
    chain->SetBranchAddress("eff_BR",&eff_BR);

    int nEntries = chain->GetEntries();

    // create copy of merged chain to adjust Tl208 BR (tree is write once, read often):
    TFile* rootFile = new TFile(FileName_out+".root","recreate");
    TTree* tree = new TTree("tree","tree");
    //auto tree = chain->CloneTree(0);
    tree->Branch("energy",&energy); // as above
    tree->Branch("efficiency",&efficiency); // as above
    tree->Branch("efficiency_err",&efficiency_err); // as above
    tree->Branch("eff_BR",&eff_BRstar); // this is the magic!

    for (int i=0; i<nEntries; ++i) {
        chain->GetEntry(i);
        eff_BRstar = eff_BR;
        if ((energy==583.2) or (energy==2614.5)){
            eff_BRstar = eff_BR*0.3594;
        }
        tree->Fill();
        /*
        std::cout<< "#energy:" << energy << std::endl;
        std::cout<< "#efficiency:" << efficiency << std::endl;
        std::cout<< "#eff_err:" << efficiency_err << std::endl;
        std::cout<< "#eff_BR:" << eff_BR << std::endl;
        std::cout<< "#  ->eff_BRstar:" << eff_BRstar << std::endl;
        */
    }
    tree->Print();
    rootFile->Write();

    // plot efficiencies
    TCanvas* c = new TCanvas("c");
    tree->Draw("energy:efficiency:efficiency_err","","goff");
    TGraphErrors * g = new TGraphErrors (tree->GetEntries(),tree->GetV1(),tree->GetV2(),0,tree->GetV3());
    g->Draw("ap");
    gPad->Update();
    g->GetXaxis()->SetTitle("energy [keV]");
    g->GetYaxis()->SetTitle("efficiency [1]");
    c->SaveAs(FileName_out+"_eff.pdf");
    // 
    TCanvas* c2 = new TCanvas("c2");
    tree->Draw("energy:eff_BR:efficiency_err/efficiency*eff_BR","","goff");
    TGraphErrors * g2 = new TGraphErrors (tree->GetEntries(),tree->GetV1(),tree->GetV2(),0,tree->GetV3());
    g2->Draw("ap");
    gPad->Update();
    g2->GetXaxis()->SetTitle("energy [keV]");
    g2->GetYaxis()->SetTitle("eff_BR [1]");
    c2->SaveAs(FileName_out+"_effBR.pdf");

}





