/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkradiomenuitem.c -

  $Author: ggc $
  $Date: 2007/07/13 16:07:31 $

  Copyright (C) 2002-2006 Ruby-GNOME2 Project Team
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi,
                          dellin 
************************************************/

#include "global.h"

static GSList*
ary2gslist(VALUE ary)
{
    long i;
    GSList *glist = NULL;

    if (NIL_P(ary)) return NULL;
    Check_Type(ary, T_ARRAY);
    for (i=0; i<RARRAY_LEN(ary); i++) {
        glist = g_slist_append(glist,RVAL2GOBJ(RARRAY_PTR(ary)[i]));
    }

    return glist;
}

static VALUE
rmitem_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE arg1, arg2, arg3;
    GtkWidget *widget;
    GSList *list = NULL;
    char *label = NULL;
    char *mnemonic = NULL;
    
    if (rb_scan_args(argc, argv, "03", &arg1, &arg2, &arg3) > 0 &&
        TYPE(arg1) == T_STRING) {
        if (NIL_P(arg2) || RVAL2CBOOL(arg2)){
            mnemonic = RVAL2CSTR(arg1);
        } else {
            label = RVAL2CSTR(arg1);
        }
    } else {
        if (!NIL_P(arg2)) {
            if (NIL_P(arg3) || RVAL2CBOOL(arg3)){
                mnemonic = RVAL2CSTR(arg2);
            } else {
                label = RVAL2CSTR(arg2);
            }
        }
        if (rb_obj_is_kind_of(arg1, GTYPE2CLASS(GTK_TYPE_RADIO_MENU_ITEM))){
            list = GTK_RADIO_MENU_ITEM(RVAL2GOBJ(arg1))->group;
        } else if (TYPE(arg1) == T_ARRAY){
            list = ary2gslist(arg1);
        } else if (! NIL_P(arg1)){
            rb_raise(rb_eArgError, "invalid argument %s (expect Array or Gtk::RadioMenuItem)", 
                     rb_class2name(CLASS_OF(label)));
        }
    }
    if (label) {
        widget = gtk_radio_menu_item_new_with_label(list, label);
    } else if (mnemonic){
        widget = gtk_radio_menu_item_new_with_mnemonic(list, mnemonic);
    } else {
        widget = gtk_radio_menu_item_new(list);
    }
    RBGTK_INITIALIZE(self, widget);
    return Qnil;
}

static VALUE
rmitem_get_group(VALUE self)
{
    /* Owened by GTK+ */
    return GSLIST2ARY(gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(RVAL2GOBJ(self))));
}

static VALUE
rmitem_set_group(VALUE self, VALUE grp_ary)
{
    GtkRadioMenuItem *rmitem2add, *rmitem_orig;
    GSList *group;

    rmitem2add = GTK_RADIO_MENU_ITEM(RVAL2GOBJ(self));
    rmitem_orig = GTK_RADIO_MENU_ITEM(RVAL2GOBJ(rb_ary_entry(grp_ary, 0)));
    group = gtk_radio_menu_item_group(rmitem_orig);

    gtk_radio_menu_item_set_group(rmitem2add, group);

    return GSLIST2ARY(gtk_radio_menu_item_get_group(rmitem2add));
}

void 
Init_gtk_radio_menu_item()
{
    VALUE gRMenuItem = G_DEF_CLASS(GTK_TYPE_RADIO_MENU_ITEM, "RadioMenuItem", mGtk);

    rb_define_method(gRMenuItem, "initialize", rmitem_initialize, -1);
    rb_define_method(gRMenuItem, "group", rmitem_get_group, 0);
    rb_define_method(gRMenuItem, "set_group", rmitem_set_group, 1);

    G_DEF_SETTERS(gRMenuItem);
}
