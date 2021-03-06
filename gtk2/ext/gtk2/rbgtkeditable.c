/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkeditable.c -

  $Author: ggc $
  $Date: 2007/07/13 16:07:31 $

  Copyright (C) 2002,2003 Ruby-GNOME2 Project Team
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
edit_sel_region(VALUE self, VALUE start, VALUE end)
{
    gtk_editable_select_region(GTK_EDITABLE(RVAL2GOBJ(self)),
			       NUM2INT(start), NUM2INT(end));
    return self;
}

static VALUE
edit_get_sel_bounds(VALUE self)
{
    gint start, end;
    gboolean ret;
    ret = gtk_editable_get_selection_bounds(GTK_EDITABLE(RVAL2GOBJ(self)),
                                            &start, &end);
    return ret ? rb_ary_new3(2, INT2NUM(start), INT2NUM(end)) : Qnil;
}

static VALUE
edit_insert_text(VALUE self, VALUE new_text, VALUE pos)
{
    gint p = NUM2INT(pos);

    StringValue(new_text);
    gtk_editable_insert_text(GTK_EDITABLE(RVAL2GOBJ(self)),
			     RSTRING_PTR(new_text),
			     RSTRING_LEN(new_text),
			     &p);
    return INT2NUM(p);
}

static VALUE
edit_delete_text(VALUE self, VALUE start, VALUE end)
{
    gtk_editable_delete_text(GTK_EDITABLE(RVAL2GOBJ(self)),
			     NUM2INT(start), NUM2INT(end));
    return self;
}

static VALUE
edit_get_chars(VALUE self, VALUE start, VALUE end)
{
    return CSTR2RVAL_FREE(
    	gtk_editable_get_chars(GTK_EDITABLE(RVAL2GOBJ(self)),   /* check s */
			       NUM2INT(start), NUM2INT(end)));  /* check start,end */
}

static VALUE
edit_delete_selection(VALUE self)
{
    gtk_editable_delete_selection(GTK_EDITABLE(RVAL2GOBJ(self)));
    return self;
}

static VALUE
edit_get_position(VALUE self)
{
    return INT2NUM(gtk_editable_get_position(GTK_EDITABLE(RVAL2GOBJ(self))));
}

static VALUE
edit_set_position(VALUE self, VALUE position)
{
    gtk_editable_set_position(GTK_EDITABLE(RVAL2GOBJ(self)),
			      NUM2INT(position));
    return self;
}

static VALUE
edit_set_editable(VALUE self, VALUE editable)
{
    gtk_editable_set_editable(GTK_EDITABLE(RVAL2GOBJ(self)), RVAL2CBOOL(editable));
    return self;
}

static VALUE
edit_get_editable(VALUE self)
{
    return CBOOL2RVAL(gtk_editable_get_editable(GTK_EDITABLE(RVAL2GOBJ(self))));
}

static VALUE
edit_cut_clipboard(VALUE self)
{
    gtk_editable_cut_clipboard(GTK_EDITABLE(RVAL2GOBJ(self)));
    return self;
}

static VALUE
edit_copy_clipboard(VALUE self)
{
    gtk_editable_copy_clipboard(GTK_EDITABLE(RVAL2GOBJ(self)));
    return self;
}

static VALUE
edit_paste_clipboard(VALUE self)
{
    gtk_editable_paste_clipboard(GTK_EDITABLE(RVAL2GOBJ(self)));
    return self;
}

void 
Init_gtk_editable()
{
    VALUE mEditable = G_DEF_INTERFACE(GTK_TYPE_EDITABLE, "Editable", mGtk);

    rb_define_method(mEditable, "select_region", edit_sel_region, 2);
    rb_define_method(mEditable, "selection_bounds", edit_get_sel_bounds, 0);
    rb_define_method(mEditable, "insert_text", edit_insert_text, 2);
    rb_define_method(mEditable, "delete_text", edit_delete_text, 2);
    rb_define_method(mEditable, "get_chars", edit_get_chars, 2);
    rb_define_method(mEditable, "delete_selection", edit_delete_selection, 0);
    rb_define_method(mEditable, "position", edit_get_position, 0);
    rb_define_method(mEditable, "set_position", edit_set_position, 1);
    rb_define_method(mEditable, "set_editable", edit_set_editable, 1);
    rb_define_method(mEditable, "editable?", edit_get_editable, 0);
    rb_define_method(mEditable, "copy_clipboard", edit_copy_clipboard, 0);
    rb_define_method(mEditable, "cut_clipboard", edit_cut_clipboard, 0);
    rb_define_method(mEditable, "paste_clipboard", edit_paste_clipboard, 0);

    G_DEF_SETTERS(mEditable);
}
