/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbpangoattrlist.c -

  $Author: mutoh $
  $Date: 2005/03/05 18:46:23 $

  Copyright (C) 2002-2005 Masao Mutoh 
************************************************/

#include "rbpango.h"

static ID id_call;

#define _SELF(self) ((PangoAttrList*)RVAL2BOXED(self, PANGO_TYPE_ATTR_LIST))

static VALUE
attrlist_initialize(self)
    VALUE self;
{
    G_INITIALIZE(self, pango_attr_list_new());
    return Qnil;
}

static VALUE
attrlist_insert(self, attr)
    VALUE self, attr;
{
    pango_attr_list_insert(_SELF(self), RVAL2ATTR(attr));
    return self;
}

static VALUE
attrlist_insert_before(self, attr)
    VALUE self, attr;
{
    pango_attr_list_insert_before(_SELF(self), RVAL2ATTR(attr));
    return self;
}

static VALUE
attrlist_change(self, attr)
    VALUE self, attr;
{
    pango_attr_list_change(_SELF(self), RVAL2ATTR(attr));
    return self;
}

static VALUE
attrlist_splice(self, other, pos, len)
    VALUE self, other, pos, len;
{
    pango_attr_list_splice(_SELF(self), _SELF(other), NUM2INT(pos), NUM2INT(len));
    return self;
}

#if PANGO_CHECK_VERSION(1,4,0)
static gboolean
filter_func(attr, data)
    PangoAttribute* attr;
    gpointer data;
{
    return CBOOL2RVAL(rb_funcall((VALUE)data, id_call, 1, ATTR2RVAL(attr)));
}

static VALUE
attrlist_filter(self)
    VALUE self;
{
    VALUE func = G_BLOCK_PROC();
    G_RELATIVE(self, func);
    return BOXED2RVAL(pango_attr_list_filter(_SELF(self), 
                                             (PangoAttrFilterFunc)filter_func, 
                                             (gpointer)func),
                      PANGO_TYPE_ATTR_LIST);
}
#endif

static VALUE
attrlist_get_iterator(self)
    VALUE self;
{
    return BOXED2RVAL(pango_attr_list_get_iterator(_SELF(self)), PANGO_TYPE_ATTR_ITERATOR);
}

void
Init_pango_attrlist()
{
    VALUE pAttrlist = G_DEF_CLASS(PANGO_TYPE_ATTR_LIST, "AttrList", mPango);

    id_call = rb_intern("call");

    rb_define_method(pAttrlist, "initialize", attrlist_initialize, 0);
    rb_define_method(pAttrlist, "insert", attrlist_insert, 1);
    rb_define_method(pAttrlist, "insert_before", attrlist_insert_before, 1);
    rb_define_method(pAttrlist, "change", attrlist_change, 1);
    rb_define_method(pAttrlist, "splice", attrlist_splice, 3);
#if PANGO_CHECK_VERSION(1,4,0)
    rb_define_method(pAttrlist, "filter", attrlist_filter, 0);
#endif
    rb_define_method(pAttrlist, "iterator", attrlist_get_iterator, 0);

}
