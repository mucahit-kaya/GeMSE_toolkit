#include "macros.h"

TString fFileName_spectrum;
std::vector<double> fenergy;
std::vector<double> fch_mean;
std::vector<double> fch_unc;
std::vector<double> fe_res;
std::vector<double> fch_res;
//std::vector<double> fch_res_unc;

// ----------------------------------------------------
// This file is supposed to support manual fitting of peaks (e.g., from within TBrowser()
// ----------------------------------------------------


// ----------------------------------------------------
// read parameters from user fit results
// It expects a file, that contains 
// #energy_literature #peak_pos_ch #peak_pos_unc_ch
// ----------------------------------------------------

int read_parameters(TString FileName) {
    
    //double energy, fitrange_low, fitrange_high, amp_st, mean_st, sigma_st, const_st, slope_st;
    double energy, ch_mean, ch_unc;
    
    std::ifstream File;
    File.open(FileName);
    
    if (!File.is_open()) {
        std::cout << "##### ERROR: could not open " << FileName << std::endl;
        return 1;
    }
    
    std::string headerline;
    
    getline(File, headerline);
    File >> fFileName_spectrum;
    getline(File, headerline);
    getline(File, headerline);
    while (true)
    {
        File >> energy >> ch_mean >> ch_unc;
        fenergy.push_back(energy);
        fch_mean.push_back(ch_mean);
        fch_unc.push_back(ch_unc);
        if( File.eof() ) break;
        
    }
    
    File.close();
    
    // print information
    std::cout << "######################################" << std::endl;
    std::cout << "#### Reading "<< FileName << " ..." << std::endl;
    std::cout << "spectrum file name: " << fFileName_spectrum << std::endl;
    //std::cout << "fitrange low \t fitrange high \t counts \t mean \t sigma  \t const. \t slope \t energy" << std::endl;
    std::cout << "energy [keV] \t mean [ch] \t mean_unc [ch]" << std::endl;
    for (int i=0; i<fenergy.size(); ++i)
    {
        std::cout << fenergy[i] << "\t" << fch_mean[i] << "\t" << fch_unc[i] << std::endl;
    }
    std::cout << "######################################" << std::endl;
    
    return 0;
}

// ----------------------------------------------------
// make energy calibration
// ----------------------------------------------------

