/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/code_location.h>

   Defines a class to represent a location (file and line) within the
   body of source code.  This is useful for reporting errors and for
   logging. */

#pragma once

#include <cassert>
#include <ostream>

/* Use this macro to represent the current location in the code.
   For example, if a function takes a code location, like this:

     void SomeFunc(const TCodeLocation &code_location, ...);

   You can call it like this:

     SomeFunc(HERE, ...); */
#define HERE ::Base::TCodeLocation(__FILE__, __LINE__)

namespace Base {

  /* Represents a location (file and line) within the body of source
     code.  This is a value type. */
  class TCodeLocation {
    public:

    /* The default is a blank file at line 1. */
    TCodeLocation() : File(""), LineNumber(1) {}

    /* Represents the given file and line.  'file' must not be null and
       'line_number' must be > 0. */
    TCodeLocation(const char *file, unsigned line_number);

    /* Returns the file.  Never returns null. */
    const char *GetFile() const {
      assert(this);
      return File;
    }

    /* Returns the line number.  Always returns > 0. */
    unsigned GetLineNumber() const {
      assert(this);
      return LineNumber;
    }

    /* Stream out a human-readable version of our state. */
    void Write(std::ostream &strm) const {
      assert(this);
      assert(&strm);
      strm << '[' << File << ", " << LineNumber << ']';
    }

    private:

    /* Never null. */
    const char *File;

    /* Always > 0. */
    unsigned LineNumber;
  };

}  // namespace Base

/* Standard stream inserter for Base::TCodeLocation. */
inline std::ostream &operator<<(std::ostream &strm, const Base::TCodeLocation &that) {
  assert(&that);
  that.Write(strm);
  return strm;
}
