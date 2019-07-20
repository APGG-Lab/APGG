#!/bin/bash

echo Compiling C++-code ...

cd bin

g++ -Wall -O3 -std=c++17  -c ../APGG/*.cpp
g++ -Wall -O3 -std=c++17  -c ../APGG/archivers/*.cpp
g++ -Wall -O3 -std=c++17  -c ../APGG/grids/*.cpp
g++ -Wall -O3 -std=c++17  -c ../APGG/matchupgenerators/*.cpp
g++ -Wall -O3 -std=c++17  -c ../APGG/payoffcalculators/*.cpp
g++ -Wall -O3 -std=c++17  -c ../APGG/optimizer/*.cpp
g++ -Wall -O3 -std=c++17  -c ../APGG/optimizer/mutators/*.cpp
g++ -Wall -O3 -std=c++17  -c ../APGG/optimizer/selectors/*.cpp
g++ -Wall -O3 -std=c++17 -c ../APGG/optimizer/repopulators/*.cpp

cd ../

echo Linking ...

gcc -O3 -o bin/apgg_release bin/*.o -std=c++17 -lstdc++ -lm -lstdc++fs

rm bin/*.o
