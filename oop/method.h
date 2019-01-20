#ifndef CLASSFILE_METHOD_H
#define CLASSFILE_METHOD_H

#include <vector>
#include "oop/oop.h"

class Klass;

class Executable {
  public:
    Executable();
    ~Executable();
  public:
    const std::string& GetName();
    void        SetName(const std::string& name);

    int GetModifier();
    void SetModifier(int modifier);

    Klass*      GetDeclareClass();
    void        SetDeclareClass(Klass* klass);

    const std::vector<Klass*>& GetParamerterTypes();
    void        SetParameterTypes(const std::vector<Klass*>& parameterTypes);
    int         GetParameterCount();

    Klass*      GetReturnType();
    void        SetReturnType(Klass* returnType);

    Klass*      GetType();
    void		SetType(Klass* klass);

    jobject Invoke(jobject obj, const std::vector<jobject>& parameters);
  private:
    int modifier_;
    Klass* returnType_;
    Klass* klass_;
    std::string name_;
    std::vector<Klass*> parameterTypes_;
};


class Method : public Executable {

};


class Constructor : public Executable {
  public:
    jobject New();
};

#endif