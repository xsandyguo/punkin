#ifndef OOP_JARRAY_H
#define OOP_JARRAY_H

#include "oop/jobject.h"

class JArray :      public JObject {
  public:
    JArray(addr list, int length, Klass* componentType);

  public:
    inline int get_length() {
        return length_;
    }

    Klass* get_component_type() {
        return compoentType_;
    }

    inline JObject* get_jobject(int index) {
        check_index(index);

        JObject** ar = (JObject**) data_;
        return ar[index];
    }

    inline jbyte     get_jbyte(int index) {
        check_index(index);

        jbyte* ar = (jbyte*)data_;
        return ar[index];
    }

    inline jchar     get_jchar(int index) {
        check_index(index);

        jchar* ar = (jchar*)data_;
        return ar[index];
    }

    inline jshort    get_jshort(int index) {
        check_index(index);
        jshort* ar = (jshort*)data_;
        return ar[index];
    }

    inline jint      get_jint(int index) {
        check_index(index);
        jint* ar = (jint*)data_;
        return ar[index];
    }

    inline jlong     get_jlong(int index) {
        check_index(index);
        jlong* ar = (jlong*)data_;
        return ar[index];
    }

    inline jfloat    get_jfloat(int index) {
        check_index(index);
        jfloat* ar = (jfloat*)data_;
        return ar[index];
    }

    inline jdouble   get_jdouble(int index) {
        check_index(index);
        jdouble* ar = (jdouble*)data_;
        return ar[index];
    }

    inline void set_jobject(int index, JObject* val) {
        check_index(index);
        JObject** ar = (JObject**) data_;
        ar[index] = val;
    }

    inline void set_jchar(int index, jchar val) {
        check_index(index);
        jchar* ar = (jchar*)data_;
        ar[index] = val;
    }

    inline void set_jbyte(int index, jbyte val) {
        check_index(index);
        jbyte* ar = (jbyte*)data_;
        ar[index] = val;
    }

    inline void set_jshort(int index, jshort val) {
        check_index(index);
        jshort* ar = (jshort*)data_;
        ar[index] = val;
    }

    inline void set_jint(int index, jint val) {
        check_index(index);
        jint* ar = (jint*)data_;
        ar[index] = val;
    }

    inline void set_jlong(int index, jlong val) {
        check_index(index);
        jlong* ar = (jlong*)data_;
        ar[index] = val;
    }

    inline void set_jfloat(int index, jfloat val) {
        check_index(index);
        jfloat* ar = (jfloat*)data_;
        ar[index] = val;
    }

    inline void set_jdouble(int index, jdouble val) {
        check_index(index);
        jdouble* ar = (jdouble*)data_;
        ar[index] = val;
    }

  private:
    void check_index(int index);

  private:
    int length_;
    Klass* compoentType_;
};


class JThrowable :  public JObject {};
class JString :     public JObject {};
class BoolArray :   public JArray {};
class ByteArray :   public JArray {};
class CharArray :   public JArray {};
class ShortArray :  public JArray {};
class IntArray :    public JArray {};
class LongArray :   public JArray {};
class FloatArray :  public JArray {};
class DoubleArray : public JArray {};
class ObjectArray : public JArray {};

typedef Klass   *       jclass;
typedef JThrowable *    jthrowable;
typedef JString *       jstring;
typedef JArray *        jarray;
typedef BoolArray *     jbooleanArray;
typedef ByteArray *     jbyteArray;
typedef CharArray *     jcharArray;
typedef ShortArray *    jshortArray;
typedef IntArray *      jintArray;
typedef LongArray *     jlongArray;
typedef FloatArray *    jfloatArray;
typedef DoubleArray *   jdoubleArray;
typedef ObjectArray *   jobjectArray;

#endif