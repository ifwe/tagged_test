/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <test/fixture.cc>

   Implements <test/fixture.h>. */

#include <test/fixture.h>

#include <base/assert_true.h>

using namespace Base;
using namespace Test;

TFixture::TFixture(
    const TCodeLocation &code_location, const char *name, TFunc func)
  : CodeLocation(code_location), Name(AssertTrue(name)),
    Func(AssertTrue(func)), NextFixture(0) {
  (LastFixture ? LastFixture->NextFixture : FirstFixture) = this;
  LastFixture = this;
}

const TFixture
  *TFixture::FirstFixture = 0,
  *TFixture::LastFixture = 0;

