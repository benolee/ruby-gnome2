/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkstatusbar.c -

  $Author: ggc $
  $Date: 2007/07/13 16:07:32 $

  Copyright (C) 2002,2003 Ruby-GNOME2 Project Team
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

#define _SELF(self) (GTK_STATUSBAR(RVAL2GOBJ(self)))

static VALUE
statusbar_initialize(VALUE self)
{
    RBGTK_INITIALIZE(self, gtk_statusbar_new());
    return Qnil;
}

static VALUE
statusbar_get_context_id(VALUE self, VALUE text)
{

    return INT2FIX(gtk_statusbar_get_context_id(_SELF(self),
                                                RVAL2CSTR(text)));
}

static VALUE
statusbar_push(VALUE self, VALUE id, VALUE text)
{
    return INT2FIX(gtk_statusbar_push(_SELF(self), 
                                      NUM2INT(id), RVAL2CSTR(text)));
}
    
static VALUE
statusbar_pop(VALUE self, VALUE id)
{
    gtk_statusbar_pop(_SELF(self), NUM2INT(id));
    return self;

}

static VALUE
statusbar_remove(VALUE self, VALUE cid, VALUE mid)
{
    gtk_statusbar_remove(_SELF(self), NUM2INT(cid), NUM2INT(mid)); 
    return self;
}

static VALUE
statusbar_set_has_resize_grip(VALUE self, VALUE setting)
{
    gtk_statusbar_set_has_resize_grip(_SELF(self), RVAL2CBOOL(setting));
    return self;
}

static VALUE
statusbar_get_has_resize_grip(VALUE self)
{
    return CBOOL2RVAL(gtk_statusbar_get_has_resize_grip(_SELF(self)));
}

void 
Init_gtk_statusbar()
{
    VALUE gStatusBar = G_DEF_CLASS(GTK_TYPE_STATUSBAR, "Statusbar", mGtk);

    rb_define_method(gStatusBar, "initialize", statusbar_initialize, 0);
    rb_define_method(gStatusBar, "get_context_id", statusbar_get_context_id, 1);
    rb_define_method(gStatusBar, "push", statusbar_push, 2);
    rb_define_method(gStatusBar, "pop", statusbar_pop, 1);
    rb_define_method(gStatusBar, "remove", statusbar_remove, 2);
    rb_define_method(gStatusBar, "set_has_resize_grip", statusbar_set_has_resize_grip, 1);
    rb_define_method(gStatusBar, "has_resize_grip?", statusbar_get_has_resize_grip, 0);

    G_DEF_SETTERS(gStatusBar);
}
