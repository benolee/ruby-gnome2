/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkinputdialog.c -

  $Author: mutoh $
  $Date: 2003/01/19 14:28:25 $

  Copyright (C) 2002,2003 The Ruby-GNOME2 Project
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
idiag_initialize(self)
    VALUE self;
{
    RBGTK_INITIALIZE(self, gtk_input_dialog_new());
    return Qnil;
}

void 
Init_gtk_input_dialog()
{
    VALUE gInputDialog = G_DEF_CLASS(GTK_TYPE_INPUT_DIALOG, "InputDialog", mGtk);
    rb_define_method(gInputDialog, "initialize", idiag_initialize, 0);
}
