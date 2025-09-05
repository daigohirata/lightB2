//
// Created by Daigo Hirata on 2025/08/29
//

#include "L2TrackAnalyzer.hh"

// ROOT include
#include <TFile.h>
#include <TSpline.h>
#include <TVector3.h>

// B2MC include
#include <B2SpillSummary.hh>
#include <B2TrackSummary.hh>
#include <B2HitSummary.hh>
#include <B2Enum.hh>
#include <B2Pdg.hh>

std::unique_ptr<TFile> L2TrackAnalyzer::spline_file_ = nullptr;
std::vector<TSpline3*> L2TrackAnalyzer::mucl_spline_;

L2TrackAnalyzer::L2TrackAnalyzer(const B2SpillSummary* spill,
                                 const B2TrackSummary* track,
                                 B2Detector vertex_detector,
                                 const std::string& spline_file_path)
  : spill_(spill), track_(track), vertex_detector_(vertex_detector) {
  if (!spline_file_) {
    spline_file_.reset(TFile::Open(spline_file_path.c_str(), "READ"));

    if (!spline_file_ || spline_file_->IsZombie()) {
      throw std::runtime_error("Failed to open spline file: " + spline_file_path);
    }

    mucl_spline_.emplace_back((TSpline3*)spline_file_->Get("spline_1_0_0_0")); // PM Ingrid
    mucl_spline_.emplace_back((TSpline3*)spline_file_->Get("spline_1_0_1_0")); // PM Scibar
    mucl_spline_.emplace_back((TSpline3*)spline_file_->Get("spline_1_1_0_0")); // UWG grid
    mucl_spline_.emplace_back((TSpline3*)spline_file_->Get("spline_1_1_1_0")); // UWG plane
    mucl_spline_.emplace_back((TSpline3*)spline_file_->Get("spline_1_2_0_0")); // DWG grid
    mucl_spline_.emplace_back((TSpline3*)spline_file_->Get("spline_1_2_1_0")); // DWG plane
    mucl_spline_.emplace_back((TSpline3*)spline_file_->Get("spline_1_1_0_1")); // UWG grid high angle
    mucl_spline_.emplace_back((TSpline3*)spline_file_->Get("spline_1_2_0_1")); // DWG grid high angle
  }
}

const B2TrackSummary* L2TrackAnalyzer::SearchChildMuon(const B2SpillSummary* spill) const {
  for (auto it_track = spill->BeginTrueTrack(); const auto* track = it_track.Next(); ) {
    if (!B2Pdg::IsMuonPlusOrMinus(track->GetParticlePdg())) continue;
    if (track->GetTrackType() == B2TrackType::kPrimaryTrack) continue;

    Int_t parent_id = track->GetParentTrackId();
    if (parent_id != track_->GetTrackId()) continue;

    return track;
  }
  return nullptr;
}

Bool_t L2TrackAnalyzer::HasVertexDetectorHit() const {
  Int_t num_hits_top = 0;
  Int_t num_hits_side = 0;

  num_hits_top = track_->GetNumHits(B2View::kTopView, vertex_detector_, 0);
  num_hits_side = track_->GetNumHits(B2View::kSideView, vertex_detector_, 0);

  if ( B2Pdg::IsChargedPion(track_->GetParticlePdg()) ) {
    const B2TrackSummary* child_muon = SearchChildMuon(spill_);
    if (child_muon) {
      num_hits_top  += child_muon->GetNumHits(B2View::kTopView,  vertex_detector_, 0);
      num_hits_side += child_muon->GetNumHits(B2View::kSideView, vertex_detector_, 0);
    }
  }

  return (num_hits_top >= 3 && num_hits_side >= 3);
}

B2Detector L2TrackAnalyzer::HitMuonDetector(const Int_t& bm_top_required) const {
  if ( track_->GetNumHits(B2View::kTopView, B2Detector::kBabyMind, 0) >= bm_top_required &&
      (track_->GetNumHits(B2View::kSideView, B2Detector::kBabyMind, 0) + track_->GetNumHits(B2View::kSideView, B2Detector::kYasuTracker, 0)) >= 3 ) {
    return B2Detector::kBabyMind;
  } else if ( track_->GetNumHits(B2View::kTopView, B2Detector::kWallMrdNorth, 0) >= 3 ) {
    return B2Detector::kWallMrdNorth;
  } else if ( track_->GetNumHits(B2View::kTopView, B2Detector::kWallMrdSouth, 0) >= 3 ) {
    return B2Detector::kWallMrdSouth;
  } else {
    return B2Detector::kUnknownDetector;
  }
}

