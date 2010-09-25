=begin
extconf.rb for Ruby/Atk extention library
=end

require 'pathname'

base_dir = Pathname(__FILE__).dirname.parent.parent.expand_path
top_dir = base_dir.parent
top_build_dir = Pathname(".").parent.parent.parent.expand_path

mkmf_gnome2_dir = top_dir + "glib2" + 'lib'
version_suffix = ""
unless mkmf_gnome2_dir.exist?
  if /(-\d+\.\d+\.\d+)\z/ =~ base_dir.basename.to_s
    version_suffix = $1
    mkmf_gnome2_dir = top_dir + "glib2#{version_suffix}" + 'lib'
  end
end

$LOAD_PATH.unshift(mkmf_gnome2_dir.to_s)

module_name = "atk"
package_id = "atk"

require 'mkmf-gnome2'

setup_win32(module_name, base_dir)

PKGConfig.have_package(package_id) or exit 1

atk_header = "atk/atk.h"
have_func('atk_action_get_localized_name', atk_header)
have_func('atk_hyperlink_is_inline', atk_header)
have_func('atk_object_add_relationship', atk_header)
have_func('atk_object_remove_relationship', atk_header)
have_func('atk_component_get_layer', atk_header)
have_func('atk_component_get_mdi_zorder', atk_header)
have_func('atk_hyperlink_is_selected_link', atk_header)
have_func('atk_text_get_bounded_ranges', atk_header)
have_func('atk_role_get_localized_name', atk_header)
have_func('atk_text_clip_type_get_type', atk_header)

have_func('atk_text_free_ranges', atk_header)

["glib2"].each do |package|
  directory = "#{package}#{version_suffix}"
  build_dir = "#{directory}/tmp/#{RUBY_PLATFORM}/#{package}/#{RUBY_VERSION}"
  add_depend_package(package, "#{directory}/ext/#{package}",
                     top_dir.to_s,
                     :top_build_dir => top_build_dir.to_s,
                     :target_build_dir => build_dir)
end

add_distcleanfile("rbatkinits.c")

make_version_header("ATK", package_id, ".")

create_pkg_config_file("Ruby/ATK", package_id)
$defs << " -DRUBY_ATK_COMPILATION"
create_makefile(module_name)
