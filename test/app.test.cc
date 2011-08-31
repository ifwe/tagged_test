/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <test/app.test.cc>

   Unit test for <test/app.h>. */

#include <test/kit.h>

FIXTURE(Misc) {
  int x = 101, y = 101;
  EXPECT_EQ(x, y);
}

