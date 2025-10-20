#include "macros.h"

TString fFileName_spectrum;
std::vector<double> ffitrange_low;
std::vector<double> ffitrange_high;
std::vector<double> famp_st;
std::vector<double> fmean_st;
std::vector<double> fsigma_st;
std::vector<double> fconst_st;
std::vector<double> fslope_st;
std::vector<double> fsig_res;


// ----------------------------------------------------
// read parameters from user specified file
// ----------------------------------------------------

int read_parameters(TString FileName) {
    
    double fitrange_low, fitrange_high, amp_st, mean_st, sigma_st, const_st, slope_st;
    
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
        File >> fitrange_low >> fitrange_high >> amp_st >> mean_st >> sigma_st >> const_st >> slope_st;
        ffitrange_low.push_back(fitrange_low);
        ffitrange_high.push_back(fitrange_high);
        famp_st.push_back(amp_st);
        fmean_st.push_back(mean_st);
        fsigma_st.push_back(sigma_st);
        fconst_st.push_back(const_st);
        fslope_st.push_back(slope_st);
        if( File.eof() ) break;
        
    }
    
    File.close();
    
    // print information
    std::cout << "######################################" << std::endl;
    std::cout << "#### Reading "<< FileName << " ..." << std::endl;
    std::cout << "spectrum file name: " << fFileName_spectrum << std::endl;
    std::cout << "fitrange low \t fitrange high \t counts \t mean \t sigma \t const. \t slope" << std::endl;
    for (int i=0; i<ffitrange_low.size(); ++i)
    {
        std::cout << ffitrange_low[i] << "\t" << ffitrange_high[i] << "\t" << famp_st[i] << "\t" << fmean_st[i] << "\t" << fsigma_st[i]<< "\t"  << fconst_st[i]<< "\t"  << fslope_st[i]<< "\t"  << std::endl;
    }
    std::cout << "######################################" << std::endl;
    
    return 0;
}

// simplified version of read:
int read_parameters_simple(TString FileName) {
    
    double fitrange_low, fitrange_high,  mean_st;
    
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
        File >> mean_st >> fitrange_low >> fitrange_high;
        if( File.eof() ) break;
        ffitrange_low.push_back(fitrange_low);
        ffitrange_high.push_back(fitrange_high);
        fmean_st.push_back(mean_st);
    }
    
    File.close();
    
    // print information
    std::cout << "######################################" << std::endl;
    std::cout << "#### Reading "<< FileName << " ..." << std::endl;
    std::cout << "spectrum file name: " << fFileName_spectrum << std::endl;
    std::cout << "mean \t fitrange low \t fitrange high" << std::endl;
    for (int i=0; i<ffitrange_low.size(); ++i)
    {
        std::cout << fmean_st[i] << "\t" << ffitrange_low[i] << "\t" << ffitrange_high[i]  << std::endl;
    }
    std::cout << "######################################" << std::endl;
    
    return 0;
}

