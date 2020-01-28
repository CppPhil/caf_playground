# frozen_string_literal: true

require 'etc'
require 'fileutils'
require 'optparse'

RUBY_DIR = __dir__
ROOT_DIR = "#{RUBY_DIR}/../.."
BUILD_DIR = "#{ROOT_DIR}/build"

DEBUG_OPTION = 'Debug'
RELEASE_OPTION = 'Release'

def print_help
  system "ruby #{RUBY_DIR}/build.rb --help"
end

options = {}
begin
  OptionParser.new do |opt|
    opt.on('-b', '--build_type {Debug|Release}', 'The build type to use') { |o| options[:build_type] = o }
    opt.on('-r', '--rebuild {true|false}', 'Whether to force a rebuild or not') { |o| options[:rebuild] = o }
  end.parse!
rescue OptionParser::InvalidOption
  printf "Unknown option was given!\n\n"
  print_help
  exit 1
end

build_option = options[:build_type]

if build_option.nil?
  printf "build_type option wasn't set!\n\n"
  print_help
  exit 1
end

FileUtils.rm_rf BUILD_DIR if options[:rebuild] == 'true'

Dir.mkdir BUILD_DIR unless File.directory? BUILD_DIR

previous_directory = Dir.pwd

Dir.chdir ROOT_DIR

system "CC=gcc CXX=g++ cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=#{build_option} -G \"Unix Makefiles\" #{BUILD_DIR}"

Dir.chdir BUILD_DIR

system "CC=gcc CXX=g++ cmake --build #{BUILD_DIR} --config #{build_option} -- -j#{Etc.nprocessors} VERBOSE=1"

Dir.chdir previous_directory
