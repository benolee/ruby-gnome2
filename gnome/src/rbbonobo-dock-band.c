/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/* $Id: rbbonobo-dock-band.c,v 1.3 2002/10/26 06:22:24 tkubo Exp $ */
/* based on libbonoboui/bonobo/bonobo-doc-band.h */
/* renamed from rbgnome-dock-band.c */

/* Bonobo::DockBand widget for Ruby/GNOME2
 * Copyright (C) 1999 Minoru Inachi <inachi@earth.interq.or.jp>
 *               2002 KUBO Takehiro <kubo@jiubao.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "rbbonobo.h"

#define _SELF(self) BONOBO_DOCK_BAND(RVAL2GOBJ(self))

/*
 * Class Bonobo::DockBand
 *
 * Hierarchy:
 *
 *   Object
 *     +----Gtk::Object
 *            +----Gtk::Widget
 *                   +----Gtk::Container
 *                          +----Bonobo::DockBand
 */

static VALUE
dockband_initialize(self)
    VALUE self;
{
    RBGTK_INITIALIZE(self, bonobo_dock_band_new());
    return Qnil;
}

static VALUE
dockband_set_orientation(self, orientation)
    VALUE self, orientation;
{
    bonobo_dock_band_set_orientation(_SELF(self),
                                     NUM2INT(orientation));
    return self;
}

static VALUE
dockband_get_orientation(self)
    VALUE self;
{
    GtkOrientation result;
    result = bonobo_dock_band_get_orientation(_SELF(self));
    return INT2FIX(result);
}

static VALUE
dockband_insert(self, child, offset, position)
    VALUE self, child, offset, position;
{
    gboolean result;
    result = bonobo_dock_band_insert(_SELF(self),
                                     GTK_WIDGET(RVAL2GOBJ(child)),
                                     NUM2INT(offset),
                                     NUM2INT(position));
    if (!result) {
        rb_raise(rb_eRuntimeError, "operation failed\n");
    }
    return self;
}

static VALUE
dockband_prepend(self, child, offset)
    VALUE self, child, offset;
{
    gboolean result;
    result = bonobo_dock_band_prepend(_SELF(self),
                                      GTK_WIDGET(RVAL2GOBJ(child)),
                                      NUM2INT(offset));
    if (!result) {
        rb_raise(rb_eRuntimeError, "operation failed\n");
    }
    return self;
}

static VALUE
dockband_append(self, child, offset)
    VALUE self, child, offset;
{
    gboolean result;
    result = bonobo_dock_band_append(_SELF(self),
                                     GTK_WIDGET(RVAL2GOBJ(child)),
                                     NUM2INT(offset));
    if (!result) {
        rb_raise(rb_eRuntimeError, "operation failed\n");
    }
    return self;
}
    
static VALUE
dockband_set_child_offset(self, child, offset)
    VALUE self, child, offset;
{
    bonobo_dock_band_set_child_offset(_SELF(self),
                                      GTK_WIDGET(RVAL2GOBJ(child)),
                                      NUM2INT(offset));
    return self;
}
    
static VALUE
dockband_get_child_offset(self, child)
    VALUE self, child;
{
    guint result;
    result = bonobo_dock_band_get_child_offset(_SELF(self),
                                               GTK_WIDGET(RVAL2GOBJ(child)));
    return INT2NUM(self);
}

#if 0
static VALUE
dockband_move_child(self, old_child, new_num)
    VALUE self, old_child, new_num;
{
    return self;
}
#endif

static VALUE
dockband_get_num_children(self)
    VALUE self;
{
    guint result;
    result = bonobo_dock_band_get_num_children(_SELF(self));
    return INT2NUM(result);
}

static VALUE
dockband_drag_begin(self, item)
    VALUE self, item;
{
    bonobo_dock_band_drag_begin(_SELF(self),
                                BONOBO_DOCK_ITEM(RVAL2GOBJ(item)));
    return self;
}

static VALUE
dockband_drag_to(self, item, x, y)
    VALUE self, item, x, y;
{
    gboolean result;
    result = bonobo_dock_band_drag_to(_SELF(self),
                                      BONOBO_DOCK_ITEM(RVAL2GOBJ(item)),
                                      NUM2INT(x), NUM2INT(y));
    if (!result) {
        rb_raise(rb_eRuntimeError, "operation failed\n");
    }
    return self;
}

static VALUE
dockband_drag_end(self, item)
    VALUE self, item;
{
    bonobo_dock_band_drag_end(_SELF(self),
                              BONOBO_DOCK_ITEM(RVAL2GOBJ(item)));
    return self;
}

static VALUE
dockband_get_item_by_name(self, name)
    VALUE self, name;
{
    BonoboDockItem *result;
    guint position, offset;
    VALUE ary;

    result = bonobo_dock_band_get_item_by_name(_SELF(self), RVAL2CSTR(name),
                                               &position, &offset);
    ary = rb_ary_new2(3);
    rb_ary_push(ary, GOBJ2RVAL(result));
    rb_ary_push(ary, INT2NUM(position));
    rb_ary_push(ary, INT2NUM(offset));
    return ary;
}

static VALUE
dockband_layout_add(self, layout, placement, band_num)
    VALUE self, layout, placement, band_num;
{
    bonobo_dock_band_layout_add(_SELF(self),
                                BONOBO_DOCK_LAYOUT(RVAL2GOBJ(layout)),
                                NUM2INT(placement), NUM2INT(band_num));
    return self;
}

void
Init_bonobo_dock_band(mBonobo)
    VALUE mBonobo;
{
    VALUE bnbDockBand = G_DEF_CLASS(BONOBO_TYPE_DOCK_BAND, "DockBand", mBonobo);

    /*
     * instance methods
     */
    rb_define_method(bnbDockBand, "initialize", dockband_initialize, 0);
    rb_define_method(bnbDockBand, "set_orientation", dockband_set_orientation, 1);
    rb_define_method(bnbDockBand, "orientation", dockband_get_orientation, 0);
    rb_define_method(bnbDockBand, "insert", dockband_insert, 3);
    rb_define_method(bnbDockBand, "prepend", dockband_prepend, 2);
    rb_define_method(bnbDockBand, "append", dockband_append, 2);
    rb_define_method(bnbDockBand, "set_child_offset", dockband_set_child_offset, 2);
    rb_define_method(bnbDockBand, "get_child_offset", dockband_get_child_offset, 1);
#if 0
    rb_define_method(bnbDockBand, "move_child", dockband_move_child, 2);
#endif
    rb_define_method(bnbDockBand, "get_num_children", dockband_get_num_children, 0);
    rb_define_method(bnbDockBand, "drag_begin", dockband_drag_begin, 1);
    rb_define_method(bnbDockBand, "drag_to", dockband_drag_to, 3);
    rb_define_method(bnbDockBand, "drag_end", dockband_drag_end, 1);
    rb_define_method(bnbDockBand, "get_item_by_name", dockband_get_item_by_name, 1);
    rb_define_method(bnbDockBand, "layout_add", dockband_layout_add, 3);

    G_DEF_SETTERS(bnbDockBand);
}
