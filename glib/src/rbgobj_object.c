/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/**********************************************************************

  rbgobj_object.c -

  $Author: sakai $
  $Date: 2002/09/29 13:36:28 $

  Copyright (C) 2002  Masahiro Sakai

  This file is derived from rbgtkobject.c in Ruby/Gtk distribution.
  rbgtkobject.c -
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi

**********************************************************************/

#include "ruby.h"
#include "st.h"
#include "global.h"

static VALUE
gobj_s_allocate(klass)
    VALUE klass;
{
    const RGObjClassInfo* cinfo = rbgobj_lookup_class(klass);
    if (G_TYPE_IS_ABSTRACT(cinfo->gtype))
        rb_raise(rb_eTypeError, "abstract class");
    return rbgobj_create_object(klass);
}

static gboolean
is_gtkobject(gobj)
    GObject* gobj;
{
    static GType gtype_gtkobject = G_TYPE_INVALID;
    if (!gtype_gtkobject)
        gtype_gtkobject = g_type_from_name("GtkObject");
    return gtype_gtkobject && g_type_is_a(G_OBJECT_TYPE(gobj), gtype_gtkobject);
}

#ifdef RBGLIB_ENABLE_EXPERIMENTAL

static VALUE
gobj_s_gobject_new(argc, argv, self)
    int argc;
    VALUE* argv;
    VALUE self;
{
    VALUE type, params_hash;
    GType gtype;
    GObject* gobj;
    VALUE result;

    rb_scan_args(argc, argv, "11", &type, &params_hash);

    if (RTEST(rb_obj_is_kind_of(type, rbgobj_cType))) {
        gtype = rbgobj_gtype_get(type);
    } else {
        StringValue(type);
        gtype = g_type_from_name(StringValuePtr(type));
    }

    gobj = rbgobj_gobject_new(gtype, params_hash);
    result = GOBJ2RVAL(gobj);

    // XXX: Ughhhhh
    if (is_gtkobject(gobj)){
        // We can't call gtk_object_sink() here.
        // But hopefully someone will call it in the future.
        //gtk_object_sink(gobj);
    } else {
        g_object_unref(gobj);
    }

    return result;
}

#endif /* RBGLIB_ENABLE_EXPERIMENTAL */

#if 0
void        g_object_class_install_property   (GObjectClass   *oclass,
					       guint           property_id,
					       GParamSpec     *pspec);
#endif

static VALUE
gobj_s_find_property(self, property_name)
     VALUE self, property_name;
{
    GObjectClass* oclass = g_type_class_ref(CLASS2GTYPE(self));
    const char* name;
    VALUE result;

    if (SYMBOL_P(property_name)) {
        name = rb_id2name(SYM2ID(property_name));
    } else {
        StringValue(property_name);
        name = StringValuePtr(property_name);
    }

    result = GOBJ2RVAL(g_object_class_find_property(oclass, name));

    g_type_class_unref(oclass);
    return result;
}

static VALUE
gobj_s_list_properties(self)
     VALUE self;
{
    GObjectClass* oclass = g_type_class_ref(CLASS2GTYPE(self));
    gint n_properties;
    GParamSpec** props;
    VALUE ary;
    int i;

    props = g_object_class_list_properties(oclass, &n_properties);

    ary = rb_ary_new2(n_properties);
    for (i = 0; i < n_properties; i++)
        rb_ary_store(ary, i, GOBJ2RVAL(props[i]));

    g_type_class_unref(oclass);
    return ary;
}

static VALUE
gobj_set_property(self, prop_name, val)
    VALUE self, prop_name, val;
{
    GParamSpec* pspec;
    const char* name;

    if (SYMBOL_P(prop_name)) {
        name = rb_id2name(SYM2ID(prop_name));
    } else {
        StringValue(prop_name);
        name = StringValuePtr(prop_name);
    }

    pspec = g_object_class_find_property(G_OBJECT_GET_CLASS(RVAL2GOBJ(self)),
                                         name);

    if (!pspec)
        rb_raise(rb_eArgError, "No such property: %s", name);
    else {
        GValue tmp = {0,};
        g_value_init(&tmp, G_PARAM_SPEC_VALUE_TYPE(pspec));
        if (!NIL_P(val))
            rbgobj_rvalue_to_gvalue(val, &tmp);
        g_object_set_property(RVAL2GOBJ(self), name, &tmp);
        g_value_unset(&tmp);
        return self;
    }
}

