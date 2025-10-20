#include <TH1D.h>
#include <TF1.h>
#include <TTree.h>
#include <TString.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TVectorD.h>
#include <TPaveStats.h>
#include <TMinuit.h>
#include <TVectorD.h>
#include <TLatex.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>     /* atof */


// ----------------------------------------------------
// erase comma from number
// ----------------------------------------------------
double getNumber(std::string a) {
    
    for(int i=0; i<=a.size(); i++) {  //Loop through the entire string
        if(a[i]==',') { //Check for occurence of comma
            a.erase(i,1); //If comma , remove that single character
        }
    }
    
    return atof(a.c_str()); //Will return double

}

// ----------------------------------------------------
// make 'normal' ROOT file from CoMPASS ROOT tree (incl. optional calibration)
// ----------------------------------------------------
// int convert_compass_tree(TString FileName, TF1* calibration=0) {
//     
//     // open CoMPASS ROOT file
//     TFile* File = TFile::Open(FileName);
//  
//     if (!File) {
//         std::cout << "###### ERROR: could not open " << FileName << std::endl;
//         return 0;
//     }
//     
//     double t_live, t_real;
//     // std::string t_live_string, t_real_string;
//     
//     const int Nchannels=16382;
//     double channel[Nchannels+1];
//     int counts[Nchannels];
//     
//     // read real and live time
//     //File >> t_real_string >> t_live_string;
//     
//     // remove commas and convert to double
//     //t_real = getNumber(t_real_string);
//     //t_live = getNumber(t_live_string);
//     //
//     // TODO: read t_real and t_live from CoMPASS:    
//     
//     // read counts for every channel
//     for (int i=0; i<Nchannels; i++) {
//         File >> counts[i];
//         
//         // apply energy calibration
//         if (calibration!=0) {
//             channel[i]=calibration->Eval(i+0.5);
//         }
//         else {
//             channel[i]=i+0.5;
//         }
//     }
//     if (calibration!=0) {
//         channel[Nchannels]=calibration->Eval(Nchannels+0.5);
//     }
//     else {
//         channel[Nchannels]=Nchannels+0.5;
//     }
// 
//     
//     File.close();
//     
//     // create root file
//     if (calibration!=0) {
//         FileName += "_calibrated";
//     }
//     
//     TFile* histFile = TFile::Open(FileName+".root","RECREATE");
//     
//     // make histogram
//     TH1D* hist = new TH1D("hist",";ADC Channel;Counts",Nchannels,channel);
//     
//     if (calibration!=0) {
//         hist->GetXaxis()->SetTitle("Energy (keV)");
//     }
//     
//     for (int i=0; i<Nchannels; i++) {
//         
//         hist->SetBinContent(i+1,counts[i]);
//         
//     }
//     
//     // draw histogram
//     TCanvas* c1 = new TCanvas("c1");
//     gStyle->SetOptStat(0);
//     c1->SetLogy();
//     hist->Draw();
//     c1->SaveAs(FileName+".pdf");
//     
//     
//     // save histogram to root file
//     hist->Write();
//     TVectorD v_live(1);
//     TVectorD v_real(1);
//     v_live[0] = t_live;
//     v_real[0] = t_real;
//     v_live.Write("t_live");
//     v_real.Write("t_real");
//     
//     histFile->Close();
//     
//     return 0;
//     
//     
// }

// ----------------------------------------------------
// make root file from ascii spectrum
// ----------------------------------------------------
int make_spectrum(TString FileName, TF1* calibration=0) {
    
    // open ascii file
    std::ifstream File;
    
    File.open(FileName);
    
    if (!File.is_open()) {
        std::cout << "##### ERROR: could not open " << FileName << std::endl;
        return 1;
    }
    
    double t_live, t_real;
    std::string t_live_string, t_real_string;
    
    const int Nchannels=16382;
    double channel[Nchannels+1];
    int counts[Nchannels];
    
    // read real and live time
    File >> t_real_string >> t_live_string;
    
    // remove commas and convert to double
    t_real = getNumber(t_real_string);
    t_live = getNumber(t_live_string);
    
    
    // read counts for every channel
    for (int i=0; i<Nchannels; i++) {
        File >> counts[i];
        
        // apply energy calibration
        if (calibration!=0) {
            channel[i]=calibration->Eval(i+0.5);
        }
        else {
            channel[i]=i+0.5;
        }
    }
    if (calibration!=0) {
        channel[Nchannels]=calibration->Eval(Nchannels+0.5);
    }
    else {
        channel[Nchannels]=Nchannels+0.5;
    }

    
    File.close();
    
    // create root file
    if (calibration!=0) {
        FileName += "_calibrated";
    }
    
    TFile* histFile = TFile::Open(FileName+".root","RECREATE");
    
    // make histogram
    TH1D* hist = new TH1D("hist",";ADC Channel;Counts",Nchannels,channel);
    
    if (calibration!=0) {
        hist->GetXaxis()->SetTitle("Energy (keV)");
    }
    
    for (int i=0; i<Nchannels; i++) {
        
        hist->SetBinContent(i+1,counts[i]);
        
    }
    
    // draw histogram
    TCanvas* c1 = new TCanvas("c1");
    gStyle->SetOptStat(0);
    c1->SetLogy();
    hist->Draw();
    c1->SaveAs(FileName+".pdf");
    
    
    // save histogram to root file
    hist->Write();
    TVectorD v_live(1);
    TVectorD v_real(1);
    v_live[0] = t_live;
    v_real[0] = t_real;
    v_live.Write("t_live");
    v_real.Write("t_real");
    
    histFile->Close();
    
    return 0;
    
    
}

