/* -*- c-file-style: "ruby" -*- */
/************************************************

  rbgtkwidget.c -

  $Author: mutoh $
  $Date: 2002/05/19 12:29:40 $

  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
widget_show(self)
    VALUE self;
{
    gtk_widget_show(get_widget(self));
    return self;
}

static VALUE
widget_show_all(self)
    VALUE self;
{
    gtk_widget_show_all(get_widget(self));
    return self;
}

static VALUE
widget_show_now(self)
    VALUE self;
{
    gtk_widget_show_now(get_widget(self));
    return self;
}

static VALUE
widget_hide(self)
    VALUE self;
{
    gtk_widget_hide(get_widget(self));
    return self;
}

static VALUE
widget_hide_all(self)
    VALUE self;
{
    gtk_widget_hide_all(get_widget(self));
    return self;
}

static VALUE
widget_map(self)
    VALUE self;
{
    gtk_widget_map(get_widget(self));
    return self;
}

static VALUE
widget_unmap(self)
    VALUE self;
{
    gtk_widget_unmap(get_widget(self));
    return self;
}

static VALUE
widget_realize(self)
    VALUE self;
{
    gtk_widget_realize(get_widget(self));
    return self;
}

static VALUE
widget_unrealize(self)
    VALUE self;
{
    gtk_widget_unrealize(get_widget(self));
    return self;
}

static VALUE
widget_queue_draw(self)
    VALUE self;
{
    gtk_widget_queue_draw(get_widget(self));
    return self;
}

static VALUE
widget_queue_resize(self)
    VALUE self;
{
    gtk_widget_queue_resize(get_widget(self));
    return self;
}

static VALUE
widget_queue_clear(self)
    VALUE self;
{
    gtk_widget_queue_clear(get_widget(self));
    return self;
}

static VALUE
widget_draw(self, rect)
    VALUE self, rect;
{
    gtk_widget_draw(get_widget(self), get_gdkrectangle(rect));
    return self;
}

static VALUE
widget_draw_focus(self)
    VALUE self;
{
    gtk_widget_draw_focus(get_widget(self));
    return self;
}

static VALUE
widget_draw_default(self)
    VALUE self;
{
    gtk_widget_draw_default(get_widget(self));
    return self;
}

static VALUE
widget_size_request(self)
    VALUE self;
{
    GtkRequisition req;
    gtk_widget_size_request(get_widget(self), &req);
    return make_grequisition(&req);
}

static VALUE
widget_size_allocate(self, alloc)
    VALUE self, alloc;
{
    gtk_widget_size_allocate(get_widget(self), get_gallocation(alloc));
    return self;
}

static VALUE
widget_add_accel(self, sig, accel, key, mod, flag)
     VALUE self, sig, accel, key, mod, flag;
{
    gtk_widget_add_accelerator(get_widget(self),
                               STR2CSTR(sig),
                               get_gtkaccelgrp(accel),
                               NUM2INT(key),
                               NUM2INT(mod),
                               NUM2INT(flag));
    return self;
}

static VALUE
widget_rm_accel(self, accel, key, mod)
    VALUE self, accel, key, mod;
{
    gtk_widget_remove_accelerator(get_widget(self),
                                  get_gtkaccelgrp(accel),
                                  NUM2INT(key),
                                  NUM2INT(mod));
    return self;
}

static VALUE
widget_rm_accels(self, sig, visible)
     VALUE self, sig, visible;
{
    gtk_widget_remove_accelerators(get_widget(self),
                                   STR2CSTR(sig),
                                   (gboolean)RTEST(visible));
    return self;
}

static VALUE
widget_accel_signal(self, accel, key, mod)
     VALUE self, accel, key, mod;
{
    return INT2NUM(gtk_widget_accelerator_signal(get_widget(self),
                                                 get_gtkaccelgrp(accel),
                                                 NUM2INT(key),
                                                 NUM2INT(mod)));
}

static VALUE
widget_event(self, event)
    VALUE self, event;
{
    return INT2NUM(gtk_widget_event(get_widget(self), get_gdkevent(event)));
}

static VALUE
widget_activate(self)
    VALUE self;
{
    return (gtk_widget_activate(get_widget(self)) ? Qtrue : Qfalse);
}

static VALUE
widget_grab_focus(self)
    VALUE self;
{
    gtk_widget_grab_focus(get_widget(self));
    return self;
}

static VALUE
widget_grab_default(self)
    VALUE self;
{
    gtk_widget_grab_default(get_widget(self));
    return self;
}

static VALUE
widget_reparent(self, parent)
    VALUE self, parent;
{
    gtk_widget_reparent(get_widget(self), get_widget(parent));
    return self;
}

static VALUE
widget_popup(self, x, y)
    VALUE self, x, y;
{
    gtk_widget_popup(get_widget(self), NUM2INT(x), NUM2INT(y));
    return self;
}

static VALUE
widget_intersect(self, area, intersect)
    VALUE self, area, intersect;
{
    return INT2NUM(gtk_widget_intersect(get_widget(self),
                                        get_gdkrectangle(area),
                                        get_gdkrectangle(intersect)));
}

static VALUE
widget_set_state(self, state)
    VALUE self, state;
{
    gtk_widget_set_state(get_widget(self), (GtkStateType)NUM2INT(state));
    return self;
}

static VALUE
widget_set_style(self, style)
    VALUE self, style;
{
    gtk_widget_set_style(get_widget(self), get_gstyle(style));
    return self;
}

static VALUE
widget_set_app_paintable(self, app_paintable)
    VALUE self, app_paintable;
{
    gtk_widget_set_app_paintable(get_widget(self), RTEST(app_paintable));
    return self;
}

static VALUE
widget_set_parent(self, parent)
    VALUE self, parent;
{
    gtk_widget_set_parent(get_widget(self), get_widget(parent));
    return self;
}

static VALUE
widget_set_name(self, name)
    VALUE self, name;
{
    gtk_widget_set_name(get_widget(self), STR2CSTR(name));
    return self;
}

static VALUE
widget_get_name(self)
    VALUE self;
{
    return rb_str_new2(gtk_widget_get_name(get_widget(self)));
}

static VALUE
widget_set_sensitive(self, sensitive)
    VALUE self, sensitive;
{
    gtk_widget_set_sensitive(get_widget(self), RTEST(sensitive));
    return self;
}

static VALUE
widget_set_uposition(self, x, y)
    VALUE self, x, y;
{
    gtk_widget_set_uposition(get_widget(self), NUM2INT(x), NUM2INT(y));
    return self;
}

static VALUE
widget_set_usize(self, w, h)
    VALUE self, w, h;
{
    gtk_widget_set_usize(get_widget(self), NUM2INT(w), NUM2INT(h));
    return self;
}

static VALUE
widget_set_events(self, events)
    VALUE self, events;
{
    gtk_widget_set_events(get_widget(self), NUM2INT(events));
    return self;
}

static VALUE
widget_set_extension_events(self, mode)
    VALUE self, mode;
{
    gtk_widget_set_extension_events(get_widget(self),
                                    (GdkExtensionMode)NUM2INT(mode));
    return self;
}

static VALUE
widget_add_events(self, events)
    VALUE self, events;
{
    gtk_widget_add_events(get_widget(self), NUM2INT(events));
    return self;
}

static VALUE
widget_unparent(self)
    VALUE self;
{
    gtk_widget_unparent(get_widget(self));
    return self;
}

static VALUE
widget_window(self)
    VALUE self;
{
    return make_gdkwindow(get_widget(self)->window);
}

static VALUE
widget_get_toplevel(self)
    VALUE self;
{
    return get_value_from_gobject(GTK_OBJECT(gtk_widget_get_toplevel(get_widget(self))));
}

static VALUE
widget_get_ancestor(self, type)
    VALUE self, type;
{
    GtkWidget *widget = get_widget(self);
#if 0
    if (rb_obj_is_kind_of(type, rb_cClass)) {
    }
#endif
    widget = gtk_widget_get_ancestor(widget, NUM2INT(type));

    return get_value_from_gobject(GTK_OBJECT(widget));
}

static VALUE
widget_get_colormap(self)
    VALUE self;
{
    return make_gdkcmap(gtk_widget_get_colormap(get_widget(self)));
}

static VALUE
widget_get_visual(self)
    VALUE self;
{
    return make_gdkvisual(gtk_widget_get_visual(get_widget(self)));
}

static VALUE
widget_get_style(self)
    VALUE self;
{
    return make_gstyle(gtk_widget_get_style(get_widget(self)));
}

static VALUE
widget_get_pointer(self)
    VALUE self;
{
    int x, y;

    gtk_widget_get_pointer(get_widget(self), &x, &y);
    return rb_assoc_new(INT2FIX(x), INT2FIX(y));
}

static VALUE
widget_is_ancestor(self, ancestor)
    VALUE self, ancestor;
{
    return (gtk_widget_is_ancestor(get_widget(self), get_widget(ancestor)) ? Qtrue : Qfalse);
}

static VALUE
widget_hide_on_delete(self)
  VALUE self;
{
    gtk_widget_hide_on_delete(get_widget(self));
    return Qnil;
}

static VALUE
widget_get_events(self)
    VALUE self;
{
    return INT2NUM(gtk_widget_get_events(get_widget(self)));
}

static VALUE
widget_get_extension_events(self)
    VALUE self;
{
    return INT2NUM(gtk_widget_get_extension_events(get_widget(self)));
}

static VALUE
widget_push_cmap(self, cmap)
    VALUE self, cmap;
{
    gtk_widget_push_colormap(get_gdkcmap(cmap));
    return Qnil;
}

static VALUE
widget_push_visual(self, visual)
    VALUE self, visual;
{
    gtk_widget_push_visual(get_gdkvisual(visual));
    return visual;
}

static VALUE
widget_push_style(self, style)
    VALUE self, style;
{
    gtk_widget_push_style(get_gstyle(style));
    return style;
}

static VALUE
widget_pop_cmap(self)
    VALUE self;
{
    gtk_widget_pop_colormap();
    return Qnil;
}

static VALUE
widget_pop_visual(self)
    VALUE self;
{
    gtk_widget_pop_visual();
    return Qnil;
}

static VALUE
widget_pop_style(self)
    VALUE self;
{
    gtk_widget_pop_style();
    return Qnil;
}

#define DEFINE_IS_WIDGET(STATE) \
static VALUE \
widget_ ## STATE (self) \
    VALUE self; \
{ \
    return( GTK_WIDGET_ ## STATE (get_widget(self))? Qtrue: Qfalse ); \
}
DEFINE_IS_WIDGET(TOPLEVEL)
DEFINE_IS_WIDGET(NO_WINDOW)
DEFINE_IS_WIDGET(REALIZED)
DEFINE_IS_WIDGET(MAPPED)
DEFINE_IS_WIDGET(VISIBLE)
DEFINE_IS_WIDGET(DRAWABLE)
DEFINE_IS_WIDGET(SENSITIVE)
DEFINE_IS_WIDGET(PARENT_SENSITIVE)
DEFINE_IS_WIDGET(IS_SENSITIVE)
DEFINE_IS_WIDGET(CAN_FOCUS)
DEFINE_IS_WIDGET(HAS_FOCUS)
DEFINE_IS_WIDGET(CAN_DEFAULT)
DEFINE_IS_WIDGET(HAS_DEFAULT)
DEFINE_IS_WIDGET(HAS_GRAB)
DEFINE_IS_WIDGET(RC_STYLE)

static VALUE
widget_set_default_cmap(self, cmap)
    VALUE self, cmap;
{
    gtk_widget_set_default_colormap(get_gdkcmap(cmap));
    return Qnil;
}

static VALUE
widget_set_default_visual(self, visual)
    VALUE self, visual;
{
    gtk_widget_set_default_visual(get_gdkvisual(visual));
    return visual;
}

static VALUE
widget_set_default_style(self, style)
    VALUE self, style;
{
    gtk_widget_set_default_style(get_gstyle(style));
    return Qnil;
}

static VALUE
widget_get_default_cmap(self)
    VALUE self;
{
    return make_gdkcmap(gtk_widget_get_default_colormap());
}

static VALUE
widget_get_default_visual(self)
    VALUE self;
{
    return make_gdkvisual(gtk_widget_get_default_visual());
}

static VALUE
widget_get_default_style(self)
    VALUE self;
{
    return make_gstyle(gtk_widget_get_default_style());
}

static VALUE
widget_shape_combine_mask(self, shape_mask, offset_x, offset_y)
    VALUE self, shape_mask, offset_x, offset_y;
{
    gtk_widget_shape_combine_mask(get_widget(self),
                                  get_gdkbitmap(shape_mask),
                                  NUM2INT(offset_x),
                                  NUM2INT(offset_y));
    return self;
}

static VALUE
widget_get_alloc(self)
    VALUE self;
{
    return make_gallocation(&(get_widget(self)->allocation));
}
static VALUE
widget_set_alloc(self, x,y,w,h)
    VALUE self, x,y,w,h;
{
    GtkAllocation *a = &(get_widget(self)->allocation);
    a->x      = NUM2INT(x);
    a->y      = NUM2INT(y);
    a->width  = NUM2INT(w);
    a->height = NUM2INT(h);
    return self;
}

static VALUE
widget_get_requisition(self)
    VALUE self;
{
    return make_grequisition(&(get_widget(self)->requisition));
}

static VALUE
widget_set_requisition(self, w,h)
    VALUE self,w,h;
{
    GtkRequisition *r = &(get_widget(self)->requisition);
    r->width  = NUM2INT(w);
    r->height = NUM2INT(h);
    return self;
}

static VALUE
widget_get_child_requisition(self)
    VALUE self;
{
    GtkRequisition r;

    gtk_widget_get_child_requisition(get_widget(self), &r);
    return make_grequisition(&r);
}

static VALUE
widget_state(self)
    VALUE self;
{
    return INT2FIX(get_widget(self)->state);
}

static VALUE
widget_parent(self)
    VALUE self;
{
    GtkWidget *p = get_widget(self)->parent;
    VALUE obj;

    if (p == NULL) {
        return Qnil;
    }
    obj = get_value_from_gobject((GtkObject *)p);
    return obj? obj: make_gobject(gWidget, (GtkObject *)p);
}

static VALUE
widget_path(self)
    VALUE self;
{
    guint path_length;
    gchar *path;
    gchar *path_reversed;
    VALUE str_path;
    /* VALUE str_path_reversed; */

    gtk_widget_path(get_widget(self), &path_length, &path, &path_reversed);
    str_path = rb_str_new(path, path_length);
    /* str_path_reversed = rb_str_new(path_reversed, path_length); */
    g_free(path);
    g_free(path_reversed);
    /* return rb_ary_new3(2, str_path, str_path_reversed); */
    return str_path;
}