int main(int argc, char *argv[]) {
    
    // argc should be 2 for correct execution
    if ( argc != 2 ) {
        
        // We print argv[0] assuming it is the program name
        std::cout<<"usage: "<< argv[0] <<" <parameters_file.txt>" << std::endl;
        return 1;
    }
    
    TString FileName_parameters = argv[1];
    
    // read parameters from file
    if (read_parameters(FileName_parameters)) {
        return 1;
    }
    
    // get spectrum
    TH1D* hist = getspectrum(fFileName_spectrum);
    
    if (hist==0) {
        return 1;
    }
    
    // draw spectrum (ToDo: adjust to draw specified values?)
/* 
    TCanvas* c1 = new TCanvas("c1");
    hist->Draw();
    
    TF1* fit = new TF1();
    std::vector<double> peakpos;
    std::vector<double> peakpos_err;
    
    int npeaks = fenergy.size();

    // loop over all peaks
    for (int i=0; i<npeaks; ++i) {
        
        // fit peak with Gauss+Pol1
        std::cout << "###################################################" << std::endl;
        std::cout << "Fitting line " << i+1 << " in range " << ffitrange_low[i] << " - " << ffitrange_high[i] << std::endl;
        // fit = FitGaussPol1(hist,famp_st[i],fmean_st[i], fsigma_st[i], fconst_st[i], fslope_st[i], ffitrange_low[i], ffitrange_high[i]);
        fit = FitGauss(hist,famp_st[i],fmean_st[i], fsigma_st[i], ffitrange_low[i], ffitrange_high[i]);
        if (fit==0) {
            return 1;
        }
        peakpos.push_back(fit->GetParameter(1));
        peakpos_err.push_back(fit->GetParError(1));

    }
    
    // save calibration fits
    c1->SaveAs(fFileName_spectrum+"_calibration_fits.root");
    c1->SaveAs(fFileName_spectrum+"_calibration_fits.pdf");
  
*/    

    


    // plot peak position vs. energy
    int npeaks = fenergy.size();
    TGraphErrors* graph = new TGraphErrors(npeaks, &fch_mean.at(0), &fenergy.at(0), &fch_unc.at(0), 0 );
    
    // fit with pol2
    std::cout << "###################################################" << std::endl;
    std::cout << "Fitting calibration curve ..." << std::endl;
    TF1* fit_calib = FitPol2(graph,0.,1.,0.);
    if (fit_calib==0) {
        return 1;
    }
    
    TCanvas* c2 = new TCanvas("c2");
    graph->SetTitle("Energy Calibration");
    graph->SetMarkerStyle(2);
    graph->GetXaxis()->SetTitle("ADC Channel");
    graph->GetYaxis()->SetTitle("Energy (keV)");
    graph->Draw("ap");
    
    c2->SaveAs(fFileName_spectrum+"_calibration_function.root");
    c2->SaveAs(fFileName_spectrum+"_calibration_function.pdf");

    TCanvas* c3 = new TCanvas("c3");
    double e_res;
    for (int i=0; i<npeaks; ++i) {
        e_res = fenergy[i] - fit_calib->Eval(fch_mean[i]);
        fe_res.push_back(e_res);
    }

/*
    std::cout << "energy [keV] \t mean [ch] \t mean_unc [ch] \t Fit(mean) [keV] \t residual [keV]" << std::endl;
    for (int i=0; i<fenergy.size(); ++i)
    {
        std::cout << fenergy[i] << "\t" << fch_mean[i] << "\t" << fch_unc[i]  << "\t" << fit_calib->Eval( fch_mean[i] ) << "\t" << fe_res[i] << std::endl;
    }
    std::cout << "######################################" << std::endl;
*/  

    TGraphErrors* graph_res = new TGraphErrors(npeaks, &fch_mean.at(0), &fe_res.at(0), &fch_unc.at(0), 0 );
    graph_res->SetTitle("Energy Calibration");
    graph_res->SetMarkerStyle(2);
    graph_res->GetXaxis()->SetTitle("ADC Channel");
    graph_res->GetYaxis()->SetTitle("Energy - Fit (keV)");
    graph_res->Draw("ap");
    
    c3->SaveAs(fFileName_spectrum+"_calibration_function_residuals.root");
    c3->SaveAs(fFileName_spectrum+"_calibration_function_residuals.pdf");


    TCanvas* c4 = new TCanvas("c4");
    double ch_res;
    for (int i=0; i<npeaks; ++i) {
        ch_res = fch_mean[i] - fit_calib->GetX(fenergy[i], fch_mean[i]-100., fch_mean[i]+100.);
        fch_res.push_back(ch_res);
    }

    std::cout << "energy [keV] \t mean [ch] \t mean_unc [ch] \t Fit_inv(energy) [ch] \t residual [ch]" << std::endl;
    for (int i=0; i<fenergy.size(); ++i)
    {
        std::cout << fenergy[i] << "\t" << fch_mean[i] << "\t" << fch_unc[i]  << "\t" << fit_calib->GetX( fenergy[i], fch_mean[i]-100., fch_mean[i]+100. ) << "\t" << fch_res[i] << std::endl;
    }
    std::cout << "######################################" << std::endl;
    
    TGraphErrors* graph_res2 = new TGraphErrors(npeaks, &fenergy.at(0), &fch_res.at(0), 0, &fch_unc.at(0) );
    graph_res2->SetTitle("Energy Calibration Residual 2");
    graph_res2->SetMarkerStyle(2);
    graph_res2->GetXaxis()->SetTitle("Energy / keV");
    graph_res2->GetYaxis()->SetTitle("Residual / channel");
    graph_res2->Draw("ap");

    TLine* l = new TLine(graph_res2->GetXaxis()->GetXmin(),0.0,graph_res2->GetXaxis()->GetXmax(),0.0);
    l->SetLineColor(kRed);
    l->SetLineStyle(kDashed);
    l->SetLineWidth(2);
    l->Draw();

/*
    TLine* l2 = new TLine();
    l2->SetLineColor(kRed);
    l2->SetLineStyle(kDotted);
    l2->DrawLineNDC(0,0,1,0);
*/  

    c4->SaveAs(fFileName_spectrum+"_calibration_function_residuals2.root");
    c4->SaveAs(fFileName_spectrum+"_calibration_function_residuals2.pdf");
       
    return 0;
}


