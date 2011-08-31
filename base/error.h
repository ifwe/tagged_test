/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/error.h>

   Defines the base class for all exceptions thrown in the code. */

#pragma once

#include <cassert>
#include <exception>
#include <string>
#include <typeinfo>

#include <base/code_location.h>

namespace Base {

  /* The base class for all exceptions thrown in this code base.  It inherits from std::exception, so can catch as you normally would.  The code location which
     gave rise to the error is recorded and included in the std::what() message, along with the name of the final error class and any descriptive text that the
     final error class thinks might be useful.

     All error objects are (implicitly) value types.  They also support polymorphic duplication through the Dupe() function.  This can be useful in situations
     where you want to capture an error and deal with it later, perhaps on a different thread.  For example:

       TError *error = 0;
       try {
         ... do risky stuff..
       } catch (const TSomeError &some_error) {
         error = some_error.Dupe();
       }
       ... do other stuff ...
       if (error) {
         ... handle the error...
       }

     This class employs a post-construction pattern, so you must not create descendants that are both inheritable and instantiable.  You must call PostCtor() in
     the constructor of your final class and nowhere else.

     The constructor of this class takes no parameters, so you can feel free to inherit virtually and create mix-ins to provide error categorization.  Inherit
     from the TFinalError<> template (below, q.v.) to provide standard implementations of the TError pure virtual functions. */
  class TError : public std::exception {
    public:

    /* Do-nothing destructor, here to satisfy the throw() constraint declared by our base class. */
    virtual ~TError() throw() {};

    /* Returns a human-readable description of what went wrong.  This message has the following pattern: (<file>,<line>),<error class>[,<details>] */
    const char *what() const throw() {
      assert(this);
      return WhatPtr;
    }

    /* Returns a duplicate of the error object.  This function must not return a null and must not throw.  If the duplicate cannot be constructed, the
       function should abort the program. */
    virtual TError *Dupe() const = 0;

    /* Returns the location at which the exception was thrown. */
    const TCodeLocation &GetCodeLocation() const {
      assert(this);
      return CodeLocation;
    }

    /* Returns the name of the final error class.  Never null. */
    virtual const char *GetClassName() const = 0;

    /* Aborts the program, sending an error message to stderr. */
    static void Abort(const TCodeLocation &code_location) __attribute__((noreturn));

    protected:

    /* Defaults to safe but useless values.  PostCtor() does the real work. */
    TError();

    /* Caches the location as which the exception was thrown and composes the 'what' message.  Call this function in the constructor of your final class.
       No-throw. */
    void PostCtor(const TCodeLocation &code_location, const char *details = 0);
    void PostCtor(const TCodeLocation &code_location, const char *details_start, const char *details_end);

    private:

    /* The location at which the exception was thrown. */
    TCodeLocation CodeLocation;

    /* This stores the string returned by what().  It'll be empty until after PostCtor() is called. */
    std::string WhatBuffer;

    /* This is the actual pointer returned by what().  After you call PostCtor(), it will point into the 'WhatBuffer' above.  Before you call PostCtor(), this
       pointer points to a static string reminding you to call PostCtor(). */
    const char *WhatPtr;
  };

  /* TODO */
  template <typename TFinal>
  class TFinalError : public virtual TError {
    public:

    /* TODO */
    TError *Dupe() const {
      const TFinal *final = dynamic_cast<const TFinal *>(this);
      assert(final);
      return new TFinal(*final);
    }

    /* TODO */
    virtual const char *GetClassName() const {
      return typeid(TFinal).name();
    }

    protected:

    /* TODO */
    TFinalError() {}
  };

}

