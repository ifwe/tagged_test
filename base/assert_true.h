/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/assert_true.h>

   Defines a function for performing pass-through assertions.  Useful in
   ctor-initializer lines and other places where you want to check a
   value while accessing it. */

#pragma once

#include <cassert>

namespace Base {

  /* Returns the value given, after asserting that the value, when cast to
     bool, equals true.  This means non-null pointers and non-zero numbers
     will pass through, but null pointers and zeros will not. */
  template <typename TVal>
  const TVal &AssertTrue(const TVal &val) {
    assert(val);
    return val;
  }

}
