/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/no_construction.h>

   Defines a macro to disable construction of an aggregate type. */

#pragma once

/* Use this macro to disable construction of a class, struct, or union,
   essentially turning the type into a namespace with accessibility
   controls.  This is particularly useful for creating namespace-like
   separation of declarations within classes.  For example:

      class TFoo {
        public:

        struct Alpha {
          NO_CONSTRUCTION(Alpha);
          static CallMe();
        };

        struct Beta {
          NO_CONSTRUCTION(Beta);
          static CallMe();
        };

      };

   A caller can now call TFoo::Alpha:CallMe() or TFoo::Beta::CallMe() without
   ambiguity.  Note that it is convention *not* to use the T-prefix with types
   without construction.  This makes them read more like namespaces, which they
   essentially are.

   All the members of a type without construction must obviously be static.  A
   per-instance member makes no sense in a type that will never be instantiated.

   If you attempt to default-construct, destruct, copy-construct or assign an
   instance of a type declared with this macro, you'll get a compile-time error
   telling you function is private.  If the attempt is made from within a scope
   friendly to the type, you'll get a link-time error telling you the function
   is undefined. */
#define NO_CONSTRUCTION(cls) \
  private: \
  cls(); \
  ~cls(); \
  cls(const cls &); \
  cls &operator=(const cls &);

