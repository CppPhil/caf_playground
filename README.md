# caf_playground
This project servers as a place to experiment with the C++ Actor Framework (CAF).  
See: [CAF](https://github.com/actor-framework/actor-framework)  

## Supported operating systems
* GNU/Linux

## Cloning the repository
The repository uses git submodules.  
In order to clone the repository including the git submodules use  
`git clone --recursive https://github.com/CppPhil/caf_playground.git`  
Or using SSH: `git clone --recursive git@github.com:CppPhil/caf_playground.git`  

## Prerequisites
### GNU C++ Compiler
A recent version of gcc and g++ is required.  
Using g++-9 or newer is recommended.  
g++-9 can be installed with apt-get using  
`sudo apt-get install -y g++-9 g++-9-multilib libc6-dbg linux-libc-dev`  

### OpenSSL
CMake and CAF both require OpenSSL to be installed.  
Using apt-get OpenSSL can be installed with `sudo apt-get install -y openssl libssl-dev`  

### CMake
CMake 3.15 or newer is required.  
CMake 3.16 or newer is recommended.  
Note that package managers such as apt-get typically install very outdated versions of CMake.  
If you have a distribution of CMake installed through a package manager such as apt-get it is recommended to uninstall the CMake package before building a recent CMake release from source.  
CMake 3.16.2 can be installed using the following commands:  
`version=3.16`  
`build=2`  
`mkdir ~/temp`  
`cd ~/temp`  
`wget https://cmake.org/files/v$version/cmake-$version.$build.tar.gz`  
`tar -xzvf cmake-$version.$build.tar.gz`  
`cd cmake-$version.$build/`  
`./bootstrap`  
`make -j$(nproc)`  
`sudo make install`  
Source: [askubuntu](https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line)  

### Ruby
Ruby is used for the build script.  
Ruby can be installed with apt-get using:  
`sudo apt-get install ruby-full -y`  

## Setup
To set up the project CAF needs to be installed.  
To install CAF the install_caf.sh script can be invoked using `./install_caf.sh`  
The process might query for your password because it uses `sudo make install` to install CAF on the system.  

## Scripts
The root directory contains multiple bash scripts which are described below.  

| script                   | details                                                                                                |
|--------------------------|--------------------------------------------------------------------------------------------------------|
| build.sh                 | Invokes the underlying Ruby build script to build the project. Pass -h or --help to print a help text. |
| format.sh                | Formats the source code. Requires clang-format.                                                        |
| install_caf.sh           | Setup script to initially install CAF on the system.                                                   |
| run.sh                   | Runs the main executable of the project. Requires the project to have been built.                      |
| test.sh                  | Runs the unit test executable of the project. Requires the project to have been built.                 |
| update_git_submodules.sh | Utility script to update the git submodules of the project.                                            |

## Building the project
To build the project in debug mode use `./build.sh --build_type Debug`  
To build the project in release mode use `./build.sh --build_type Release`  
To force a rebuild of the project the --rebuild option can be used.  
Example: `./build.sh --build_type Debug --rebuild true`  
Instead of --build_type the -b short option can be used.  
Instead of --rebuild the -r short option can be used.  
For instance one can build the project in release mode forcing a rebuild using `./build.sh -b Release -r true`  

## Generating the documentation
Documentation can be generated using `doxygen Doxyfile` (requires doxygen).  

## Project structure
The project attempts to follow the [Pitchfork Layout](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs)  
