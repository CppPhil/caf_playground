#!/bin/bash

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly PREVIOUS_DIRECTORY=${pwd}

cd $DIR/build/tests/cpp

./cafPlaygroundTest

cd $PREVIOUS_DIRECTORY

exit 0

