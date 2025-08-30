//
// Created by Daigo Hirata on 2025/08/29
//

// system include
#include <vector>
#include <iostream>

// ROOT include
#include <TFile.h>
#include <TTree.h>

// B2MC include
#include <B2Enum.hh>

// project include
#include "L2Writer.hh"

L2Writer::L2Writer(const TString& filename) {
  outfile_ = std::make_unique<TFile>(filename, "RECREATE");
  tree_ = new TTree("l2tree", "Light TTree fomat for WGBM analysis");

  tree_->Branch("file_id",           &file_id_);
  tree_->Branch("event_id",          &event_id_);
  tree_->Branch("incoming_neutrino", &incoming_neutrino_);
  tree_->Branch("mode",              &mode_);
  tree_->Branch("vertex_detector",   &vertex_detector_);
  tree_->Branch("num_fs_pion",       &num_fs_pion_);
  tree_->Branch("num_hit_track",     &num_hit_track_);
  tree_->Branch("pdg",               &particle_pdg_);
  tree_->Branch("length",            &length_);
  tree_->Branch("momentum",          &momentum_);
  tree_->Branch("cos_theta",         &cos_theta_);
  tree_->Branch("hit_muon_detector", &hit_muon_detector_);
  tree_->Branch("mucl",              &mucl_);
  tree_->Branch("is_contained",      &is_contained_);

  Clear();
}

L2Writer::~L2Writer() {
  std::cout << "[L2Writer] Destructor called." << std::endl;
  // delete tree_;   ←消す
  std::cout << "[L2Writer] Destructor finished." << std::endl;
}

void L2Writer::Clear() {
  file_id_ = -1;
  event_id_ = -1;
  incoming_neutrino_ = 0;
  mode_ = 0;
  vertex_detector_ = -2;
  num_fs_pion_ = 0;
  num_hit_track_ = 0;
  particle_pdg_.clear();
  length_.clear();
  momentum_.clear();
  cos_theta_.clear();
  hit_muon_detector_.clear();
  mucl_.clear();
  is_contained_.clear();
}

void L2Writer::Fill() {
  tree_->Fill();
  Clear();
}

void L2Writer::Write() {
  outfile_->cd();
  tree_->Write();
  outfile_->Close();
  std::cout << "[L2Writer] Succcessfully done." << std::endl;
}