/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/os_error.h>

   Implements an exception for reporting operating system errors. */

#pragma once

#include <cerrno>
#include <cstring>

#include <base/error.h>

namespace Base {

  /* Throw an instance of this class to report an operating system error. */
  class TOsError : public TFinalError<TOsError> {
    public:

    /* If no number if explicitly given, the constructor will pick it up from the global 'errno' defined in <cerrno>. */
    TOsError(const TCodeLocation &code_location, int error_code = errno) {
      PostCtor(code_location, strerror(error_code));
    }

    /* Use this helper function when calling an OS function which returns < 0 on failure, leaving an error code in errno, like this:

          TOsError::IfLt0(HERE, pipe(fds));

       The helper function will throw iff. the predicate fails. */
    static void IfLt0(const TCodeLocation &code_location, int ret) {
      if (ret < 0) {
        throw TOsError(code_location);
      }
    }

    /* Use this helper function when calling an OS function which returns an error code directly, like this:

          TOsError::IfNe0(HERE, pthread_setspecific(key, val));

       The helper function will throw iff. the function returns non-zero. */
    static void IfNe0(const TCodeLocation &code_location, int ret) {
      if (ret) {
        throw TOsError(code_location, ret);
      }
    }
  };

}

