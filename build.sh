mkdir tmp
mkdir build
cd tmp
cmake ".." -G "MinGW Makefiles"
make
cp RoadTrafficSimulator ../build/
cd ..
rm -r tmp
cp -r ./resources build/
