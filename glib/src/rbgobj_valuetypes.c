/* -*- c-file-style: "ruby" -*- */
/**********************************************************************

  rbgobj_valuetypes.c -

  $Author: sakai $
  $Date: 2002/08/10 16:07:09 $

  Copyright (C) 2002  Masahiro Sakai

**********************************************************************/

#include "global.h"

static VALUE
ptr_s_gtype(klass)
    VALUE klass;
{
    return rbgobj_gtype_new(rbgobj_lookup_class(klass)->gtype);
}

static VALUE
ptr_gtype(self)
    VALUE self;
{
    return ptr_s_gtype(CLASS_OF(self));
}

static void
Init_gtype_pointer()
{
    VALUE cPtr = G_DEF_CLASS(G_TYPE_POINTER, "Pointer", mGLib);
    rb_define_singleton_method(cPtr, "gtype", ptr_s_gtype, 1);
    rb_define_method(cPtr, "gtype", ptr_gtype, 1);
}

/**********************************************************************/

static VALUE boxed_ruby_value_markers;

typedef struct {
    VALUE obj;
    guint ref_count;
} boxed_ruby_value_counter;

static void
boxed_ruby_value_counter_mark(boxed_ruby_value_counter* counter)
{
    if (counter->ref_count)
        rb_gc_mark(counter->obj);
}

static VALUE
boxed_ruby_value_ref(VALUE val)
{
    if (!SPECIAL_CONST_P(val)){
        VALUE key = rb_obj_id(val);
        VALUE marker = rb_hash_aref(boxed_ruby_value_markers, key);
        boxed_ruby_value_counter* counter;

        if (NIL_P(marker)){
            marker = Data_Make_Struct(rb_cData, boxed_ruby_value_counter,
                                      boxed_ruby_value_counter_mark, free,
                                      counter);
            counter->obj       = val;
            counter->ref_count = 1;
            rb_hash_aset(boxed_ruby_value_markers, key, marker);
        } else {
            Data_Get_Struct(marker, boxed_ruby_value_counter, counter);
            counter->ref_count += 1;
        }
    }
    return val;
}

static void
boxed_ruby_value_unref(VALUE val)
{
    if (!SPECIAL_CONST_P(val)){
        VALUE key = rb_obj_id(val);
        VALUE marker = rb_hash_aref(boxed_ruby_value_markers, key);
        boxed_ruby_value_counter* counter;

        Data_Get_Struct(marker, boxed_ruby_value_counter, counter);
        counter->ref_count -= 1;

        if (!counter->ref_count)
            rb_hash_aset(boxed_ruby_value_markers, key, Qnil);
    }
}

GType rbgobj_ruby_value_get_type()
{
  static GType our_type = 0;
  if (!our_type){
      our_type = g_boxed_type_register_static(
          "VALUE",
          (GBoxedCopyFunc)boxed_ruby_value_ref,
          (GBoxedFreeFunc)boxed_ruby_value_unref);
  }
  return our_type;
}

VALUE
g_value_get_ruby_value(const GValue* value)
{
    return (VALUE)g_value_get_boxed(value);
}

void
g_value_set_ruby_value(GValue* value, VALUE ruby)
{
    g_value_set_boxed(value, (gconstpointer)ruby);
}

static void
value_transform_ruby_any(const GValue *src_value,
                         GValue       *dest_value)
{
    rbgobj_rvalue_to_gvalue(g_value_get_ruby_value(src_value),
                            dest_value);
}

static void
value_transform_any_ruby(const GValue *src_value,
                         GValue       *dest_value)
{
    g_value_set_ruby_value(dest_value, GVAL2RVAL(src_value));
}

static void
Init_boxed_ruby_value()
{
    boxed_ruby_value_markers = rb_hash_new();
    rb_global_variable(&boxed_ruby_value_markers);

    rbgobj_register_g2r_func(RBGOBJ_TYPE_RUBY_VALUE, g_value_get_ruby_value);
    // rbgobj_register_r2g_func(rb_cObject, g_value_set_ruby_value);

    {
        const GType table[] = {
            G_TYPE_CHAR,
            G_TYPE_UCHAR,
            G_TYPE_BOOLEAN,
            G_TYPE_INT,
            G_TYPE_UINT,
            G_TYPE_LONG,
            G_TYPE_ULONG,
            G_TYPE_INT64,
            G_TYPE_UINT64,
            G_TYPE_ENUM,
            G_TYPE_FLAGS,
            G_TYPE_FLOAT,
            G_TYPE_DOUBLE,
            G_TYPE_STRING,
            G_TYPE_POINTER,
            //G_TYPE_BOXED,
            G_TYPE_PARAM,
            G_TYPE_OBJECT,
        };
        int i;

        for (i = 0; i < sizeof(table)/sizeof(table[0]); i++){
            g_value_register_transform_func(RBGOBJ_TYPE_RUBY_VALUE, table[i],
                                            value_transform_ruby_any);
            g_value_register_transform_func(table[i], RBGOBJ_TYPE_RUBY_VALUE,
                                            value_transform_any_ruby);
        }
    }
}

/**********************************************************************/

void
Init_gobject_gvaluetypes()
{
    Init_gtype_pointer();
    Init_boxed_ruby_value();
}