// ----------------------------------------------------
// get spectrum from root file
// ----------------------------------------------------
TH1D* getspectrum(TString FileName) {
    
    // check for root file
    TFile* File = TFile::Open(FileName);
    
    if (!File) {
        
        std::cout << "###### ERROR: could not open " << FileName << std::endl;
        return 0;
    }
    
    if (!File->GetListOfKeys()->Contains("hist")) {
        std::cout << "###### ERROR: no histogram in file " << FileName << std::endl;
        return 0;
    }

    
    TH1D* hist = (TH1D*) File->Get("hist");
    hist->SetDirectory(0);
    File->Close();
    
    return hist;
    
}


// ----------------------------------------------------
// get real time from root file
// ----------------------------------------------------
double getreal(TString FileName) {
    
    // check for root file
    TFile* File = TFile::Open(FileName);
    
    if (!File) {
        
        std::cout << "###### ERROR: could not open " << FileName << std::endl;
        return 0;
    }
    
    if (!File->GetListOfKeys()->Contains("t_real")) {
        std::cout << "###### ERROR: no real time in file " << FileName << std::endl;
        return 0;
    }

    
    TVectorD* v_real = (TVectorD*) File->Get("t_real");
    double t_real = ((*v_real)[0]);
    
    File->Close();
    
    return t_real;
    
}

// ----------------------------------------------------
// get real time from CoMPASS ROOT tree
// ----------------------------------------------------
double getrealCompass(TString FileName) {
    
    // check for root file
    TFile* File = TFile::Open(FileName);
    
    if (!File) {
        
        std::cout << "###### ERROR: could not open " << FileName << std::endl;
        return 0;
    }
    
//    if (!File->GetListOfKeys()->Contains("t_real")) {
//        std::cout << "###### ERROR: no real time in file " << FileName << std::endl;
//        return 0;
//    }
//
//    Does CoMPASS store this information separately somewhere? Maybe in HCompassR ...RealTime_0?
//    Alternatively, take difference between first and last timestamp? (biased; especially for low rates)

    
    TVectorD* v_real = (TVectorD*) File->Get("t_real");
    double t_real = ((*v_real)[0]);
    
    File->Close();
    
    return t_real;
    
}

// ----------------------------------------------------
// get live time from root file
// ----------------------------------------------------
double getlive(TString FileName) {
    
    // check for root file
    TFile* File = TFile::Open(FileName);
    
    if (!File) {
        
        std::cout << "###### ERROR: could not open " << FileName << std::endl;
        return 0;
    }
    
    if (!File->GetListOfKeys()->Contains("t_live")) {
        std::cout << "###### ERROR: no live time in file " << FileName << std::endl;
        return 0;
    }
    
    TVectorD* v_live = (TVectorD*) File->Get("t_live");
    double t_live = ((*v_live)[0]);
    
    File->Close();
    
    return t_live;
    
}


// ----------------------------------------------------
// add up spectra and measurement times
// ----------------------------------------------------
int addspectra(std::vector<TString> FileNames, TString results_filename) {
    
    std::cout << "opening spectrum " << FileNames[0] << " ..." << std::endl;

    TH1D* hist = getspectrum(FileNames[0]);
    double t_real=getreal(FileNames[0]);
    double t_live=getlive(FileNames[0]);
    
    int Nfiles = FileNames.size();
    
    for (int i=1; i<Nfiles; ++i) {
        
        if(getspectrum(FileNames[i])==0) {return 1;}
        else {
            std::cout << "adding spectrum " << FileNames[i] << " ..." << std::endl;
            hist->Add(getspectrum(FileNames[i]));
            t_live+=getlive(FileNames[i]);
            t_real+=getreal(FileNames[i]);
        }
    }
    
    
    // draw spectrum
    TCanvas* c1 = new TCanvas("c1");
    gStyle->SetOptStat(0);
    c1->SetLogy();
    
    hist->Draw();
    
    c1->SaveAs(results_filename+".pdf");
    
    // write to file
    TFile* histFile = new TFile(results_filename+".root","recreate");
    hist->Write();
    TVectorD v_real(1);
    TVectorD v_live(1);
    v_real[0] = t_real;
    v_live[0] = t_live;
    v_real.Write("t_real");
    v_live.Write("t_live");
    histFile->Close();
    
    return 0;

    
}

