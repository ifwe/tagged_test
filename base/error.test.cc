/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/error.test.cc>

   Unit test for <base/error.h>. */

#include <base/error.h>

#include <test/kit.h>

using namespace Base;

class TMyError : public TFinalError<TMyError> {
  public:

  TMyError(const TCodeLocation &code_location, const char *details = 0) {
    PostCtor(code_location, details);
  }
  TMyError(const TCodeLocation &code_location, const char *details_start, const char *details_end) {
    PostCtor(code_location, details_start, details_end);
  }
};

FIXTURE(Typical) {
  TMyError my_error(HERE);
}