static VALUE
widget_class_path(self)
    VALUE self;
{
    guint path_length;
    gchar *path;
    gchar *path_reversed;
    VALUE str_path;
    /* VALUE str_path_reversed; */

    gtk_widget_class_path(get_widget(self), &path_length, &path, &path_reversed);
    str_path = rb_str_new(path, path_length);
    /* str_path_reversed = rb_str_new(path_reversed, path_length); */
    g_free(path);
    g_free(path_reversed);
    /* return rb_ary_new3(2, str_path, str_path_reversed); */
    return str_path;
}

static VALUE
widget_set_rc_style(self)
    VALUE self;
{
    gtk_widget_set_rc_style(get_widget(self));
    return self;
}

static VALUE
widget_ensure_style(self)
    VALUE self;
{
    gtk_widget_ensure_style(get_widget(self));
    return self;
}

static VALUE
widget_modify_style(self, style)
    VALUE self, style;
{
    gtk_widget_modify_style(get_widget(self),
                            get_grcstyle(style));
    return self;
}

static VALUE
widget_restore_default_style(self)
    VALUE self;
{
    gtk_widget_restore_default_style(get_widget(self));
    return self;
}

static VALUE
widget_reset_rc_styles(self)
    VALUE self;
{
    gtk_widget_reset_rc_styles(get_widget(self));
    return self;
}

