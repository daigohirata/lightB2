//
// Created by Daigo Hirata on 2025/08/29
//

#include "L2Process.hh"

// system include
#include <iostream>

// ROOT include
#include <TTree.h>

// B2MC include
#include <B2Enum.hh>
#include <B2Pdg.hh>
#include <B2SpillSummary.hh>
#include <B2TrackSummary.hh>
#include <B2VertexSummary.hh>
#include <B2HitSummary.hh>

// project include
#include "L2Writer.hh"
#include "L2TrackAnalyzer.hh"
#include "L2FV.hh"
#include "L2Util.hh"
#include "L2MichelElectron.hh"

// process each files
Int_t process(const int& file_number, L2Writer& writer, const std::string& geometry_dir,
              const std::string& spline_file_path, const int& bm_required_hit, const int& num_exclude_hits) {
  // TString file_name = "/group/nu/ninja/work/han/mc/e71a/3_b2mc/out/mc." + TString::Format("%03d", file_number) + ".root";
  TString file_name = "/hsm/nu/wagasci/dhirata/mc/250kA/2_B2MC/out/b2mc." + TString::Format("%03d", file_number) + ".root";

  std::cout << "Processing " << file_name << std::endl;
  
  TFile *file=TFile::Open(file_name);
  if (!file || file->IsZombie()) {
      std::cerr << "Error: Failed to open file: " << file_name << std::endl;
      return 999;
  }
  TTree *tree_wgbm = (TTree*)file->Get("tree");
  if ( !tree_wgbm ) {
      std::cout << "Error: Failed to open TTree: tree" << std::endl;
      return 999;
  }

  // L2Util::set_branch_status(tree_wgbm);
  B2SpillSummary* spill = nullptr;
  tree_wgbm->SetBranchAddress("spill", &spill);

  // event loop
  Int_t nEntries = tree_wgbm->GetEntries();
  for (Int_t iEntry=0; iEntry<nEntries; ++iEntry){ 
    writer.Clear();
    tree_wgbm->GetEntry(iEntry);
    
    // vertex check
    auto vertex = (B2VertexSummary*)spill->GetTrueVertices().At(0);
    const TVector3& abs_pos = vertex->GetAbsolutePosition().GetValue();
    B2Detector vertex_detector = L2FV::CheckInsideFV(abs_pos);
    if (vertex_detector == B2Detector::kUnknownDetector) continue;

    L2MichelElectron me_seacher(spill, vertex_detector);

    writer.file_id_ = file_number;
    writer.event_id_ = iEntry;
    writer.incoming_neutrino_ = vertex->GetIncomingParticlePdg();
    writer.mode_ = vertex->GetInteractionType();
    writer.vertex_detector_ = (Int_t)vertex_detector;
    writer.num_delayed_hits_vertex_ = me_seacher.SearchAroundVertex();

    // track loop
    for (auto it_track = spill->BeginTrueTrack(); const auto* track = it_track.Next(); ) {
      if (track->GetTrackType() != B2TrackType::kPrimaryTrack) continue;
      L2TrackAnalyzer analyzer(spill, track, vertex_detector, spline_file_path);
      
      if ( B2Pdg::IsChargedPion(track->GetParticlePdg()) ) 
        writer.num_fs_pion_++;

      if ( analyzer.HasVertexDetectorHit() ) {
        writer.has_vd_hits_.emplace_back( true );
        writer.num_hit_track_++; 
      } else {
        writer.has_vd_hits_.emplace_back( false );
      }

      const TVector3& initial_pos = track->GetInitialPosition().GetValue();
      const TVector3& final_pos = track->GetFinalPosition().GetValue();
      const TVector3& dir = track->GetInitialDirection().GetValue();
      Double_t cos_theta = dir.X()*L2Util::nu_avg_dir.X() + dir.Y()*L2Util::nu_avg_dir.Y() + dir.Z()*L2Util::nu_avg_dir.Z();

      writer.particle_pdg_.emplace_back( (Int_t)track->GetParticlePdg() );
      writer.length_.emplace_back( (initial_pos - final_pos).Mag() );
      writer.momentum_.emplace_back( track->GetInitialAbsoluteMomentum().GetValue() );
      writer.cos_theta_.emplace_back( cos_theta );
      writer.hit_muon_detector_.emplace_back( analyzer.HitMuonDetector(bm_required_hit) );
      writer.num_hits_.emplace_back( track->GetNumHits(B2View::kUnknownView, vertex_detector, 0) );
      
      auto child_muon = analyzer.SearchChildMuon(spill);
      if ( B2Pdg::IsChargedPion(track->GetParticlePdg()) && child_muon) {
        writer.is_contained_.emplace_back( L2FV::IsContained(vertex_detector, analyzer.SearchChildMuon(spill)->GetFinalPosition().GetValue()) );
      } else {
        writer.is_contained_.emplace_back( L2FV::IsContained(vertex_detector, final_pos) );
      }

      if ( writer.is_contained_.back() ) {
        writer.mucl_.emplace_back( analyzer.CalculateMucl(num_exclude_hits) );
        writer.num_delayed_hits_track_.emplace_back( me_seacher.SearchAroundTrackEnd(track) );
      } else {
        writer.mucl_.emplace_back( analyzer.CalculateMucl(0) );
        writer.num_delayed_hits_track_.emplace_back( -1 );
      }
    }

    writer.Fill();
  }
  file->Close();

  delete file;
  return 0;
}
