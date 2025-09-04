//
// Created by Daigo Hirata on 2025/09/05
//

#ifndef LIGHTB2_L2MICHELELECTRON_HH
#define LIGHTB2_L2MICHELELECTRON_HH

// B2MC include
#include <B2SpillSummary.hh>
#include <B2TrackSummary.hh>
#include <B2Enum.hh>

class L2MichelElectron {
public:
  L2MichelElectron(const B2SpillSummary* spill,
                   B2Detector vertex_detector);
  Bool_t SearchAroundVertex();
  Bool_t SearchAroundTrackEnd(const B2TrackSummary* track);
  Bool_t SearchAroundPoint(const TVector3& point, const double search_radius);


private:
  const B2SpillSummary* spill_;
  B2Detector vertex_detector_;
  const double radius_from_vertex_ = 30.0 * cm;
  const double radius_from_trackend_ = 15.0 * cm;
  const double hit_time_threshold = 120.0; //[ns]
  const int num_required_hits_ = 3;
};


#endif // LIGHTB2_L2MICHELELECTRON_HH