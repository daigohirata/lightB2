cmake_minimum_required(VERSION 3.12)
project(LightB2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost
find_package(Boost REQUIRED COMPONENTS program_options)

# ROOT
find_package(ROOT 6.18 CONFIG REQUIRED)
include(${ROOT_USE_FILE})

# Geant4
find_package(Geant4 REQUIRED)

# include directories
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${Boost_INCLUDE_DIRS}
  ${ROOT_INCLUDE_DIRS}
  ${Geant4_USE_FILES}
  /home/nu/dhirata/wg_app/WagasciMC/include/wagasci/b2
)

add_library(l2core
  src/L2FV.cc
  src/L2Process.cc
  src/L2TrackAnalyzer.cc
  src/L2Util.cc
  src/L2Writer.cc
)

# link
target_link_libraries(l2core
  ${Boost_LIBRARIES}
  ${Geant4_LIBRARIES}
  /home/nu/dhirata/wg_app/WagasciMC/lib/wagasci/b2/libB2MC.so
)

# executable
add_executable(lightb2 src/main.cc)

target_link_libraries(lightb2
  PRIVATE
    l2core
    Boost::program_options
    ROOT::Core
    ROOT::RIO
    ROOT::Tree
    ROOT::Hist
    ROOT::Graf
    ROOT::Gpad
    ROOT::Physics
)