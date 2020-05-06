#!/bin/bash
BUILD_OPTIONS="-Wall -O3 -std=c++17"

echo Compiling C++-code ...

cd bin

g++ ${BUILD_OPTIONS}  -c ../APGG/*.cpp
g++ ${BUILD_OPTIONS}  -c ../APGG/archivers/*.cpp
g++ ${BUILD_OPTIONS}  -c ../APGG/grids/*.cpp
g++ ${BUILD_OPTIONS}  -c ../APGG/payoffcalculators/*.cpp
g++ ${BUILD_OPTIONS}  -c ../APGG/optimizer/*.cpp
g++ ${BUILD_OPTIONS}  -c ../APGG/optimizer/mutators/*.cpp
g++ ${BUILD_OPTIONS}  -c ../APGG/optimizer/selectors/*.cpp
g++ ${BUILD_OPTIONS}  -c ../APGG/optimizer/repopulators/*.cpp

cd ../

echo Linking ...

gcc ${BUILD_OPTIONS} -o bin/apgg_release bin/*.o -lstdc++ -lm -lstdc++fs

rm bin/*.o

