=begin
extconf.rb for Ruby/Libglade2 extention library
=end
require "mkmf"

rubyglib_dir = File.expand_path(File.dirname(__FILE__))+"/../glib"
unless FileTest.exist?(rubyglib_dir)
  raise "Directory #{rubyglib_dir} not found.  Please specify Ruby/GLib2 source dir."
end
$CFLAGS += " -I#{rubyglib_dir}/src "

rubygtk_dir = File.expand_path(File.dirname(__FILE__))+"/../gtk"
unless FileTest.exist?(rubyglib_dir)
  raise "Directory #{rubygtk_dir} not found.  Please specify Ruby/GTK2 source dir."
end
$CFLAGS += " -I#{rubygtk_dir}/src "

unless system('pkg-config', '--exists', 'libglade-2.0')
  STDERR.print("libglade-2.0 doesn't exist\n")
  exit
end
$libs += ' ' + `pkg-config libglade-2.0 --libs`.chomp
$CFLAGS += " -I../glib/src -I../gtk/src  "
$CFLAGS += `pkg-config libglade-2.0 --cflags`.chomp
$CFLAGS += ' -g'

create_makefile("libglade2")  
