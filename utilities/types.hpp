#ifndef UTILITIES_TYPES_HPP
#define UTILITIES_TYPES_HPP

typedef unsigned char      u1;
typedef unsigned short	   u2;
typedef unsigned int       u4;
typedef unsigned __int64   u8;

typedef char               su1;
typedef short              su2;
typedef int                su4;
typedef __int64            su8;

typedef unsigned char      byte;

#define TRAPS
#define addr         void*
#define BitsPerByte     8
 

enum BasicType{
    T_CHAR  ,
    T_BYTE  ,
    T_SHORT ,
    T_FLOAT ,
    T_DOUBLE,
    T_INT   ,
    T_LONG  ,
    T_OBJECT,
    T_VOID  ,
    T_ILLEGAL
};

#endif

