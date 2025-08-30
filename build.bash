#/bin/bash

export CMAKE_PREFIX_PATH=/sw/packages/root/6.32.04/cmake/

rm -rf /home/nu/dhirata/wg_app/LightB2/build
mkdir /home/nu/dhirata/wg_app/LightB2/build
cd /home/nu/dhirata/wg_app/LightB2/build

cmake ..
make

export