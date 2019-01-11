#ifndef UTILITIES_TYPES_HPP
#define UTILITIES_TYPES_HPP

typedef  char			   u1;
typedef unsigned short	   u2;
typedef unsigned int       u4;
typedef unsigned long long u8;

#define TRAPS
#define address         void*
#define BitsPerByte     8

typedef char            s_char;
typedef unsigned char   u_char;


typedef unsigned char   byte; 
typedef unsigned char   boolean;

typedef char            jchar;
typedef int             jint;
typedef long            jlong;
typedef float           jfloat;
typedef double          jdouble;
typedef short           jshort;

enum BasicType{
    T_FLOAT ,
    T_DOUBLE,
    T_INT   ,
    T_LONG  ,
    T_BYTE  ,
    T_CHAR  ,
    T_SHORT ,
    T_VOID  ,
    T_OBJECT,
    T_ILLEGAL
};

#endif

