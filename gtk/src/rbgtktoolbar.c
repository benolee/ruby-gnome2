/* -*- c-file-style: "ruby" -*- */
/************************************************

  rbgtktoolbar.c -

  $Author: mutoh $
  $Date: 2002/05/19 13:59:10 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
tbar_initialize(argc, argv, self)
    int argc;
    VALUE *argv;
    VALUE self;
{
    VALUE arg1, arg2;
    GtkOrientation orientation = GTK_ORIENTATION_HORIZONTAL;
    GtkToolbarStyle style = GTK_TOOLBAR_BOTH;

    rb_scan_args(argc, argv, "02", &arg1, &arg2);
    if (!NIL_P(arg1)) orientation = (GtkOrientation)NUM2INT(arg1);
    if (!NIL_P(arg2)) style = (GtkToolbarStyle)NUM2INT(arg2);

#if GTK_MAJOR_VERSION >= 2
    {
        GtkWidget* w = gtk_toolbar_new();
        gtk_toolbar_set_orientation(GTK_TOOLBAR(w), orientation);
        gtk_toolbar_set_style(GTK_TOOLBAR(w), style);
        set_widget(self, w);
    }    
#else
    set_widget(self, gtk_toolbar_new(orientation, style));
#endif
    return Qnil;
}

static VALUE
tbar_get_widget(widget, type)
    GtkWidget *widget;
    VALUE type;
{
    VALUE ret = Qnil;
    switch (NUM2INT(type)){
      case GTK_TOOLBAR_CHILD_SPACE:
        ret = Qnil;
	break;
      case GTK_TOOLBAR_CHILD_BUTTON:
	ret = make_widget(gButton, widget);
	break;
      case GTK_TOOLBAR_CHILD_TOGGLEBUTTON:
	ret = make_widget(gTButton, widget);
	break;
      case GTK_TOOLBAR_CHILD_RADIOBUTTON:
	ret = make_widget(gRButton, widget);
	break;
      case GTK_TOOLBAR_CHILD_WIDGET:
	ret = make_widget(gWidget, widget);
	break;
    }
    return ret;
}

static VALUE
tbar_append_item(self, text, ttext, ptext, icon, func)
    VALUE self, text, ttext, ptext, icon, func;
{
    GtkWidget *ret = NULL;

    if (NIL_P(func)) {
	func = rb_f_lambda();
    }
    add_relative(self, func);
    ret = gtk_toolbar_append_item(GTK_TOOLBAR(get_widget(self)),
				  NIL_P(text)?NULL:STR2CSTR(text),
				  NIL_P(ttext)?NULL:STR2CSTR(ttext),
				  NIL_P(ptext)?NULL:STR2CSTR(ptext),
				  NIL_P(icon)?NULL:get_widget(icon),
				  GTK_SIGNAL_FUNC(exec_callback),
				  (gpointer)func);
    return ret ? make_widget(gWidget, ret) : Qnil;
}

static VALUE
tbar_prepend_item(self, text, ttext, ptext, icon, func)
    VALUE self, text, ttext, ptext, icon, func;
{
    GtkWidget *ret = NULL;

    if (NIL_P(func)) {
	func = rb_f_lambda();
    }
    add_relative(self, func);
    ret = gtk_toolbar_prepend_item(GTK_TOOLBAR(get_widget(self)),
				   NIL_P(text)?NULL:STR2CSTR(text),
				   NIL_P(ttext)?NULL:STR2CSTR(ttext),
				   NIL_P(ptext)?NULL:STR2CSTR(ptext),
				   NIL_P(icon)?NULL:get_widget(icon),
				   GTK_SIGNAL_FUNC(exec_callback),
				   (gpointer)func);
    return ret ? make_widget(gWidget, ret) : Qnil;
}

static VALUE
tbar_insert_item(self, text, ttext, ptext, icon, func, pos)
    VALUE self, text, ttext, ptext, icon, func, pos;
{
    GtkWidget *ret = NULL;

    if (NIL_P(func)) {
	func = rb_f_lambda();
    }
    add_relative(self, func);
    ret = gtk_toolbar_insert_item(GTK_TOOLBAR(get_widget(self)),
				  NIL_P(text)?NULL:STR2CSTR(text),
				  NIL_P(ttext)?NULL:STR2CSTR(ttext),
				  NIL_P(ptext)?NULL:STR2CSTR(ptext),
				  NIL_P(icon)?NULL:get_widget(icon),
				  GTK_SIGNAL_FUNC(exec_callback),
				  (gpointer)func,
				  NUM2INT(pos));
    return ret ? make_widget(gWidget, ret) : Qnil;
}

static VALUE
tbar_append_space(self)
    VALUE self;
{
    gtk_toolbar_append_space(GTK_TOOLBAR(get_widget(self)));
    return self;
}

static VALUE
tbar_prepend_space(self)
    VALUE self;
{
    gtk_toolbar_prepend_space(GTK_TOOLBAR(get_widget(self)));
    return self;
}

static VALUE
tbar_insert_space(self, pos)
    VALUE self, pos;
{
    gtk_toolbar_insert_space(GTK_TOOLBAR(get_widget(self)), NUM2INT(pos));
    return self;
}

static VALUE
tbar_append_widget(self, widget, ttext, ptext)
    VALUE self, widget, ttext, ptext;
{
    gtk_toolbar_append_widget(GTK_TOOLBAR(get_widget(self)),
                              get_widget(widget),
                              NIL_P(ttext)?NULL:STR2CSTR(ttext),
                              NIL_P(ptext)?NULL:STR2CSTR(ptext));
    return self;
}

static VALUE
tbar_prepend_widget(self, widget, ttext, ptext)
    VALUE self, widget, ttext, ptext;
{
    gtk_toolbar_prepend_widget(GTK_TOOLBAR(get_widget(self)),
                              get_widget(widget),
                              NIL_P(ttext)?NULL:STR2CSTR(ttext),
                              NIL_P(ptext)?NULL:STR2CSTR(ptext));
    return self;
}

static VALUE
tbar_insert_widget(self, widget, ttext, ptext, pos)
    VALUE self, widget, ttext, ptext, pos;
{
    gtk_toolbar_insert_widget(GTK_TOOLBAR(get_widget(self)),
                              get_widget(widget),
                              NIL_P(ttext)?NULL:STR2CSTR(ttext),
                              NIL_P(ptext)?NULL:STR2CSTR(ptext),
                              NUM2INT(pos));
    return self;
}

static VALUE
tbar_append_element(self, type, widget, text, ttext, ptext, icon)
    VALUE self, type, widget, text, ttext, ptext, icon;
{
    VALUE func = (VALUE)NULL;
    void *callback = NULL;
    GtkWidget *ret = NULL;

    if (rb_block_given_p()) {
	func = rb_f_lambda();
	add_relative(self, func);
	callback = exec_callback;
    }
    ret = gtk_toolbar_append_element(GTK_TOOLBAR(get_widget(self)),
				      NUM2INT(type),
				      NIL_P(widget)?NULL:get_widget(widget),
				      NIL_P(text)?NULL:STR2CSTR(text),
				      NIL_P(ttext)?NULL:STR2CSTR(ttext),
				      NIL_P(ptext)?NULL:STR2CSTR(ptext),
				      NIL_P(icon)?NULL:get_widget(icon),
				      GTK_SIGNAL_FUNC(callback),
				      (gpointer)func);
    return tbar_get_widget(ret, type);
}

static VALUE
tbar_prepend_element(self, type, widget, text, ttext, ptext, icon)
    VALUE self, type, widget, text, ttext, ptext, icon;
{
    VALUE func = (VALUE)NULL;
    void *callback = NULL;
    GtkWidget *ret = NULL;

    if (rb_block_given_p()) {
	func = rb_f_lambda();
	add_relative(self, func);
	callback = exec_callback;
    }
    ret = gtk_toolbar_prepend_element(GTK_TOOLBAR(get_widget(self)),
				      NUM2INT(type),
				      NIL_P(widget)?NULL:get_widget(widget),
				      NIL_P(text)?NULL:STR2CSTR(text),
				      NIL_P(ttext)?NULL:STR2CSTR(ttext),
				      NIL_P(ptext)?NULL:STR2CSTR(ptext),
				      NIL_P(icon)?NULL:get_widget(icon),
				      GTK_SIGNAL_FUNC(callback),
				      (gpointer)func);
    return tbar_get_widget(ret, type);
}

static VALUE
tbar_insert_element(self, type, widget, text, ttext, ptext, icon, position)
    VALUE self, type, widget, text, ttext, ptext, icon, position;
{
    VALUE func = (VALUE)NULL;
    void *callback = NULL;
    GtkWidget *ret = NULL;

    if (rb_block_given_p()) {
	func = rb_f_lambda();
	add_relative(self, func);
	callback = exec_callback;
    }
    ret = gtk_toolbar_insert_element(GTK_TOOLBAR(get_widget(self)),
				     NUM2INT(type),
				     NIL_P(widget)?NULL:get_widget(widget),
				     NIL_P(text)?NULL:STR2CSTR(text),
				     NIL_P(ttext)?NULL:STR2CSTR(ttext),
				     NIL_P(ptext)?NULL:STR2CSTR(ptext),
				     NIL_P(icon)?NULL:get_widget(icon),
				     GTK_SIGNAL_FUNC(callback),
				     (gpointer)func,
				     NUM2INT(position));
    return tbar_get_widget(ret, type);
}

static VALUE
tbar_set_orientation(self, orientation)
    VALUE self, orientation;
{
    gtk_toolbar_set_orientation(GTK_TOOLBAR(get_widget(self)), 
				(GtkOrientation)NUM2INT(orientation));
    return self;
}

static VALUE
tbar_set_style(self, style)
    VALUE self, style;
{
    gtk_toolbar_set_style(GTK_TOOLBAR(get_widget(self)), 
			  (GtkToolbarStyle)NUM2INT(style));
    return self;
}

#if GTK_MAJOR_VERSION < 2
static VALUE
tbar_set_space_size(self, size)
    VALUE self, size;
{
    gtk_toolbar_set_space_size(GTK_TOOLBAR(get_widget(self)), NUM2INT(size));
    return self;
}
#endif

static VALUE
tbar_set_tooltips(self, enable)
    VALUE self, enable;
{
    gtk_toolbar_set_tooltips(GTK_TOOLBAR(get_widget(self)), RTEST(enable));
    return self;
}

#if GTK_MAJOR_VERSION < 2

static VALUE
tbar_set_button_relief(self, style)
    VALUE self, style;
{
    gtk_toolbar_set_button_relief(GTK_TOOLBAR(get_widget(self)),
				  NUM2INT(style));
    return self;
}

static VALUE
tbar_get_button_relief(self)
    VALUE self;
{
    GtkReliefStyle style;
    style = gtk_toolbar_get_button_relief(GTK_TOOLBAR(get_widget(self)));
    return INT2FIX(style);
}

static VALUE
tbar_set_space_style(self, style)
    VALUE self, style;
{
    gtk_toolbar_set_space_style(GTK_TOOLBAR(get_widget(self)),
				NUM2INT(style));
    return self;
}

#endif

void Init_gtk_toolbar()
{
    gToolbar = rb_define_class_under(mGtk, "Toolbar", gContainer);

    rb_define_const(gToolbar, "CHILD_SPACE", INT2NUM(GTK_TOOLBAR_CHILD_SPACE));
    rb_define_const(gToolbar, "CHILD_BUTTON", INT2NUM(GTK_TOOLBAR_CHILD_BUTTON));
    rb_define_const(gToolbar, "CHILD_TOGGLEBUTTON", INT2NUM(GTK_TOOLBAR_CHILD_TOGGLEBUTTON));
    rb_define_const(gToolbar, "CHILD_RADIOBUTTON", INT2NUM(GTK_TOOLBAR_CHILD_RADIOBUTTON));
    rb_define_const(gToolbar, "CHILD_WIDGET", INT2NUM(GTK_TOOLBAR_CHILD_WIDGET));
    rb_define_const(gToolbar, "SPACE_EMPTY", INT2FIX(GTK_TOOLBAR_SPACE_EMPTY));
    rb_define_const(gToolbar, "SPACE_LINE", INT2FIX(GTK_TOOLBAR_SPACE_LINE));
    rb_define_const(gToolbar, "ICONS", INT2FIX(GTK_TOOLBAR_ICONS));
    rb_define_const(gToolbar, "TEXT", INT2FIX(GTK_TOOLBAR_TEXT));
    rb_define_const(gToolbar, "BOTH", INT2FIX(GTK_TOOLBAR_BOTH));

    rb_define_const(gToolbar, "SIGNAL_ORIENTATION_CHANGED", rb_str_new2("orientation_changed"));
    rb_define_const(gToolbar, "SIGNAL_STYLE_CHANGED", rb_str_new2("style_changed"));

    rb_define_method(gToolbar, "initialize", tbar_initialize, -1);
    rb_define_method(gToolbar, "append_item", tbar_append_item, 5);
    rb_define_method(gToolbar, "prepend_item", tbar_prepend_item, 5);
    rb_define_method(gToolbar, "insert_item", tbar_insert_item, 6);
    rb_define_method(gToolbar, "append_space", tbar_append_space, 0);
    rb_define_method(gToolbar, "prepend_space", tbar_prepend_space, 0);
    rb_define_method(gToolbar, "insert_space", tbar_insert_space, 1);
    rb_define_method(gToolbar, "append_widget", tbar_append_widget, 3);
    rb_define_method(gToolbar, "prepend_widget", tbar_prepend_widget, 3);
    rb_define_method(gToolbar, "insert_widget", tbar_insert_widget, 4);
    rb_define_method(gToolbar, "append_element", tbar_append_element, 6);
    rb_define_method(gToolbar, "prepend_element", tbar_prepend_element, 6);
    rb_define_method(gToolbar, "insert_element", tbar_insert_element, 7);
    rb_define_method(gToolbar, "set_orientation", tbar_set_orientation, 1);
    rb_define_method(gToolbar, "set_style", tbar_set_style, 1);
#if GTK_MAJOR_VERSION < 2
    rb_define_method(gToolbar, "set_space_size", tbar_set_space_size, 1);
#endif
    rb_define_method(gToolbar, "set_tooltips", tbar_set_tooltips, 1);
#if GTK_MAJOR_VERSION < 2
    rb_define_method(gToolbar, "set_button_relief", tbar_set_button_relief, 1);
    rb_define_method(gToolbar, "get_button_relief", tbar_get_button_relief, 0);
    rb_define_method(gToolbar, "set_space_style", tbar_set_space_style, 1);
#endif
}
