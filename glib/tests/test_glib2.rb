require 'test/unit'
require 'glib2'

class TestGLib < Test::Unit::TestCase

  def test_version
    assert_kind_of(Array, GLib::VERSION)
    assert_equal(GLib::VERSION.length, 3)
    assert(GLib::VERSION.all?{|i| i.is_a? Integer })

    assert_kind_of(Integer, GLib::MAJOR_VERSION)
    assert_kind_of(Integer, GLib::MINOR_VERSION)
    assert_kind_of(Integer, GLib::MICRO_VERSION)

    assert_kind_of(Array, GLib::BINDING_VERSION)
    assert_equal(GLib::BINDING_VERSION.length, 3)
    assert(GLib::BINDING_VERSION.all?{|i| i.is_a? Integer })
  end

  def test_priority
    assert_kind_of(Integer, GLib::PRIORITY_HIGH)
    assert_kind_of(Integer, GLib::PRIORITY_DEFAULT)
    assert_kind_of(Integer, GLib::PRIORITY_HIGH_IDLE)
    assert_kind_of(Integer, GLib::PRIORITY_DEFAULT_IDLE)
    assert_kind_of(Integer, GLib::PRIORITY_LOW)
  end

  def test_int64
  end

  def test_convert
    assert_kind_of(String, GLib.charset)

    sjis = "\202\261\202\361\202\311\202\277\202\315\220\242\212E"
    euc  = "\244\263\244\363\244\313\244\301\244\317\300\244\263\246"
    utf8 = "\343\201\223\343\202\223\343\201\253\343\201\241\343\201\257\344\270\226\347\225\214"
    assert_equal(GLib.convert(sjis, "UTF-8", "SHIFT_JIS"), utf8)
    assert_equal(GLib.convert(sjis, "EUC-JP", "SHIFT_JIS"), euc)
    assert_equal(GLib.convert(sjis, "SHIFT_JIS", "SHIFT_JIS"), sjis)
    assert_equal(GLib.convert(euc, "UTF-8", "EUC-JP"), utf8)
    assert_equal(GLib.convert(euc, "EUC-JP", "EUC-JP"), euc)
    assert_equal(GLib.convert(euc, "SHIFT_JIS", "EUC-JP"), sjis)
    assert_equal(GLib.convert(utf8, "UTF-8", "UTF-8"), utf8)
    assert_equal(GLib.convert(utf8, "EUC-JP", "UTF-8"), euc)
    assert_equal(GLib.convert(utf8, "SHIFT_JIS", "UTF-8"), sjis)

    # rb_define_module_function(mGLib, "locale_to_utf8", rbglib_m_locale_to_utf8, 1);
    # rb_define_module_function(mGLib, "locale_from_utf8", rbglib_m_locale_from_utf8, 1);
    # rb_define_module_function(mGLib, "filename_to_utf8", rbglib_m_filename_to_utf8, 1);
    # rb_define_module_function(mGLib, "filename_from_utf8", rbglib_m_filename_from_utf8, 1);
    # 
    # rb_define_module_function(mGLib, "filename_to_uri", rbglib_m_filename_to_uri, -1);
    # rb_define_module_function(mGLib, "filename_from_uri", rbglib_m_filename_from_uri, 1);

  end

  def test_messages
    #rb_define_module_function(mGLog, "set_handler", rbglib_m_log_set_handler, 2);
    #rb_define_module_function(mGLog, "remove_handler", rbglib_m_log_remove_handler, 2);
  end


  def test_interface_extend
    assert_raises(TypeError){
      Object.__send__(:include, GLib::TypePlugin)
    }
  end

  def test_inheritance_and_gc
    begin 
      require 'gtk2'

      mybutton = Class.new(Gtk::Button)
      box = Gtk::HBox.new
      10.times{
	box.add mybutton.new
      }
      GC.start
      assert(box.children.all?{|item| item.is_a? mybutton })
    rescue LoadError
    end
  end

  def test_signal_has_handler_pending
    obj = GLib::Object.new
    signal_name = "notify"

    assert(!obj.signal_has_handler_pending?(signal_name))

    h = obj.signal_connect(signal_name){}
    assert(obj.signal_has_handler_pending?(signal_name))

    obj.signal_handler_block(h) {
      assert(obj.signal_has_handler_pending?(signal_name, true))
      assert(!obj.signal_has_handler_pending?(signal_name, false))
    }
    assert(obj.signal_has_handler_pending?(signal_name, false))

    obj.signal_handler_disconnect(h)
    assert(!obj.signal_has_handler_pending?(signal_name))

    obj = nil
  end

  def test_signal_handler_disconnect_and_gc
    obj = GLib::Object.new
    klass = Class.new
    1000.times {
      a = klass.new
      id = obj.signal_connect("notify") { p a }
      obj.signal_handler_disconnect(id)
    }
    ary = []
    ObjectSpace.each_object(klass) { |a| ary.push(a) }
    assert(ary.size < 1000)
  end
end
