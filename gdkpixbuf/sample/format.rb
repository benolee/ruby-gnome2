#!/usr/local/bin/ruby
=begin
  format.rb - Ruby/GdkPixbuf sample script.

  Copyright (c) 2004 Ruby-GNOME2 Project Team
  This program is licenced under the same licence as Ruby-GNOME2.

  $Id: format.rb,v 1.2 2005/03/05 06:50:42 mutoh Exp $
=end

require 'gtk2'

Gtk.init

if str = Gtk.check_version(2, 2, 0)
  puts "This sample requires GTK+ 2.2.0 or later"
  puts str
  exit
end

filename = ARGV[0]
unless filename
  puts "ruby #{$0} filename"
  exit(1)
end

puts fileinfo = Gdk::Pixbuf.get_file_info(filename)[0]
puts "name = #{fileinfo.name}"
puts "description = #{fileinfo.description}"
puts "mime_types = #{fileinfo.mime_types.inspect}"
puts "extensions = #{fileinfo.extensions.inspect}"
puts "writable = #{fileinfo.writable?}"
puts "domain = #{fileinfo.domain}"
puts "signature = #{fileinfo.signature.inspect}"

if Gtk.check_version?(2, 6, 0)
  puts "Since 2.6 --- "
  puts "scalable = #{fileinfo.scalable?}"
  puts "disabled = #{fileinfo.disabled?}"
  puts "license = #{fileinfo.license.inspect}"
end
