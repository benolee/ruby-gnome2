/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtktreemodelsort.c -

  $Author: mutoh $
  $Date: 2005/11/06 04:44:24 $

  Copyright (C) 2003-2005 Masao Mutoh
************************************************/

#include "global.h"

#define _SELF(s) (GTK_TREE_MODEL_SORT(RVAL2GOBJ(s)))

static ID id_model;

static VALUE
tmodelsort_initialize(VALUE self, VALUE model)
{
    G_CHILD_SET(self, id_model, model);
    G_INITIALIZE(self, 
                 gtk_tree_model_sort_new_with_model(GTK_TREE_MODEL(RVAL2GOBJ(model))));
    return Qnil;
}

static VALUE
tmodelsort_convert_child_path_to_path(VALUE self, VALUE child_path)
{
    return GTKTREEPATH2RVAL(gtk_tree_model_sort_convert_child_path_to_path(
                             _SELF(self),
                             RVAL2GTKTREEPATH(child_path)));
}

static VALUE
tmodelsort_convert_child_iter_to_iter(VALUE self, VALUE child_iter)
{
    GtkTreeIter sort_iter;
    GtkTreeModelSort* modelsort = _SELF(self);
    gtk_tree_model_sort_convert_child_iter_to_iter(modelsort, &sort_iter,
                                                   RVAL2GTKTREEITER(child_iter));
    sort_iter.user_data3 = gtk_tree_model_sort_get_model(modelsort);
    return GTKTREEITER2RVAL(&sort_iter);
}

static VALUE
tmodelsort_convert_path_to_child_path(VALUE self, VALUE sorted_path)
{
    return GTKTREEPATH2RVAL(gtk_tree_model_sort_convert_path_to_child_path(
                             _SELF(self),
                             RVAL2GTKTREEPATH(sorted_path)));
}

static VALUE
tmodelsort_convert_iter_to_child_iter(VALUE self, VALUE sorted_iter)
{
    GtkTreeIter child_iter;
    GtkTreeModelSort* modelsort = _SELF(self);
    gtk_tree_model_sort_convert_iter_to_child_iter(modelsort, &child_iter,
                                                   RVAL2GTKTREEITER(sorted_iter));
    child_iter.user_data3 = gtk_tree_model_sort_get_model(modelsort);
    return GTKTREEITER2RVAL(&child_iter);
} 

static VALUE
tmodelsort_reset_default_sort_func(VALUE self)
{
    gtk_tree_model_sort_reset_default_sort_func(_SELF(self));
    return self;
}

static VALUE
tmodelsort_clear_cache(VALUE self)
{
    gtk_tree_model_sort_clear_cache(_SELF(self));
    return self;
}

#if GTK_CHECK_VERSION(2,2,0)
static VALUE
tmodelsort_iter_is_valid(VALUE self, VALUE iter)
{
    return CBOOL2RVAL(gtk_tree_model_sort_iter_is_valid(_SELF(self), RVAL2GTKTREEITER(iter)));
}
#endif

void 
Init_gtk_tmodelsort()
{
    VALUE gTMSort = G_DEF_CLASS(GTK_TYPE_TREE_MODEL_SORT, "TreeModelSort", mGtk);

    id_model = rb_intern("model");

    rb_define_method(gTMSort, "initialize", tmodelsort_initialize, 1);
    rb_define_method(gTMSort, "convert_child_path_to_path", tmodelsort_convert_child_path_to_path, 1);
    rb_define_method(gTMSort, "convert_child_iter_to_iter", tmodelsort_convert_child_iter_to_iter, 1);
    rb_define_method(gTMSort, "convert_path_to_child_path", tmodelsort_convert_path_to_child_path, 1);
    rb_define_method(gTMSort, "convert_iter_to_child_iter", tmodelsort_convert_iter_to_child_iter, 1);
    rb_define_method(gTMSort, "reset_default_sort_func", tmodelsort_reset_default_sort_func, 0);
    rb_define_method(gTMSort, "clear_cache", tmodelsort_clear_cache, 0);
#if GTK_CHECK_VERSION(2,2,0)
    rb_define_method(gTMSort, "iter_is_valid?", tmodelsort_iter_is_valid, 1);
#endif

}