// ----------------------------------------------------
// calculate integral rate
// ----------------------------------------------------

int integralrate(TString filename, double E_min, double E_max) {
    
    TH1D* hist = getspectrum(filename);
    double t_live = getlive(filename);
    
    if(hist==0||t_live==0) {
        return 0;
    }
    
    
    double counts = hist->Integral(hist->FindBin(E_min),hist->FindBin(E_max));
    double rate = counts/t_live*3600.*24.;
    double rate_err =  sqrt(counts)/t_live*3600.*24.;
    
    std::cout << "integral rate: " << rate << " +- " << rate_err << " cts/day" << std::endl;
    
    // draw histogram
    TCanvas* c1 = new TCanvas("c1");
    gStyle->SetOptStat(0);
    c1->SetLogy();
    hist->Draw();
    
    TString textToPlot;
    textToPlot = TString::Format("#scale[0.7]{#splitline{integral rate (%1.0f - %1.0f keV):}{%1.1f #pm %1.1f cts/day}}",E_min,E_max,rate,rate_err);
    
    TLatex* t = new TLatex(0.55,0.8,textToPlot);
    t->SetNDC();
    
    t->Draw();
    
    TString resultsname;
    resultsname = TString::Format(filename+"_integral_rate_%1.0f-%1.0fkeV.pdf",E_min,E_max);
    
    c1->SaveAs(resultsname);
    
    return 1;
}


// ----------------------------------------------------
// get calibration function from root file
// ----------------------------------------------------
TF1* getcalibration(TString FileName) {
    
    // check for root file
    TFile* File = TFile::Open(FileName);
    
    if (!File) {
        
        std::cout << "###### ERROR: could not open " << FileName << std::endl;
        return 0;
    }
    TCanvas* c = (TCanvas*) File->Get("c2");
    TGraphErrors* graph = (TGraphErrors*) c->GetPrimitive("Graph");
    TF1* fit = (TF1*) graph->GetFunction("fitFunction");
    
    File->Close();
    
    return fit;
    
}

// ----------------------------------------------------
// fit peak only
// ----------------------------------------------------
TF1* FitGauss(TH1D* hist, double amp_st, double mean_st, double sigma_st, double range_min, double range_max) {
    
    TObject* func = gROOT->FindObject("fitFunction");
    
    if (func) {
        std::cout << "#### 'fitFunction' already defined, deleting ..." << std::endl;
        delete func;
    }
    //TF1* fitFunction = new TF1("fitFunction", "[0]/([2]*sqrt(2*3.14159265))*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))");
    //fitFunction->SetParName(0,"amplitude");
    //fitFunction->SetParName(1,"mean");
    //fitFunction->SetParName(2,"sigma");
    
    TF1* fitFunction = new TF1("fitFunction", "gaus");
    
    fitFunction->SetRange(range_min,range_max);
    
    fitFunction->SetParameter(0,amp_st);
    fitFunction->SetParameter(1,mean_st);
    fitFunction->SetParameter(2,sigma_st);
    
    //fitFunction->SetParLimits(0,0.,1000.*amp_st);
    //fitFunction->SetParLimits(1,range_min,range_max);
    //fitFunction->SetParLimits(2,0.,1000.*sigma_st);
    
    // fit signal
    hist->Fit(fitFunction,"0RMEL");
    
    fitFunction = hist->GetFunction("fitFunction"); 
    fitFunction->SetLineColor(1);
    fitFunction->SetLineStyle(2);
    fitFunction->DrawCopy("LSAME");
    
    TString status=gMinuit->fCstatu.Data();
    
    if (status!="SUCCESSFUL") {
        std::cout << "###### ERROR: Fit not successful! Try different start parameters!" << std::endl;
        return 0;
    }
    
    
    return fitFunction;
    
}

