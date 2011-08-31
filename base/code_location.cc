/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/code_location.cc>

   Implements <base/code_location.h>. */

#include <base/code_location.h>

#include <base/assert_true.h>

#include <cstring>

using namespace Base;

TCodeLocation::TCodeLocation(const char *file, unsigned line_number)
    : File(AssertTrue(file) + (strstr(file, SRC_ROOT) == file?  strlen(SRC_ROOT):0)), LineNumber(AssertTrue(line_number)) {
}
