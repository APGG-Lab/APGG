#!/bin/bash

echo Compiling C++-code ...

cd bin

g++  -O3 -std=c++17  -c ../APGG/*.cpp
g++  -O3 -std=c++17  -c ../APGG/optimizer/*.cpp
g++  -O3 -std=c++17  -c ../APGG/optimizer/mutators/*.cpp
g++  -O3 -std=c++17  -c ../APGG/optimizer/selectors/*.cpp
g++  -O3 -std=c++17 -c ../APGG/optimizer/repopulators/*.cpp

cd ../

echo Linking ...

gcc -O3 -o bin/apgg_release bin/*.o -std=c++17 -lstdc++ -lm -lstdc++fs

rm bin/*.o
