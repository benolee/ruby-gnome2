/* -*- c-file-style: "ruby" -*- */
/************************************************

  rbgtkvruler.c -

  $Author: mutoh $
  $Date: 2002/06/22 19:50:57 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
vruler_initialize(self)
    VALUE self;
{
    RBGTK_INITIALIZE(self, gtk_vruler_new());
    return Qnil;
}

void Init_gtk_vruler()
{
    static rbgtk_class_info cinfo;

    gVRuler = rb_define_class_under(mGtk, "VRuler", gRuler);
    cinfo.klass = gVRuler;
    cinfo.gtype = GTK_TYPE_VRULER;
    cinfo.mark = 0;
    cinfo.free = 0;
    rbgtk_register_class(&cinfo);

    rb_define_method(gVRuler, "initialize", vruler_initialize, 0);
}