Int_t L2TrackAnalyzer::ClassifyScintillator(const B2HitSummary* single_hit) const {
  if (single_hit->GetDetectorId() == B2Detector::kProtonModule) {
    if ( (single_hit->GetPlane() == 0) ||
         (18 <= single_hit->GetPlane() && single_hit->GetPlane() <= 21) ) {
      return 0;
    } else if (1 <= single_hit->GetPlane() && single_hit->GetPlane() <= 17) {
      if (8 <= single_hit->GetSlot().GetValue(single_hit->GetSingleReadout()) && single_hit->GetSlot().GetValue(single_hit->GetSingleReadout()) <= 23) {
        return 1;
      } else {
        return 0;
      }
    } 
  } else if ( single_hit->GetDetectorId() == B2Detector::kWagasciUpstream ) {
    if (0 <= single_hit->GetSlot().GetValue(single_hit->GetSingleReadout()) && single_hit->GetSlot().GetValue(single_hit->GetSingleReadout()) <= 39) {
      return 3;
    } else {
      return 2;
    }
  } else if ( single_hit->GetDetectorId() == B2Detector::kWagasciDownstream ) {
    if (0 <= single_hit->GetSlot().GetValue(single_hit->GetSingleReadout()) && single_hit->GetSlot().GetValue(single_hit->GetSingleReadout()) <= 39) {
      return 5;
    } else {
      return 4;
    }
  }

  return -1;
};

Double_t L2TrackAnalyzer::CalculateDedx(const B2HitSummary* single_hit) const {
  Double_t scintillator_thickness; //[cm]
  const Int_t scintillator_class = ClassifyScintillator(single_hit);
  TVector3 dir = track_->GetInitialDirection().GetValue();
  Double_t energy_deposit = single_hit->GetEnergyDeposit();
  Double_t path_length;
  Double_t max_path_length = 100.0; //[cm]

  if (scintillator_class == 0) {
    scintillator_thickness = PM_INGRID_SCINTI_THICK / cm;
    if ( 18 <= single_hit->GetPlane() && single_hit->GetPlane() <= 21 ) {
      path_length = scintillator_thickness / std::abs(dir.X());
    } else {
      path_length = scintillator_thickness / std::abs(dir.Z());
    }
  } else if ( scintillator_class == 1 ) {
    scintillator_thickness = PM_SCIBAR_SCINTI_THICK / cm;
    path_length = scintillator_thickness / std::abs(dir.Z());
  } else if ( scintillator_class == 2 || scintillator_class == 4 ) {
    scintillator_thickness = WGS_SCINTI_THICK / cm;
    path_length = scintillator_thickness / std::abs(dir.X());
  } else if ( scintillator_class == 3 || scintillator_class == 5 ) {
    scintillator_thickness = WGS_SCINTI_THICK / cm;
    path_length = scintillator_thickness / std::abs(dir.Z());
  } else {
    return 999.0;
  }

  path_length = (path_length > max_path_length) ? max_path_length : path_length;
  return (energy_deposit / path_length);
}

