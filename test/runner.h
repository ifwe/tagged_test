/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <test/runner.h>

   Runs a fixture in unit test program. */

#pragma once

#include <base/assert_true.h>
#include <base/no_copy_semantics.h>
#include <test/app.h>

namespace Test {

  /* TODO */
  class TFixture;

  /* TODO */
  class TRunner : public TApp::TRunner {
    NO_COPY_SEMANTICS(TRunner);
    public:

    /* TODO */
    class TExpect {
      NO_COPY_SEMANTICS(TExpect);
      public:

      /* TODO */
      virtual ~TExpect();

      /* TODO */
      virtual operator bool() const = 0;

      protected:

      /* TODO */
      TExpect() {}

      /* TODO */
      void PreDtor();
    };

    /* TODO */
    TRunner(const TFixture *fixture);

    /* TODO */
    virtual ~TRunner();

    /* TODO */
    virtual operator bool() const;

    /* TODO */
    void Run();

    /* TODO */
    static TRunner *GetRunner() {
      return Base::AssertTrue(Runner);
    }

    private:

    /* TODO */
    void OnExpectDtor(const TExpect *expect);

    /* TODO */
    const TFixture *Fixture;

    /* TODO */
    bool Pass;

    /* TODO */
    static TRunner *Runner;
  };

}

