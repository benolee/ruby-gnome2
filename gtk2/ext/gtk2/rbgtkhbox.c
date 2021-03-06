/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkhbox.c -

  $Author: ggc $
  $Date: 2007/07/13 16:07:31 $

  Copyright (C) 2002,2003 Ruby-GNOME2 Project Team
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
hbox_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE homogeneous, spacing;

    rb_scan_args(argc, argv, "02", &homogeneous, &spacing);

    RBGTK_INITIALIZE(self, gtk_hbox_new(RVAL2CBOOL(homogeneous),
				  (NIL_P(spacing)?0:NUM2INT(spacing))));
    return Qnil;
}

void 
Init_gtk_hbox()
{
    VALUE gHBox = G_DEF_CLASS(GTK_TYPE_HBOX, "HBox", mGtk);

    rb_define_method(gHBox, "initialize", hbox_initialize, -1);
}
