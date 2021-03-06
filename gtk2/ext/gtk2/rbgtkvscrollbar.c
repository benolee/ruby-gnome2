/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkvscrollbar.c -

  $Author: mutoh $
  $Date: 2003/02/01 16:46:24 $

  Copyright (C) 2002,2003 Ruby-GNOME2 Project Team
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
vscrollbar_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE arg1;
    GtkAdjustment *adj = NULL;

    rb_scan_args(argc, argv, "01", &arg1);
    if (!NIL_P(arg1)) adj = GTK_ADJUSTMENT(RVAL2GOBJ(arg1));

    RBGTK_INITIALIZE(self, gtk_vscrollbar_new(adj));
    return Qnil;
}

void 
Init_gtk_vscrollbar()
{
    VALUE gVScrollbar = G_DEF_CLASS(GTK_TYPE_VSCROLLBAR, "VScrollbar", mGtk);
    rb_define_method(gVScrollbar, "initialize", vscrollbar_initialize, -1);
}
