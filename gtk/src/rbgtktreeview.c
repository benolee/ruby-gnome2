/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtktreeview.c -

  $Author: mutoh $
  $Date: 2002/10/02 15:39:06 $

  Copyright (C) 2002 Masao Mutoh
************************************************/

#include "global.h"

#define _SELF(s) (GTK_TREE_VIEW(RVAL2GOBJ(s)))
#define TREEVIEW_COL(c) (GTK_TREE_VIEW_COLUMN(RVAL2GOBJ(c)))
#define TREEPATH2RVAL(t) (BOXED2RVAL(t, GTK_TYPE_TREE_PATH))
#define RVAL2TREEPATH(p) ((GtkTreePath*)RVAL2BOXED(p, GTK_TYPE_TREE_PATH))

static VALUE
treeview_initialize(argc, argv, self)
    int argc;
    VALUE *argv;
    VALUE self;
{
    VALUE model;
    GtkWidget *widget;

    if (rb_scan_args(argc, argv, "01", &model) == 1) {
        widget = gtk_tree_view_new_with_model(GTK_TREE_MODEL(RVAL2GOBJ(model)));
    }
    else {
        widget = gtk_tree_view_new();
    }

    RBGTK_INITIALIZE(self, widget);
    return Qnil;
}

static VALUE
treeview_get_selection(self)
    VALUE self;
{
    return GOBJ2RVAL(gtk_tree_view_get_selection(_SELF(self)));
}

static VALUE
treeview_columns_autosize(self)
    VALUE self;
{
    gtk_tree_view_columns_autosize(_SELF(self));
    return self;
}

static VALUE
treeview_append_column(self, column)
    VALUE self, column;
{
    return INT2NUM(gtk_tree_view_append_column(_SELF(self), 
                                               TREEVIEW_COL(column)));
}

static VALUE
treeview_remove_column(self, column)
    VALUE self, column;
{
    return INT2NUM(gtk_tree_view_remove_column(_SELF(self), 
                                               TREEVIEW_COL(column)));
}  

static VALUE
treeview_insert_column(self, column, position)
    VALUE self, column, position;
{
    return INT2NUM(gtk_tree_view_insert_column(_SELF(self), 
                                               TREEVIEW_COL(column),
                                               NUM2INT(position)));
}

/* XXXX these 2 methods are not implemented yet.
   gint        gtk_tree_view_insert_column_with_attributes
   (GtkTreeView *tree_view,
   gint position,
   const gchar *title,
   GtkCellRenderer *cell,
   ...);

   gint        gtk_tree_view_insert_column_with_data_func
   (GtkTreeView *tree_view,
   gint position,
   const gchar *title,
   GtkCellRenderer *cell,
   GtkTreeCellDataFunc func,
   gpointer data,
   GDestroyNotify dnotify);
*/

static VALUE
treeview_get_column(self, num)
    VALUE self, num;
{
    return GOBJ2RVAL(gtk_tree_view_get_column(_SELF(self), NUM2INT(num)));
}

static VALUE
treeview_get_columns(self)
    VALUE self;
{
    return GLIST2ARY(gtk_tree_view_get_columns(_SELF(self)));
}

static VALUE
treeview_move_column_after(self, column, base_column)
    VALUE self, column, base_column;
{
    gtk_tree_view_move_column_after(_SELF(self), TREEVIEW_COL(column),
                                    TREEVIEW_COL(base_column));
    return self;
}

/* XXXX
   void        gtk_tree_view_set_column_drag_function
   (GtkTreeView *tree_view,
   GtkTreeViewColumnDropFunc func,
   gpointer user_data,
   GtkDestroyNotify destroy);
*/

static VALUE
treeview_scroll_to_point(self, x, y)
    VALUE self, x, y;
{
    gtk_tree_view_scroll_to_point(_SELF(self), NUM2INT(x), NUM2INT(y));
    return self;
}

static VALUE
treeview_scroll_to_cell(self, path, column, use_align, row_align, col_align)
    VALUE self, path, column, use_align, row_align, col_align;
{
    gtk_tree_view_scroll_to_cell(_SELF(self), RVAL2TREEPATH(path),
                                 TREEVIEW_COL(column), RTEST(use_align),
                                 NUM2DBL(row_align), NUM2DBL(col_align));
    return self;
}

static VALUE
treeview_set_cursor(self, path, focus_column, start_editing)
    VALUE self, path, focus_column, start_editing;
{
    gtk_tree_view_set_cursor(_SELF(self), RVAL2TREEPATH(path),
                             TREEVIEW_COL(focus_column), RTEST(start_editing));
    return self;
}

static VALUE
treeview_get_cursor(self)
    VALUE self;
{
    GtkTreePath* path;
    GtkTreeViewColumn* focus_column;

    gtk_tree_view_get_cursor(_SELF(self), &path, &focus_column);
    return rb_ary_new3(2, (path == NULL) ? Qnil : TREEPATH2RVAL(path),
                       (focus_column == NULL) ? Qnil : GOBJ2RVAL(focus_column));
}

