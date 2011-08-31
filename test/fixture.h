/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <test/fixture.h>

   A fixture in a unit test program. */

#pragma once

#include <cassert>

#include <base/code_location.h>
#include <base/no_copy_semantics.h>

#define FIXTURE(name) \
  static void name##_(); \
  static const ::Test::TFixture name##Fixture(HERE, #name, name##_); \
  static void name##_()

namespace Test {

  /* TODO */
  class TFixture {
    NO_COPY_SEMANTICS(TFixture);
    public:

    /* TODO */
    typedef void (*TFunc)();

    /* TODO */
    TFixture(
        const Base::TCodeLocation &code_location, const char *name, TFunc func);

    /* TODO */
    TFunc GetFunc() const {
      assert(this);
      return Func;
    }

    /* TODO */
    const char *GetName() const {
      assert(this);
      return Name;
    }

    /* TODO */
    const TFixture *GetNextFixture() const {
      assert(this);
      return NextFixture;
    }

    /* TODO */
    static const TFixture *GetFirstFixture() {
      return FirstFixture;
    }

    private:

    /* TODO */
    Base::TCodeLocation CodeLocation;

    /* TODO */
    const char *Name;

    /* TODO */
    TFunc Func;

    /* TODO */
    mutable const TFixture *NextFixture;

    /* TODO */
    static const TFixture *FirstFixture, *LastFixture;
  };

}