// ----------------------------------------------------
// fit peak + background
// ----------------------------------------------------
TF1* FitGaussPol1(TH1D* hist, double amp_st, double mean_st, double sigma_st, double const_st, double slope_st, double range_min, double range_max) {
    
    TObject* func = gROOT->FindObject("fitFunction");
    
    if (func) {
        std::cout << "#### 'fitFunction' already defined, deleting ..." << std::endl;
        delete func;
    }
    //TF1* fitFunction = new TF1("fitFunction", "[0]/([2]*sqrt(2*3.14159265))*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))+pol1(3)");
    TF1* fitFunction = new TF1("fitFunction", "gaus+pol1(3)");

    
    fitFunction->SetParName(0,"amplitude");
    fitFunction->SetParName(1,"mean");
    fitFunction->SetParName(2,"sigma");
    fitFunction->SetParName(3,"constant");
    fitFunction->SetParName(4,"slope");
    
    fitFunction->SetRange(range_min,range_max);
    
    fitFunction->SetParameter(0,amp_st);
    fitFunction->SetParameter(1,mean_st);
    fitFunction->SetParameter(2,sigma_st);
    fitFunction->SetParameter(3,const_st);
    fitFunction->SetParameter(4,slope_st);
    
    //fitFunction->SetParLimits(0,0.,1000.*amp_st);
    //fitFunction->SetParLimits(1,range_min,range_max);
    //fitFunction->SetParLimits(2,0.,1000.*sigma_st);
    //fitFunction->SetParLimits(3,0.,0.5*amp_st);
    
    // fit signal
    hist->Fit(fitFunction,"0RMEL");
    //hist->Fit(fitFunction,"0REL");
    //hist->Fit(fitFunction);
    
    fitFunction->DrawCopy("LSAME");
    
    TString status=gMinuit->fCstatu.Data();
    
    if (((status!="SUCCESSFUL")&&(status!="CONVERGED"))&&(status!="PROBLEMS  ")) {
        std::cout << "###### ERROR: Fit not successful! Try different start parameters!" << std::endl;
        std::cout << "       **** Fit status: --" << status <<"--"<< std::endl;
        return 0;
    }
    
    return fitFunction;

}

// ----------------------------------------------------
// fit 2 peaks + background
// ----------------------------------------------------
TF1* Fit2Peak(TH1D* hist, double amp1_st, double mean1_st, double sigma1_st, double amp2_st, double mean2_st, double sigma2_st, double const_st, double slope_st, double range_min, double range_max) {
    
    TObject* func = gROOT->FindObject("fitFunction");
    
    if (func) {
        std::cout << "#### 'fitFunction' already defined, deleting ..." << std::endl;
        delete func;
    }

    
    TF1* fitFunction = new TF1("fitFunction", "[0]/([2]*sqrt(2*3.14159265))*exp(-(x-[1])*(x-[1])/(2*[2]*[2]))+[3]/([5]*sqrt(2*3.14159265))*exp(-(x-[4])*(x-[4])/(2*[5]*[5]))+pol1(6)");
    
    fitFunction->SetParName(0,"amplitude1");
    fitFunction->SetParName(1,"mean1");
    fitFunction->SetParName(2,"sigma1");
    fitFunction->SetParName(3,"amplitude2");
    fitFunction->SetParName(4,"mean2");
    fitFunction->SetParName(5,"sigma2");
    fitFunction->SetParName(6,"constant");
    fitFunction->SetParName(7,"slope");
    
    fitFunction->SetRange(range_min,range_max);
    
    fitFunction->SetParameter(0,amp1_st);
    fitFunction->SetParameter(1,mean1_st);
    fitFunction->SetParameter(2,sigma1_st);
    fitFunction->SetParameter(3,amp2_st);
    fitFunction->SetParameter(4,mean2_st);
    fitFunction->SetParameter(5,sigma2_st);
    fitFunction->SetParameter(6,const_st);
    fitFunction->SetParameter(7,slope_st);
    
    // fitFunction->SetParLimits(0,0.,1000.);
    
    // fit signal
    hist->Fit(fitFunction,"0RMWL");
    
    fitFunction->DrawCopy("LSAME");
    
    TString status=gMinuit->fCstatu.Data();
    
    if (status!="SUCCESSFUL") {
        std::cout << "###### ERROR: Fit not successful! Try different start parameters!" << std::endl;
        return 0;
    }
    
    return fitFunction;
    
}

// ----------------------------------------------------
// fit background only
// ----------------------------------------------------
TF1* FitPol1(TH1D* hist, double a_st, double b_st, double range_min, double range_max) {
    
    TF1* fitFunction = new TF1("fitFunction", "pol1");
    
    fitFunction->SetParameter(0,a_st);
    fitFunction->SetParameter(1,b_st);
    
    fitFunction->SetRange(range_min,range_max);
    
    // fit graph
    hist->Fit(fitFunction,"0REMF");
    
    gStyle->SetOptFit(1);
    
    fitFunction->DrawCopy("LSAME");
    
    TString status=gMinuit->fCstatu.Data();
    
    if (status!="SUCCESSFUL") {
        std::cout << "###### ERROR: Fit not successful! Try different start parameters!" << std::endl;
        return 0;
    }
    
    return fitFunction;
}

