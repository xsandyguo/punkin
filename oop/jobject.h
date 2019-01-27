#ifndef OOP_JOBJECT_H
#define OOP_JOBJECT_H

#include "oop/oop.h"

class Klass;

class JObject {
  public:
    JObject(Klass* klass, addr data);

    inline Klass* GetKlass() {
        return this->klass_;
    }

    inline addr GetObjectData() {
        return this->data_;
    }

  protected:
    Klass* klass_;
    addr data_;
};

#endif

