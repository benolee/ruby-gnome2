/* -*- c-file-style: "ruby" -*- */

#include "rbgobject.h"

extern void Init_gobject();
extern void Init_gobject_gtype();
extern void Init_gobject_gclosure();
extern void Init_gobject_gvalue();
extern void Init_gobject_signal();
extern void Init_gobject_gparam();

#ifndef StringValue
#define StringValue(s) ((s) = (TYPE(s) == T_STRING) ? (s) : rb_str_to_str(s))
#endif
#ifndef SafeStringValue
#define SafeStringValue(v) rb_check_safe_str(StringValue(v))
#endif
#ifndef StringValuePtr
#define StringValuePtr(s) STR2CSTR(s)
#endif
