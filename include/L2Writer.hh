//
// Created by Daigo Hirata on 2025/08/29
//

#ifndef LIGHTB2_L2WRITER_HH
#define LIGHTB2_L2WRITER_HH

// system include
#include <vector>

// ROOT include
#include <TFile.h>
#include <TTree.h>

// B2MC include
#include <B2Enum.hh>

class L2Writer {
public:
  Int_t file_id_;
  Int_t event_id_;
  Int_t incoming_neutrino_;
  Int_t mode_;
  Int_t vertex_detector_;
  Int_t num_fs_pion_;
  Int_t num_hit_track_;
  Bool_t has_vertex_me_;
  std::vector<Int_t> particle_pdg_;
  std::vector<Double_t> length_;
  std::vector<Double_t> momentum_;
  std::vector<Double_t> cos_theta_;
  std::vector<Int_t> hit_muon_detector_;
  std::vector<Double_t> mucl_;
  std::vector<Bool_t> is_contained_;
  std::vector<Bool_t> has_track_me_;
  std::vector<Int_t> num_hits_;

  std::unique_ptr<TFile> outfile_;
  TTree *tree_;

  explicit L2Writer(const TString& filename);

  ~L2Writer();

  void Clear();

  void Fill();

  void Write();
};

#endif // LIGHTB2_L2WRITER_HH