/* $Id: rbgnome-i18n.c,v 1.1 2002/05/19 12:29:54 mutoh Exp $ */

/* Gnome::I18n module for Ruby/Gnome
 * Copyright (C) 2001 Neil Conway <neilconway@rogers.com>
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

#include <libintl.h>
#include "rbgnome.h"

VALUE mGnomeI18n;

static VALUE
gnoi18n_bindtextdomain(self, domain, dirname)
    VALUE self, domain, dirname;
{
    char* new_dirname;

    switch (TYPE(dirname)) {
    case T_STRING:
        new_dirname = bindtextdomain(STR2CSTR(domain), STR2CSTR(dirname));
        break;
    case T_NIL:
        new_dirname = bindtextdomain(STR2CSTR(domain), 0);
        break;
    default:
        rb_raise(rb_eTypeError, "dirname is Not String or Null");
    }

    return rb_str_new2(new_dirname);
}

static VALUE
gnoi18n_textdomain(self, domain)
    VALUE self, domain;
{
    char* new_domain;
    new_domain = textdomain(STR2CSTR(domain));
    return rb_str_new2(new_domain);
}

static VALUE
gnoi18n_gettext(self, msgid)
    VALUE self, msgid;
{
    char* msgstr;
    msgstr = gettext(STR2CSTR(msgid));
    return rb_str_new2(msgstr);
}

static VALUE
gnoi18n_gettext_noop(self, msgid)
    VALUE self, msgid;
{
    return msgid;
}

static VALUE
gnoi18n_dgettext(self, domain, msgid)
    VALUE self, domain, msgid;
{
    char* msgstr;
    msgstr = dgettext(STR2CSTR(domain), STR2CSTR(msgid));

    return rb_str_new2(msgstr);
}

static VALUE
gnoi18n_dcgettext(self, domain, msgid, category)
    VALUE self, domain, msgid, category;
{
    char* msgstr;
    msgstr = dcgettext(STR2CSTR(domain), STR2CSTR(msgid), FIX2INT(category));

    return rb_str_new2(msgstr);
}

static VALUE
gnoi18n_get_language(self)
    VALUE self;
{
    const char* lang;
    lang = gnome_i18n_get_language();
    return NIL_P(lang)?Qnil:rb_str_new2(lang);
}

static VALUE
gno18n_get_language_list(self, category_name)
    VALUE self, category_name;
{
    GList* lang_list;
    VALUE ary;
    lang_list = gnome_i18n_get_language_list(STR2CSTR(category_name));

    ary = rb_ary_new();
    while (lang_list) {
	char* lang = (char*)lang_list->data;
	lang_list = lang_list->next;
	rb_ary_push(ary, rb_str_new2(lang));
    }

    return ary;
}

static VALUE
gnoi18n_set_preferred_language(self, val)
    VALUE self, val;
{
    gnome_i18n_set_preferred_language(STR2CSTR(val));
    return self;
}

static VALUE
gnoi18n_get_preferred_language(self)
    VALUE self;
{
    const char *val;
    val = gnome_i18n_get_preferred_language();
    return NIL_P(val)?Qnil:rb_str_new2(val);
}

void
Init_gnome_i18n()
{
    mGnomeI18n = rb_define_module_under(mGnome, "I18n");

    rb_define_module_function(mGnomeI18n, "bindtextdomain",
			      gnoi18n_bindtextdomain, 2);
    rb_define_module_function(mGnomeI18n, "textdomain", gnoi18n_textdomain, 1);
    rb_define_module_function(mGnomeI18n, "gettext", gnoi18n_gettext, 1);
    rb_define_module_function(mGnomeI18n, "_", gnoi18n_gettext, 1);
    rb_define_module_function(mGnomeI18n, "gettext_noop",
			      gnoi18n_gettext_noop, 1);
    rb_define_module_function(mGnomeI18n, "N_", gnoi18n_gettext_noop, 1);
    rb_define_module_function(mGnomeI18n, "dgettext", gnoi18n_dgettext, 2);
    rb_define_module_function(mGnomeI18n, "dcgettext", gnoi18n_dcgettext, 3);

    rb_define_module_function(mGnomeI18n, "get_language",
			      gnoi18n_get_language, 0);
    rb_define_module_function(mGnomeI18n, "get_language_list",
			      gno18n_get_language_list, 1);
    rb_define_module_function(mGnomeI18n, "set_preferred_language",
			      gnoi18n_set_preferred_language, 1);
    rb_define_module_function(mGnomeI18n, "get_preferred_language",
			      gnoi18n_get_preferred_language, 0);
}
