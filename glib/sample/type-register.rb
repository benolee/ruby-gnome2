require 'gtk2'
Gtk.init

class MyButton < Gtk::Button
  type_register("MyButton")

  def initialize(label = nil)
    # XXX: type_register$B$9$k$H(Bsuper$B$,(BGLib::Object#initialize$BAjEv$K$J$k(B
    super("label" => label)
    @fuga = 0
  end

  # $B4{B8$N%7%0%J%k$N%G%U%)%k%H%O%s%I%i$r%*!<%P!<%i%$%I(B
  def signal_do_clicked(*args)
    puts "MyButton#signal_do_clicked enter"
    #p caller
    super
    puts "MyButton#signal_do_clicked leave"
  end

  # $B?7$7$$%7%0%J%k$rDj5A(B
  signal_new("hoge",                  # $BL>A0(B
             GLib::Signal::RUN_FIRST, # $B%U%i%0(B
             nil,                     # accumulator (XXX: $B;EMM$,L$3NDj(B)
             GLib::Type["void"],      # $BJV$jCM$N7?(B
             GLib::Type["gint"], GLib::Type["gint"] # $B0z?t$N7?(B
             )
  # $B?7$7$$%7%0%J%k$N%G%U%)%k%H%O%s%I%i(B
  def signal_do_hoge(a, b)
    puts "MyButton#signal_do_hoge enter"
    #p caller
    puts "MyButton#signal_do_hoge leave"
  end

  # $B?7$7$$%W%m%Q%F%#$N:n@.(B
  install_property(GLib::Param::Int.new("fuga", # name
                                        "Fuga", # nick
                                        "fuga hoge", # blurb
                                        0,     # min
                                        10000, # max
                                        0,     # default
                                        GLib::Param::READABLE |
                                        GLib::Param::WRITABLE))
  # $B%W%m%Q%F%#$N<BAu(B
  def fuga
    puts "MyButton#fuga is called"
    @fuga
  end
  def fuga=(arg)
    puts "MyButton#fuga= is called"
    @fuga = arg
  end
end

class MyButton2 < MyButton
  type_register("MyButton2")

  # clicked$B%7%0%J%k$N%G%U%)%k%H%O%s%I%i$r%*!<%P!<%i%$%I(B
  def signal_do_clicked(*args)
    puts "MyButton2#signal_do_clicked enter"
    super(*args)
    puts "MyButton2#signal_do_clicked leave"
  end

  # hoge$B%7%0%J%k$N%G%U%)%k%H%O%s%I%i$r%*!<%P!<%i%$%I(B
  def signal_do_hoge(a, b)
    puts "MyButton2#signal_do_hoge enter"
    #p caller
    super
    puts "MyButton2#signal_do_hoge leave"
  end
end

b = MyButton2.new("Hello")
p b
p b.label
p b.gtype
b.clicked
b.signal_emit("hoge", 1, 2)

b.signal_connect("notify"){|obj, pspec|
  puts "#{b} notify #{pspec}"
}

p b.get_property("fuga")
b.set_property("fuga", 1)
p b.get_property("fuga")

p MyButton2.ancestors
