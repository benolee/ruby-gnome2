/* -*- c-file-style: "ruby" -*- */
/************************************************

  rbgtkimage.c -

  $Author: igapy $
  $Date: 2002/05/30 00:46:41 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
image_initialize(self, val, mask)
    VALUE self, val, mask;
{
    set_widget(self, gtk_image_new_from_image(
        get_gdkimage(val),
        (GdkBitmap*)get_gdkpixmap(mask)));
    return Qnil;
}

static VALUE
image_set(self, val, mask)
    VALUE self, val, mask;
{
    gtk_image_set(GTK_IMAGE(get_widget(self)), get_gdkimage(val),
		  get_gdkpixmap(mask));
    return self;
}

static VALUE
image_get(self)
    VALUE self;
{
    GdkImage  *val;
    GdkBitmap *mask;

    gtk_image_get(GTK_IMAGE(get_widget(self)), &val, &mask);

    return rb_assoc_new(make_gdkimage(val),
			make_gdkpixmap(mask));
}

void Init_gtk_image()
{
    static rbgtk_class_info cinfo;

    gImage = rb_define_class_under(mGtk, "Image", gMisc);
    cinfo.klass = gImage;
    cinfo.gtype = GTK_TYPE_IMAGE;
    cinfo.mark = 0;
    cinfo.free = 0;
    rbgtk_register_class(&cinfo);

    rb_define_method(gImage, "initialize", image_initialize, 2);
    rb_define_method(gImage, "set", image_set, 2);
    rb_define_method(gImage, "get", image_get, 0);
}