static VALUE
widget_pop_composite_child(self)
    VALUE self;
{
    gtk_widget_pop_composite_child();
    return self;
}

static VALUE
widget_push_composite_child(self)
    VALUE self;
{
    gtk_widget_push_composite_child();
    return self;
}

static VALUE
widget_get_composite_name(self)
    VALUE self;
{
    char *name = gtk_widget_get_composite_name(get_widget(self));
    VALUE val;
    if (name == NULL) val = Qnil;
    else {
        val = rb_str_new2(name);
        g_free(name);
    }
    return val;
}

static VALUE
widget_set_composite_name(self, name)
    VALUE self, name;
{
    gtk_widget_set_composite_name(get_widget(self), STR2CSTR(name));
    return Qnil;
}

static VALUE
widget_reset_shapes(self)
    VALUE self;
{
    gtk_widget_reset_shapes(get_widget(self));
    return Qnil;
}

static VALUE
widget_set_scroll_adjustments(self, h, v)
    VALUE self, h, v;
{
    gboolean res = gtk_widget_set_scroll_adjustments(get_widget(self),
                                                     GTK_ADJUSTMENT(get_widget(h)),
                                                     GTK_ADJUSTMENT(get_widget(v)));
    return res ? Qtrue : Qfalse;
}

static GtkTargetEntry*
get_target_entry(targets)
	VALUE targets;
{
	VALUE ary;
	VALUE e_target, e_flags, e_info;
	GtkTargetEntry *entries;
	int i, n_targets;

	Check_Type(targets, T_ARRAY);

	n_targets = RARRAY(targets)->len;
	entries = ALLOC_N(GtkTargetEntry, n_targets);

    for (i = 0; i < n_targets; i++) {
		ary = rb_ary_entry(targets, i);
        Check_Type(ary, T_ARRAY);
        e_target = rb_ary_entry(ary, 0);
        e_flags = rb_ary_entry(ary, 1);
        e_info = rb_ary_entry(ary, 2);

		entries[i].target = NIL_P(e_target) ? NULL:STR2CSTR(e_target);
		entries[i].flags = NIL_P(e_flags) ? 0:NUM2INT(e_flags);
		entries[i].info = NIL_P(e_info) ? 0:NUM2INT(e_info);

    }
    return entries;
}

