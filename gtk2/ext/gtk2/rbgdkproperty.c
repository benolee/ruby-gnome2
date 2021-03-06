/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgdkproperty.c -

  $Author: ggc $
  $Date: 2007/07/13 16:07:31 $


  Copyright (C) 2003,2004 Ruby-GNOME2 Project Team

  Devided from rbgdkwindow.c
  rbgdkwindow.c - 
  Copyright (C) 2002,2003 Ruby-GNOME2 Project Team
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/
#include "global.h"

static VALUE
gdkprop_text_property_to_text_list(int argc, VALUE *argv, VALUE self)
{
    gint num, i;
    gchar** list;
    VALUE ret = Qnil;
    
    if (argc == 3) {
        VALUE encoding, format, text;
        rb_scan_args(argc, argv, "30", &encoding, &format, &text);
        StringValue(text);
        
        num = gdk_text_property_to_text_list(RVAL2ATOM(encoding),
                                             NUM2INT(format),
                                             (const guchar*)RVAL2CSTR(text), 
                                             RSTRING_LEN(text), &list);
    } else {
#if GTK_CHECK_VERSION(2,2,0)
        VALUE display, encoding, format, text;
        rb_scan_args(argc, argv, "40", &display, &encoding, &format, &text);
        StringValue(text);
        
        num = gdk_text_property_to_text_list_for_display(GDK_DISPLAY_OBJECT(RVAL2GOBJ(display)),
                                                         RVAL2ATOM(encoding),
                                                         NUM2INT(format),
                                                         (const guchar*)RVAL2CSTR(text),
                                                         RSTRING_LEN(text),
                                                         &list);
#else
        VALUE encoding, format, text;
        rb_scan_args(argc, argv, "30", &encoding, &format, &text);
        rb_warn("Gdk::Property.text_property_to_text_list: Not supported arguments in GTK+-2.0.x.");
        num = gdk_text_property_to_text_list(RVAL2ATOM(encoding),
                                             NUM2INT(format),
                                             (const guchar*)RVAL2CSTR(text),
                                             RSTRING_LEN(text), &list);
#endif
    }

    ret = rb_ary_new2(num);
    for (i =0; i < num; i++){
        rb_ary_push(ret, CSTR2RVAL(list[i]));
    }
    gdk_free_text_list(list);
    return ret;
}

static VALUE
gdkprop_text_property_to_utf8_list(int argc, VALUE *argv, VALUE self)
{
    gint num, i;
    gchar** list;
    VALUE ret = Qnil;
    
    if (argc == 3) {
        VALUE encoding, format, text;
        rb_scan_args(argc, argv, "30", &encoding, &format, &text);
        StringValue(text);
        
        num = gdk_text_property_to_utf8_list(RVAL2ATOM(encoding),
                                             NUM2INT(format),
                                             (const guchar*)RVAL2CSTR(text),
                                             RSTRING_LEN(text), &list);
    } else {
#if GTK_CHECK_VERSION(2,2,0)
        VALUE display, encoding, format, text;
        rb_scan_args(argc, argv, "40", &display, &encoding, &format, &text);
        StringValue(text);
        
        num = gdk_text_property_to_utf8_list_for_display(GDK_DISPLAY_OBJECT(RVAL2GOBJ(display)),
                                                         RVAL2ATOM(encoding),
                                                         NUM2INT(format),
                                                         (const guchar*)RVAL2CSTR(text),
                                                         RSTRING_LEN(text),
                                                         &list);
#else
        VALUE encoding, format, text;
        rb_scan_args(argc, argv, "30", &encoding, &format, &text);
        StringValue(text);

        rb_warn("Gdk::Property.text_property_to_utf8_list: Not supported arguments in GTK+-2.0.x.");
        num = gdk_text_property_to_utf8_list(RVAL2ATOM(encoding),
                                             NUM2INT(format),
                                             (const guchar*)RVAL2CSTR(text),
                                             RSTRING_LEN(text), &list);
#endif
    }

    ret = rb_ary_new2(num);
    for (i =0; i < num; i++){
        rb_ary_push(ret, CSTR2RVAL(list[i]));
    }
    g_strfreev(list);
    return ret;
}

