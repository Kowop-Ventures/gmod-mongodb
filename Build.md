# Build

Prerequisites
```
cmake 3.24.3
Visual Studio 17 2022
```

# Build and compile mongo-c-driver

For Windows:
```powershell
mkdir mongo-c-driver
mkdir temp
cd temp
git clone https://github.com/mongodb/mongo-c-driver.git
cd mongo-c-driver
git checkout 1.17.1
echo "1.17.1" | tee VERSION_CURRENT
mkdir cmake-build
cd cmake-build
cmake -DCMAKE_INSTALL_PREFIX=out -DCMAKE_PREFIX_PATH=out ..
cmake --build . --config RelWithDebInfo --target install
cd ../../../
cp -r ./temp/mongo-c-driver/cmake-build/out ./
mv ./out ./mongo-c-driver
```

# Build gmod module

For Windows
```powershell
mkdir build
cd build
$CMAKE_PREFIX_PATH = (Resolve-Path -Path  ../mongo-c-driver).Path
cmake -DCMAKE_GENERATOR_PLATFORM=x64 -A x64 ..  
cmake --build . --target ALL_BUILD --config Release
```