/* Drag and Drop */
static VALUE
widget_drag_dest_set(self, flags, targets, actions)
    VALUE self, flags, targets, actions;
{
    GtkTargetEntry *entries = get_target_entry(targets);
    int num = RARRAY(targets)->len;

    gtk_drag_dest_set(get_widget(self), NUM2INT(flags), entries, 
                      num, NUM2INT(actions));
    return self;
}

static VALUE
widget_drag_dest_unset(self)
    VALUE self;
{
    gtk_drag_dest_unset(get_widget(self));
    return self;
}

static VALUE
widget_drag_dest_set_proxy(self, proxy_window, protocol, use_coordinates)
    VALUE self, proxy_window, protocol, use_coordinates;
{
    gtk_drag_dest_set_proxy(get_widget(self), get_gdkwindow(proxy_window),
                              NUM2INT(protocol), RTEST(use_coordinates)); 
    return self;
}

static VALUE
widget_drag_get_data(self, context, target, time)
    VALUE self, context, target, time;
{
    gtk_drag_get_data(get_widget(self), get_gdkdragcontext(context), 
                      get_gdkatom(target), NUM2INT(time));
    return self;
}

static VALUE
widget_drag_source_set(self, flags, targets, actions)
    VALUE self, flags, targets, actions;
{
    gtk_drag_source_set(get_widget(self), NUM2INT(flags), 
                        get_target_entry(targets), 
                        RARRAY(targets)->len, NUM2INT(actions));
    return self;
}

static VALUE
widget_drag_source_set_icon(self, colormap, pixmap, mask)
    VALUE self, colormap, pixmap, mask;
{
    gtk_drag_source_set_icon(get_widget(self), get_gdkcmap(colormap),
                             get_gdkpixmap(pixmap), get_gdkbitmap(mask));
    return self;
}

static VALUE
widget_drag_source_unset(self)
    VALUE self;
{
    gtk_drag_source_unset(get_widget(self));
    return self;
}

/* Selection */
static VALUE
widget_selection_owner_set(self, selection, time)
    VALUE self, selection, time;
{
    int ret = gtk_selection_owner_set(get_widget(self), 
                                      get_gdkatom(selection), NUM2INT(time));
    return ret ? Qtrue : Qfalse;
}

static VALUE
widget_selection_add_target(self, selection, target, info)
    VALUE self, selection, target, info;
{
    gtk_selection_add_target(get_widget(self), 
                   get_gdkatom(selection), get_gdkatom(target),
                   NUM2INT(info));
    return self;
}

static VALUE
widget_selection_add_targets(self, selection, targets)
    VALUE self, selection, targets;
{
    gtk_selection_add_targets(get_widget(self), get_gdkatom(selection), 
                              get_target_entry(targets), RARRAY(targets)->len);
    return self;
}

static VALUE
widget_selection_convert(self, selection, target, time)
    VALUE self, selection, target, time;
{
    int ret = gtk_selection_convert(get_widget(self), 
                   get_gdkatom(selection), get_gdkatom(target), NUM2INT(time));
    return ret ? Qtrue : Qfalse;
}

static VALUE
widget_selection_remove_all(self)
    VALUE self;
{
    gtk_selection_remove_all(get_widget(self));
    return self;
}

/* yashi
static VALUE
signal_setup_args(self, sig, argc, params, args)
    VALUE obj;
    ID sig;
    int argc;
    GtkArg *params;
    VALUE args;
{
    char *signame = rb_id2name(sig);
    ID id_supre = rb_intern("super");

    if (signal_comp(signame, "draw", GTK_TYPE_WIDGET)) {
        rb_ary_push(args, make_gdkrectangle(GTK_VALUE_POINTER(params[0])));
        return;
    }
    if (signal_comp(signame, "size_request", GTK_TYPE_WIDGET)) {
        rb_ary_push(args, make_grequisition(GTK_VALUE_POINTER(params[0])));
        return;
    }
    if (signal_comp(signame, "size_allocate", GTK_TYPE_WIDGET)) {
        rb_ary_push(args, make_gallocation(GTK_VALUE_POINTER(params[0])));
        return;
    }
    rb_func_call(self, id_super, sig, argc, params, args);
}
*/

