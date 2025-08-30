void draw_mucl_spline(const char* inputfile = "", const char* outputdir = ""){

  const char* detector_name[3]    = {"Proton Module", "WagasciUpstream", "WagasciDownstream"};
  const char* scitype_name[3][2]  = { {"ingrid", "scibar"}, {"grid", "plane"}, {"grid", "plane"} };

  TFile* file = new TFile(inputfile, "READ");
  TSpline3* spline[2][3][2][10];

  Int_t maxang[3][2] = { {1,1}, {2,1}, {2,1} };

  for(int datatype=0; datatype<2; datatype++)
    for(int idet=0; idet<3; idet++)
      for(int scitype=0; scitype<2; scitype++){
	for(int ang=0; ang<maxang[idet][scitype]; ang++){
	  spline[datatype][idet][scitype][ang] = (TSpline3*)file->Get(Form("spline_%d_%d_%d_%d", datatype, idet, scitype, ang));
	  spline[datatype][idet][scitype][ang] -> SetLineColor(2+datatype);
	}
      }
	
  TCanvas* canvas[3][2];
  TLegend* legend[3][2];
  
  for(int idet=0; idet<3; idet++){
    for(int scitype=0; scitype<2; scitype++){
      canvas[idet][scitype] = new TCanvas(Form("canvas_%d_%d", idet, scitype), "", 1200, 800);
      canvas[idet][scitype] -> cd();

      spline[0][idet][scitype][0] -> SetTitle(Form("spline %s %s", detector_name[idet], scitype_name[idet][scitype]));
      //spline[0][idet][scitype][1] -> SetXTitle("energy deposit (MeV/cm)");
      //spline[0][idet][scitype][1] -> SetYTitle("MUCL");

      spline[0][idet][scitype][0] -> Draw("C");
      spline[1][idet][scitype][0] -> Draw("C,same");
      
      legend[idet][scitype] = new TLegend(0.6, 0.7, 0.9, 0.9);
      legend[idet][scitype] -> AddEntry(spline[0][idet][scitype][0], Form("spline %s %s for real", detector_name[idet], scitype_name[idet][scitype]), "l");
      legend[idet][scitype] -> AddEntry(spline[1][idet][scitype][0], Form("spline %s %s for mc", detector_name[idet], scitype_name[idet][scitype]), "l");
      legend[idet][scitype] -> Draw("");
      
      canvas[idet][scitype] -> SaveAs(Form("%s/spline_%s_%s.png", outputdir, detector_name[idet], scitype_name[idet][scitype]));
    }
  }
  
}
