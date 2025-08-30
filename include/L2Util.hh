//
// Created by Daigo Hirata on 2025/08/29
//

#ifndef LIGHTB2_L2UTIL_HH
#define LIGHTB2_L2UTIL_HH

// ROOT include
#include <TTree.h>
#include <TVector3.h>

namespace L2Util {
  // The average direction of the incident neutrinos
  // Calculated with /hsm/nu/wagasci/dhirata/mc/event_selection/direction_avg.C
  extern const TVector3 nu_avg_dir;
  // // In Yasutome-san's doctral thesis p.127
  // static const ROOT::Math::XYZVector nu_avg_dir(-0.019972, -0.079947, 0.996599);
  
  void set_branch_status(TTree* tree_wgbm);
}

#endif // LIGHTB2_L2UTIL_HH