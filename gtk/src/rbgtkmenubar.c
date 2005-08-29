/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkmenubar.c -

  $Author: ggc $
  $Date: 2005/08/29 20:48:47 $

  Copyright (C) 2002,2003 Ruby-GNOME2 Project Team
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
mbar_initialize(self)
    VALUE self;
{
    RBGTK_INITIALIZE(self, gtk_menu_bar_new());
    return Qnil;
}

/* Defined as property
void        gtk_menu_bar_set_pack_direction (GtkMenuBar *menubar,
                                             GtkPackDirection pack_dir);
GtkPackDirection gtk_menu_bar_get_pack_direction
                                            (GtkMenuBar *menubar);
void        gtk_menu_bar_set_child_pack_direction
                                            (GtkMenuBar *menubar,
                                             GtkPackDirection child_pack_dir);
GtkPackDirection gtk_menu_bar_get_child_pack_direction
                                            (GtkMenuBar *menubar);
*/

void 
Init_gtk_menu_bar()
{
    VALUE gMenuBar = G_DEF_CLASS(GTK_TYPE_MENU_BAR, "MenuBar", mGtk);
    rb_define_method(gMenuBar, "initialize", mbar_initialize, 0);

#if GTK_CHECK_VERSION(2,8,0)
    /* GtkPackDirection */
    G_DEF_CLASS(GTK_TYPE_PACK_DIRECTION, "PackDirection", gMenuBar);
    G_DEF_CONSTANTS(gMenuBar, GTK_TYPE_PACK_DIRECTION, "GTK_PACK_DIRECTION_");
#endif
}
