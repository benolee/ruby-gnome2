/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/* $Id: rbbonobo-dock-layout.c,v 1.2 2002/09/25 17:17:24 tkubo Exp $ */

/* Bonobo::DockLayout class for Ruby/Gnome
 * Copyright (C) 1999 Minoru Inachi <inachi@earth.interq.or.jp>
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

#include "rbgnome.h"

#define _SELF(self) BONOBO_DOCK_LAYOUT(RVAL2GOBJ(self))
static VALUE bnbDockLayoutItem;

/*
 * Class Bonobo::DockLayout
 *
 * Hierarchy:
 *
 *   Object
 *     +----Glib::Object
 *            +----Bonobo::DockLayout
 */

static VALUE
docklayout_initialize(self)
    VALUE self;
{
    G_INITIALIZE(self, bonobo_dock_layout_new());
    return Qnil;
}

/*
 * Bonobo::DockLayout#add_item(item, placement,
 *                band_num, band_position, offset)
 *
 * Add item to layout with the specified parameters.
 *
 * arguments:
 *   item - The dock item to be added to @layout
 *   placement - Placement of @item in @layout
 *   band_num - Band number
 *   band_position - Position within the band
 *   offset - Distance from the previous element in the band
 */
static VALUE
docklayout_add_item(self, item, placement,
                    band_num, band_position, offset)
    VALUE self, item, placement;
    VALUE band_num, band_position, offset;
{
    gboolean result;
    result = bonobo_dock_layout_add_item(_SELF(self),
                                         BONOBO_DOCK_ITEM(RVAL2GOBJ(item)),
                                         NUM2INT(placement),
                                         NUM2INT(band_num),
                                         NUM2INT(band_position),
                                         NUM2INT(offset));
    if (!result) {
        rb_raise(rb_eRuntimeError, "operation failed\n");
    }
    return self;
}

static VALUE
docklayout_add_floating_item(self, item, x, y, orientation)
    VALUE self, item, x, y, orientation;
{
    gboolean result;
    result = bonobo_dock_layout_add_floating_item(_SELF(self),
                                                  BONOBO_DOCK_ITEM(RVAL2GOBJ(item)),
                                                  NUM2INT(x),
                                                  NUM2INT(y),
                                                  NUM2INT(orientation));
    if (!result) {
        rb_raise(rb_eRuntimeError, "operation failed\n");
    }
    return self;
}

static VALUE
docklayout_get_item(self, item)
    VALUE self, item;
{
    BonoboDockLayoutItem *result;

    if (TYPE(item) == T_STRING) {
        result = bonobo_dock_layout_get_item_by_name(_SELF(self),
                                                     RVAL2CSTR(item));
    } else {
        result = bonobo_dock_layout_get_item(_SELF(self),
                                             BONOBO_DOCK_ITEM(RVAL2GOBJ(item)));
    }
    return Data_Wrap_Struct(bnbDockLayoutItem, 0, 0, result);
}

static VALUE
docklayout_remove_item(self, item)
    VALUE self, item;
{
    gboolean result;

    if (TYPE(item) == T_STRING) {
        result = bonobo_dock_layout_remove_item_by_name(
            _SELF(self),
            RVAL2CSTR(item));
    } else {
        result = bonobo_dock_layout_remove_item(
            _SELF(self),
            BONOBO_DOCK_ITEM(RVAL2GOBJ(item)));
    }

    if (!result) {
        rb_raise(rb_eRuntimeError, "operation failed\n");
    }

    return self;
}

static VALUE
docklayout_create_string(self)
    VALUE self;
{
    gchar *result;
    result = bonobo_dock_layout_create_string(
        _SELF(self));
    return rb_str_new2(result);
}

static VALUE
docklayout_parse_string(self, string)
    VALUE self, string;
{
    gboolean result;
    result = bonobo_dock_layout_parse_string(
        _SELF(self),
        RVAL2CSTR(string));

    if (!result) {
        rb_raise(rb_eRuntimeError, "operation failed\n");
    }

    return self;
}

static VALUE
docklayout_add_to_dock(self, dock)
    VALUE self, dock;
{
    gboolean result;
    result = bonobo_dock_layout_add_to_dock(_SELF(self),
                                            BONOBO_DOCK(RVAL2GOBJ(dock)));
    if (!result) {
        rb_raise(rb_eRuntimeError, "operation failed\n");
    }
    return self;
}

void
Init_bonobo_dock_layout(mBonobo)
    VALUE mBonobo;
{
    VALUE bnbDockLayout = G_DEF_CLASS(BONOBO_TYPE_DOCK_LAYOUT, "DockLayout", mBonobo);
    bnbDockLayoutItem = rb_define_class_under(mBonobo, "DockLayoutItem", rb_cData);

    /*
     * instance methods
     */
    rb_define_method(bnbDockLayout, "initialize", docklayout_initialize, 0);
    rb_define_method(bnbDockLayout, "add_item", docklayout_add_item, 5);
    rb_define_method(bnbDockLayout, "add_floating_item", docklayout_add_floating_item, 4);
    rb_define_method(bnbDockLayout, "get_item", docklayout_get_item, 1);
    rb_define_method(bnbDockLayout, "remove_item", docklayout_remove_item, 1);
    rb_define_method(bnbDockLayout, "create_string", docklayout_create_string, 0);
    rb_define_method(bnbDockLayout, "parse_string", docklayout_parse_string, 1);
    rb_define_method(bnbDockLayout, "add_to_dock", docklayout_add_to_dock, 1);
}
