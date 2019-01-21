#ifndef CLASSFILE_FIELD_H
#define CLASSFILE_FIELD_H

#include <string>
#include "oop/oop.h"

class Klass;

class Field {
  public:
    Field();
    ~Field();

  public:
    const std::string& GetName();
    void        SetName(const std::string& name);

    Klass*      GetType();
    void        SetType(Klass* type);

    int         GetModifier();
    void        SetModifier(int modifier);

    int		    GetDataOffset();
    void	    SetDataOffset(int offset);

    int			GetIndex();
    void		SetIndex(int index);

  public:
    jobject     Get(jobject obj);
    jbool       GetBoolean(jobject obj);
    jbyte       GetByte(jobject obj);
    jchar       GetChar(jobject obj);
    jshort      GetShort(jobject obj);
    jint        GetInt(jobject obj);
    jlong       GetLong(jobject obj);
    jfloat      GetFloat(jobject obj);
    jdouble     GetDouble(jobject obj);

    void Set(jobject obj, jobject val);
    void SetBoolean(jobject obj, jbool val);
    void SetByte(jobject obj, jbyte val);
    void SetChar(jobject obj, jchar val);
    void SetShort(jobject obj, jshort val);
    void SetInt(jobject obj, jint val);
    void SetLong(jobject obj, jlong val);
    void SetFloat(jobject obj, jfloat val);
    void SetDouble(jobject obj, jdouble val);
  private:
    addr GetFieldData(jobject obj);

  private:
    int offset_;
    std::string name_;
    int modifier_;
    Klass* type_;
    int index_;
};


#endif