static VALUE
treeview_row_activated(self, path, column)
    VALUE self, path, column;
{
    gtk_tree_view_row_activated(_SELF(self), RVAL2TREEPATH(path),
                                TREEVIEW_COL(column));
    return self;
}

static VALUE
treeview_expand_all(self)
    VALUE self;
{
    gtk_tree_view_expand_all(_SELF(self));
    return self;
}

static VALUE
treeview_collapse_all(self)
    VALUE self;
{
    gtk_tree_view_collapse_all(_SELF(self));
    return self;
}

static VALUE
treeview_expand_row(self, path, open_all)
    VALUE self, path, open_all;
{
    return gtk_tree_view_expand_row(_SELF(self), 
                                    RVAL2TREEPATH(path),
                                    RTEST(open_all)) ? Qtrue: Qfalse;
}

static VALUE
treeview_collapse_row(self, path)
    VALUE self, path;
{
    return gtk_tree_view_collapse_row(_SELF(self), 
                                      RVAL2TREEPATH(path)) ? Qtrue : Qfalse;
}

/* XXXX
   void        gtk_tree_view_map_expanded_rows (GtkTreeView *tree_view,
   GtkTreeViewMappingFunc func,
   gpointer data);
*/

static VALUE
treeview_row_expanded(self, path)
    VALUE self, path;
{
    return gtk_tree_view_row_expanded(_SELF(self), 
                                      RVAL2TREEPATH(path)) ? Qtrue : Qfalse;
}

static VALUE
treeview_get_path_at_pos(self, x, y)
    VALUE self;
{
    GtkTreePath* path;
    GtkTreeViewColumn* column;
    gint cell_x, cell_y;
    gboolean ret;

    ret = gtk_tree_view_get_path_at_pos(_SELF(self), 
                                        INT2NUM(x), INT2NUM(y),
                                        &path, &column, &cell_x, &cell_y);
    return ret ? rb_ary_new3(4, 
                             (path == NULL) ? Qnil : TREEPATH2RVAL(path),
                             (column == NULL) ? Qnil : GOBJ2RVAL(column),
                             INT2NUM(cell_x), INT2NUM(cell_y)) : Qnil;
}

static VALUE
treeview_get_cell_area(self, path, column)
    VALUE self, path, column;
{
    GdkRectangle rect;
    gtk_tree_view_get_cell_area(_SELF(self), RVAL2TREEPATH(path),
                                TREEVIEW_COL(column), &rect);
    return BOXED2RVAL(&rect, GDK_TYPE_RECTANGLE);
}

static VALUE
treeview_get_background_area(self, path, column)
    VALUE self, path, column;
{
    GdkRectangle rect;
    gtk_tree_view_get_background_area(_SELF(self), 
                                      RVAL2TREEPATH(path),
                                      TREEVIEW_COL(column), &rect);
    return BOXED2RVAL(&rect, GDK_TYPE_RECTANGLE);
}

static VALUE
treeview_get_visible_rect(self)
    VALUE self;
{
    GdkRectangle rect;
    gtk_tree_view_get_visible_rect(_SELF(self), &rect);
    return BOXED2RVAL(&rect, GDK_TYPE_RECTANGLE);
}

static VALUE
treeview_get_bin_window(self)
    VALUE self;
{
    return GOBJ2RVAL(gtk_tree_view_get_bin_window(_SELF(self)));
}

static VALUE
treeview_widget_to_tree_coords(self, wx, wy)
    VALUE self, wx, wy;
{
    gint tx, ty;
    gtk_tree_view_widget_to_tree_coords(_SELF(self), 
                                        NUM2INT(wx), NUM2INT(wy), 
                                        &tx, &ty);
    return rb_ary_new3(2, INT2NUM(tx), INT2NUM(ty));
}

static VALUE
treeview_tree_to_widget_coords(self, tx, ty)
    VALUE self, tx, ty;
{
    gint wx, wy;
    gtk_tree_view_tree_to_widget_coords(_SELF(self),
                                        NUM2INT(tx), NUM2INT(ty), 
                                        &wx, &wy);
    return rb_ary_new3(2, INT2NUM(wx), INT2NUM(wy));
}

/* XXXX
   void        gtk_tree_view_enable_model_drag_dest
   (GtkTreeView *tree_view,
   const GtkTargetEntry *targets,
   gint n_targets,
   GdkDragAction actions);
   void        gtk_tree_view_enable_model_drag_source
   (GtkTreeView *tree_view,
   GdkModifierType start_button_mask,
   const GtkTargetEntry *targets,
   gint n_targets,
   GdkDragAction actions);
*/

static VALUE
treeview_unset_rows_drag_source(self)
    VALUE self;
{
    gtk_tree_view_unset_rows_drag_source(_SELF(self));
    return self;
}

static VALUE
treeview_unset_rows_drag_dest(self)
    VALUE self;
{
    gtk_tree_view_unset_rows_drag_dest(_SELF(self));
    return self;
}

static VALUE
treeview_set_drag_dest_row(self, path, pos)
    VALUE self, path, pos;
{
    gtk_tree_view_set_drag_dest_row(_SELF(self), RVAL2TREEPATH(path),
                                    NUM2INT(pos));
    return self;
}

