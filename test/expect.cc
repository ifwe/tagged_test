/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <test/expect.cc>

   Implements <test/expect.h>. */

#include <test/app.h>
#include <test/expect.h>

using namespace Base;
using namespace Test;

TExpect::~TExpect() {
  assert(this);
  PreDtor();
  TApp::TLogger(!Pass)
    << CodeLocation << Source << "; " << Expression << "; " << (Pass ? "pass" : "fail");
}

