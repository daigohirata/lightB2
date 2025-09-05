//
// Created by Daigo Hirata on 2025/08/29
//

#include "L2FV.hh"

// system include
#include <iostream>

// ROOT include
#include <TVector3.h>

// B2MC inlcude
#include <B2Const.hh>
#include <B2Dimension.hh>

Double_t L2FV::PM_FV_MIN_X = -1., L2FV::PM_FV_MAX_X = -1.;
Double_t L2FV::PM_FV_MIN_Y = -1., L2FV::PM_FV_MAX_Y = -1.;
Double_t L2FV::PM_FV_MIN_Z = -1., L2FV::PM_FV_MAX_Z = -1.;
Double_t L2FV::UWG_FV_MIN_X = -1., L2FV::UWG_FV_MAX_X = -1.;
Double_t L2FV::UWG_FV_MIN_Y = -1., L2FV::UWG_FV_MAX_Y = -1.;
Double_t L2FV::UWG_FV_MIN_Z = -1., L2FV::UWG_FV_MAX_Z = -1.;
Double_t L2FV::DWG_FV_MIN_X = -1., L2FV::DWG_FV_MAX_X = -1.;
Double_t L2FV::DWG_FV_MIN_Y = -1., L2FV::DWG_FV_MAX_Y = -1.;
Double_t L2FV::DWG_FV_MIN_Z = -1., L2FV::DWG_FV_MAX_Z = -1.;
Double_t L2FV::PM_BOX_MIN_X = -1., L2FV::PM_BOX_MAX_X = -1.;
Double_t L2FV::PM_BOX_MIN_Y = -1., L2FV::PM_BOX_MAX_Y = -1.;
Double_t L2FV::PM_BOX_MIN_Z = -1., L2FV::PM_BOX_MAX_Z = -1.;
Double_t L2FV::UWG_BOX_MIN_X = -1., L2FV::UWG_BOX_MAX_X = -1.;
Double_t L2FV::UWG_BOX_MIN_Y = -1., L2FV::UWG_BOX_MAX_Y = -1.;
Double_t L2FV::UWG_BOX_MIN_Z = -1., L2FV::UWG_BOX_MAX_Z = -1.;
Double_t L2FV::DWG_BOX_MIN_X = -1., L2FV::DWG_BOX_MAX_X = -1.;
Double_t L2FV::DWG_BOX_MIN_Y = -1., L2FV::DWG_BOX_MAX_Y = -1.;
Double_t L2FV::DWG_BOX_MIN_Z = -1., L2FV::DWG_BOX_MAX_Z = -1.;
Double_t L2FV::BM_CV_MIN_X = -1., L2FV::BM_CV_MAX_X = -1.;
Double_t L2FV::BM_CV_MIN_Y = -1., L2FV::BM_CV_MAX_Y = -1.;
Double_t L2FV::WMN_CV_MIN_X = -1., L2FV::WMN_CV_MAX_X = -1.;
Double_t L2FV::WMN_CV_MIN_Z = -1., L2FV::WMN_CV_MAX_Z = -1.;
Double_t L2FV::WMS_CV_MIN_X = -1., L2FV::WMS_CV_MAX_X = -1.;
Double_t L2FV::WMS_CV_MIN_Z = -1., L2FV::WMS_CV_MAX_Z = -1.;

