/************************************************

  rbgdkplug.c -

  $Author: sakai $
  $Date: 2002/08/12 09:39:49 $

  Copyright (C) 2002 Neil Conway
************************************************/

#include "global.h"

#ifdef HAVE_GTK_PLUG_GET_TYPE

static VALUE
plug_initialize(argc, argv, self)
    int argc;
    VALUE *argv;
    VALUE self;
{
    VALUE socket_id;
    GdkNativeWindow id;

    if (rb_scan_arg(argc, argv, "01", &socket_id) == 0)
        id = 0;
    else {
#ifdef GDK_NATIVE_WINDOW_POINTER
        id = GUINT_TO_POINTER(NUM2ULONG(socket_id));
#else
        id = NUM2UINT(socket_id);
#endif
    }

    RBGTK_INITIALIZE(self, gtk_plug_new(id));
    return Qnil;
}

static VALUE
plug_construct(self, socket_id)
    VALUE self, socket_id;
{
#ifdef GDK_NATIVE_WINDOW_POINTER
    gtk_plug_construct(GTK_PLUG(RVAL2GOBJ(self)), GUINT_TO_POINTER(NUM2ULONG(socket_id)));
#else
    gtk_plug_construct(GTK_PLUG(RVAL2GOBJ(self)), (guint32)NUM2UINT(socket_id));
#endif
    return Qnil;
}

static VALUE
plug_get_id(self)
    VALUE self;
{
    GdkNativeWindow id = gtk_plug_get_id();
#ifdef GDK_NATIVE_WINDOW_POINTER
    return UINT2NUM(GPOINTER_TO_UINT(id));
#else
    return UINT2NUM(id);
#endif
}

#endif /* HAVE_GTK_PLUG_GET_TYPE */

void Init_gtk_plug()
{
#ifdef HAVE_GTK_PLUG_GET_TYPE
    VALUE gPlug = G_DEF_CLASS(GTK_TYPE_PLUG, "Plug", mGtk);
    
    rb_define_method(gPlug, "initialize", plug_initialize, -1);
    rb_define_method(gPlug, "construct", plug_construct, 1);
    rb_define_method(gPlug, "id", plug_get_id, 0);
#endif
}
