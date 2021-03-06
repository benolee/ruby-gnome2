/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkradiotoolbutton.c -

  $Author: mutoh $
  $Date: 2006/06/17 06:59:32 $

  Copyright (C) 2004-2006 Masao Mutoh
************************************************/

#include "global.h"
                                                                                
#if GTK_CHECK_VERSION(2,4,0)

#define _SELF(self) (GTK_RADIO_TOOL_BUTTON(RVAL2GOBJ(self)))

static VALUE gRToolButton;

static VALUE
rbtn_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE group_or_stock_id, stock_id;
    GtkToolItem *widget;

    if (rb_scan_args(argc, argv, "02", &group_or_stock_id, &stock_id) > 0) {
        GSList* list = NULL;
        if (TYPE(group_or_stock_id) == T_ARRAY){
            int i;
            Check_Type(group_or_stock_id, T_ARRAY);
            for (i = 0; i < RARRAY_LEN(group_or_stock_id); i++) {
                list = g_slist_append(list, RVAL2GOBJ(RARRAY_PTR(group_or_stock_id)[i]));
            }
        } else if (rb_obj_is_kind_of(group_or_stock_id, gRToolButton)){
            list = gtk_radio_tool_button_get_group(_SELF(group_or_stock_id));
        } else {
            list = NULL;
        }
        if (NIL_P(stock_id)){
            widget = gtk_radio_tool_button_new(list);
        } else {
            if (TYPE(stock_id) == T_SYMBOL){
                widget = gtk_radio_tool_button_new_from_stock(list, rb_id2name(SYM2ID(stock_id)));
            } else {
                widget = gtk_radio_tool_button_new_from_stock(list, RVAL2CSTR(stock_id));
            }
        }
    } else {
        widget = gtk_radio_tool_button_new(NULL);
    }
    
    RBGTK_INITIALIZE(self, widget);
    return Qnil;
}

static VALUE
rbtn_get_group(VALUE self)
{
    /* Owned by GTK+ */
    return GSLIST2ARY(gtk_radio_tool_button_get_group(_SELF(self)));
}

static VALUE
rbtn_set_group(VALUE self, VALUE group)
{
    GSList* list = NULL;
    if (TYPE(group) == T_ARRAY){
        int i;
        for (i = 0; i < RARRAY_LEN(group); i++){
            list = g_slist_append(list, RVAL2GOBJ(RARRAY_PTR(group)[i]));
        }
    } else {
        list = gtk_radio_tool_button_get_group(_SELF(group));
    }
    gtk_radio_tool_button_set_group(_SELF(self), list);
        
    return self;
}

#endif

void 
Init_gtk_radiotoolbutton()
{
#if GTK_CHECK_VERSION(2,4,0)
    gRToolButton = G_DEF_CLASS(GTK_TYPE_RADIO_TOOL_BUTTON, "RadioToolButton", mGtk);

    rb_define_method(gRToolButton, "initialize", rbtn_initialize, -1);
    rb_define_method(gRToolButton, "group", rbtn_get_group, 0);
    rb_define_method(gRToolButton, "set_group", rbtn_set_group, 1);

    G_DEF_SETTERS(gRToolButton);
#endif
}
