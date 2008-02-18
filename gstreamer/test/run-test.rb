#!/usr/bin/env ruby

# ENV["GST_DEBUG"] = "GST_BUFFER:5"

$VERBOSE = true

base_dir = File.expand_path(File.join(File.dirname(__FILE__), ".."))

system("cd #{base_dir.dump} && make > /dev/null") or exit(1)

$LOAD_PATH.unshift(File.join(base_dir, "..", "glib", "src"))
$LOAD_PATH.unshift(File.join(base_dir, "..", "glib", "src", "lib"))

$LOAD_PATH.unshift(File.join(base_dir, "src"))
$LOAD_PATH.unshift(File.join(base_dir, "src", "lib"))
require "gst"

$LOAD_PATH.unshift(File.join(base_dir, "test"))
$LOAD_PATH.unshift(File.join(base_dir, "test-unit-ext", "lib"))
require 'test-unit-ext'

test_file = File.join(base_dir, "test", "test_*.rb")
case ARGV.first
when /\A--\z/
  ARGV.shift
when /\A-/, nil;
else
  test_file = ARGV.shift
end

Dir.glob(test_file) do |file|
  require file
end

argv = ARGV.dup
unless argv.find {|opt| /\A(?:-v|--verbose=)/ =~ opt}
  argv << "--verbose=n"
end
unless argv.find {|opt| /\A--(?:no-)priority/ =~ opt}
  argv << "--priority"
end

args = [File.dirname($0), argv.dup]
if Test::Unit::AutoRunner.respond_to?(:standalone?)
  args.unshift(false)
else
  args.unshift($0)
end
Test::Unit::AutoRunner.run(*args)
