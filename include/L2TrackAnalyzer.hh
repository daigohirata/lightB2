//
// Created by Daigo Hirata on 2025/08/29
//

#ifndef LIGHTB2_L2TRACKANALYZER_HH
#define LIGHTB2_L2TRACKANALYZER_HH

// B2MC include
#include <B2SpillSummary.hh>
#include <B2TrackSummary.hh>
#include <B2Enum.hh>
#include <TSpline.h>

class L2TrackAnalyzer {
public:
  L2TrackAnalyzer(const B2SpillSummary* spill,
                  const B2TrackSummary* track,
                  B2Detector vertex_detector,
                  const std::string& spline_file_path);

  const B2TrackSummary* SearchChildMuon(const B2SpillSummary* spill) const;
  Bool_t HasVertexDetectorHit() const;
  B2Detector HitMuonDetector(const Int_t& bm_top_required) const;

  /**
   * @return scintillator number defined as following
   *  0:PM Ingrid,  1:PM Scibar,
   *  2:UWG grid,   3:UWG plane,
   *  4:DWG grid,   5:DWG plane
   */
  Int_t ClassifyScintillator(const B2HitSummary* single_hit) const;
  Double_t CalculateDedx(const B2HitSummary* single_hit) const;
  std::vector<const B2HitSummary*> SelectHitsExcludingFarthest(const B2TrackSummary* track, int num_exclude_hits) const;
  std::pair<Double_t, Int_t> CalculateMuclFromHits(const std::vector<const B2HitSummary*>& hits) const;
  Double_t CalculateMucl(const int& mucl_ignore_hit) const;


private:
  const B2SpillSummary* spill_;
  const B2TrackSummary* track_;
  B2Detector vertex_detector_;
  static std::unique_ptr<TFile> spline_file_;
  static std::vector<TSpline3*> mucl_spline_;
};

#endif // LIGHTB2_L2TRACKANALYZER