// ----------------------------------------------------
// fit energy calibration
// ----------------------------------------------------
TF1* FitPol2(TGraphErrors* graph, double a_st, double b_st, double c_st) {

    TF1* fitFunction = new TF1("fitFunction", "pol2");
    
    fitFunction->SetParameter(0,a_st);
    fitFunction->SetParameter(1,b_st);
    fitFunction->SetParameter(2,c_st);

    // fit graph
    graph->Fit(fitFunction,"EMF");
    
    gStyle->SetOptFit(1);
    
    TString status=gMinuit->fCstatu.Data();
    
    if (status!="SUCCESSFUL") {
        std::cout << "###### ERROR: Fit not successful! Try different start parameters!" << std::endl;
        return 0;
    }
    
    return fitFunction;
}

// ----------------------------------------------------
// fit resolution
// ----------------------------------------------------
TF1* FitSqrt(TGraphErrors* graph, double a_st, double b_st, double c_st) {
    
    TF1* fitFunction = new TF1("fitFunction", "sqrt([0]+[1]*x+[2]*x*x)");
    
    //TF1* fitFunction = new TF1("fitFunction", "sqrt([0]+[1]*x)");

    fitFunction->SetParameter(0,a_st);
    fitFunction->SetParameter(1,b_st);
    fitFunction->SetParameter(2,c_st);
    
    // fit graph
    graph->Fit(fitFunction,"EMF");
    
    gStyle->SetOptFit(1);
    
    TString status=gMinuit->fCstatu.Data();
    
    if (status!="SUCCESSFUL") {
        std::cout << "###### ERROR: Fit not successful! Try different start parameters!" << std::endl;
        return 0;
    }
    
    return fitFunction;
}

// ----------------------------------------------------
// make classic root file from CoMPASS root file
// ----------------------------------------------------
int convert_compass_rootfile(TString FileName, TF1* calibration=0) {
    // open CoMPASS ROOT file
    TFile* CompassFile = TFile::Open(FileName);
 
    if (!CompassFile) {
        std::cout << "###### ERROR: could not open " << FileName << std::endl;
        return 0;
    }

    // open compass tree:
    TTree *compasstree;
    CompassFile->GetObject("Data_R", compasstree);
    // Deactivate all branches
    compasstree->SetBranchStatus("*", 0);
    // Activate relevant branches
    for (auto activeBranchName : {"Timestamp", "Energy", "Flags"})
      compasstree->SetBranchStatus(activeBranchName, 1);


    // create 'old-style' root file containing trees:
    TFile* rootFile = new TFile(FileName+".root","recreate");
    
    TTree* dataTree = new TTree("dataTree","dataTree");
//    TTree* headerTree =new TTree("headerTree","headerTree"); // CoMPASS doesn't write the classical header lines. Skip this part
    
    long long int time; // time stamp in 10ns unit
    ULong64_t ctime;       // Compass uses slightly different datatypes. Let's see, if this causes problems...
    int pulseheight; // 15 bit pulseheight
    UShort_t cpulseheight;
    long long int extras; // extra information about saturation, pileup, deadtime, timestamp rollover
    UInt_t cextras;           
    double energy;

//    std::string headerline;
    
    if (calibration) {
        dataTree->Branch("energy",&energy);
        
        // also save the xbins to a Tree
        // after calibration histo has variable bin size
        std::vector<double> xbins;
        for (int i=0; i<32768; ++i) {
            xbins.push_back(calibration->Eval(i+0.5));
        }
        TTree* binTree = new TTree("binTree","binTree");
        binTree->Branch("xbins",&xbins);
        binTree->Fill();
        binTree->Write();
    }
    
    dataTree->Branch("time",&time);
    dataTree->Branch("pulseheight",&pulseheight);
    dataTree->Branch("extras",&extras);
  
    // here the mapping between the different trees: 
    compasstree->SetBranchAddress("Timestamp",&ctime); 
    compasstree->SetBranchAddress("Energy",&cpulseheight); 
    compasstree->SetBranchAddress("Flags",&cextras); 
    // headerTree->Branch("headerline",&headerline);  // CoMPASS doesn't write the classical header lines. Skip this part
    // now we loop over the compass tree and fill the old-style tree:
    Long64_t nentries = compasstree->GetEntries();
    for (Long64_t i=0;i<nentries;i++) {
        compasstree->GetEntry(i);
        if (calibration) {
            energy = calibration->Eval(pulseheight);
        }
        // convert datatypse to match old-style root tree
        time= (long long int) ctime/10000.;
        pulseheight= (int) cpulseheight;
        extras = (long long int) cextras;
        //std::cout << time_raw << "\t" << pulseheight << "\t" << extras << std::endl;
        dataTree->Fill();
    }
    CompassFile->Close();
    
    //headerTree->Write();
    dataTree->Write();
    
    rootFile->Close();
    
    return 0;
    
 
}

