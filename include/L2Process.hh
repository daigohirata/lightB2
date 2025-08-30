//
// Created by Daigo Hirata on 2025/08/29
//

#ifndef LIGHTB2_L2PROCESS_HH
#define LIGHTB2_L2PROCESS_HH

#include "L2Writer.hh"

Int_t process(const int& file_number, L2Writer& writer, const std::string& gemetry_dir,
              const std::string& spline_file_path, const int& bm_required_hit);

#endif // LIGHTB2_L2PROCESS_HH