#ifndef CLASSFILE_METHOD_H
#define CLASSFILE_METHOD_H

#include <vector>
#include "oop/oop.h"

class Klass;

struct ExceptionHandler {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

struct CodeArea {
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1* code;
    std::vector<ExceptionHandler> exception_table;
};

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

    CodeArea*   GetCodeArea();

    jobject Invoke(jobject obj, const std::vector<jobject>& parameters);
  private:
    int modifier_;
    Klass* returnType_;
    Klass* klass_;
    std::string name_;
    std::vector<Klass*> parameterTypes_;
    CodeArea* codeArea_;
};


class Method : public Executable {

};


class Constructor : public Executable {
  public:
    jobject NewInstance();
};


#endif