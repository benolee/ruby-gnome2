/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkcellrenderertext.c -

  $Author: mutoh $
  $Date: 2002/10/02 15:39:06 $

  Copyright (C) 2002 Masao Mutoh
************************************************/

#include "global.h"


#define _SELF(s) (GTK_CELL_RENDERER_TEXT(RVAL2GOBJ(s)))

static VALUE
crtext_initialize(self)
    VALUE self;
{
    RBGTK_INITIALIZE(self, gtk_cell_renderer_text_new());
    return Qnil;
}

static VALUE
crtext_set_fixed_height_from_font(self, number_of_rows)
    VALUE self, number_of_rows;
{
    gtk_cell_renderer_text_set_fixed_height_from_font(_SELF(self), NUM2INT(number_of_rows));
    return self;
}

static VALUE
crtext_set_fixed_height_from_font_equal(self, number_of_rows)
    VALUE self, number_of_rows;
{
    gtk_cell_renderer_text_set_fixed_height_from_font(_SELF(self), NUM2INT(number_of_rows));
    return number_of_rows;
}

void
Init_gtk_cellrenderertext()
{
    VALUE renderer = G_DEF_CLASS(GTK_TYPE_CELL_RENDERER_TEXT, "CellRendererText", mGtk);
    
    rb_define_method(renderer, "initialize", crtext_initialize, 0);
    rb_define_method(renderer, "set_fixed_height_from_font", crtext_set_fixed_height_from_font, 1);
    rb_define_method(renderer, "fixed_height_from_font=", crtext_set_fixed_height_from_font_equal, 1);
}


 
