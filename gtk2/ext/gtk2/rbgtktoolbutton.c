/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtktoolbutton.c -

  $Author: ggc $
  $Date: 2005/08/30 20:31:00 $

  Copyright (C) 2004 Masao Mutoh
************************************************/

#include "global.h"
                                                                                
#if GTK_CHECK_VERSION(2,4,0)
#define _SELF(self) (GTK_TOOL_BUTTON(RVAL2GOBJ(self)))
static VALUE
toolbutton_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE obj, label;
    GtkToolItem* item;

    rb_scan_args(argc, argv, "02", &obj, &label);

    if (TYPE(obj) == T_SYMBOL){
        item = gtk_tool_button_new_from_stock(rb_id2name(SYM2ID(obj)));
    } else if (TYPE(obj) == T_STRING){
        item = gtk_tool_button_new_from_stock(RVAL2CSTR(obj));
    } else {
        item = gtk_tool_button_new(GTK_WIDGET(RVAL2GOBJ(obj)), 
                                   NIL_P(label) ? NULL : RVAL2CSTR(label));
    }
    RBGTK_INITIALIZE(self, item);
    return Qnil;
}

/* Defined as Properties.
void        gtk_tool_button_set_label       (GtkToolButton *button,
                                             const gchar *label);
G_CONST_RETURN gchar* gtk_tool_button_get_label
                                            (GtkToolButton *button);
void        gtk_tool_button_set_use_underline
                                            (GtkToolButton *button,
                                             gboolean use_underline);
gboolean    gtk_tool_button_get_use_underline
                                            (GtkToggletoolbutton *button);
void        gtk_tool_button_set_stock_id    (GtkToggletoolbutton *button,
                                             const gchar *stock_id);
G_CONST_RETURN gchar* gtk_tool_button_get_stock_id
                                            (GtkToggletoolbutton *button);
void        gtk_tool_button_set_icon_widget (GtkToggletoolbutton *button,
                                             GtkWidget *icon_widget);
GtkWidget*  gtk_tool_button_get_icon_widget (GtkToggletoolbutton *button);
void        gtk_tool_button_set_icon_name   (GtkToolButton *button,
                                             const gchar *icon_name);
const gchar* gtk_tool_button_get_icon_name  (GtkToolButton *button);
void        gtk_tool_button_set_label_widget
                                            (GtkToggletoolbutton *button,
                                             GtkWidget *label_widget);
GtkWidget*  gtk_tool_button_get_label_widget
                                            (GtkToggletoolbutton *button);
*/
#endif

void 
Init_gtk_toolbutton()
{
#if GTK_CHECK_VERSION(2,4,0)
    VALUE gToolbutton = G_DEF_CLASS(GTK_TYPE_TOOL_BUTTON, "ToolButton", mGtk);

    rb_define_method(gToolbutton, "initialize", toolbutton_initialize, -1);
#endif
}