static VALUE
gobj_get_property(self, prop_name)
    VALUE self, prop_name;
{
    GParamSpec* pspec;
    const char* name;

    if (SYMBOL_P(prop_name)) {
        name = rb_id2name(SYM2ID(prop_name));
    } else {
        StringValue(prop_name);
        name = StringValuePtr(prop_name);
    }

    pspec = g_object_class_find_property(G_OBJECT_GET_CLASS(RVAL2GOBJ(self)),
                                         name);

    if (!pspec)
        rb_raise(rb_eArgError, "No such property: %s", name);
    else {
        GValue tmp = {0,};
        VALUE ret;
        g_value_init(&tmp, G_PARAM_SPEC_VALUE_TYPE(pspec));
        g_object_get_property(RVAL2GOBJ(self), name, &tmp);
        ret = GVAL2RVAL(&tmp);
        g_value_unset(&tmp);
        return ret;
    }
}

static VALUE gobj_thaw_notify(VALUE self);

static VALUE
gobj_freeze_notify(self)
    VALUE self;
{
    g_object_freeze_notify(RVAL2GOBJ(self));
    if (rb_block_given_p()) {
        return rb_ensure(rb_yield, self, gobj_thaw_notify, self);
    }
    return self;
}

static VALUE
gobj_notify(self, property_name)
    VALUE self, property_name;
{
    StringValue(property_name);
    g_object_notify(RVAL2GOBJ(self), StringValuePtr(property_name));
    return self;
}

static VALUE
gobj_thaw_notify(self)
    VALUE self;
{
    g_object_thaw_notify(RVAL2GOBJ(self));
    return self;
}

static VALUE
gobj_inspect(self)
    VALUE self;
{
    gobj_holder* holder;
    char *cname = rb_class2name(CLASS_OF(self));
    char *s;
    VALUE result;

    Data_Get_Struct(self, gobj_holder, holder);

    if (!holder->destroyed)
        s = g_strdup_printf("#<%s:%p ptr=%p>", cname, (void *)self, holder->gobj);
    else
        s = g_strdup_printf("#<%s:%p destroyed>", cname, (void *)self);

    result = rb_str_new2(s);
    g_free(s);

    return result;
}

static VALUE
gobj_initialize(argc, argv, self)
    int argc;
    VALUE *argv;
    VALUE self;
{
    const RGObjClassInfo* cinfo = rbgobj_lookup_class(CLASS_OF(self));
    VALUE params_hash;
    GObject* gobj;
    
    rb_scan_args(argc, argv, "01", &params_hash);

    gobj = rbgobj_gobject_new(cinfo->gtype, params_hash);

    if (is_gtkobject(gobj)){
        gobj = g_object_ref(gobj);
        // We can't call gtk_object_sink() here.
        // But hopefully someone will call it in the future.
        //gtk_object_sink(gobj);
    }

    G_INITIALIZE(self, gobj);
    return Qnil;
}

static VALUE
null()
{
    return (VALUE)NULL;
}

static VALUE
gobj_ref_count(self)
    VALUE self;
{
    GObject* gobj = (GObject*)rb_rescue((VALUE(*)())rbgobj_get_gobject, self, null, 0);
    return INT2NUM(gobj ? gobj->ref_count : 0);
}

static VALUE
gobj_smethod_added(self, id)
    VALUE self, id;
{
    GObject *obj = RVAL2GOBJ(self);
    const char* name = rb_id2name(SYM2ID(id));
    
    if (g_signal_lookup(name, G_OBJECT_TYPE(obj))) {
        VALUE method = rb_funcall(self, rb_intern("method"), 1, id);
        g_signal_connect_closure(RVAL2GOBJ(self), name,
                                 g_rclosure_new(method, Qnil), FALSE);
    }

    return Qnil;
}

/**********************************************************************/

void 
Init_gobject_gobject()
{
    VALUE cGObject = G_DEF_CLASS(G_TYPE_OBJECT, "Object", mGLib);

    rb_define_singleton_method(cGObject, "allocate", &gobj_s_allocate, 0);
#ifdef RBGLIB_ENABLE_EXPERIMENTAL
    rb_define_singleton_method(cGObject, "gobject_new", gobj_s_gobject_new, -1);
#endif

    rb_define_singleton_method(cGObject, "find_property", &gobj_s_find_property, 1);
    rb_define_singleton_method(cGObject, "list_properties", &gobj_s_list_properties, 0);

    rb_define_method(cGObject, "set_property", gobj_set_property, 2);
    rb_define_method(cGObject, "get_property", gobj_get_property, 1);
    rb_define_alias(cGObject, "property", "get_property");
    rb_define_method(cGObject, "freeze_notify", gobj_freeze_notify, 0);
    rb_define_method(cGObject, "notify", gobj_notify, 1);
    rb_define_method(cGObject, "thaw_notify", gobj_thaw_notify, 0);

    rb_define_method(cGObject, "initialize", gobj_initialize, -1);
    rb_define_method(cGObject, "ref_count", gobj_ref_count, 0); /* for debugging */
    rb_define_method(cGObject, "inspect", gobj_inspect, 0);

    rb_define_method(cGObject, "singleton_method_added", gobj_smethod_added, 1);
}