static VALUE
gdkprop_string_to_compound_text(int argc, VALUE *argv, VALUE self)
{
    gint num;
    GdkAtom encoding;
    gint format;
    guchar *ctext;
    gint length;

    if (argc == 1) {
        VALUE str;
        rb_scan_args(argc, argv, "10", &str);
        num = gdk_string_to_compound_text(RVAL2CSTR(str),
                                          &encoding, &format,
                                          &ctext, &length);
    } else {
#if GTK_CHECK_VERSION(2,2,0)
        VALUE display, str;

        rb_scan_args(argc, argv, "20", &display, &str);
        num = gdk_string_to_compound_text_for_display(GDK_DISPLAY_OBJECT(RVAL2GOBJ(display)),
                                                      RVAL2CSTR(str),
                                                      &encoding, &format,
                                                      &ctext, &length);
#else
        VALUE str;
        rb_scan_args(argc, argv, "10", &str);
        rb_warn("Gdk::Property.string_to_compound_text: Not supported arguments in GTK+-2.0.x.");
        num = gdk_string_to_compound_text(RVAL2CSTR(str),
                                          &encoding, &format,
                                          &ctext, &length);
#endif
    }

    if (num == 0){
        VALUE ret = CSTR2RVAL((const char*)ctext);
        gdk_free_compound_text(ctext);
        return rb_ary_new3(3, BOXED2RVAL(encoding, GDK_TYPE_ATOM),
                           INT2NUM(format), ret);
    } else {
        rb_raise(rb_eRuntimeError, "failed to converts a string %d\n", num);
    }
    return Qnil;
}

static VALUE
gdkprop_utf8_to_string_target(VALUE self, VALUE str)
{
    return CSTR2RVAL((const char*)gdk_utf8_to_string_target(RVAL2CSTR(str)));
}

static VALUE
gdkprop_utf8_to_compound_text(int argc, VALUE *argv, VALUE self)
{
    GdkAtom encoding;
    gint format;
    guchar *ctext;
    gint length;
    gint ret;

    if (argc == 1) {
        VALUE str;
        rb_scan_args(argc, argv, "10", &str);
    
        ret = gdk_utf8_to_compound_text(RVAL2CSTR(str),
                                        &encoding, &format,
                                        &ctext, &length);
    } else {
#if GTK_CHECK_VERSION(2,2,0)
        VALUE display, str;

        rb_scan_args(argc, argv, "20", &display, &str);
        ret = gdk_utf8_to_compound_text_for_display(GDK_DISPLAY_OBJECT(RVAL2GOBJ(display)),
                                                    RVAL2CSTR(str),
                                                    &encoding, &format,
                                                    &ctext, &length);
#else
        VALUE str;
        rb_scan_args(argc, argv, "10", &str);
    
        rb_warn("Gdk::Property.utf8_to_compound_text: Not supported arguments in GTK+-2.0.x.");
        ret = gdk_utf8_to_compound_text(RVAL2CSTR(str),
                                        &encoding, &format,
                                        &ctext, &length);
#endif
    }

    if (ret){
        VALUE val = CSTR2RVAL((const char*)ctext);
        gdk_free_compound_text(ctext);
        return rb_ary_new3(3, BOXED2RVAL(encoding, GDK_TYPE_ATOM),
                           INT2NUM(format), val);
    } else {
        rb_raise(rb_eRuntimeError, "failed to converts a string %d\n", ret);
    }
    return Qnil;
}


