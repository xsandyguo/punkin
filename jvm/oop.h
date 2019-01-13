#ifndef INTERPRETER_OOP_H
#define INTERPRETER_OOP_H
 
#include "utilities/top.hpp"

class JObject;

typedef unsigned char   jbool;
typedef signed char     jbyte;
typedef unsigned short  jchar;
typedef short           jshort;
typedef long            jint;
typedef __int64         jlong;
typedef float           jfloat;
typedef double          jdouble;
typedef JObject*        jobject;
typedef jint            jsize; 

union jvalue {
    jbool    z;
    jbyte    b;
    jchar    c;
    jshort   s;
    jint     i;
    jlong    j;
    jfloat   f;
    jdouble  d;
    jobject  l;
};

enum BasicDataType{
    BASIC_TYPE_BOOL         =1,
    BASIC_TYPE_CHAR         ,
    BASIC_TYPE_BYTE         ,
    BASIC_TYPE_SHORT        ,
    BASIC_TYPE_INTEGER      ,
    BASIC_TYPE_FLOAT        ,
    BASIC_TYPE_LONG         ,
    BASIC_TYPE_DOUBLE       ,
    BASIC_TYPE_REF          ,
    BASIC_TYPE_VOID         , 
    BASIC_TYPE_ILLEGAL 
};

class Klass;

struct VirtualTable{

};

struct ObjectData{
    addr* data;
}

class JObject{
public:
    JObject(Klass* klass);
    bool IsPrimativeType(); 

    JObject* GetRefFieldVal(u2 symIdx);
    void SetRefFieldVal(u2 symIndx, JObject* val);

    char GetCharFieldVal(u2 symIdx);
    void SetCharFieldVal(u2 symIdx, char val);

    byte GetByteFieldVal(u2 symIdx);
    void SetByteFieldVal(u2 symIdx, byte val);

    int GetIntFieldVal(u2 symIdx);
    void SetIntFieldVal(u2 symIdx, int);

    long GetLongFieldVal(u2 symIdx); 
    void SetLongFieldVal(u2 symIdx, long val);

    float GetFloatFieldVal(u2 symIdx);
    void SetFloatFieldVal(u2 symIdx, float val);

    double GetDoubleFieldVal(u2 symIdx); 
    void SetDoubleFieldVal(u2 symIdx, double val);

private:

    Klass* klass_;
};
 

 
class JArray :      public JObject {
public:
    JArray(addr list, int length, BasicDataType type, Klass* componentType);

public:
    int GetLength();
    BasicDataType GetComponentType();

    inline JObject* GetRefItem(int index) {
        CheckIndex(index);

        JObject** ar = (JObject**) dataList_;
        return ar[index];
    }

    inline jbyte     GetByteItem(int index){
        CheckIndex(index);

        jbyte* ar = (jbyte*)dataList_;
        return ar[index];
    }

    inline jchar     GetCharItem(int index){
        CheckIndex(index);

        jchar* ar = (jchar*)dataList_;
        return ar[index];
    }

    inline jshort    GetShortItem(int index){
        CheckIndex(index);
        jshort* ar = (jshort*)dataList_;
        return ar[index];
    }

    inline jint      GetIntItem(int index){
        CheckIndex(index);
        jint* ar = (jint*)dataList_;
        return ar[index];
    }

    inline jlong     GetLongItem(int index){
        CheckIndex(index);
        jlong* ar = (jlong*)dataList_;
        return ar[index];
    }

    inline jfloat    GetFloatItem(int index){
        CheckIndex(index);
        jfloat* ar = (jfloat*)dataList_;
        return ar[index];
    }

    inline jdouble   GetDoubleItem(int index){
        CheckIndex(index);
        jdouble* ar = (jdouble*)dataList_;
        return ar[index];
    }

    inline void SetRefItem(int index, JObject* val){
        CheckIndex(index);
        JObject** ar = (JObject**) dataList_;
        ar[index] = val;
    }

    inline void SetCharItem(int index, jchar val){ 
        CheckIndex(index);
        jchar* ar = (jchar*)dataList_;
        ar[index] = val;
    }

    inline void SetByteItem(int index, jbyte val){ 
        CheckIndex(index);
        jbyte* ar = (jbyte*)dataList_;
        ar[index] = val;
    }

    inline void SetShortItem(int index, jshort val){ 
        CheckIndex(index);
        jshort* ar = (jshort*)dataList_;
        ar[index] = val;
    }

    inline void SetIntItem(int index, jint val){
        CheckIndex(index);
        jint* ar = (jint*)dataList_;
        ar[index] = val;
    }

    inline void SetLongItem(int index, jlong val){ 
        CheckIndex(index);
        jlong* ar = (jlong*)dataList_;
        ar[index] = val;
    }

    inline void SetFloatItem(int index, jfloat val){
        CheckIndex(index);
        jfloat* ar = (jfloat*)dataList_;
        [index] = val;
    }

    inline void SetDoubleItem(int index, jdouble val){
        CheckIndex(index);
        jdouble* ar = (jdouble*)dataList_;
        ar[index] = val;
    }

private:
    void CheckIndex(int index);

private:
    addr dataList_;
    int length_;
    BasicDataType compoentType_;
};



class JThrowable :  public JObject{};
class JString :     public JObject{};
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