void L2FV::set_volume_constants(const std::string& geometry_dir) {
  B2Dimension dim(geometry_dir);
  TVector3 pos;

  /*** Proton Module ***/
  dim.GetPosPm(B2View::kTopView, 1, 2, pos);
  PM_FV_MIN_X = PROTON_MODULE_POS_X + pos.X() - 0.5 * PM_INGRID_SCINTI_LARGE;
  dim.GetPosPm(B2View::kTopView, 1, 29, pos);
  PM_FV_MAX_X = PROTON_MODULE_POS_X + pos.X() + 0.5 * PM_INGRID_SCINTI_LARGE;
  dim.GetPosPm(B2View::kSideView, 1, 2, pos);
  PM_FV_MIN_Y = PROTON_MODULE_POS_Y + pos.Y() - 0.5 * PM_INGRID_SCINTI_LARGE;
  dim.GetPosPm(B2View::kSideView, 1, 29, pos);
  PM_FV_MAX_Y = PROTON_MODULE_POS_Y + pos.Y() + 0.5 * PM_INGRID_SCINTI_LARGE;
  dim.GetPosPm(B2View::kTopView, 1, 0, pos);
  PM_FV_MIN_Z = PROTON_MODULE_POS_Z + pos.Z() + 0.5 * PM_INGRID_SCINTI_THICK;
  dim.GetPosPm(B2View::kSideView, 15, 0, pos);
  PM_FV_MAX_Z = PROTON_MODULE_POS_Z + pos.Z() + 0.5 * PM_INGRID_SCINTI_THICK;

  PM_BOX_MIN_X = PROTON_MODULE_POS_X - 0.5*PM_BOX_WIDTH;
  PM_BOX_MAX_X = PROTON_MODULE_POS_X + 0.5*PM_BOX_WIDTH;
  PM_BOX_MIN_Y = PROTON_MODULE_POS_Y - 0.5*PM_BOX_HEIGHT;
  PM_BOX_MAX_Y = PROTON_MODULE_POS_Y + 0.5*PM_BOX_HEIGHT;
  PM_BOX_MIN_Z = PROTON_MODULE_POS_Z - 0.5*PM_BOX_DEPTH;
  PM_BOX_MAX_Z = PROTON_MODULE_POS_Z + 0.5*PM_BOX_DEPTH;
  
  /*** WAGASCI Upstream ***/
  dim.GetPosWgs(B2View::kTopView, 0, 2, kGridLeftScintillator, pos);
  UWG_FV_MIN_X = WAGASCI_UPSTREAM_POS_X + pos.X() - 0.5 * WGS_SCINTI_THICK;
  dim.GetPosWgs(B2View::kTopView, 0, 17, kGridLeftScintillator, pos);
  UWG_FV_MAX_X = WAGASCI_UPSTREAM_POS_X + pos.X() + 0.5 * WGS_SCINTI_THICK;
  dim.GetPosWgs(B2View::kSideView, 0, 2, kGridLeftScintillator, pos);
  UWG_FV_MIN_Y = WAGASCI_UPSTREAM_POS_Y + pos.Y() - 0.5 * WGS_SCINTI_THICK;
  dim.GetPosWgs(B2View::kSideView, 0, 17, kGridLeftScintillator, pos);
  UWG_FV_MAX_Y = WAGASCI_UPSTREAM_POS_Y + pos.Y() + 0.5 * WGS_SCINTI_THICK;
  dim.GetPosWgs(B2View::kTopView, 1, 0, kPlaneScintillator, pos);
  UWG_FV_MIN_Z = WAGASCI_UPSTREAM_POS_Z + pos.Z() + 0.5 * WGS_SCINTI_THICK;
  dim.GetPosWgs(B2View::kSideView, 5, 0, kPlaneScintillator, pos);
  UWG_FV_MAX_Z = WAGASCI_UPSTREAM_POS_Z + pos.Z() + 0.5 * WGS_SCINTI_THICK;

  UWG_BOX_MIN_X = WAGASCI_UPSTREAM_POS_X - 0.5*WGS_WATER_BOX_WIDTH;
  UWG_BOX_MAX_X = WAGASCI_UPSTREAM_POS_X + 0.5*WGS_WATER_BOX_WIDTH;
  UWG_BOX_MIN_Y = WAGASCI_UPSTREAM_POS_Y - 0.5*WGS_WATER_BOX_HEIGHT;
  UWG_BOX_MAX_Y = WAGASCI_UPSTREAM_POS_Y + 0.5*WGS_WATER_BOX_HEIGHT;
  UWG_BOX_MIN_Z = WAGASCI_UPSTREAM_POS_Z - 0.5*WGS_WATER_BOX_DEPTH;
  UWG_BOX_MAX_Z = WAGASCI_UPSTREAM_POS_Z + 0.5*WGS_WATER_BOX_DEPTH;
  
  /*** WAGASCI Downstream ***/
  dim.GetPosWgs(B2View::kTopView, 0, 2, kGridLeftScintillator, pos);
  DWG_FV_MIN_X = WAGASCI_DOWNSTREAM_POS_X + pos.X() - 0.5 * WGS_SCINTI_THICK;
  dim.GetPosWgs(B2View::kTopView, 0, 17, kGridLeftScintillator, pos);
  DWG_FV_MAX_X = WAGASCI_DOWNSTREAM_POS_X + pos.X() + 0.5 * WGS_SCINTI_THICK;
  dim.GetPosWgs(B2View::kSideView, 0, 2, kGridLeftScintillator, pos);
  DWG_FV_MIN_Y = WAGASCI_DOWNSTREAM_POS_Y + pos.Y() - 0.5 * WGS_SCINTI_THICK;
  dim.GetPosWgs(B2View::kSideView, 0, 17, kGridLeftScintillator, pos);
  DWG_FV_MAX_Y = WAGASCI_DOWNSTREAM_POS_Y + pos.Y() + 0.5 * WGS_SCINTI_THICK;
  dim.GetPosWgs(B2View::kTopView, 1, 0, kPlaneScintillator, pos);
  DWG_FV_MIN_Z = WAGASCI_DOWNSTREAM_POS_Z + pos.Z() + 0.5 * WGS_SCINTI_THICK;
  dim.GetPosWgs(B2View::kSideView, 5, 0, kPlaneScintillator, pos);
  DWG_FV_MAX_Z = WAGASCI_DOWNSTREAM_POS_Z + pos.Z() + 0.5 * WGS_SCINTI_THICK;

  DWG_BOX_MIN_X = WAGASCI_DOWNSTREAM_POS_X - 0.5*WGS_WATER_BOX_WIDTH;
  DWG_BOX_MAX_X = WAGASCI_DOWNSTREAM_POS_X + 0.5*WGS_WATER_BOX_WIDTH;
  DWG_BOX_MIN_Y = WAGASCI_DOWNSTREAM_POS_Y - 0.5*WGS_WATER_BOX_HEIGHT;
  DWG_BOX_MAX_Y = WAGASCI_DOWNSTREAM_POS_Y + 0.5*WGS_WATER_BOX_HEIGHT;
  DWG_BOX_MIN_Z = WAGASCI_DOWNSTREAM_POS_Z - 0.5*WGS_WATER_BOX_DEPTH;
  DWG_BOX_MAX_Z = WAGASCI_DOWNSTREAM_POS_Z + 0.5*WGS_WATER_BOX_DEPTH;
  
  /*** Baby MIND ***/
  BM_CV_MIN_X = BABYMIND_POS_X - 1300;  BM_CV_MAX_X = BABYMIND_POS_X + 1300;
  BM_CV_MIN_Y = BABYMIND_POS_Y - 900;   BM_CV_MAX_Y = BABYMIND_POS_Y + 900;
  
  /*** Wall-MRD ***/
  WMN_CV_MIN_X = WALLMRD_NORTH_POS_X - 170;  WMN_CV_MAX_X = WALLMRD_NORTH_POS_X + 170;
  WMN_CV_MIN_Z = WALLMRD_NORTH_POS_Z - 750;  WMN_CV_MAX_Z = WALLMRD_NORTH_POS_Z + 750;
  WMS_CV_MIN_X = WALLMRD_SOUTH_POS_X - 170;  WMS_CV_MAX_X = WALLMRD_SOUTH_POS_X + 170;
  WMS_CV_MIN_Z = WALLMRD_SOUTH_POS_Z - 750;  WMS_CV_MAX_Z = WALLMRD_SOUTH_POS_Z + 750;

  volume_constants_is_set_ = true;
}

