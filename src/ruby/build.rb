# frozen_string_literal: true

require 'etc'

RUBY_DIR = __dir__
ROOT_DIR = "#{RUBY_DIR}/../.."
BUILD_DIR = "#{ROOT_DIR}/build"

DEBUG_OPTION = 'debug'
RELEASE_OPTION = 'release'

HELP = <<ENDHELP
  Invalid command line arguments!
  Possible options:

  #{DEBUG_OPTION}     Build in debug mode.
  #{RELEASE_OPTION}   Build in release mode.
ENDHELP

arguments = ARGV.join

if arguments != DEBUG_OPTION && arguments != RELEASE_OPTION
  puts HELP
  exit
end

Dir.mkdir BUILD_DIR unless File.directory? BUILD_DIR

previous_directory = Dir.pwd

Dir.chdir ROOT_DIR

system "cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=#{arguments} -G \"Unix Makefiles\" #{BUILD_DIR}"

Dir.chdir BUILD_DIR

system "cmake --build #{BUILD_DIR} -- -j#{Etc.nprocessors} VERBOSE=1"

Dir.chdir previous_directory
