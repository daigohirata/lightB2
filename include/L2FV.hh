//
// Created by Daigo Hirata on 2025/08/29
//

#ifndef LIGHTB2_L2FV_HH
#define LIGHTB2_L2FV_HH

// ROOT include
#include <TVector3.h>

// B2MC include
#include <B2Enum.hh>

namespace L2FV {
  // Definition of fidicial volumes of target detectors
  extern Double_t PM_FV_MIN_X, PM_FV_MAX_X;
  extern Double_t PM_FV_MIN_Y, PM_FV_MAX_Y;
  extern Double_t PM_FV_MIN_Z, PM_FV_MAX_Z;

  extern Double_t UWG_FV_MIN_X, UWG_FV_MAX_X;
  extern Double_t UWG_FV_MIN_Y, UWG_FV_MAX_Y;
  extern Double_t UWG_FV_MIN_Z, UWG_FV_MAX_Z;

  extern Double_t DWG_FV_MIN_X, DWG_FV_MAX_X;
  extern Double_t DWG_FV_MIN_Y, DWG_FV_MAX_Y;
  extern Double_t DWG_FV_MIN_Z, DWG_FV_MAX_Z;

  extern Double_t PM_BOX_MIN_X, PM_BOX_MAX_X;
  extern Double_t PM_BOX_MIN_Y, PM_BOX_MAX_Y;
  extern Double_t PM_BOX_MIN_Z, PM_BOX_MAX_Z;

  extern Double_t UWG_BOX_MIN_X, UWG_BOX_MAX_X;
  extern Double_t UWG_BOX_MIN_Y, UWG_BOX_MAX_Y;
  extern Double_t UWG_BOX_MIN_Z, UWG_BOX_MAX_Z;

  extern Double_t DWG_BOX_MIN_X, DWG_BOX_MAX_X;
  extern Double_t DWG_BOX_MIN_Y, DWG_BOX_MAX_Y;
  extern Double_t DWG_BOX_MIN_Z, DWG_BOX_MAX_Z;

  extern Double_t BM_CV_MIN_X, BM_CV_MAX_X;
  extern Double_t BM_CV_MIN_Y, BM_CV_MAX_Y;

  extern Double_t WMN_CV_MIN_X, WMN_CV_MAX_X;
  extern Double_t WMN_CV_MIN_Z, WMN_CV_MAX_Z;
  extern Double_t WMS_CV_MIN_X, WMS_CV_MAX_X;
  extern Double_t WMS_CV_MIN_Z, WMS_CV_MAX_Z;

  static Bool_t volume_constants_is_set_ = false;

  void set_volume_constants(const std::string& geometry_dir);

  B2Detector CheckInsideFV(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos);
  B2Detector CheckInsideFV(const TVector3& position);

  Bool_t is_inside_pm_fv(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos);
  Bool_t is_inside_pm_fv(const TVector3& position);

  Bool_t is_inside_uwg_fv(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos);
  Bool_t is_inside_uwg_fv(const TVector3& position);

  Bool_t is_inside_dwg_fv(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos);
  Bool_t is_inside_dwg_fv(const TVector3& position);

  Bool_t IsContained(const B2Detector& vertex_detector, const TVector3& stop_position);

  Bool_t is_inside_pm(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos);
  Bool_t is_inside_pm(const TVector3& position);

  Bool_t is_inside_uwg(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos);
  Bool_t is_inside_uwg(const TVector3& position);

  Bool_t is_inside_dwg(const Double_t& x_pos, const Double_t& y_pos, const Double_t& z_pos);
  Bool_t is_inside_dwg(const TVector3& position);

  Bool_t is_inside_bm_cv(const Double_t& x_pos, const Double_t& y_pos);
  Bool_t is_inside_bm_cv(const TVector3& position);

  Bool_t is_inside_wmn_cv(const Double_t& x_pos, const Double_t& z_pos);
  Bool_t is_inside_wmn_cv(const TVector3& position);

  Bool_t is_inside_wms_cv(const Double_t& x_pos, const Double_t& z_pos);
  Bool_t is_inside_wms_cv(const TVector3& position);
}

#endif // LIGHTB2_L2FV_HH