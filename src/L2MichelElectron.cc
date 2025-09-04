//
// Created by Daigo Hirata on 2025/09/05
//

#include "L2MichelElectron.hh"

// ROOT include
#include <TVector3.h>

// B2MC include
#include <B2SpillSummary.hh>
#include <B2VertexSummary.hh>
#include <B2HitSummary.hh>

L2MichelElectron::L2MichelElectron(const B2SpillSummary* spill,
                                   B2Detector vertex_detector)
  : spill_(spill), vertex_detector_(vertex_detector) {};

Bool_t L2MichelElectron::SearchAroundVertex() {
  auto vertex = (B2VertexSummary*)spill_->GetTrueVertices().At(0);
  const TVector3& vertex_pos = vertex->GetAbsolutePosition().GetValue();
  
  double me_hits_counter = 0;

  for (auto it_hit = spill_->BeginHit(); auto hit = it_hit.Next(); ) {
    if ( hit->GetDetectorId() != vertex_detector_ ||
         hit->GetTrueTimeNs() < hit_time_threshold ) continue;
    
    double dist = (hit->GetTrueAbsolutePosition().GetValue() - vertex_pos).Mag();
    if (dist < radius_from_vertex_) 
      me_hits_counter++;
  }

  return (me_hits_counter >= num_required_hits_);
}

Bool_t L2MichelElectron::SearchAroundVertex() {
  auto vertex = (B2VertexSummary*)spill_->GetTrueVertices().At(0);
  return SearchAroundPoint(vertex->GetAbsolutePosition().GetValue(), radius_from_vertex_);
}

Bool_t L2MichelElectron::SearchAroundTrackEnd(const B2TrackSummary* track) {
  return SearchAroundPoint(track->GetFinalPosition().GetValue(), radius_from_trackend_);
}

Bool_t L2MichelElectron::SearchAroundPoint(const TVector3& point, const double search_radius){  
  double me_hits_counter = 0;

  for (auto it_hit = spill_->BeginHit(); auto hit = it_hit.Next(); ) {
    if ( hit->GetDetectorId() != vertex_detector_ ||
         hit->GetTrueTimeNs() < hit_time_threshold ) continue;
    
    double dist = (hit->GetTrueAbsolutePosition().GetValue() - point).Mag();
    if (dist < radius_from_vertex_) 
      me_hits_counter++;
  }

  return (me_hits_counter >= num_required_hits_);
};

