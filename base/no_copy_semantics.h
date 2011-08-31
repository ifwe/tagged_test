/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/no_copy_semantics.h>

   Defines a macro to disable compiler-provided copy semantics. */

#pragma once

/* Use this macro to disable compiler-provided copy semantics in any
   class you intend to operate as a reference type.  Convention is to
   have this macro appear as the first thing in the class, before the
   first accessability declaration, like this:

      class TFoo {
        NO_COPY_SEMANTICS(TFoo);
        public:
        ...
      }

   If you attempt to copy-construct or assign an instance of a class
   declared with this macro, you'll get a compile-time error telling you
   that the copy constructor or assignment operator is private.  If the
   attempt is made from within a scope friendly to the class, you'll get
   a link-time error telling you the copy constructor or assignment
   operator is undefined. */
#define NO_COPY_SEMANTICS(cls) \
  private: \
  cls(const cls &); \
  cls &operator=(const cls &);
