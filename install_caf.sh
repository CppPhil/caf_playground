#!/bin/bash

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly CAF_DIR=$DIR/external/libcaf

readonly PREVIOUS_DIRECTORY=${pwd}

cd $CAF_DIR

./configure --libs-only --with-gcc=g++

cd ./build

make -j$(nproc) VERBOSE=1

sudo make install

cd $PREVIOUS_DIRECTORY

exit 0