#define DEFINE_EVENT_FUNC(EVENT,TYPE) \
static VALUE \
widget_event_ ## EVENT (self, event) \
    VALUE self, event; \
{ \
    GtkWidget *widget = get_widget(self); \
    GTK_WIDGET_CLASS(GTK_OBJECT(widget)->klass)->EVENT \
        (widget, &get_gdkevent(event)->TYPE); \
    return Qnil; \
}
DEFINE_EVENT_FUNC(button_press_event, button)
DEFINE_EVENT_FUNC(button_release_event, button)
DEFINE_EVENT_FUNC(motion_notify_event, motion)
DEFINE_EVENT_FUNC(delete_event, any)
DEFINE_EVENT_FUNC(destroy_event, any)
DEFINE_EVENT_FUNC(expose_event, expose)
DEFINE_EVENT_FUNC(key_press_event, key)
DEFINE_EVENT_FUNC(key_release_event, key)
DEFINE_EVENT_FUNC(enter_notify_event, crossing)
DEFINE_EVENT_FUNC(leave_notify_event, crossing)
DEFINE_EVENT_FUNC(configure_event, configure)
DEFINE_EVENT_FUNC(focus_in_event, focus_change)
DEFINE_EVENT_FUNC(focus_out_event, focus_change)
DEFINE_EVENT_FUNC(map_event, any)
DEFINE_EVENT_FUNC(unmap_event, any)
DEFINE_EVENT_FUNC(property_notify_event, property)
DEFINE_EVENT_FUNC(selection_clear_event, selection)
DEFINE_EVENT_FUNC(selection_request_event, selection)
DEFINE_EVENT_FUNC(selection_notify_event, selection)
DEFINE_EVENT_FUNC(proximity_in_event, proximity)
DEFINE_EVENT_FUNC(proximity_out_event, proximity)
DEFINE_EVENT_FUNC(visibility_notify_event, visibility)
DEFINE_EVENT_FUNC(client_event, client)
DEFINE_EVENT_FUNC(no_expose_event, any)

