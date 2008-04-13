# -*- coding: utf-8 -*-

class TestGLibUnicode < Test::Unit::TestCase
  include GLibTestUtils

  def test_gunicode_type
    assert_nothing_raised do
      GLib::Unicode::CONTROL
    end
  end

  def test_gunicode_break_type
    assert_nothing_raised do
      GLib::Unicode::BREAK_MANDATORY
    end
  end

  def test_unichar_alnum?
    assert(GLib::UniChar.alnum?(unichar("a")))
    assert(GLib::UniChar.alnum?(unichar("1")))
    assert(!GLib::UniChar.alnum?(unichar("!")))
  end

  def test_unichar_alpha?
    assert(GLib::UniChar.alpha?(unichar("a")))
    assert(GLib::UniChar.alpha?(unichar("A")))
    assert(!GLib::UniChar.alpha?(unichar("1")))
  end

  def test_unichar_cntrl?
    assert(GLib::UniChar.cntrl?(unichar("\t")))
    assert(!GLib::UniChar.cntrl?(unichar("\h")))
    assert(!GLib::UniChar.cntrl?(unichar("a")))
    assert(!GLib::UniChar.cntrl?(unichar("1")))
  end

  def test_unichar_digit?
    assert(GLib::UniChar.digit?(unichar("1")))
    assert(!GLib::UniChar.digit?(unichar("a")))
  end

  def test_unichar_graph?
    assert(GLib::UniChar.graph?(unichar("a")))
    assert(!GLib::UniChar.graph?(unichar(" ")))
    assert(!GLib::UniChar.graph?(unichar("\t")))
  end

  def test_unichar_lower?
    assert(GLib::UniChar.lower?(unichar("a")))
    assert(!GLib::UniChar.lower?(unichar("A")))
    assert(!GLib::UniChar.lower?(unichar("1")))
  end

  def test_unichar_print?
    assert(GLib::UniChar.print?(unichar("a")))
    assert(GLib::UniChar.print?(unichar(" ")))
    assert(!GLib::UniChar.print?(unichar("\t")))
  end

  def test_unichar_punct?
    assert(GLib::UniChar.punct?(unichar(",")))
    assert(GLib::UniChar.punct?(unichar(".")))
    assert(!GLib::UniChar.punct?(unichar("a")))
    assert(!GLib::UniChar.punct?(unichar("\t")))
  end

  def test_unichar_space?
    assert(GLib::UniChar.space?(unichar(" ")))
    assert(GLib::UniChar.space?(unichar("\t")))
    assert(GLib::UniChar.space?(unichar("\r")))
    assert(GLib::UniChar.space?(unichar("\n")))
    assert(!GLib::UniChar.space?(unichar("a")))
  end

  def test_unichar_upper?
    assert(GLib::UniChar.upper?(unichar("A")))
    assert(!GLib::UniChar.upper?(unichar("a")))
    assert(!GLib::UniChar.upper?(unichar("1")))
  end

  def test_unichar_xdigit?
    assert(GLib::UniChar.xdigit?(unichar("1")))
    assert(GLib::UniChar.xdigit?(unichar("a")))
    assert(GLib::UniChar.xdigit?(unichar("A")))
    assert(GLib::UniChar.xdigit?(unichar("F")))
    assert(!GLib::UniChar.xdigit?(unichar("X")))
  end

  def test_unichar_title?
  end

  def test_unichar_defined?
  end

  def test_unichar_wide?
    assert(GLib::UniChar.wide?(unichar("あ")))
    assert(GLib::UniChar.wide?(unichar("Ａ")))
    assert(!GLib::UniChar.wide?(unichar("a")))
  end

  def test_unichar_wide_cjk?
    only_glib_version(2, 12, 0)
    assert(GLib::UniChar.wide_cjk?(unichar("あ")))
    assert(GLib::UniChar.wide_cjk?(0xD55C)) # HANGUL SYLLABLE HAN
    assert(!GLib::UniChar.wide_cjk?(unichar("a")))
  end

  def test_unichar_to_upper
    assert_equal(unichar("A"), GLib::UniChar.to_upper(unichar("a")))
    assert_equal(unichar("A"), GLib::UniChar.to_upper(unichar("A")))
    assert_equal(unichar("*"), GLib::UniChar.to_title(unichar("*")))
  end

  def test_unichar_to_lower
    assert_equal(unichar("a"), GLib::UniChar.to_lower(unichar("A")))
    assert_equal(unichar("a"), GLib::UniChar.to_lower(unichar("a")))
    assert_equal(unichar("*"), GLib::UniChar.to_title(unichar("*")))
  end

  def test_unichar_to_title
    assert_equal(unichar("A"), GLib::UniChar.to_title(unichar("a")))
    assert_equal(unichar("A"), GLib::UniChar.to_title(unichar("A")))
    assert_equal(unichar("*"), GLib::UniChar.to_title(unichar("*")))
  end

  def test_unichar_digit_value
    assert_equal(0, GLib::UniChar.digit_value(unichar("0")))
    assert_equal(9, GLib::UniChar.digit_value(unichar("9")))
    assert_equal(-1, GLib::UniChar.digit_value(unichar("a")))
  end

  def test_unichar_xdigit_value
    assert_equal(0, GLib::UniChar.xdigit_value(unichar("0")))
    assert_equal(9, GLib::UniChar.xdigit_value(unichar("9")))
    assert_equal(10, GLib::UniChar.xdigit_value(unichar("a")))
    assert_equal(15, GLib::UniChar.xdigit_value(unichar("F")))
    assert_equal(-1, GLib::UniChar.xdigit_value(unichar("g")))
  end

  def test_unichar_type
    assert_equal(GLib::Unicode::DECIMAL_NUMBER,
                 GLib::UniChar.type(unichar("0")))
    assert_equal(GLib::Unicode::LOWERCASE_LETTER,
                 GLib::UniChar.type(unichar("a")))
    assert_equal(GLib::Unicode::UPPERCASE_LETTER,
                 GLib::UniChar.type(unichar("A")))
  end

  def test_unichar_break_type
    assert_equal(GLib::Unicode::BREAK_HYPHEN,
                 GLib::UniChar.break_type(unichar("-")))
    assert_equal(GLib::Unicode::BREAK_NUMERIC,
                 GLib::UniChar.break_type(unichar("0")))
  end

  def test_unicode_canonical_ordering
    require 'uconv'
    original = [unichar("a"), 0x0308, 0x0323,
                unichar("e"), 0x0304, 0x0301, 0x0323].pack("U*")
    expected = [unichar("a"), 0x0323, 0x0308,
                unichar("e"), 0x0323, 0x0304, 0x0301].pack("U*")
    assert_equal(Uconv.u8tou4(expected),
                 GLib::Unicode.canonical_ordering(Uconv.u8tou4(original)))
  end

  def test_unicode_canonical_decomposition
    require 'uconv'
    a_with_acute = 0x00E1
    expected = [unichar("a"), 0x0301].pack("U*")
    assert_equal(Uconv.u8tou4(expected),
                 GLib::Unicode.canonical_decomposition(a_with_acute))

    hiragana_ga = 0x304C
    hiragana_ka = 0x304B
    expected = [hiragana_ka, 0x3099].pack("U*")
    assert_equal(Uconv.u8tou4(expected),
                 GLib::Unicode.canonical_decomposition(hiragana_ga))
  end

  def test_unichar_get_mirror_char
    assert_equal(unichar("("), GLib::UniChar.get_mirror_char(unichar(")")))
    assert_equal(unichar(")"), GLib::UniChar.get_mirror_char(unichar("(")))
    assert_equal(unichar("x"), GLib::UniChar.get_mirror_char(unichar("x")))
  end

  def test_unichar_get_script
    only_glib_version(2, 14, 0)
    assert_equal(GLib::Unicode::SCRIPT_HIRAGANA,
                 GLib::UniChar.get_script(unichar("あ")))
  end

  def test_utf8_get_char
    require "uconv"
    assert_equal(Uconv.u8tou4("あ").unpack("L*")[0],
                 GLib::UTF8.get_char("あ"))

    assert_equal(Uconv.u8tou4("あ").unpack("L*")[0],
                 GLib::UTF8.get_char("あ", true))
    partial_input = "あ".unpack("c*")[0..-2].pack("c*")
    assert_equal(-2, GLib::UTF8.get_char(partial_input, true))
    invalid_input = "あ".unpack("c*")[2..-1].pack("c*")
    assert_equal(-1, GLib::UTF8.get_char(invalid_input, true))
  end

  def test_utf8_size
    assert_equal(1, GLib::UTF8.size("あ"))
    assert_equal(2, GLib::UTF8.size("あい"))
  end

  def test_utf8_reverse
    assert_equal("おえういあ", GLib::UTF8.reverse("あいうえお"))
  end

  def test_utf8_validate
    assert(GLib::UTF8.validate("あ"))
    assert(!GLib::UTF8.validate("あ"[1..-1]))
  end

  def test_utf8_upcase
    assert_equal("ABCあいう", GLib::UTF8.upcase("aBcあいう"))
  end

  def test_utf8_downcase
    assert_equal("abcあいう", GLib::UTF8.downcase("aBcあいう"))
  end

  def test_utf8_casefold
    assert_equal(GLib::UTF8.casefold("AbCあいう"),
                 GLib::UTF8.casefold("aBcあいう"))
  end

  def test_utf8_normalize
    original = [0x00c1].pack("U*") # A with acute

    nfd = [0x0041, 0x0301].pack("U*")
    assert_equal(nfd,
                 GLib::UTF8.normalize(original, GLib::NormalizeMode::NFD))

    nfc = [0x00c1].pack("U*")
    assert_equal(nfc,
                 GLib::UTF8.normalize(original, GLib::NormalizeMode::NFC))

    nfkd = [0x0041, 0x0301].pack("U*")
    assert_equal(nfkd,
                 GLib::UTF8.normalize(original, GLib::NormalizeMode::NFKD))

    nfkc = [0x00c1].pack("U*")
    assert_equal(nfkc,
                 GLib::UTF8.normalize(original, GLib::NormalizeMode::NFKC))
  end

  def test_utf8_collate
    assert_operator(0, :>, GLib::UTF8.collate("あ", "い"))
    assert_operator(0, :<, GLib::UTF8.collate("い", "あ"))
    assert_equal(0, GLib::UTF8.collate("あ", "あ"))
  end

  def test_utf8_collate_key
    assert_operator(0, :>,
                    GLib::UTF8.collate_key("あ") <=>
                    GLib::UTF8.collate_key("い"))
    assert_operator(0, :<,
                    GLib::UTF8.collate_key("い") <=>
                    GLib::UTF8.collate_key("あ"))
    assert_equal(0,
                 GLib::UTF8.collate_key("あ") <=>
                 GLib::UTF8.collate_key("あ"))
  end

  def test_utf8_collate_key_for_filename
    assert_equal(["event.c", "event.h", "eventgenerator.c"],
                 ["event.c", "eventgenerator.c", "event.h"].sort_by do |f|
                   GLib::UTF8.collate_key(f, true)
                 end)

    assert_equal(["file1", "file5", "file10"],
                 ["file1", "file10", "file5"].sort_by do |f|
                   GLib::UTF8.collate_key(f, true)
                 end)
  end

  def test_utf8_to_utf16
    require 'uconv'
    assert_equal(Uconv.u8tou16("あいうえお"),
                 GLib::UTF8.to_utf16("あいうえお"))
  end

  def test_utf8_to_ucs4
    require 'uconv'
    assert_equal(Uconv.u8tou4("あいうえお"),
                 GLib::UTF8.to_ucs4("あいうえお"))

    assert_raise(GLib::ConvertError) do
      GLib::UTF8.to_ucs4("あいうえお"[1..-1])
    end
    assert_nothing_raised do
      GLib::UTF8.to_ucs4("あいうえお"[1..-1], true)
    end
  end

  def test_utf16_to_ucs4
    require 'uconv'
    assert_equal(Uconv.u8tou4("あいうえお"),
                 GLib::UTF16.to_ucs4(Uconv.u8tou16("あいうえお")))
  end

  def test_utf16_to_utf8
    require 'uconv'
    assert_equal("あいうえお",
                 GLib::UTF16.to_utf8(Uconv.u8tou16("あいうえお")))
  end


  def test_ucs4_to_utf16
    require 'uconv'
    assert_equal(Uconv.u8tou16("あいうえお"),
                 GLib::UCS4.to_utf16(Uconv.u8tou4("あいうえお")))

    assert_raise(GLib::ConvertError) do
      GLib::UCS4.to_utf16(Uconv.u8tou4("あいうえお")[1..-1])
    end
  end

  def test_ucs4_to_utf8
    require 'uconv'
    assert_equal("あいうえお",
                 GLib::UCS4.to_utf8(Uconv.u8tou4("あいうえお")))
  end

  def test_unichar_to_utf8
    require 'uconv'
    assert_equal("あ",
                 GLib::UniChar.to_utf8(Uconv.u8tou4("あ").unpack("L*")[0]))
  end

  def test_unichar_combining_class
    only_glib_version(2, 14, 0)
    assert_equal(0, GLib::UniChar.combining_class(unichar("a")))
    assert_equal(230, GLib::UniChar.combining_class(unichar("́")))
  end

  def test_unichar_mark?
    only_glib_version(2, 14, 0)
    assert(!GLib::UniChar.mark?(unichar("a")))
    assert(!GLib::UniChar.mark?(0x200E)) # LEFT-TO-RIGHT MARK
    assert(GLib::UniChar.mark?(0x1DC3)) # COMBINING SUSPENSION MARK
  end

  def test_unichar_zero_width?
    only_glib_version(2, 14, 0)
    assert(!GLib::UniChar.zero_width?(unichar("a")))
    assert(GLib::UniChar.zero_width?(0x200B)) # ZERO WIDTH SPACE
  end

  private
  def unichar(char)
    GLib::UTF8.get_char(char)
  end
end
