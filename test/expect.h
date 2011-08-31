/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <test/expect.h>

   An expectation in a unit test fixture. */

#pragma once

#include <cassert>
#include <sstream>
#include <string>
#include <typeinfo>

#include <base/code_location.h>
#include <base/no_copy_semantics.h>
#include <base/no_default_case.h>
#include <test/runner.h>

/* Exepects lhs == rhs. */
#define EXPECT_EQ(lhs, rhs) \
    ::Test::TExpect(HERE, #lhs, lhs, ::Test::TExpect::Eq, #rhs, rhs)

/* Exepects lhs != rhs. */
#define EXPECT_NE(lhs, rhs) \
    ::Test::TExpect(HERE, #lhs, lhs, ::Test::TExpect::Ne, #rhs, rhs)

/* Exepects lhs < rhs. */
#define EXPECT_LT(lhs, rhs) \
    ::Test::TExpect(HERE, #lhs, lhs, ::Test::TExpect::Lt, #rhs, rhs)

/* Exepects lhs <= rhs. */
#define EXPECT_LE(lhs, rhs) \
    ::Test::TExpect(HERE, #lhs, lhs, ::Test::TExpect::Le, #rhs, rhs)

/* Exepects lhs > rhs. */
#define EXPECT_GT(lhs, rhs) \
    ::Test::TExpect(HERE, #lhs, lhs, ::Test::TExpect::Gt, #rhs, rhs)

/* Exepects lhs >= rhs. */
#define EXPECT_GE(lhs, rhs) \
    ::Test::TExpect(HERE, #lhs, lhs, ::Test::TExpect::Ge, #rhs, rhs)

/* Exepects arg == true. */
#define EXPECT_TRUE(arg) \
    ::Test::TExpect(HERE, ::Test::TExpect::IsTrue, #arg, arg)

/* Exepects arg == false. */
#define EXPECT_FALSE(arg) \
    ::Test::TExpect(HERE, ::Test::TExpect::IsFalse, #arg, arg)

/* Exepects lhs == rhs. */
#define EXPECT_EQ_AT(here, lhs, rhs) \
    ::Test::TExpect(here, #lhs, lhs, ::Test::TExpect::Eq, #rhs, rhs)

/* Exepects lhs != rhs. */
#define EXPECT_NE_AT(here, lhs, rhs) \
    ::Test::TExpect(here, #lhs, lhs, ::Test::TExpect::Ne, #rhs, rhs)

/* Exepects lhs < rhs. */
#define EXPECT_LT_AT(here, lhs, rhs) \
    ::Test::TExpect(here, #lhs, lhs, ::Test::TExpect::Lt, #rhs, rhs)

/* Exepects lhs <= rhs. */
#define EXPECT_LE_AT(here, lhs, rhs) \
    ::Test::TExpect(here, #lhs, lhs, ::Test::TExpect::Le, #rhs, rhs)

/* Exepects lhs > rhs. */
#define EXPECT_GT_AT(here, lhs, rhs) \
    ::Test::TExpect(here, #lhs, lhs, ::Test::TExpect::Gt, #rhs, rhs)

/* Exepects lhs >= rhs. */
#define EXPECT_GE_AT(here, lhs, rhs) \
    ::Test::TExpect(here, #lhs, lhs, ::Test::TExpect::Ge, #rhs, rhs)

/* Exepects arg == true. */
#define EXPECT_TRUE_AT(here, arg) \
    ::Test::TExpect(here, ::Test::TExpect::IsTrue, #arg, arg)

/* Exepects arg == false. */
#define EXPECT_FALSE_AT(here, arg) \
    ::Test::TExpect(here, ::Test::TExpect::IsFalse, #arg, arg)

namespace Test {

  /* TODO */
  class TExpect : public TRunner::TExpect {
    NO_COPY_SEMANTICS(TExpect);
    public:

    /* TODO */
    enum TInfixOp { Eq, Ne, Lt, Le, Gt, Ge };

    /* TODO */
    enum TPrefixOp { IsTrue, IsFalse };

    /* TODO */
    template <typename TLhs, typename TRhs>
    TExpect(
        const Base::TCodeLocation &code_location,
        const char *lhs_str, const TLhs &lhs, TInfixOp op,
        const char *rhs_str, const TRhs &rhs)
        : CodeLocation(code_location) {
      assert(lhs_str);
      assert(rhs_str);
      const char *op_str;
      std::ostringstream strm;
      switch (op) {
        case Eq: {
          op_str = "==";
          Pass = (lhs == rhs);
          break;
        }
        case Ne: {
          op_str = "!=";
          Pass = (lhs != rhs);
          break;
        }
        case Lt: {
          op_str = "<";
          Pass = (lhs < rhs);
          break;
        }
        case Le: {
          op_str = "<=";
          Pass = (lhs <= rhs);
          break;
        }
        case Gt: {
          op_str = ">";
          Pass = (lhs > rhs);
          break;
        }
        case Ge: {
          op_str = ">=";
          Pass = (lhs >= rhs);
          break;
        }
        NO_DEFAULT_CASE;
      }
      WriteType<TLhs>(strm);
      strm << lhs_str << ' ' << op_str << ' ';
      WriteType<TRhs>(strm);
      strm << rhs_str;
      Source = strm.str();
      strm.str("");
      strm << lhs << ' ' << op_str << ' ' << rhs;
      Expression = strm.str();
    }

    /* TODO */
    template <typename TArg>
    TExpect(
        const Base::TCodeLocation &code_location,
        TPrefixOp op, const char *arg_str, const TArg &arg)
        : CodeLocation(code_location) {
      assert(arg_str);
      const char *op_str;
      std::ostringstream strm;
      switch (op) {
        case IsTrue: {
          op_str = "";
          Pass = (!!arg);
          break;
        }
        case IsFalse: {
          op_str = "!";
          Pass = (!arg);
          break;
        }
        NO_DEFAULT_CASE;
      }
      WriteType<TArg>(strm);
      strm << op_str << arg_str;
      Source = strm.str();
      strm.str("");
      strm << op_str << arg;
      Expression = strm.str();
    }

    /* TODO */
    virtual ~TExpect();

    /* TODO */
    operator bool() const {
      assert(this);
      return Pass;
    }

    /* TODO */
    template <typename TVal>
    const TExpect &Write(const TVal &val) const {
      assert(this);
      Explanation << val;
      return *this;
    }

    private:

    /* TODO */
    template <typename TArg>
    static void WriteType(std::ostream &strm) {
      strm << '(' << typeid(TArg).name() << ')';
    }

    /* TODO */
    Base::TCodeLocation CodeLocation;

    /* TODO */
    bool Pass;

    /* TODO */
    std::string Source, Expression;

    /* TODO */
    mutable std::ostringstream Explanation;
  };

}

/* A stream inserter for Test::TExpect targets. */
template <typename TVal>
const Test::TExpect &operator<<(const Test::TExpect &expect, const TVal &val) {
  assert(&expect);
  return expect.Write(val);
}