// ----------------------------------------------------
// determine resolution
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
    if (read_parameters_simple(FileName_parameters)) {
        return 1;
    }
    
    // get spectrum
    TH1D* hist = getspectrum(fFileName_spectrum);
    
    if (hist==0) {
        return 1;
    }
    
    // draw spectrum
    TCanvas* c1 = new TCanvas("c1");
    hist->Draw();
    
    TF1* prefit = new TF1();
    TF1* fit = new TF1();
    std::vector<double> peakpos, peakpos_err, sigma, sigma_err;
    
    int npeaks = ffitrange_low.size();
    double frl, frh, frl_p, frh_p;

    // loop over all peaks
    for (int i=0; i<npeaks; ++i) {
        
        // fit peak with Gauss+Pol1
        std::cout << "###################################################" << std::endl;
        if (ffitrange_low[i] > 0) {
            frl = ffitrange_low[i];
            frh = ffitrange_high[i];
        } else {
            frl = fmean_st[i]+ffitrange_low[i];
            frh = fmean_st[i]+ffitrange_high[i];
        }

        //frl_p = frh; // fmean_st[i]-1.;
        //frh_p = frh; //fmean_st[i]+1.;
        frl_p = fmean_st[i]-1.5;
        frh_p = fmean_st[i]+1.5;
        std::cout << "Fitting line " << i+1 << " (" << fmean_st[i] << " keV) in range " << frl << " - " << frh << std::endl;
        hist->GetXaxis()->SetRangeUser( frl, frh );
        prefit = FitGauss(hist, 100., fmean_st[i], 1., frl_p, frh_p);
        if (prefit==0) {
            // prefit failed.
            std::cout << "Prefit failed. Exit." << std::endl;
            return 1;
        }
        c1->SaveAs(fFileName_spectrum+"_resolution_prefits_peak"+ (i+1) +".pdf");

        std::cout << "    ... now the full fit including pol1 ..." << std::endl;
        fit = FitGaussPol1(hist, prefit->GetParameter(0), prefit->GetParameter(1), prefit->GetParameter(2), 1., 0., frl, frh);

        if (fit==0) {
            std::cout << "    ... full fit failed!!!!" << std::endl;
            return 1;
        }
        peakpos.push_back(fit->GetParameter(1));
        peakpos_err.push_back(fit->GetParError(1));
        sigma.push_back(fit->GetParameter(2));
        sigma_err.push_back(fit->GetParError(2));

        hist->GetXaxis()->SetRangeUser(fit->GetParameter(1)-3*fit->GetParameter(2), fit->GetParameter(1)+3*fit->GetParameter(2));
        c1->SaveAs(fFileName_spectrum+"_resolution_fits_peak"+ (i+1) +".pdf");
    }
    
    // save calibration fits
    hist->GetXaxis()->SetRangeUser(0, hist->GetBinCenter( hist->GetNbinsX()-1) );
    c1->SaveAs(fFileName_spectrum+"_resolution_fits.root");
    c1->SaveAs(fFileName_spectrum+"_resolution_fits.pdf");
    
    // plot peak position vs. energy
    TGraphErrors* graph = new TGraphErrors(npeaks, &peakpos.at(0), &sigma.at(0), &peakpos_err.at(0), &sigma_err.at(0) );
    
    // fit with sqrt
    std::cout << "###################################################" << std::endl;
    std::cout << "Fitting resolution curve ..." << std::endl;
    TF1* fit_res = FitSqrt(graph,0.1,0.,0.);
    if (fit_res==0) {
        return 1;
    }
    
    TCanvas* c2 = new TCanvas("c2");
    graph->SetTitle("Energy Resolution");
    graph->SetMarkerStyle(2);
    graph->GetXaxis()->SetTitle("Energy (keV)");
    graph->GetYaxis()->SetTitle("Sigma (keV)");
    graph->Draw("ap");
    
    c2->SaveAs(fFileName_spectrum+"_resolution_function.root");
    c2->SaveAs(fFileName_spectrum+"_resolution_function.pdf");
    

    TCanvas* c3 = new TCanvas("c3");
    double sig_res;
    for (int i=0; i<npeaks; ++i) {
        sig_res = sigma[i] - fit_res->Eval(peakpos[i]);
        fsig_res.push_back(sig_res);
    }

    TGraphErrors* graph_res = new TGraphErrors(npeaks, &peakpos.at(0), &fsig_res.at(0), &peakpos_err.at(0), &sigma_err.at(0) );
    graph_res->SetTitle("Energy Calibration");
    graph_res->SetMarkerStyle(2);
    graph_res->GetXaxis()->SetTitle("ADC Channel");
    graph_res->GetYaxis()->SetTitle("Energy - Fit (keV)");
    graph_res->Draw("ap");

    TLine* l = new TLine(graph_res->GetXaxis()->GetXmin(),0.0,graph_res->GetXaxis()->GetXmax(),0.0);
    l->SetLineColor(kRed);
    l->SetLineStyle(kDashed);
    l->SetLineWidth(2);
    l->Draw();

    c3->SaveAs(fFileName_spectrum+"_resolution_function_residuals.root");
    c3->SaveAs(fFileName_spectrum+"_resolution_function_residuals.pdf");



    return 0;
}