void Init_gtk_widget()
{
    gWidget = rb_define_class_under(mGtk, "Widget", gObject);

    /*
     * constants
     */
    rb_define_const(gWidget, "TOPLEVEL", INT2NUM(GTK_TOPLEVEL));
    rb_define_const(gWidget, "NO_WINDOW", INT2NUM(GTK_NO_WINDOW));
    rb_define_const(gWidget, "REALIZED", INT2NUM(GTK_REALIZED));
    rb_define_const(gWidget, "MAPPED", INT2NUM(GTK_MAPPED));
    rb_define_const(gWidget, "VISIBLE", INT2NUM(GTK_VISIBLE));
    rb_define_const(gWidget, "SENSITIVE", INT2NUM(GTK_SENSITIVE));
    rb_define_const(gWidget, "PARENT_SENSITIVE", INT2NUM(GTK_PARENT_SENSITIVE));
    rb_define_const(gWidget, "CAN_FOCUS", INT2NUM(GTK_CAN_FOCUS));
    rb_define_const(gWidget, "HAS_FOCUS", INT2NUM(GTK_HAS_FOCUS));
    rb_define_const(gWidget, "CAN_DEFAULT", INT2NUM(GTK_CAN_DEFAULT));
    rb_define_const(gWidget, "HAS_DEFAULT", INT2NUM(GTK_HAS_DEFAULT));
    rb_define_const(gWidget, "HAS_GRAB", INT2NUM(GTK_HAS_GRAB));
    rb_define_const(gWidget, "RC_STYLE", INT2NUM(GTK_RC_STYLE));
    rb_define_const(gWidget, "COMPOSITE_CHILD", INT2NUM(GTK_COMPOSITE_CHILD));
    rb_define_const(gWidget, "NO_REPARENT", INT2NUM(GTK_NO_REPARENT));
    rb_define_const(gWidget, "APP_PAINTABLE", INT2NUM(GTK_APP_PAINTABLE));
    rb_define_const(gWidget, "RECEIVES_DEFAULT", INT2NUM(GTK_RECEIVES_DEFAULT));

    /*
     * signals
     */
    rb_define_const(gWidget, "SIGNAL_SHOW", rb_str_new2("show"));
    rb_define_const(gWidget, "SIGNAL_HIDE", rb_str_new2("hide"));
    rb_define_const(gWidget, "SIGNAL_MAP", rb_str_new2("map"));
    rb_define_const(gWidget, "SIGNAL_UNMAP", rb_str_new2("unmap"));
    rb_define_const(gWidget, "SIGNAL_REALIZE", rb_str_new2("realize"));
    rb_define_const(gWidget, "SIGNAL_UNREALIZE", rb_str_new2("unrealize"));
    rb_define_const(gWidget, "SIGNAL_DRAW", rb_str_new2("draw"));
    rb_define_const(gWidget, "SIGNAL_DRAW_FOCUS", rb_str_new2("draw_focus"));
    rb_define_const(gWidget, "SIGNAL_DRAW_DEFAULT", rb_str_new2("draw_default"));
    rb_define_const(gWidget, "SIGNAL_SIZE_REQUEST", rb_str_new2("size_request"));
    rb_define_const(gWidget, "SIGNAL_SIZE_ALLOCATE", rb_str_new2("size_allocate"));
    rb_define_const(gWidget, "SIGNAL_STATE_CHANGED", rb_str_new2("state_changed"));
    rb_define_const(gWidget, "SIGNAL_PARENT_SET", rb_str_new2("parent_set"));
    rb_define_const(gWidget, "SIGNAL_STYLE_SET", rb_str_new2("style_set"));
    rb_define_const(gWidget, "SIGNAL_ADD_ACCELERATOR", rb_str_new2("add_accelerator"));
    rb_define_const(gWidget, "SIGNAL_REMOVE_ACCELERATOR", rb_str_new2("remove_accelerator"));
    rb_define_const(gWidget, "SIGNAL_GRAB_FOCUS", rb_str_new2("grab_focus"));
    rb_define_const(gWidget, "SIGNAL_EVENT", rb_str_new2("event"));
    rb_define_const(gWidget, "SIGNAL_BUTTON_PRESS_EVENT", rb_str_new2("button_press_event"));
    rb_define_const(gWidget, "SIGNAL_BUTTON_RELEASE_EVENT", rb_str_new2("button_release_event"));
    rb_define_const(gWidget, "SIGNAL_MOTION_NOTIFY_EVENT", rb_str_new2("motion_notify_event"));
    rb_define_const(gWidget, "SIGNAL_DELETE_EVENT", rb_str_new2("delete_event"));
    rb_define_const(gWidget, "SIGNAL_DESTROY_EVENT", rb_str_new2("destroy_event"));
    rb_define_const(gWidget, "SIGNAL_EXPOSE_EVENT", rb_str_new2("expose_event"));
    rb_define_const(gWidget, "SIGNAL_KEY_PRESS_EVENT", rb_str_new2("key_press_event"));
    rb_define_const(gWidget, "SIGNAL_KEY_RELEASE_EVENT", rb_str_new2("key_release_event"));
    rb_define_const(gWidget, "SIGNAL_ENTER_NOTIFY_EVENT", rb_str_new2("enter_notify_event"));
    rb_define_const(gWidget, "SIGNAL_LEAVE_NOTIFY_EVENT", rb_str_new2("leave_notify_event"));
    rb_define_const(gWidget, "SIGNAL_CONFIGURE_EVENT", rb_str_new2("configure_event"));
    rb_define_const(gWidget, "SIGNAL_FOCUS_IN_EVENT", rb_str_new2("focus_in_event"));
    rb_define_const(gWidget, "SIGNAL_FOCUS_OUT_EVENT", rb_str_new2("focus_out_event"));
    rb_define_const(gWidget, "SIGNAL_MAP_EVENT", rb_str_new2("map_event"));
    rb_define_const(gWidget, "SIGNAL_UNMAP_EVENT", rb_str_new2("unmap_event"));
    rb_define_const(gWidget, "SIGNAL_PROPERTY_NOTIFY_EVENT", rb_str_new2("property_notify_event"));
    rb_define_const(gWidget, "SIGNAL_SELECTION_CLEAR_EVENT", rb_str_new2("selection_clear_event"));
    rb_define_const(gWidget, "SIGNAL_SELECTION_REQUEST_EVENT", rb_str_new2("selection_request_event"));
    rb_define_const(gWidget, "SIGNAL_SELECTION_NOTIFY_EVENT", rb_str_new2("selection_notify_event"));
    rb_define_const(gWidget, "SIGNAL_SELECTION_GET", rb_str_new2("selection_get"));
    rb_define_const(gWidget, "SIGNAL_SELECTION_RECEIVED", rb_str_new2("selection_received"));
    rb_define_const(gWidget, "SIGNAL_PROXIMITY_IN_EVENT", rb_str_new2("proximity_in_event"));
    rb_define_const(gWidget, "SIGNAL_PROXIMITY_OUT_EVENT", rb_str_new2("proximity_out_event"));
    rb_define_const(gWidget, "SIGNAL_DRAG_BEGIN", rb_str_new2("drag_begin"));
    rb_define_const(gWidget, "SIGNAL_DRAG_END", rb_str_new2("drag_end"));
    rb_define_const(gWidget, "SIGNAL_DRAG_DATA_DELETE", rb_str_new2("drag_data_delete"));
    rb_define_const(gWidget, "SIGNAL_DRAG_LEAVE", rb_str_new2("drag_leave"));
    rb_define_const(gWidget, "SIGNAL_DRAG_MOTION", rb_str_new2("drag_motion"));
    rb_define_const(gWidget, "SIGNAL_DRAG_DROP", rb_str_new2("drag_drop"));
    rb_define_const(gWidget, "SIGNAL_DRAG_DATA_GET", rb_str_new2("drag_data_get"));
    rb_define_const(gWidget, "SIGNAL_DRAG_DATA_RECEIVED", rb_str_new2("drag_data_received"));
    rb_define_const(gWidget, "SIGNAL_CLIENT_EVENT", rb_str_new2("client_event"));
    rb_define_const(gWidget, "SIGNAL_NO_EXPOSE_EVENT", rb_str_new2("no_expose_event"));
    rb_define_const(gWidget, "SIGNAL_VISIBILITY_NOTIFY_EVENT", rb_str_new2("visibility_notify_event"));
    rb_define_const(gWidget, "SIGNAL_DEBUG_MSG", rb_str_new2("debug_msg"));
    rb_define_const(gWidget, "SIGNAL_LAST_SIGNAL", rb_str_new2("last_signal"));

    /*
     * instance methods
     */
    rb_define_method(gWidget, "show", widget_show, 0);
    rb_define_method(gWidget, "show_all", widget_show_all, 0);
    rb_define_method(gWidget, "show_now", widget_show_now, 0);
    rb_define_method(gWidget, "hide", widget_hide, 0);
    rb_define_method(gWidget, "hide_all", widget_hide_all, 0);
    rb_define_method(gWidget, "map", widget_map, 0);
    rb_define_method(gWidget, "unmap", widget_unmap, 0);
    rb_define_method(gWidget, "realize", widget_realize, 0);
    rb_define_method(gWidget, "unrealize", widget_unrealize, 0);
    rb_define_method(gWidget, "queue_draw", widget_queue_draw, 0);
    rb_define_method(gWidget, "queue_resize", widget_queue_resize, 0);
    rb_define_method(gWidget, "queue_clear", widget_queue_clear, 0);
    rb_define_method(gWidget, "draw", widget_draw, 1);
    rb_define_method(gWidget, "draw_focus", widget_draw_focus, 0);
    rb_define_method(gWidget, "draw_default", widget_draw_default, 0);
    rb_define_method(gWidget, "size_request", widget_size_request, 0);
    rb_define_method(gWidget, "size_allocate", widget_size_allocate, 1);
    rb_define_method(gWidget, "add_accelerator", widget_add_accel, 5);
    rb_define_method(gWidget, "remove_accelerator", widget_rm_accel, 3);
    rb_define_method(gWidget, "remove_accelerators", widget_rm_accels, 2);
    rb_define_method(gWidget, "accelerator_signal", widget_accel_signal, 3);
    rb_define_method(gWidget, "event", widget_event, 1);
    rb_define_method(gWidget, "activate", widget_activate, 0);
    rb_define_method(gWidget, "grab_focus", widget_grab_focus, 0);
    rb_define_method(gWidget, "grab_default", widget_grab_default, 0);
    rb_define_method(gWidget, "set_state", widget_set_state, 1);
    rb_define_method(gWidget, "reparent", widget_reparent, 1);
    rb_define_method(gWidget, "popup", widget_popup, 2);
    rb_define_method(gWidget, "intersect", widget_intersect, 2);
    rb_define_method(gWidget, "get_name", widget_get_name, 0);
    rb_define_method(gWidget, "set_name", widget_set_name, 1);
    rb_define_method(gWidget, "set_parent", widget_set_parent, 1);
    rb_define_method(gWidget, "set_sensitive", widget_set_sensitive, 1);
    rb_define_method(gWidget, "set_usize", widget_set_usize, 2);
    rb_define_method(gWidget, "set_uposition", widget_set_uposition, 2);
    rb_define_method(gWidget, "set_style", widget_set_style, 1);
    rb_define_method(gWidget, "set_app_paintable", widget_set_app_paintable, 1);
    rb_define_method(gWidget, "set_events", widget_set_events, 1);
    rb_define_method(gWidget, "add_events", widget_add_events, 1);
    rb_define_method(gWidget, "set_extension_events",
                     widget_set_extension_events, 1);
    rb_define_method(gWidget, "unparent", widget_unparent, 0);
    rb_define_method(gWidget, "allocation", widget_get_alloc, 0);
    rb_define_method(gWidget, "requisition", widget_get_requisition, 0);
    rb_define_method(gWidget, "allocation=", widget_set_alloc, 4);
    rb_define_method(gWidget, "requisition=", widget_set_requisition, 2);
    rb_define_method(gWidget, "get_child_requisition",
                     widget_get_child_requisition, 0);
    rb_define_method(gWidget, "set_scroll_adjustments",
                     widget_set_scroll_adjustments, 2);

    rb_define_method(gWidget, "state", widget_state, 0);
    rb_define_method(gWidget, "parent", widget_parent, 0);
    rb_define_method(gWidget, "get_toplevel", widget_get_toplevel, 0);
    rb_define_method(gWidget, "get_ancestor", widget_get_ancestor, 1);
    rb_define_method(gWidget, "get_colormap", widget_get_colormap, 0);
    rb_define_method(gWidget, "get_visual", widget_get_visual, 0);
    rb_define_method(gWidget, "get_style", widget_get_style, 0);
    rb_define_method(gWidget, "style", widget_get_style, 0);
    rb_define_method(gWidget, "get_events", widget_get_events, 0);
    rb_define_method(gWidget, "get_extension_events", widget_get_extension_events, 0);
    rb_define_method(gWidget, "get_pointer", widget_get_pointer, 0);
    rb_define_method(gWidget, "is_ancestor?", widget_is_ancestor, 1);
    rb_define_method(gWidget, "hide_on_delete", widget_hide_on_delete, 0);
    rb_define_method(gWidget, "window", widget_window, 0);
    rb_define_method(gWidget, "shape_combine_mask", widget_shape_combine_mask, 3);
    rb_define_method(gWidget, "path", widget_path, 0);
    rb_define_method(gWidget, "class_path", widget_class_path, 0);
    rb_define_method(gWidget, "set_rc_style", widget_set_rc_style, 0);
    rb_define_method(gWidget, "ensure_style", widget_ensure_style, 0);
    rb_define_method(gWidget, "modify_style", widget_modify_style, 1);
    rb_define_method(gWidget, "restore_default_style",
                     widget_restore_default_style, 0);
    rb_define_method(gWidget, "reset_rc_styles", widget_reset_rc_styles, 0);
    rb_define_method(gWidget, "get_composite_name", widget_get_composite_name, 0);
    rb_define_method(gWidget, "set_composite_name", widget_set_composite_name, 1);
    rb_define_method(gWidget, "reset_shapes", widget_reset_shapes, 0);

    rb_define_method(gWidget, "toplevel?",  widget_TOPLEVEL, 0);
    rb_define_method(gWidget, "no_window?", widget_NO_WINDOW, 0);
    rb_define_method(gWidget, "realized?",  widget_REALIZED, 0);
    rb_define_method(gWidget, "mapped?",    widget_MAPPED, 0);
    rb_define_method(gWidget, "visible?",   widget_VISIBLE, 0);
    rb_define_method(gWidget, "drawable?",  widget_DRAWABLE, 0);
    rb_define_method(gWidget, "individual_sensitive?", widget_SENSITIVE, 0);
    rb_define_method(gWidget, "parent_sensitive?", widget_PARENT_SENSITIVE, 0);
    rb_define_method(gWidget, "sensitive?",   widget_IS_SENSITIVE, 0);
    rb_define_method(gWidget, "can_focus?",   widget_CAN_FOCUS, 0);
    rb_define_method(gWidget, "has_focus?",   widget_HAS_FOCUS, 0);
    rb_define_method(gWidget, "can_default?", widget_CAN_DEFAULT, 0);
    rb_define_method(gWidget, "has_default?", widget_HAS_DEFAULT, 0);
    rb_define_method(gWidget, "has_grab?",    widget_HAS_GRAB, 0);
    rb_define_method(gWidget, "rc_style?",    widget_RC_STYLE, 0);

    /* Drag and Drop */
    rb_define_method(gWidget, "drag_dest_set", widget_drag_dest_set, 3);
    rb_define_method(gWidget, "drag_dest_unset", widget_drag_dest_unset, 0);
    rb_define_method(gWidget, "drag_dest_set_proxy", widget_drag_dest_set_proxy, 3);
    rb_define_method(gWidget, "drag_source_set", widget_drag_source_set, 3);
    rb_define_method(gWidget, "drag_source_set_icon", widget_drag_source_set_icon, 3);
    rb_define_method(gWidget, "drag_source_unset", widget_drag_source_unset, 0);
    rb_define_method(gWidget, "drag_get_data", widget_drag_get_data, 3);

    /* Selection */
    rb_define_method(gWidget, "selection_owner_set", widget_selection_owner_set, 2);
    rb_define_method(gWidget, "selection_add_target", widget_selection_add_target, 3);
    rb_define_method(gWidget, "selection_add_targets", widget_selection_add_targets, 2);
    rb_define_method(gWidget, "selection_convert", widget_selection_convert, 3);
    rb_define_method(gWidget, "selection_remove_all", widget_selection_remove_all, 0);
	
    /*
     * events
     */
    rb_define_method(gWidget, "button_press_event", widget_event_button_press_event, 1);
    rb_define_method(gWidget, "button_release_event", widget_event_button_release_event, 1);
    rb_define_method(gWidget, "motion_notify_event", widget_event_motion_notify_event, 1);
    rb_define_method(gWidget, "delete_event", widget_event_delete_event, 1);
    rb_define_method(gWidget, "destroy_event", widget_event_destroy_event, 1);
    rb_define_method(gWidget, "expose_event", widget_event_expose_event, 1);
    rb_define_method(gWidget, "key_press_event", widget_event_key_press_event, 1);
    rb_define_method(gWidget, "key_release_event", widget_event_key_release_event, 1);
    rb_define_method(gWidget, "enter_notify_event", widget_event_enter_notify_event, 1);
    rb_define_method(gWidget, "leave_notify_event", widget_event_leave_notify_event, 1);
    rb_define_method(gWidget, "configure_event", widget_event_configure_event, 1);
    rb_define_method(gWidget, "focus_in_event", widget_event_focus_in_event, 1);
    rb_define_method(gWidget, "focus_out_event", widget_event_focus_out_event, 1);
    rb_define_method(gWidget, "map_event", widget_event_map_event, 1);
    rb_define_method(gWidget, "unmap_event", widget_event_unmap_event, 1);
    rb_define_method(gWidget, "property_notify_event", widget_event_property_notify_event, 1);
    rb_define_method(gWidget, "selection_clear_event", widget_event_selection_clear_event, 1);
    rb_define_method(gWidget, "selection_request_event", widget_event_selection_request_event, 1);
    rb_define_method(gWidget, "selection_notify_event", widget_event_selection_notify_event, 1);
    rb_define_method(gWidget, "proximity_in_event", widget_event_proximity_in_event, 1);
    rb_define_method(gWidget, "proximity_out_event", widget_event_proximity_out_event, 1);
    rb_define_method(gWidget, "visibility_notify_event", widget_event_visibility_notify_event, 1);
    rb_define_method(gWidget, "client_event", widget_event_client_event, 1);
    rb_define_method(gWidget, "no_expose_event", widget_event_no_expose_event, 1);

    /*
     * singleton methods
     */
    rb_define_singleton_method(gWidget, "push_colormap", widget_push_cmap, 1);
    rb_define_singleton_method(gWidget, "push_visual", widget_push_visual, 1);
    rb_define_singleton_method(gWidget, "push_style", widget_push_style, 1);
    rb_define_singleton_method(gWidget, "pop_colormap", widget_pop_cmap, 0);
    rb_define_singleton_method(gWidget, "pop_visual", widget_pop_visual, 0);
    rb_define_singleton_method(gWidget, "pop_style", widget_pop_style, 0);
    rb_define_singleton_method(gWidget, "set_default_colormap",
                               widget_set_default_cmap, 1);
    rb_define_singleton_method(gWidget, "set_default_visual",
                               widget_set_default_visual, 1);
    rb_define_singleton_method(gWidget, "set_default_style",
                               widget_set_default_style, 1);
    rb_define_singleton_method(gWidget, "get_default_colormap",
                               widget_get_default_cmap, 0);
    rb_define_singleton_method(gWidget, "get_default_visual",
                               widget_get_default_visual, 0);
    rb_define_singleton_method(gWidget, "get_default_style",
                               widget_get_default_style, 0);
    rb_define_singleton_method(gWidget, "pop_composite_child",
                               widget_pop_composite_child, 0);
    rb_define_singleton_method(gWidget, "push_composite_child",
                               widget_push_composite_child, 0);

    /* private method */
    /* need rb_call_super, which will hopefully be implemented in Ruby 1.5 - yashi
    rb_define_private_method(gWidget, "signal_setup_args", 4);
    */

    /* child initialization */
    Init_gtk_calendar();
    Init_gtk_container();
    Init_gtk_drawing_area();
    Init_gtk_editable();
    Init_gtk_misc();
    Init_gtk_preview();
    Init_gtk_progress();
    Init_gtk_range();
    Init_gtk_ruler();
    Init_gtk_separator();
}
