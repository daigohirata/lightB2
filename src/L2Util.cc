//
// Created by Daigo Hirata on 2025/08/29
//

#include "L2Util.hh"

// ROOT include
#include <TTree.h>
#include <TVector3.h>

const TVector3 L2Util::nu_avg_dir(-0.0257672, -0.0886532, 0.995729);

void L2Util::set_branch_status(TTree* tree_wgbm) {
  tree_wgbm->SetBranchStatus("*",0);
  tree_wgbm->SetBranchStatus("spill", 1);
  tree_wgbm->SetBranchStatus("true_vertices_", 1);
  tree_wgbm->SetBranchStatus("true_vertices_.fUniqueID", 1);
  tree_wgbm->SetBranchStatus("true_vertices_.fBits", 1);
  tree_wgbm->SetBranchStatus("true_vertices_.incoming_particle_pdg_", 1);
  tree_wgbm->SetBranchStatus("true_vertices_.interaction_type_", 1);
  tree_wgbm->SetBranchStatus("true_vertices_.outgoing_tracks_*", 1);
  tree_wgbm->SetBranchStatus("true_vertices_.absolute_position_.value_", 1);
  tree_wgbm->SetBranchStatus("true_tracks_", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.fUniqueID", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.fBits", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.hits_.*", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.track_id_", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.initial_momentum_.value_", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.particle_pdg_", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.type_", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.initial_direction_.value_", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.initial_absolute_momentum_.value_", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.initial_position_.value_", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.final_position_.value_", 1);
  tree_wgbm->SetBranchStatus("true_tracks_.angle_.value_", 1);
  tree_wgbm->SetBranchStatus("hits_", 1);
  tree_wgbm->SetBranchStatus("hits_.fUniqueID", 1);
  tree_wgbm->SetBranchStatus("hits_.fBits", 1);
  tree_wgbm->SetBranchStatus("hits_.detector_", 1);
  tree_wgbm->SetBranchStatus("hits_.view_", 1);
  tree_wgbm->SetBranchStatus("hits_.bunch_", 1);
  tree_wgbm->SetBranchStatus("hits_.high_gain_peu_.value[2]");
  tree_wgbm->SetBranchStatus("hits_.low_gain_peu_.value[2]");
  tree_wgbm->SetBranchStatus("hits_.plane_grid_");
  tree_wgbm->SetBranchStatus("hits_.scintillator_type_");
  tree_wgbm->SetBranchStatus("hits_.plane_");
  tree_wgbm->SetBranchStatus("hits_.slot_.value[2]");
  tree_wgbm->SetBranchStatus("hits_.energy_deposit_");
  tree_wgbm->SetBranchStatus("hits_.absolute_position_true_.value_");
  tree_wgbm->SetBranchStatus("hits_.relative_position_true_.value_");
}