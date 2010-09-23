=begin
extconf.rb for Ruby/GnomePrintUI extention library
=end

require 'pathname'

base_dir = Pathname(__FILE__).dirname.expand_path
top_dir = base_dir.parent.expand_path
mkmf_gnome2_dir = top_dir + "glib" + 'lib'
top_build_dir = Pathname(".").parent.expand_path

$LOAD_PATH.unshift(mkmf_gnome2_dir.to_s)

module_name = "gnomeprintui2"
package_id = "libgnomeprintui-2.2"

require 'mkmf-gnome2'

setup_win32(module_name, base_dir)

PKGConfig.have_package(package_id) or exit 1

[["glib", "glib2"],
 ["gtk", "gtk2"]].each do |directory, library_name|
  build_dir = "#{directory}/tmp/#{RUBY_PLATFORM}/#{library_name}/#{RUBY_VERSION}"
  add_depend_package(library_name, "#{directory}/ext/#{library_name}",
                     top_dir.to_s,
                     :top_build_dir => top_build_dir.to_s,
                     :target_build_dir => build_dir)
end
add_depend_package("libart2", "libart/src", top_dir.to_s)
add_depend_package("gnomeprint2", "gnomeprint/src", top_dir.to_s)

have_header("libgnomeprintui/gnome-print-config-dialog.h")
have_header("libgnomeprintui/gnome-font-dialog.h")

make_version_header("LIBGNOMEPRINTUI", package_id)

create_pkg_config_file("Ruby/GnomePrintUI", package_id,
                       nil, "ruby-gnomeprintui2.pc")
create_makefile_at_srcdir(module_name, (base_dir + "src").to_s,
                          "-DRUBY_GNOMEPRINTUI2_COMPILATION") do
  enum_type_dir = "libgnomeprintui"
  enum_type_prefix = "libgnomeprintui-enum-types"
  unless have_header("#{enum_type_dir}/#{enum_type_prefix}.h")
    include_paths = `pkg-config libgnomeprintui-2.2 --cflags-only-I`
    include_path = include_paths.split.find do |x|
      /libgnomeprintui/.match(x)
    end.sub(/^-I/, "")
    headers = Dir.glob(File.join(include_path, "libgnomeprintui", "*.h"))

    glib_mkenums(enum_type_prefix, headers, "GNOME_TYPE_PRINT_",
                 ["libgnomeprintui/gnome-print-dialog.h",
                  "libgnomeprintui/gnome-print-paper-selector.h"])
  end
end

create_top_makefile