// ----------------------------------------------------
// make root file from list file (used by make_rootfile_list.cxx)
// ----------------------------------------------------
int read_listfile(TString FileName, TF1* calibration=0) {
    
    // open list file
    std::ifstream File;
    
    File.open(FileName);
    
    if (!File.is_open()) {
        std::cout << "##### ERROR: Could not open " << FileName << std::endl;
        return 1;
    }
    
    std::cout << "Reading list file ..." << std::endl;
    
    // create root file
    TFile* rootFile = new TFile(FileName+".root","recreate");
    
    TTree* dataTree = new TTree("dataTree","dataTree");
    TTree* headerTree =new TTree("headerTree","headerTree");
    
    long long int time; // time stamp in 10ns unit
    int pulseheight; // 15 bit pulseheight
    long long int extras; // extra information about saturation, pileup, deadtime, timestamp rollover
    double energy;
    std::string headerline;
    
    if (calibration) {
        dataTree->Branch("energy",&energy);
        
        // also save the xbins to a Tree
        // after calibration histo has variable bin size
        std::vector<double> xbins;
        for (int i=0; i<32768; ++i) {
            xbins.push_back(calibration->Eval(i+0.5));
        }
        TTree* binTree = new TTree("binTree","binTree");
        binTree->Branch("xbins",&xbins);
        binTree->Fill();
        binTree->Write();
    }
    
    dataTree->Branch("time",&time);
    dataTree->Branch("pulseheight",&pulseheight);
    dataTree->Branch("extras",&extras);
    
    headerTree->Branch("headerline",&headerline);
    
    // read header lines
    for (int i=0; i<5; ++i) {
        File >> headerline ;
        //std::cout << headerline << std::endl;
        headerTree->Fill();
    }
    
    // read data
    while (true) {
        
        if( File.eof() ) break;
        
        File >> time >> pulseheight >> extras;
        
        if (calibration) {
            
            // pileup event with valid energy (pulseheight < 0 and extras < 8)
            if (pulseheight<0 && extras<8) {
                energy = calibration->Eval(-pulseheight);
            }
            else {
                energy = calibration->Eval(pulseheight);
            }
        }
        //std::cout << time_raw << "\t" << pulseheight << "\t" << extras << std::endl;
        dataTree->Fill();
        
    }
    
    File.close();
    
    headerTree->Write();
    dataTree->Write();
    
    rootFile->Close();
    
    return 0;
    
}



// ----------------------------------------------------
// make spectrum from list file (FW version >= 128.64 and MC2 version >= 1.0.10)
//  -- actually it reads a ROOT Tree and produces a TH1D and stores it in a ROOT file
// ----------------------------------------------------

