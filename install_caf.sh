#!/bin/bash

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly CAF_DIR=$DIR/external/libcaf

readonly PREVIOUS_DIRECTORY=${pwd}

cd $DIR/external
wget https://github.com/actor-framework/actor-framework/archive/0.17.3.tar.gz
tar xf 0.17.3.tar.gz
mv ./actor-framework-0.17.3 ./libcaf
rm 0.17.3.tar.gz

cd $CAF_DIR

./configure --libs-only --with-gcc=g++

cd ./build

make -j$(nproc) VERBOSE=1

sudo make install

cd $PREVIOUS_DIRECTORY

exit 0