std::vector<const B2HitSummary*> L2TrackAnalyzer::SelectHitsExcludingFarthest(const B2TrackSummary* track, int num_exclude_hits) const {
  std::vector<std::pair<Double_t, const B2HitSummary*>> hits_with_dist;
  const TVector3& initial_pos = track->GetInitialPosition().GetValue();

  for (auto it_hit = track->BeginHit(); auto hit = it_hit.Next(); ) {
    if (hit->GetDetectorId() != vertex_detector_) continue;
    if (ClassifyScintillator(hit) == -1) continue;

    Double_t dist = (hit->GetTrueAbsolutePosition().GetValue() - initial_pos).Mag();
    hits_with_dist.emplace_back(dist, hit);
  }

  // 距離大きい順にソート
  std::sort(hits_with_dist.begin(), hits_with_dist.end(), [](auto& a, auto& b) { return a.first > b.first; });

  // exclude_n個除外
  int hits_array_size = (int)hits_with_dist.size();
  if ( (num_exclude_hits + mucl_least_hits) <= hits_array_size) {
    hits_with_dist.erase(hits_with_dist.begin(), hits_with_dist.begin() + num_exclude_hits);
  } else if ( mucl_least_hits < hits_array_size ) {
    hits_with_dist.erase(hits_with_dist.begin(), hits_with_dist.begin() + mucl_least_hits);
  }

  // Hitだけ取り出す
  std::vector<const B2HitSummary*> selected_hits;
  for (auto& [dist, hit] : hits_with_dist) {
    selected_hits.push_back(hit);
  }
  return selected_hits;
}

std::pair<Double_t, Int_t> L2TrackAnalyzer::CalculateMuclFromHits(const std::vector<const B2HitSummary*>& hits) const {
  Double_t mucl_products = 1.0;
  Int_t num_calc_hits = 0;

  for (auto hit : hits) {
    Int_t scintillator_class = ClassifyScintillator(hit);
    Double_t confidence_level = 0;
    if ( (track_->GetAngle().GetValue() > 75) && (scintillator_class==2) ) {
      confidence_level = mucl_spline_.at(6)->Eval(CalculateDedx(hit));
    } else if ( (track_->GetAngle().GetValue() > 75) && (scintillator_class==4) ) {
      confidence_level = mucl_spline_.at(7)->Eval(CalculateDedx(hit));
    } else {
      confidence_level = mucl_spline_.at(scintillator_class)->Eval(CalculateDedx(hit));
    }

    if (confidence_level < 0) continue;
    mucl_products *= confidence_level;
    num_calc_hits++;
  }
  return {mucl_products, num_calc_hits};
}

Double_t L2TrackAnalyzer::CalculateMucl(const int& num_exclude_hits) const {
  Double_t mucl_products = 1.0;
  Int_t num_calc_hits = 0;

  // --- case: track が荷電パイオン ---
  if (B2Pdg::IsChargedPion(track_->GetParticlePdg())) {
    auto muon_track = SearchChildMuon(spill_);
    if (muon_track) {
      // 子ミューオンあり → 子ミューオンに除外ルール
      auto hits_mu = SelectHitsExcludingFarthest(muon_track, num_exclude_hits);
      auto [prod_mu, n_mu] = CalculateMuclFromHits(hits_mu);
      mucl_products *= prod_mu;
      num_calc_hits += n_mu;

      // 親パイオンは全ヒット
      std::vector<const B2HitSummary*> hits_pi;
      for (auto it_hit = track_->BeginHit(); auto hit = it_hit.Next(); ) {
        if (hit->GetDetectorId() != vertex_detector_) continue;
        if (ClassifyScintillator(hit) == -1) continue;
        hits_pi.push_back(hit);
      }
      auto [prod_pi, n_pi] = CalculateMuclFromHits(hits_pi);
      mucl_products *= prod_pi;
      num_calc_hits += n_pi;
    } else {
      // 子ミューオンなし → 親パイオンに除外ルール
      auto hits_pi = SelectHitsExcludingFarthest(track_, num_exclude_hits);
      auto [prod_pi, n_pi] = CalculateMuclFromHits(hits_pi);
      mucl_products *= prod_pi;
      num_calc_hits += n_pi;
    }
  }

  // --- case: track がそれ以外（muon, proton, etc.）---
  else {
    auto hits = SelectHitsExcludingFarthest(track_, num_exclude_hits);
    auto [prod, n] = CalculateMuclFromHits(hits);
    mucl_products *= prod;
    num_calc_hits += n;
  }

  // --- 補正 ---
  Double_t adjustment_factor = 0;
  for (Int_t i = 0; i < num_calc_hits; ++i) {
    adjustment_factor += std::pow(-std::log(mucl_products), i) / TMath::Factorial(i);
  }

  return mucl_products * adjustment_factor;
}