int spectrum_from_list(TString FileName, TString option="", double t_min=0., double t_max=0.) {
    
    // check for root file
    TFile* File = TFile::Open(FileName);
    
    // check for file
    if (File->IsZombie()) {
        
        std::cout << "##### ERROR: could not open " << FileName << std::endl;
        
        return 1;
        
    }
    
    TTree* dataTree = (TTree*) File->Get("dataTree");
    
    long long int time;
    long long int extras;
    int pulseheight;
    double energy;
    
    
    // make spectrum
    TH1D* hist = new TH1D();
    hist->SetName("hist");
    
    if (option=="energy") {
        if(!(dataTree->GetListOfBranches()->FindObject("energy"))) {
            std::cout << "##### ERROR: energy calibration is missing!" << std::endl;
            return 1;
        }
        else if (!(File->Get("binTree"))) {
            std::cout << "##### ERROR: binning information is missing!" << std::endl;
            return 1;
        }
        else {
            dataTree->SetBranchAddress("energy",&energy);
            
            TTree* binTree = (TTree*) File->Get("binTree");
            std::vector<double>* xbins = new std::vector<double>;
            binTree->SetBranchAddress("xbins",&xbins);
            binTree->GetEntry(0);
            hist->SetBins(xbins->size()-1,&xbins->at(0));
            hist->GetXaxis()->SetTitle("Energy (keV)");
            hist->GetYaxis()->SetTitle("Counts");

        }
    }
    
    else {
        hist->SetBins(32767,0.5,32767.5);
        hist->GetXaxis()->SetTitle("ADC Channel");
        hist->GetYaxis()->SetTitle("Counts");
    }
    
    dataTree->SetBranchAddress("pulseheight",&pulseheight);
    dataTree->SetBranchAddress("time",&time);
    dataTree->SetBranchAddress("extras",&extras);
    
    int nEntries = dataTree->GetEntries();
    
    dataTree->GetEntry(0);
    long long int t0 = time;
    long long int llt_min;
    long long int llt_max;
    
    // calculate real time (sec.)
    if (t_max==0.) {
        dataTree->GetEntry(nEntries-1);
        t_max = (double) (time-t0)/1.e8;
    }
    double t_real = t_max-t_min;
    llt_min = (long long int) t_min*1.e8+t0;
    llt_max = (long long int) t_max*1.e8+t0;
    
    
    // calculate dead time
    long long int t_dead = 0;
    long long int t_last = 0;
    
    int nPileup = 0;
    int nAll = 0;
    
    double pulseheight_energy;
    
    // loop over all entries
    for (int i=0; i<nEntries; ++i) {
        
        dataTree->GetEntry(i);
        
        if (option=="energy") {
            pulseheight_energy = energy;
        }
        else {
            pulseheight_energy = pulseheight;
        }
        
        if (time>=llt_min) {
            if (time>llt_max) {
                break;
            }
            // no fake event (extras < 8 or extras = 16)
            if (extras<8 || extras == 16) {
                nAll++;
//            } else { // temporary cout to understand what happens to CoMPASS extras in this computation:
//                     // does Compass have extras <8 or ==16? I am tempted to ignore/reject all events that have an extra != 0x0. At our rates we dont expect pilups to contribute significantly.
//                std::cout << "  ... not a 'good' event: extras=" << extras << ", pulseheight=" << pulseheight << std::endl;
            }
            
            // pileup event where pulseheight is corrupted (pulseheight = 0 and extras < 8)
            if (pulseheight==0 && extras<8) {
                nPileup++;
            }
            
            // deadtime before event (extras = odd number)
            if (extras % 2) {
                t_dead+=time-t_last;
            }
            
            /*
            // pileup event with valid energy (pulseheight < 0 and extras < 8)
            if (pulseheight<0 && extras<8) {
            }
            
            // regular event (pulseheight > 0 and extras < 8)
            if (pulseheight>0 && extras<8) {
            }
            
            // oversaturated trapezoid (pulseheight = 32767 and extras = 0)
            if (pulseheight==32767 && extras==0) {
            }
            
            // oversaturated input (pulseheight = 32767 and extras = 16)
            if (pulseheight==32767 && extras==16) {
            }
            
            // undersaturated input (pulseheight = 0 and extras = 16)
            if (pulseheight==0 && extras==16) {
            }
            */
            
            hist->Fill(pulseheight_energy);
            
        }
        t_last=time;
        
    }
    hist->SetDirectory(0);
    File->Close();
    
    
    // calculate fraction of pileup events
    double f_pileup = (double) nPileup/nAll;
    
    // calculate live time (sec.)
    //*t_live = (double) (*t_real*(1.-f_pileup)-t_dead/1.e8);
    
    // no pileup correction for low counting rates!
    double t_live = (double) (t_real-t_dead/1.e8);

    
    TString s_time;
    s_time = TString::Format("t_real: %1.3f s, t_live: %1.3f s",t_real,t_live);
    std::cout << s_time << std::endl;
    //cout << "fraction of pileup events: " << f_pileup << endl;
    //cout << "deadtime from busy: " << (double) t_dead/1.e8 << endl;
    
    
    // draw spectrum
    TCanvas* c1 = new TCanvas("c1");
    gStyle->SetOptStat(0);
    c1->SetLogy();
    
    TH1D *hdraw = (TH1D*)hist->Clone("hdraw");
    hdraw->Draw();
    
    TString timecut;
    timecut = TString::Format("%1.0f-%1.0fs",t_min,t_max);
    
    TString results_filename;
    
    if (option=="energy") {
        results_filename = FileName+"_spectrum_calibrated_"+timecut;
    }
    else {
        results_filename = FileName+"_spectrum_"+timecut;
    }
    
    
    c1->SaveAs(results_filename+".pdf");
    
    // write to file
    TFile* histFile = new TFile(results_filename+".root","recreate");
    hist->Write();
    TVectorD v_real(1);
    TVectorD v_live(1);
    v_real[0] = t_real;
    v_live[0] = t_live;
    v_real.Write("t_real");
    v_live.Write("t_live");
    histFile->Close();
    
    return 0;
}

