/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkselectiondata.c -

  $Author: mutoh $
  $Date: 2002/09/07 06:50:56 $

  Copyright (C) 2002 Masao Mutoh
************************************************/


#include "global.h"

#define _SELF(d) ((GtkSelectionData*)RVAL2BOXED(d))

static VALUE
gtkselectiondata_selection(self)
    VALUE self;
{
    return BOXED2RVAL(_SELF(self)->selection, GDK_TYPE_ATOM);
}

static VALUE
gtkselectiondata_target(self)
    VALUE self;
{
    return BOXED2RVAL(_SELF(self)->target, GDK_TYPE_ATOM);
}

static VALUE
gtkselectiondata_type(self)
    VALUE self;
{
    return BOXED2RVAL(_SELF(self)->type, GDK_TYPE_ATOM);
}

static VALUE
gtkselectiondata_format(self)
    VALUE self;
{
    return INT2NUM(_SELF(self)->format);
}

static VALUE
gtkselectiondata_data(self)
    VALUE self;
{
    return rb_str_new(_SELF(self)->data, 
					  _SELF(self)->length);
}

/* Instance Methods */
static VALUE
gtkselectiondata_set(self, type, format, data)
    VALUE self, type, format, data;
{
    gtk_selection_data_set(_SELF(self), 
                           (((GdkAtomData*)RVAL2BOXED(type))->atom),
						   NUM2INT(format), RSTRING(data)->ptr, 
						   RSTRING(data)->len);
    return self;
}

static VALUE
gtkselectiondata_copy(self)
    VALUE self;
{
    return BOXED2RVAL(gtk_selection_data_copy(_SELF(self)), GTK_TYPE_SELECTION_DATA);
}

void
Init_gtk_selectiondata()
{
    VALUE gSelectionData = G_DEF_CLASS(GTK_TYPE_SELECTION_DATA, "SelectionData", mGtk);

    rb_define_method(gSelectionData, "selection", gtkselectiondata_selection, 0);
    rb_define_method(gSelectionData, "target", gtkselectiondata_target, 0);
    rb_define_method(gSelectionData, "type", gtkselectiondata_type, 0);
    rb_define_method(gSelectionData, "format", gtkselectiondata_format, 0);
    rb_define_method(gSelectionData, "data", gtkselectiondata_data, 0);

    rb_define_method(gSelectionData, "set", gtkselectiondata_set, 3);
    rb_define_method(gSelectionData, "copy", gtkselectiondata_copy, 0);

} 

