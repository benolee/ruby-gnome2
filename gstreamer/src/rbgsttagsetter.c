/*
 * Copyright (C) 2003-2005 Laurent Sansonetti <lrz@gnome.org>
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

/* FIXME: document me */

static VALUE
rb_gst_tag_setter_merge (VALUE self, VALUE structure, VALUE merge_mode)
{
	gst_tag_setter_merge (RGST_TAG_SETTER (self),
			      ruby_hash_to_gst_structure (structure),
			      RVAL2GENUM (merge_mode, GST_TYPE_TAG_MERGE_MODE));
	return self;
}

void
Init_gst_tag_setter (void)
{
	VALUE c = G_DEF_INTERFACE (GST_TYPE_TAG_SETTER, "TagSetter", mGst);
	rb_define_method (c, "merge", rb_gst_tag_setter_merge, 2);	
}
