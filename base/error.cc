/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/error.cc>

   Implements <base/error.h>. */

#include <base/error.h>

#include <cstdlib>
#include <iostream>
#include <sstream>

#include <base/code_location.h>

using namespace std;
using namespace Base;

void TError::Abort(const TCodeLocation &code_location) {
  cerr << "aborting at " << code_location << endl;
  abort();
}

TError::TError() :  WhatBuffer(0), WhatPtr("PostCtor() was not called") {}

void TError::PostCtor(const TCodeLocation &code_location, const char *details) {
  assert(this);
  assert(&code_location);
  try {
    CodeLocation = code_location;
    stringstream out_strm;
    out_strm << CodeLocation << ", " << GetClassName();
    if (details) {
      out_strm << ", " << details;
    }

    WhatBuffer = out_strm.str();
    WhatPtr = WhatBuffer.c_str();
  } catch (...) {
    Abort(HERE);
  }
}


void TError::PostCtor(const TCodeLocation &code_location, const char *details_start, const char* details_end) {
  assert(this);
  assert(&code_location);
  try {
    CodeLocation = code_location;
    stringstream out_strm;
    out_strm << CodeLocation << ", " << GetClassName();
    if (details_start) {
      out_strm << ", ";
      out_strm.write(details_start, details_end - details_start);
    }
    WhatBuffer = out_strm.str();
    WhatPtr = WhatBuffer.c_str();
  } catch (...) {
    Abort(HERE);
  }
}

