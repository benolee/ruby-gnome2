/* -*- c-file-style: "ruby" -*- */
/************************************************

  rbgtktreeitem.c -

  $Author: mutoh $
  $Date: 2002/05/19 12:39:05 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
titem_initialize(argc, argv, self)
    int argc;
    VALUE *argv;
    VALUE self;
{
    VALUE label;
    GtkWidget *widget;

    if (rb_scan_args(argc, argv, "01", &label) == 1) {
	widget = gtk_tree_item_new_with_label(STR2CSTR(label));
    }
    else {
	widget = gtk_tree_item_new();
    }

    set_widget(self, widget);
    return Qnil;
}

static VALUE
titem_set_subtree(self, subtree)
    VALUE self, subtree;
{
    gtk_tree_item_set_subtree(GTK_TREE_ITEM(get_widget(self)),
			      get_widget(subtree));
    return self;
}

static VALUE
titem_subtree(self)
    VALUE self;
{
    GtkWidget *t;

    t = GTK_TREE_ITEM_SUBTREE(GTK_TREE_ITEM(get_widget(self)));
    return t ? get_value_from_gobject(GTK_OBJECT(t)) : Qnil;
}

static VALUE
titem_leaf_p(self)
    VALUE self;
{
    GtkWidget *t;

    t = GTK_TREE_ITEM_SUBTREE(GTK_TREE_ITEM(get_widget(self)));
    return t ? Qtrue : Qfalse;
}

static VALUE
titem_expanded_p(self)
    VALUE self;
{
    GtkTreeItem *i;

    i = GTK_TREE_ITEM(get_widget(self));
    return i->expanded ? Qtrue : Qfalse;
}

static VALUE
titem_select(self)
    VALUE self;
{
    gtk_tree_item_select(GTK_TREE_ITEM(get_widget(self)));
    return self;
}

static VALUE
titem_deselect(self)
    VALUE self;
{
    gtk_tree_item_deselect(GTK_TREE_ITEM(get_widget(self)));
    return self;
}

static VALUE
titem_expand(self)
    VALUE self;
{
    gtk_tree_item_expand(GTK_TREE_ITEM(get_widget(self)));
    return self;
}

static VALUE
titem_collapse(self)
    VALUE self;
{
    gtk_tree_item_collapse(GTK_TREE_ITEM(get_widget(self)));
    return self;
}

void Init_gtk_tree_item()
{
    gTreeItem = rb_define_class_under(mGtk, "TreeItem", gItem);

    rb_define_const(gTreeItem, "SIGNAL_EXPAND", rb_str_new2("expand"));
    rb_define_const(gTreeItem, "SIGNAL_COLLAPSE", rb_str_new2("collapse"));

    rb_define_method(gTreeItem, "initialize", titem_initialize, -1);
    rb_define_method(gTreeItem, "set_subtree", titem_set_subtree, 1);
    rb_define_method(gTreeItem, "subtree=", titem_set_subtree, 1);
    rb_define_method(gTreeItem, "subtree", titem_subtree, 0);
    rb_define_method(gTreeItem, "leaf?", titem_leaf_p, 0);
    rb_define_method(gTreeItem, "expanded?", titem_expanded_p, 0);
    rb_define_method(gTreeItem, "select", titem_select, 0);
    rb_define_method(gTreeItem, "deselect", titem_deselect, 0);
    rb_define_method(gTreeItem, "expand", titem_expand, 0);
    rb_define_method(gTreeItem, "collapse", titem_collapse, 0);
}