B2Detector L2FV::CheckInsideFV(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos) {
  if ( is_inside_pm_fv(x_pos, y_pos, z_pos) ) {
    return B2Detector::kProtonModule;
  } else if ( is_inside_uwg_fv(x_pos, y_pos, z_pos) ) {
    return B2Detector::kWagasciUpstream;
  } else if ( is_inside_dwg_fv(x_pos, y_pos, z_pos) ) {
    return B2Detector::kWagasciDownstream;
  } else {
    return B2Detector::kUnknownDetector;
  }
}

B2Detector L2FV::CheckInsideFV(const TVector3& position) {
  return CheckInsideFV(position.X(), position.Y(), position.Z());
}

Bool_t L2FV::is_inside_pm_fv(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos) {
  if (!volume_constants_is_set_) {
    std::cout << "[Warning] Volume constants is not set." << std::endl;
    return false;
  }
  if (PM_FV_MIN_X < x_pos && x_pos < PM_FV_MAX_X &&
      PM_FV_MIN_Y < y_pos && y_pos < PM_FV_MAX_Y &&
      PM_FV_MIN_Z < z_pos && z_pos < PM_FV_MAX_Z) {
    return true;
  } else {
    return false;
  }
}

Bool_t L2FV::is_inside_pm_fv(const TVector3& position) {
  return is_inside_pm_fv(position.X(), position.Y(), position.Z());
}

Bool_t L2FV::is_inside_uwg_fv(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos) {
  if (!volume_constants_is_set_) {
    std::cout << "[Warning] Volume constants is not set." << std::endl;
    return false;
  }
  if (UWG_FV_MIN_X < x_pos && x_pos < UWG_FV_MAX_X &&
      UWG_FV_MIN_Y < y_pos && y_pos < UWG_FV_MAX_Y &&
      UWG_FV_MIN_Z < z_pos && z_pos < UWG_FV_MAX_Z) {
    return true;
  } else {
    return false;
  }
}

Bool_t L2FV::is_inside_uwg_fv(const TVector3& position) {
  return is_inside_uwg_fv(position.X(), position.Y(), position.Z());
}

Bool_t L2FV::is_inside_dwg_fv(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos) {
  if (!volume_constants_is_set_) {
    std::cout << "[Warning] Volume constants is not set." << std::endl;
    return false;
  }
  if (DWG_FV_MIN_X < x_pos && x_pos < DWG_FV_MAX_X && 
      DWG_FV_MIN_Y < y_pos && y_pos < DWG_FV_MAX_Y && 
      DWG_FV_MIN_Z < z_pos && z_pos < DWG_FV_MAX_Z) {
    return true;
  } else {
    return false;
  }
}

