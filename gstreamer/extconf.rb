=begin
extconf.rb for Ruby/GStreamer extention library
=end

PACKAGE_NAME = "gst"

TOPDIR = File.expand_path(File.dirname(__FILE__) + '/..')
MKMF_GNOME2_DIR = TOPDIR + '/glib/src/lib'
SRCDIR = TOPDIR + '/gstreamer/src'

$LOAD_PATH.unshift MKMF_GNOME2_DIR

require 'mkmf-gnome2'


PKGConfig.have_package('gstreamer-0.8') or exit 1

setup_win32(PACKAGE_NAME)

add_depend_package("glib2", "glib/src", TOPDIR)

if have_library("gstmedia-info-0.8", "gst_media_info_read")
  $CFLAGS += " -DHAVE_MEDIA_INFO"
end

create_makefile_at_srcdir(PACKAGE_NAME, SRCDIR, "-DRUBY_GST_COMPILATION")
create_top_makefile
