# Riku
## Updating VS filters to match dictionary hierarchy
  1. Add all files to VS project
  2. Close Visual Studio and go to the main solution directory in command line
  3. Run ```python .\filters_from_directories.py > './Riku/Riku.vcxproj.filters'```
  4. Open Visual Studio. Filters should by updated

## Compile on 64-bit Windows

Before compiling project in Visual Studio it is necessary to install some libraries.
To do it in commandline go to directory you want to install libraries in and run following commands.
It is not required to install libraries in the project directory. vcpkg will find Visual Studio on your computer and make libraries available to it.
```
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
cd vcpkg
vcpkg install cppzmq:x64-windows
vcpkg install zeromq:x64-windows
vcpkg install cereal:x64-windows
vcpkg integrate install
```
Now you should be able to compile project using Visual Studio

## Compile on 64-bit Ubuntu 20.04

  1. Launch linux-setup.sh with root priviliges. It will install all needed packages.
  2. Compile project using CLion IDE. It may be needed to run ```Riku/get_cpp_names.py``` in terminal to get list of source files and copy the output of command to file ```Riku/CMake Lists.txt``` and replace text from line after `lib/stb_image/stb_image.cpp` to `)` character before first `target_link_libraries`
  3. Launch linux-generate-binary.sh script to create folder bin ready for user.
