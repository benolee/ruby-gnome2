/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 * Copyright (C) 2003, 2004 Laurent Sansonetti <lrz@gnome.org>
 * Copyright (C) 2007 Ruby-GNOME2 Project Team
 *
 * This file is part of Ruby/GStreamer.
 *
 * Ruby/GStreamer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Ruby/GStreamer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Ruby/GStreamer; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#include "rbgst.h"

#define SELF(self) RVAL2GST_PLUG_FEAT(self)

/* Class: Gst::PluginFeature
 * This is a base class for anything that can be added to a Gst::Plugin.
 */

/* Method: name
 * Returns: the name of the feature.
 */
static VALUE
rb_gst_pluginfeature_get_name (VALUE self)
{
	GstPluginFeature *feature = RGST_PLUGIN_FEATURE (self);
	return CSTR2RVAL (GST_PLUGIN_FEATURE_NAME (feature));
}

gboolean
is_valid_pluginfeature_type (const GType type)
{
	return type == GST_TYPE_ELEMENT_FACTORY ||
            type == GST_TYPE_INDEX_FACTORY;
}

VALUE
instanciate_pluginfeature (GstPluginFeature *feature)
{

	if (GST_IS_ELEMENT_FACTORY (feature))
		return RGST_ELEMENT_FACTORY_NEW (feature);
	else if (GST_IS_INDEX_FACTORY (feature))
		return RGST_INDEX_FACTORY_NEW (feature);
	else if (GST_IS_TYPE_FIND_FACTORY (feature))
		return RGST_TYPE_FIND_FACTORY_NEW (feature);
	else
		rb_raise(rb_eArgError,
			 "Invalid plugin feature of type ``%s''",
			 g_type_name (G_OBJECT_TYPE (feature))); 
	return Qnil;
}

static VALUE
load_bang(VALUE self)
{
    GstPluginFeature *original, *feature;

    original = SELF(self);
    feature = gst_plugin_feature_load(original);
    if (feature) {
        if (feature != original)
            G_INITIALIZE(self, feature);
        gst_object_unref(original);
        return Qtrue;
    } else {
        return Qfalse;
    }
}

void
Init_gst_plugin_feature (void)
{
    VALUE rb_cGstPluginFeature;

    rb_cGstPluginFeature = G_DEF_CLASS(GST_TYPE_PLUGIN_FEATURE,
                                       "PluginFeature", mGst);

    rb_define_method(rb_cGstPluginFeature, "name",
                     rb_gst_pluginfeature_get_name, 0);

    rb_define_method(rb_cGstPluginFeature, "load!", load_bang, 0);
}