// ----------------------------------------------------
// print some information from ROOT file
// ----------------------------------------------------
int print_info_root_file(TString FileName) {

    // check for root file
    TFile* File = new TFile(FileName);
    
    // check for file
    if (File->IsZombie()) {
        std::cout << "##### ERROR: could not open " << FileName << std::endl;
        return 1;
    }

    TTree* dataTree = (TTree*) File->Get("dataTree");
    std::cout << "dataTree extracted from " << FileName << std::endl;
    std::cout << " --------------------- " << std::endl;

    
    long long int time;
    long long int extras;
    int pulseheight;
    
    if( (dataTree->GetListOfBranches()->FindObject("energy")) ) {
        double energy;
        dataTree->SetBranchAddress("energy",&energy);
    }
    
    dataTree->SetBranchAddress("pulseheight",&pulseheight);
    dataTree->SetBranchAddress("time",&time);
    dataTree->SetBranchAddress("extras",&extras);
    
    int nEntries = dataTree->GetEntries();
    std::cout << "   Total number of entries: " << nEntries << std::endl;

    int nEntriesExtrasLTE1 = dataTree->Draw("pulseheight>>_htemp","extras>=1","goff");
    int nEntriesExtrasLTE8 = dataTree->Draw("pulseheight>>_htemp","extras>=8","goff");
    int nEntriesExtrasLTE80 = dataTree->Draw("pulseheight>>_htemp","extras>=80","goff");

    std::cout << "   Number of entries with 'extras>=1': " << nEntriesExtrasLTE1 << std::endl;
    std::cout << "   Number of entries with 'extras>=8': " << nEntriesExtrasLTE8 << std::endl;
    std::cout << "   Number of entries with 'extras>=80': " << nEntriesExtrasLTE80 << std::endl;
    
    
    dataTree->GetEntry(0);
    long long int t0 = time;
    // dont we always start time counting from zero? I.e., shouldn't t0=0.
    // if we are off by more than a minute, print a warning:
    if (t0/1.e8/60 > 1.) {
        std::cout << "**** ATTENTION: t_0 larger 1 minute! t0 =" << t0/1.e8/60 << " min." << std::endl; 
    }
    
    dataTree->GetEntry(nEntries-1);
    double t_max = (double) (time-t0)/1.e8;

    std::cout << "   Run duration: " << t_max/3600./24. << " days = " << t_max/3600. << " hours." << std::endl; 
 
    if( (dataTree->GetListOfBranches()->FindObject("energy")) ) {
        double max_enrg;
        max_enrg = dataTree->GetMaximum("energy");
        std::cout << "   Largest energy: " << max_enrg << std::endl; 
    }
    double max_ph;
    max_ph = dataTree->GetMaximum("pulseheight");
    std::cout << "   Largest pulseheight: " << max_ph << std::endl; 
    std::cout << " --------------------- " << std::endl;

 
    return 0;
}

// ----------------------------------------------------
// make rate plot from list file
// ----------------------------------------------------

int rate_from_list(TString FileName, double binwidth, double range_min, double range_max, TString option="") {
    
    
    // check for root file
    TFile* File = new TFile(FileName);
    
    // check for file
    if (File->IsZombie()) {
        
        std::cout << "##### ERROR: could not open " << FileName << std::endl;
        
        return 1;
        
    }
    
    TTree* dataTree = (TTree*) File->Get("dataTree");
    
    long long int time;
    long long int extras;
    int pulseheight;
    
    if (option=="energy") {
        double energy;
        if(!(dataTree->GetListOfBranches()->FindObject("energy"))) {
            std::cout << "##### ERROR: energy calibration is missing!" << std::endl;
            return 1;
        }
        else {
            dataTree->SetBranchAddress("energy",&energy);
        }
    }
    
    dataTree->SetBranchAddress("pulseheight",&pulseheight);
    dataTree->SetBranchAddress("time",&time);
    dataTree->SetBranchAddress("extras",&extras);
    
    int nEntries = dataTree->GetEntries();
    
    
    dataTree->GetEntry(0);
    long long int t0 = time;
    
    dataTree->GetEntry(nEntries-1);
    double t_max = (double) (time-t0)/1.e8;
    
    int nbins = t_max/binwidth;
    TH1D* hist = new TH1D("hist",";Time (s);Rate (Hz)",nbins,0,t_max);
    
    TString cut;
    TString sdraw;
    
    if (option=="energy") {
        // ignore fake events with extras >= 8 and select energy range
        cut = TString::Format("extras<8 && energy > %.1f && energy < %.1f",range_min,range_max);
    }
    
    else {
        // ignore fake events with extras >= 8 and select pulseheight range (pileup events with pulseheight < 0 are ignored!)
        cut = TString::Format("extras<8 && pulseheight > %.0f && pulseheight < %.0f",range_min,range_max);
    }
    
    // convert time to sec.
    sdraw = TString::Format("(time-%lli)/1.e8>>hist",t0);
    
    dataTree->Draw(sdraw,cut,"goff");
    hist->SetDirectory(0);
    File->Close();
    
    hist->Sumw2();
    
    // scale rate to Hz
    hist->Scale(1./binwidth);
    
    // draw spectrum
    TCanvas* c1 = new TCanvas("c1");
    gStyle->SetOptStat(0);
    
    hist->SetTitle(cut);
    
    hist->GetYaxis()->SetTitleOffset(1.2);
    
    hist->Draw();
    
    TString pulseheightcut;
    if (option=="energy") {
        pulseheightcut = TString::Format("%.1f-%.1fkeV",range_min,range_max);

    }
    else {
        pulseheightcut = TString::Format("%.0f-%.0fCh",range_min,range_max);
    }
    c1->SaveAs(FileName+"_rate_"+pulseheightcut+".pdf");
    
    
    // write to file
    TFile* histFile = new TFile(FileName+"_rate_"+pulseheightcut+".root","recreate");
    hist->Write();
    histFile->Close();
    
    return 0;
}







