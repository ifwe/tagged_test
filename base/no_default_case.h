/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/no_default_case.h>

   Implements a macro for handling switches without defaults. */

#pragma once

#include <base/error.h>

/* Use this macro to close out any switch which doesn't have a default case, like this:

      const char *GetText(int val) {
        const char *text;
        switch (val) {
          case 1: { text = "1"; break; }
          case 2: { text = "2"; break; }
          case 3: { text = "3"; break; }
          NO_DEFAULT_CASE;
        }
        return text;
      }

   If control reaches the macro, it will abort the program.  It is therefore safe to use the switch to conditionally initialize an otherwise unitialized
   variable, as shown. */
#define NO_DEFAULT_CASE default: ::Base::TError::Abort(HERE)
