/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <test/app.h>

   The application framework for unit test executables. */

#pragma once

#include <cassert>
#include <cstddef>
#include <iostream>

#include <base/assert_true.h>
#include <base/no_construction.h>
#include <base/no_copy_semantics.h>

namespace Test {

  /* TODO */
  class TFixture;

  /* TODO */
  class TApp {
    NO_COPY_SEMANTICS(TApp);
    public:

    /* TODO */
    class TLogger {
      NO_COPY_SEMANTICS(TLogger);
      public:

      /* TODO */
      TLogger(bool is_critical = false) {
        Enabled = is_critical || GetApp()->Verbose;
      }

      /* TODO */
      ~TLogger() {
        assert(this);
        if (Enabled) {
          std::cout << std::endl;
        }
      }

      /* TODO */
      template <typename TVal>
      const TLogger &Write(const TVal &val) const {
        assert(this);
        if (Enabled) {
          std::cout << val;
        }
        return *this;
      }

      private:

      /* TODO */
      bool Enabled;
    };

    /* TODO */
    class TRunner {
      NO_COPY_SEMANTICS(TRunner);
      public:

      /* TODO */
      virtual ~TRunner();

      /* TODO */
      virtual operator bool() const = 0;

      /* TODO */
      static void Run(const TFixture *fixture);

      protected:

      /* TODO */
      TRunner() {}

      /* TODO */
      void PreDtor();
    };

    /* Returns our one-and-only instance. */
    static TApp *GetApp() {
      return Base::AssertTrue(App);
    }

    /* Enforces singleton semantics. */
    TApp();

    /* Enforces singleton semantics. */
    ~TApp();

    /* Run the program. */
    int Run(bool verbose=false, bool print_timing=false);

    private:

    /* Responds to the destruction of a TRunner.  This gives us a chance to
       examine the TRunner and count it as a pass or failure. */
    void OnRunnerDtor(const TRunner *runner);

    /* A command-line flag, q.v. */
    bool Verbose;

    /* A command line flag to print timing info for each fixture. */
    bool PrintTimingInfo;

    /* The number of fixtures which passed and failed. */
    size_t PassCount, FailCount;

    /* Our single instance. */
    static TApp *App;
  };

}

/* A stream inserter for Test::TApp::TLogger targets. */
template <typename TVal>
const Test::TApp::TLogger &operator<<(
    const Test::TApp::TLogger &logger, const TVal &val) {
  assert(&logger);
  return logger.Write(val);
}

