/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbatkaction.c -

  $Author: mutoh $
  $Date: 2004/03/05 15:33:47 $

  Copyright (C) 2004 Masao Mutoh 
************************************************/

#include "rbatk.h"

#define _SELF(s) (ATK_ACTION(RVAL2GOBJ(s)))

static VALUE
rbatk_action_do_action(VALUE self, VALUE i)
{
    return CBOOL2RVAL(atk_action_do_action(_SELF(self), NUM2INT(i)));
}

static VALUE
rbatk_action_get_n_actions(VALUE self)
{
    return INT2NUM(atk_action_get_n_actions(_SELF(self)));
}

static VALUE
rbatk_action_get_description(VALUE self, VALUE i)
{
    return CSTR2RVAL(atk_action_get_description(_SELF(self), NUM2INT(i)));
}

static VALUE
rbatk_action_get_name(VALUE self, VALUE i)
{
    return CSTR2RVAL(atk_action_get_name(_SELF(self), NUM2INT(i)));
}

#ifdef HAVE_ATK_ACTION_GET_LOCALIZED_NAME
static VALUE
rbatk_action_get_localized_name(VALUE self, VALUE i)
{
    return CSTR2RVAL(atk_action_get_localized_name(_SELF(self), NUM2INT(i)));
}
#endif

static VALUE
rbatk_action_get_keybinding(VALUE self, VALUE i)
{
    return CSTR2RVAL(atk_action_get_keybinding(_SELF(self), NUM2INT(i)));
}

static VALUE
rbatk_action_set_description(VALUE self, VALUE i, VALUE desc)
{
    return CBOOL2RVAL(atk_action_set_description(_SELF(self), NUM2INT(i), RVAL2CSTR(desc)));
}

void
Init_atk_action()
{
    VALUE mAction = G_DEF_INTERFACE(ATK_TYPE_ACTION, "Action", mAtk);

    rb_define_method(mAction, "do_action", rbatk_action_do_action, 1);
    rb_define_method(mAction, "n_actions", rbatk_action_get_n_actions, 0);
    rb_define_method(mAction, "get_description", rbatk_action_get_description, 1);
    rb_define_method(mAction, "get_name", rbatk_action_get_name, 1);
#ifdef HAVE_ATK_ACTION_GET_LOCALIZED_NAME
    rb_define_method(mAction, "get_localized_name", rbatk_action_get_localized_name, 1);
#endif
    rb_define_method(mAction, "get_keybinding", rbatk_action_get_keybinding, 1);
    rb_define_method(mAction, "set_description", rbatk_action_set_description, 2);
}
