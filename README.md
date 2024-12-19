# SlopDAW
A Digital Audio Workstation using [Dear ImGui](https://github.com/ocornut/imgui)

## Requirements 
- **C++ Version**: At least C++20, gcc version 13.2.0 
- **External Dependencies**: 
  - Dear ImGui (included in repository)
  - TBD

## Building for Windows
This project uses the premake build system. 

### Step 1: Clone the repository

```bash
git clone https://github.com/JustAnEE/SlopDAW
```

### Step 2: Install Premake 
This project uses a [premake](https://premake.github.io/) based build system. The easiest way to insall premake is through [scoop](https://scoop.sh/)
Add the main bucket if you do not have it, and then get the premake latest version from main.
```bash
scoop bucket add main
scoop install main/premake
```
Note that scoop will automatically add premake to the path environment variable. 

### Step 3: Generate GNU Make Files 
Use premake to generate make files, navigate to the top level folder where premake5.lua is located and run the following command.
```bash
premake5 gmake2
```
Currently, this project does not build with GCC :). It will build on visual studio, to build the project in visual studio run the following command. 
```bash
premake5 vs2019
```
If you are using a different version of visual studio, the solution will have to be retargeted to your version. 

### Step 4: Build 
Premake automatically generated GNU make files for us, run make in the same top level directory that premake ran.
```bash
make config=debug
or
make config=release
```
The differences between the release mode and debug mode builds can be seen in the premake5.lua script, which outlines the configuration of the project.

If using visual studio, use the visual studio built in build process to build the project.
