/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkscrolledwindow.c -

  $Author: mutoh $
  $Date: 2002/10/23 18:02:18 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
scwin_initialize(argc, argv, self)
    int argc;
    VALUE *argv;
    VALUE self;
{
    VALUE arg1, arg2;
    GtkAdjustment *h_adj = NULL;
    GtkAdjustment *v_adj = NULL;

    rb_scan_args(argc, argv, "02", &arg1, &arg2);

    if (!NIL_P(arg1)) h_adj = GTK_ADJUSTMENT(RVAL2GOBJ(arg1));
    if (!NIL_P(arg2)) v_adj = GTK_ADJUSTMENT(RVAL2GOBJ(arg2));

    RBGTK_INITIALIZE(self, gtk_scrolled_window_new(h_adj, v_adj));
    return Qnil;
}

static VALUE
scwin_set_policy(self, hpolicy, vpolicy)
    VALUE self, hpolicy, vpolicy;
{
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(RVAL2GOBJ(self)),
                                   (GtkPolicyType)NUM2INT(hpolicy),
                                   (GtkPolicyType)NUM2INT(vpolicy));
    return self;
}

static VALUE
scwin_get_policy(self)
    VALUE self;
{
    GtkPolicyType hpolicy, vpolicy;

    gtk_scrolled_window_get_policy(GTK_SCROLLED_WINDOW(RVAL2GOBJ(self)),
                                   &hpolicy, &vpolicy);
    return rb_ary_new3(2, INT2FIX(hpolicy), INT2FIX(vpolicy));
}

static VALUE
scwin_add_with_viewport(self, other)
    VALUE self, other;
{
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(RVAL2GOBJ(self)),
                                          GTK_WIDGET(RVAL2GOBJ(other)));
    return self;
}


void 
Init_gtk_scrolled_window()
{
    VALUE gScrolledWin = G_DEF_CLASS(GTK_TYPE_SCROLLED_WINDOW, "ScrolledWindow", mGtk);

    rb_define_method(gScrolledWin, "initialize", scwin_initialize, -1);
    rb_define_method(gScrolledWin, "set_policy", scwin_set_policy, 2);
    rb_define_method(gScrolledWin, "policy", scwin_get_policy, 0);
    rb_define_method(gScrolledWin, "add_with_viewport", scwin_add_with_viewport, 1);
}
