#!/bin/bash

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly GOTO_RUBY="$DIR/external/goto-ruby/goto-ruby.sh"
readonly RUBY_SCRIPT="$DIR/src/ruby/build.rb"
readonly PREVIOUS_DIRECTORY=${pwd}

cd $DIR

$GOTO_RUBY $RUBY_SCRIPT "$@"

cd $PREVIOUS_DIRECTORY

exit 0