static VALUE
gdkprop_change(int argc, VALUE *argv, VALUE self)
{
    int        fmt, len;
    void*      dat;
    GdkAtom    ntype;
    VALUE win, property, type, size= Qnil, mode, src;
    
    if(6 == argc)
        rb_scan_args(argc, argv, "60", &win, &property, &type, &size, &mode, &src);
    else
        rb_scan_args(argc, argv, "50", &win, &property, &type, &mode, &src);
    
    rbgtk_atom2selectiondata(type, size, src, &ntype, &dat, &fmt, &len);
    
    gdk_property_change(GDK_WINDOW(RVAL2GOBJ(win)), RVAL2ATOM(property), 
                        ntype, fmt, RVAL2GENUM(mode, GDK_TYPE_PROP_MODE), dat, len);

    rbgtk_atom2selectiondata_free(ntype, dat);

    return self;
}

static VALUE
gdkprop_get(int argc, VALUE *argv, VALUE self)
{
    /* for argument processing */
    GdkAtom     rtype;
    gint        rfmt, rlen;
    guchar*	rdat;
    VALUE win, property, type, offset=INT2FIX(0), length=INT2FIX(9999), delete;
    
    /* for inner processing */
    int		i;
    VALUE	ret = 0;
    
    if(6 == argc)
        rb_scan_args(argc, argv, "60", &win, &property, &type, &offset, &length, &delete);
    else
        rb_scan_args(argc, argv, "40", &win, &property, &type, &delete);
    
    
    if(gdk_property_get(GDK_WINDOW(RVAL2GOBJ(win)), RVAL2ATOM(property), RVAL2ATOM(type),
                        NUM2INT(offset), NUM2INT(length),
                        RVAL2CBOOL(delete), &rtype, &rfmt, &rlen, &rdat) == FALSE){
        return Qnil;
    }
 
    switch(rfmt){
      case 8:
      default:
        ret = RBG_STRING_SET_UTF8_ENCODING(rb_str_new((const char*)rdat, rlen));
        break;
        
      case 16:
        ret = rb_ary_new();
        
        for( i = 0; i < rlen; i++){
            rb_ary_push(ret, rb_Integer(((unsigned short*)rdat)[i]));
        }
        break;
        
      case 32:
         ret = rb_ary_new();

         if(rtype != GDK_SELECTION_TYPE_ATOM){
           for(i = 0; i < (rlen/sizeof(unsigned long)); i++){
             rb_ary_push(ret, INT2FIX(((unsigned long*)rdat)[i]));
           }
         } else {
           for(i = 0; i < (rlen/sizeof(unsigned long)); i++){
             rb_ary_push(ret, BOXED2RVAL((GdkAtom)((unsigned long*)rdat)[i], GDK_TYPE_ATOM));
           }
         }
        break;
    }
    
    return rb_ary_new3(3, BOXED2RVAL(rtype, GDK_TYPE_ATOM), 
                       ret, INT2NUM(rlen));
}

static VALUE
gdkprop_delete(VALUE self, VALUE win, VALUE property)
{
    gdk_property_delete(GDK_WINDOW(RVAL2GOBJ(win)), RVAL2ATOM(property));
    return self;
}

void
Init_gtk_gdk_property()
{
    VALUE gdkProperty = rb_define_module_under(mGdk, "Property");

    rb_define_module_function(gdkProperty, "text_property_to_text_list", gdkprop_text_property_to_text_list, -1);
    rb_define_module_function(gdkProperty, "text_property_to_utf8_list", gdkprop_text_property_to_utf8_list, -1);
    rb_define_module_function(gdkProperty, "string_to_compound_text", gdkprop_string_to_compound_text, -1);
    rb_define_module_function(gdkProperty, "utf8_to_string_target", gdkprop_utf8_to_string_target, 1);
    rb_define_module_function(gdkProperty, "utf8_to_compound_text", gdkprop_utf8_to_compound_text, -1);
    rb_define_module_function(gdkProperty, "change", gdkprop_change, -1);
    rb_define_module_function(gdkProperty, "get", gdkprop_get, -1);
    rb_define_module_function(gdkProperty, "delete", gdkprop_delete, 2);

    /* GdkPropMode from GdkProperties */
    G_DEF_CLASS(GDK_TYPE_PROP_MODE, "PropMode", gdkProperty);
    G_DEF_CONSTANTS(gdkProperty, GDK_TYPE_PROP_MODE, "GDK_PROP_");

}
