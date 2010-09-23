=begin
extconf.rb for Ruby/Bonobo2 extension library
=end

require 'pathname'

base_dir = Pathname(__FILE__).dirname.expand_path
top_dir = base_dir.parent.expand_path
mkmf_gnome2_dir = top_dir + "glib" + 'lib'
top_build_dir = Pathname(".").parent.expand_path

$LOAD_PATH.unshift(mkmf_gnome2_dir.to_s)

module_name = "bonobo2"
package_id = "libbonobo-2.0"

require 'mkmf-gnome2'

setup_win32(module_name, base_dir)

(PKGConfig.have_package('libbonobo-2.0') and
 PKGConfig.have_package('libbonoboui-2.0')) or exit 1

[["glib", "glib2"],
 ["gtk", "gtk2"]].each do |directory, library_name|
  build_dir = "#{directory}/tmp/#{RUBY_PLATFORM}/#{library_name}/#{RUBY_VERSION}"
  add_depend_package(library_name, "#{directory}/ext/#{library_name}",
                     top_dir.to_s,
                     :top_build_dir => top_build_dir.to_s,
                     :target_build_dir => build_dir)
end

begin
  srcdir = File.dirname($0) == "." ? "." :
    File.expand_path(File.dirname($0) + "/src")

  create_pkg_config_file("Ruby/Bonobo2", package_id)

  Dir.mkdir "src" unless FileTest.exist? "src"
  Dir.chdir "src"

  begin
    File.delete("rbbonoboinits.c") if FileTest.exist?("rbbonoboinits.c")

    obj_ext = ".#{$OBJEXT}"

    $libs = $libs.split(/\s/).uniq.join(' ')
    $source_files = Dir.glob("#{srcdir}/*.c").map{|fname|
      fname[0, srcdir.length+1] = ''
      fname
    }
    $objs = $source_files.collect do |item|
      item.gsub(/\.c$/, obj_ext)
    end
    add_obj("rbbonoboinits#{obj_ext}")

    make_version_header("BONOBO", package_id, '.')

    #
    # create Makefiles
    #
    create_makefile(module_name, srcdir)
    raise Interrupt if not FileTest.exist? "Makefile"

    mfile = File.open("Makefile", "a")
    $source_files.each do |e|
      mfile.print "#{e.gsub(/\.c$/, obj_ext)}: #{e} rbbonobo.h \n"
    end
    mfile.print "\
rbbonoboinits.c:;    $(RUBY) $(srcdir)/makeinits.rb $(srcdir)/*.c > $@
allclean: clean
	rm -rf *.a
"
    mfile.close
  ensure
    Dir.chdir ".."
  end

  create_top_makefile

rescue Interrupt
#  if $DEBUG
    print "  [error] " + $!.to_s + "\n"
#  end
end

