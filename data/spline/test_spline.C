double GetWeight(double fWeightCoeffs[4], double dx){
  return  (fWeightCoeffs[0] + dx * (fWeightCoeffs[1] + dx * (fWeightCoeffs[2] + dx * fWeightCoeffs[3])));
}

void test_spline(){

  Double_t x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Double_t y[10] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
  TGraph* graph = new TGraph(10, x, y);

  TCanvas *c1 = new TCanvas("c1", "c1", 1000, 800);
  graph->SetMarkerStyle(21);
  graph->Draw("AP");

  //TSpline3* spline = new TSpline3("spline", x, y, 10);
  TSpline3 spline("spline", x, y, 10);

  Int_t i = 1;
  Double_t dumpX;
  Double_t coeff[4];
  spline.GetCoeff(i, dumpX, coeff[0], coeff[1], coeff[2], coeff[3]);                                                                  
  std::cout << "x = " << dumpX << " " << coeff[0] << " " << coeff[1] << " " << coeff[2] << " " << coeff[3] << '\n';                   
  std::cout << "weight = " << GetWeight(coeff, dumpX) << '\n';  

  std::cout << spline.FindX(2.4) << " " << spline.Eval(2.2)  << '\n';

  TCanvas *c2 = new TCanvas("c2", "c2", 1000, 800);
  spline.Draw("C");

  
}
