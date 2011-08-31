/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <test/runner.cc>

   Implements <test/runner.h>. */

#include <test/runner.h>

#include <cassert>
#include <exception>

#include <test/fixture.h>

using namespace std;
using namespace Base;
using namespace Test;

TRunner::TExpect::~TExpect() {}

void TRunner::TExpect::PreDtor() {
  assert(this);
  GetRunner()->OnExpectDtor(this);
}

TRunner::TRunner(const TFixture *fixture)
    : Fixture(AssertTrue(fixture)), Pass(true) {
  assert(!Runner);
  TApp::TLogger() << "begin " << fixture->GetName();
  Runner = this;
}

TRunner::~TRunner() {
  assert(this);
  assert(Runner == this);
  PreDtor();
  TApp::TLogger(!Pass)
      << "end " << Fixture->GetName()
      << "; " << (Pass ? "pass" : "fail");
  Runner = 0;
}

TRunner::operator bool() const {
  assert(this);
  return Pass;
}

void TRunner::Run() {
  assert(this);
  Pass = true;
  try {
    (*Fixture->GetFunc())();
  } catch (const exception &ex) {
    TApp::TLogger(true) << "exception: " << ex.what();
    Pass = false;
  } catch (...) {
    TApp::TLogger(true) << "unknown exception";
    Pass = false;
    throw;
  }
}

void TRunner::OnExpectDtor(const TExpect *expect) {
  assert(this);
  assert(expect);
  Pass = Pass && *expect;
}

TRunner *TRunner::Runner = 0;

void TApp::TRunner::Run(const TFixture *fixture) {
  Test::TRunner(fixture).Run();
}

