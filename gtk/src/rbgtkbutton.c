/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkbutton.c -

  $Author: mutoh $
  $Date: 2002/09/14 15:43:40 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
button_initialize(argc, argv, self)
    int argc;
    VALUE *argv;
    VALUE self;
{
    VALUE label;
    GtkWidget *widget;

    if (rb_scan_args(argc, argv, "01", &label) == 1) {
	widget = gtk_button_new_with_label(RVAL2CSTR(label));
    }
    else {
	widget = gtk_button_new();
    }

    RBGTK_INITIALIZE(self, widget);
    return Qnil;
}

static VALUE
button_pressed(self)
    VALUE self;
{
    gtk_button_pressed(GTK_BUTTON(RVAL2GOBJ(self)));
    return self;
}

static VALUE
button_released(self)
    VALUE self;
{
    gtk_button_released(GTK_BUTTON(RVAL2GOBJ(self)));
    return self;
}

static VALUE
button_clicked(self)
    VALUE self;
{
    gtk_button_clicked(GTK_BUTTON(RVAL2GOBJ(self)));
    return self;
}

static VALUE
button_enter(self)
    VALUE self;
{
    gtk_button_enter(GTK_BUTTON(RVAL2GOBJ(self)));
    return self;
}

static VALUE
button_leave(self)
    VALUE self;
{
    gtk_button_leave(GTK_BUTTON(RVAL2GOBJ(self)));
    return self;
}

static VALUE
button_set_relief(self, style)
    VALUE self, style;
{
    gtk_button_set_relief(GTK_BUTTON(RVAL2GOBJ(self)), NUM2INT(style));
    return self;
}

static VALUE
button_get_relief(self)
    VALUE self;
{
    GtkReliefStyle style;
    style = gtk_button_get_relief(GTK_BUTTON(RVAL2GOBJ(self)));
    return INT2FIX(style);
}

void 
Init_gtk_button()
{
    VALUE gButton = G_DEF_CLASS(GTK_TYPE_BUTTON, "Button", mGtk);

    rb_define_method(gButton, "initialize", button_initialize, -1);
    rb_define_method(gButton, "pressed", button_pressed, 0);
    rb_define_method(gButton, "released", button_released, 0);
    rb_define_method(gButton, "clicked", button_clicked, 0);
    rb_define_method(gButton, "enter", button_enter, 0);
    rb_define_method(gButton, "leave", button_leave, 0);
    rb_define_method(gButton, "set_relief", button_set_relief, 1);
    rb_define_method(gButton, "get_relief", button_get_relief, 0);
}
