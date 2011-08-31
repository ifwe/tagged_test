/* This file is licensed under the terms of the Apache License, Version 2.0
 * Please see the file COPYING for the full text of this license
 *
 * Copyright 2010-2011 Tagged */

/* <base/scoped_ptr.h>

   A smart pointer that deletes its object. */

#pragma once

#include <algorithm>
#include <cassert>

#include <base/no_copy_semantics.h>

namespace Base {

  /* This is a pointer which owns the lifespan of the object at which it points.
     When the pointer goes out of scope, it will delete the object.  Use this to
     hold onto pointers returned by factories and new-operators in order to
     avoid having to construct try-catch blocks.

     Note that we intentionally do not define copy semantics for this class.
     Ownership of the object being pointed at would be confusing if we allowed
     the pointers to copy-construct and/or assign.  You can, however, pass an
     owned object from pointer to pointer, like this:

      TScopedPtr<> a, b;
      a = b.Release();

     This makes the exchange of ownership explicit.

     NOTE: Take some care with this class.  Having TScopedPtr<> around makes it
     easier to manage heap allocations, but it doesn't make them less costly.
     The general rule still holds: hon't do things on the heap that would be
     better done on the stack. */
  template <typename TObj>
  class TScopedPtr {
    NO_COPY_SEMANTICS(TScopedPtr);
    public:

    /* The default pointer is null. */
    TScopedPtr() : Obj(0) {}

    /* Own the given object. */
    TScopedPtr(TObj *obj) : Obj(obj) {}

    /* Delete the object we own, if any. */
    ~TScopedPtr() {
      assert(this);
      delete Obj;
    }

    /* Own the new object, deleting our current object, if any.  This function
       is exception-safe and no-throw. */
    TScopedPtr &operator=(TObj *obj) {
      assert(this);
      TScopedPtr temp(obj);
      return Swap(temp);
    }

    /* Return a reference to our object, if any.  Note, if the pointer is null,
       so is the resulting reference. */
    TObj &operator*() const {
      assert(this);
      return *Obj;
    }

    /* Return a pointer to our object, if any. */
    TObj *operator->() const {
      assert(this);
      return Obj;
    }

    /* Return a pointer to our object, if any. */
    TObj *Get() const {
      assert(this);
      return Obj;
    }

    /* Return a pointer to our object, if any, and release the object from our
       control.  The pointer will be null after this. */
    TObj *Release() {
      assert(this);
      TObj *temp = Obj;
      Obj = 0;
      return temp;
    }

    /* Reset the pointer to its default (null) state, deleting our object,
       if any. */
    TScopedPtr &Reset() {
      assert(this);
      TScopedPtr temp;
      return Swap(temp);
    }

    /* Swap objects with the other pointer. */
    TScopedPtr &Swap(const TScopedPtr &that) {
      assert(this);
      std::swap(Obj, that.Obj);
      return *this;
    }

    private:

    /* The object we own, if any. */
    TObj *Obj;
  };

}

namespace std {

  /* A std swapper for Base::TScopedPtr<>. */
  template <typename TObj>
  void swap(Base::TScopedPtr<TObj> &lhs, Base::TScopedPtr<TObj> &rhs) {
    assert(&lhs);
    lhs.Swap(rhs);
  }

}

