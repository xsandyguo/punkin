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

enum BasicDataType {
    BASIC_TYPE_BOOL         =1,
    BASIC_TYPE_CHAR,
    BASIC_TYPE_BYTE,
    BASIC_TYPE_SHORT,
    BASIC_TYPE_INTEGER,
    BASIC_TYPE_FLOAT,
    BASIC_TYPE_LONG,
    BASIC_TYPE_DOUBLE,
    BASIC_TYPE_REF,
    BASIC_TYPE_VOID,
    BASIC_TYPE_ILLEGAL
};


#define PRIMITIVE_TYPE_KLASS_NAME_BOOL		"boolean"
#define PRIMITIVE_TYPE_KLASS_NAME_CHAR		"char"
#define PRIMITIVE_TYPE_KLASS_NAME_BYTE		"byte"
#define PRIMITIVE_TYPE_KLASS_NAME_SHORT		"short"
#define PRIMITIVE_TYPE_KLASS_NAME_INT		"int"
#define PRIMITIVE_TYPE_KLASS_NAME_LONG		"long"
#define PRIMITIVE_TYPE_KLASS_NAME_FLOAT		"float"
#define PRIMITIVE_TYPE_KLASS_NAME_DOUBLE	"double"

#define PRIMITIVE_TYPE_KLASS_NAME_COUNT     8

struct primitive_type_klass_size {
    const char* name;
    int size;
};

extern primitive_type_klass_size KLASS_TYPE_SIZE [];


#endif