Bool_t L2FV::is_inside_dwg_fv(const TVector3& position) {
  return is_inside_dwg_fv(position.X(), position.Y(), position.Z());
}

Bool_t L2FV::IsContained(const B2Detector& vertex_detector, const TVector3& stop_position) {
  if (vertex_detector == B2Detector::kProtonModule) {
    return is_inside_pm(stop_position);
  } else if (vertex_detector == B2Detector::kWagasciUpstream) {
    return is_inside_uwg(stop_position);
  } else if (vertex_detector == B2Detector::kWagasciDownstream) {
    return is_inside_dwg(stop_position);
  } else {
    return false;
  }
}

Bool_t L2FV::is_inside_pm(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos) {
  if (!volume_constants_is_set_) {
    std::cout << "[Warning] Volume constants is not set." << std::endl;
    return false;
  }
  if (PM_BOX_MIN_X < x_pos && x_pos < PM_BOX_MAX_X &&
      PM_BOX_MIN_Y < y_pos && y_pos < PM_BOX_MAX_Y &&
      PM_BOX_MIN_Z < z_pos && z_pos < PM_BOX_MAX_Z) {
    return true;
  } else {
    return false;
  }
}

Bool_t L2FV::is_inside_pm(const TVector3& position) {
  return is_inside_pm(position.X(), position.Y(), position.Z());
}

Bool_t L2FV::is_inside_uwg(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos) {
  if (!volume_constants_is_set_) {
    std::cout << "[Warning] Volume constants is not set." << std::endl;
    return false;
  }
  if (UWG_BOX_MIN_X < x_pos && x_pos < UWG_BOX_MAX_X &&
      UWG_BOX_MIN_Y < y_pos && y_pos < UWG_BOX_MAX_Y &&
      UWG_BOX_MIN_Z < z_pos && z_pos < UWG_BOX_MAX_Z) {
    return true;
  } else {
    return false;
  }
}

Bool_t L2FV::is_inside_uwg(const TVector3& position) {
  return is_inside_uwg(position.X(), position.Y(), position.Z());
}

Bool_t L2FV::is_inside_dwg(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos) {
  if (!volume_constants_is_set_) {
    std::cout << "[Warning] Volume constants is not set." << std::endl;
    return false;
  }
  if (DWG_BOX_MIN_X < x_pos && x_pos < DWG_BOX_MAX_X && 
      DWG_BOX_MIN_Y < y_pos && y_pos < DWG_BOX_MAX_Y && 
      DWG_BOX_MIN_Z < z_pos && z_pos < DWG_BOX_MAX_Z) {
    return true;
  } else {
    return false;
  }
}

Bool_t L2FV::is_inside_dwg(const TVector3& position) {
  return is_inside_dwg(position.X(), position.Y(), position.Z());
}

Bool_t L2FV::is_inside_bm_cv(const Double_t& x_pos, const Double_t& y_pos) {
  if (!volume_constants_is_set_) {
    std::cout << "[Warning] Volume constants is not set." << std::endl;
    return false;
  }
  if (BM_CV_MIN_X < x_pos && x_pos < BM_CV_MAX_X && 
      BM_CV_MIN_Y < y_pos && y_pos < BM_CV_MAX_Y) {
    return true;
  } else {
    return false;
  }
}

Bool_t L2FV::is_inside_bm_cv(const TVector3& position) {
  return is_inside_bm_cv(position.X(), position.Y());
}

Bool_t L2FV::is_inside_wmn_cv(const Double_t& x_pos, const Double_t& z_pos) {
  if (!volume_constants_is_set_) {
    std::cout << "[Warning] Volume constants is not set." << std::endl;
    return false;
  }
  if (WMN_CV_MIN_X < x_pos && x_pos < WMN_CV_MAX_X && 
      WMN_CV_MIN_Z < z_pos && z_pos < WMN_CV_MAX_Z) {
    return true;
  } else {
    return false;
  }
}

Bool_t L2FV::is_inside_wmn_cv(const TVector3& position) {
  return is_inside_wmn_cv(position.X(), position.Z());
}

Bool_t L2FV::is_inside_wms_cv(const Double_t& x_pos, const Double_t& z_pos) {
  if (!volume_constants_is_set_) {
    std::cout << "[Warning] Volume constants is not set." << std::endl;
    return false;
  }
  if (WMS_CV_MIN_X < x_pos && x_pos < WMS_CV_MAX_X && 
      WMS_CV_MIN_Z < z_pos && z_pos < WMS_CV_MAX_Z) {
    return true;
  } else {
    return false;
  }
}

Bool_t L2FV::is_inside_wms_cv(const TVector3& position) {
  return is_inside_wms_cv(position.X(), position.Z());
}