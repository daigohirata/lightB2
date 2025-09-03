//
// Created by Daigo Hirata on 2025/08/29
//

// system include
#include <iostream>
#include <string>

// boost include
#include <boost/program_options.hpp>

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
#include "L2Process.hh"
#include "L2Writer.hh"
#include "L2TrackAnalyzer.hh"
#include "L2FV.hh"
#include "L2Util.hh"

namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  int start = 0;
  int end   = 100;
  int bm_required_hit = 3;
  int num_exclude_hits = 3;
  std::string geometry_dir = "/home/nu/dhirata/wg_app/WagasciMC/etc/wagasci/b2/geometry";
  std::string spline_file_path = "/home/nu/dhirata/wg_app/LightB2/data/spline/mucl_spline_angle_correction_dE_extention_pm_wg_tuned.root";
  std::string output_dir = "/hsm/nu/wagasci/dhirata/mc/PID/2_de_dx/";

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "print help message")
    ("start", po::value<int>(&start)->default_value(start), "first file number")
    ("end",   po::value<int>(&end)->default_value(end), "last file number")
    ("bm-required-hit", po::value<int>(&bm_required_hit)->default_value(bm_required_hit), "required BM hit")
    ("mucl-ignore-hits", po::value<int>(&num_exclude_hits)->default_value(num_exclude_hits), "number of hits ignored in mucl calculation")
    ("geometry-dir", po::value<std::string>(&geometry_dir)->default_value(geometry_dir), "path to geometry file directory")
    ("spline-file", po::value<std::string>(&spline_file_path)->default_value(spline_file_path), "path to mucl spline file")
    ("output-dir", po::value<std::string>(&output_dir)->default_value(output_dir), "output directory");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 0;
  }

  L2FV::set_volume_constants(geometry_dir);

  std::string out_file_name = output_dir + "lightB2_" +
                              std::to_string(start) + "-" +
                              std::to_string(end) + ".root";
  L2Writer writer(out_file_name);
  
  int nSkippedFiles = 0;
  for (int num=start; num<end; ++num) {
    if ( process(num, 
                 writer, 
                 geometry_dir, 
                 spline_file_path, 
                 bm_required_hit, 
                 num_exclude_hits)==999 )
      std::cout << ++nSkippedFiles << " file skipped." << std::endl;
  }
  
  writer.Write();

  return 0;
}