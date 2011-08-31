/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <test/app.cc>

   Implements <test/app.h>. */

#include <test/app.h>

#include <cstdlib>
#include <iostream>
#include <time.h>

#include <base/os_error.h>
#include <test/fixture.h>

using namespace std;
using namespace Base;
using namespace Test;

TApp::TRunner::~TRunner() {}

void TApp::TRunner::PreDtor() {
  assert(this);
  GetApp()->OnRunnerDtor(this);
}

TApp::TApp() : Verbose(false), PrintTimingInfo(false), PassCount(0), FailCount(0) {
  assert(!App);
  App = this;
}

TApp::~TApp() {
  assert(this);
  assert(App == this);
  App = 0;
}

void TApp::OnRunnerDtor(const TRunner *runner) {
  assert(this);
  assert(runner);
  ++(*runner ? PassCount : FailCount);
}

int TApp::Run(bool verbose, bool print_timing) {
  assert(this);
  Verbose = verbose;
  PrintTimingInfo = print_timing;

  timespec ts_start;
  timespec ts_stop;

  for (const TFixture *fixture = TFixture::GetFirstFixture();
       fixture; fixture = fixture->GetNextFixture()) {
    //If timing, then start timer here
    if (PrintTimingInfo) {
      TOsError::IfNe0(HERE, clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_start));
    }

    TRunner::Run(fixture);
    if (PrintTimingInfo) {
      TOsError::IfNe0(HERE, clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_stop));
      //Print ts_stop - ts_start
      TLogger(true) <<fixture->GetName()<<":"<<(ts_stop.tv_sec - ts_start.tv_sec)<<"s "<<(ts_stop.tv_nsec - ts_start.tv_nsec)<<"ns";
    }
  }
  bool success = !FailCount;
  TLogger(!success) << "passed " << PassCount << ", failed " << FailCount;

  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

TApp *TApp::App = 0;

//TODO: embed main function here, with trivial arg parsing.
int main(int argc, char *argv[]) {
  bool verbose = false;
  bool print_timing = false;
  for(int i=1; i<argc; ++i) {
    char *arg = argv[i];
    if(strcmp(arg, "-v") == 0)
      verbose = true;
    if(strcmp(arg, "--print-timings") == 0)
      print_timing = true;
  }
  try {
    TApp().Run(verbose, print_timing);
  } catch (const TError &error) {
    cout<<"Unexpected Exception: "<<error.what();
  }
}
