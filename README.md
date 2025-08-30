# LightB2

LightB2 is a lightweight analysis framework for the WAGASCI experiment.  
It is designed to read B2MC simulation output (ROOT files), process the detector geometry and event summaries, and produce reduced analysis-level outputs.

## Features
- Interface to **B2MC** libraries  
- ROOT-based I/O and histograms  
- Simple modular structure for extending analysis logic  
- Example executables for running on B2MC ROOT files  

## Requirements
- C++17 or later  
- [ROOT](https://root.cern/) (>= 6.18 recommended)  
- [Geant4](https://geant4.web.cern.ch/)  
- Boost (program_options)  

Make sure that ROOT and Geant4 are properly sourced before building.

## Build Instructions

```bash
# Clone repository
git clone https://github.com/daigohirata/lightB2.git
cd lightB2

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
make -j4
```

## Usage

Run the main executable with B2MC ROOT input files:
```bash
./lightb2 /path/to/b2mc.root -o output.root
```

Options:

- `-o <file> : specify output file name`

- `-n <N> : process only first N events`


## Repository Structure
``` bash
LightB2/
├── src/        # Source codes
├── include/    # Header files
├── CMakeLists.txt
└── README.md
```

## License
This software is intended for internal use within the T2K collaboration only.  
Redistribution or use outside the collaboration is not permitted without prior approval from the authors.