static VALUE
treeview_get_drag_dest_row(self)
    VALUE self;
{
    GtkTreePath* path;
    GtkTreeViewDropPosition pos;
    gtk_tree_view_get_drag_dest_row(_SELF(self), &path, &pos);
    return rb_ary_new3(2, TREEPATH2RVAL(path), INT2NUM(pos));
}

static VALUE
treeview_get_dest_row_at_pos(self, drag_x, drag_y)
    VALUE self;
{
    GtkTreePath* path;
    GtkTreeViewDropPosition pos;
    gboolean ret;

    ret = gtk_tree_view_get_dest_row_at_pos(_SELF(self), 
                                            NUM2INT(drag_x), NUM2INT(drag_y),
                                            &path, &pos);
    return ret ? rb_ary_new3(2, TREEPATH2RVAL(path), INT2NUM(pos)) : Qnil;
}

static VALUE
treeview_create_row_drag_icon(self, path)
    VALUE self, path;
{
    return GOBJ2RVAL(gtk_tree_view_create_row_drag_icon(_SELF(self),
                                                        RVAL2TREEPATH(path)));
}

/*
  GtkTreeViewSearchEqualFunc gtk_tree_view_get_search_equal_func
  (GtkTreeView *tree_view);
  void        gtk_tree_view_set_search_equal_func
  (GtkTreeView *tree_view,
  GtkTreeViewSearchEqualFunc search_equal_func,
  gpointer search_user_data,
  GtkDestroyNotify search_destroy);
*/

void 
Init_gtk_treeview()
{
    VALUE gTv = G_DEF_CLASS(GTK_TYPE_TREE_VIEW, "TreeView", mGtk);

	rb_define_method(gTv, "initialize", treeview_initialize, -1);
	rb_define_method(gTv, "selection", treeview_get_selection, 0);
	rb_define_method(gTv, "columns_sutosize", treeview_columns_autosize, 0);
	rb_define_method(gTv, "append_column", treeview_append_column, 1);
	rb_define_method(gTv, "remove_column", treeview_remove_column, 1);
	rb_define_method(gTv, "insert_column", treeview_insert_column, 2);
	rb_define_method(gTv, "get_column", treeview_get_column, 1);
	rb_define_method(gTv, "columns", treeview_get_columns, 0);
	rb_define_method(gTv, "move_colun_after", treeview_move_column_after, 2);
	rb_define_method(gTv, "scroll_to_point", treeview_scroll_to_point, 2);
	rb_define_method(gTv, "scroll_to_cell", treeview_scroll_to_cell, 5);
	rb_define_method(gTv, "set_cursor", treeview_set_cursor, 3);
	rb_define_method(gTv, "cursor", treeview_get_cursor, 0);
	rb_define_method(gTv, "row_activated", treeview_row_activated, 2);
	rb_define_method(gTv, "expand_all", treeview_expand_all, 0);
	rb_define_method(gTv, "collapse_all", treeview_collapse_all, 0);
	rb_define_method(gTv, "expand_row", treeview_expand_row, 2);
	rb_define_method(gTv, "collapse_row", treeview_collapse_row, 1);
	rb_define_method(gTv, "row_expanded?", treeview_row_expanded, 1);
	rb_define_method(gTv, "get_path_at_pos", treeview_get_path_at_pos, 2);
	rb_define_method(gTv, "get_cell_area", treeview_get_cell_area, 2);
	rb_define_method(gTv, "get_background_area", treeview_get_background_area, 2);
	rb_define_method(gTv, "visible_rect", treeview_get_visible_rect, 0);
	rb_define_method(gTv, "bin_window", treeview_get_bin_window, 0);
	rb_define_method(gTv, "widget_to_tree_coords", treeview_widget_to_tree_coords, 2);
	rb_define_method(gTv, "tree_to_widget_coords", treeview_tree_to_widget_coords, 2);
	rb_define_method(gTv, "unset_rows_drag_source", treeview_unset_rows_drag_source, 0);
	rb_define_method(gTv, "unset_rows_drag_dest", treeview_unset_rows_drag_dest, 0);
	rb_define_method(gTv, "set_drag_dest_row", treeview_set_drag_dest_row, 2);
	rb_define_method(gTv, "drag_dest_row", treeview_get_drag_dest_row, 0);
	rb_define_method(gTv, "get_dest_row_at_pos", treeview_get_dest_row_at_pos, 2);
	rb_define_method(gTv, "create_row_drag_icon", treeview_create_row_drag_icon, 1);
    
    /* Constants */
    rb_define_const(gTv, "DROP_BEFORE", INT2NUM(GTK_TREE_VIEW_DROP_BEFORE));
    rb_define_const(gTv, "DROP_AFTER", INT2NUM(GTK_TREE_VIEW_DROP_AFTER));
    rb_define_const(gTv, "DROP_INTO_OR_BEFORE", INT2NUM(GTK_TREE_VIEW_DROP_INTO_OR_BEFORE));
    rb_define_const(gTv, "DROP_INTO_OR_AFTER", INT2NUM(GTK_TREE_VIEW_DROP_INTO_OR_AFTER));
}
