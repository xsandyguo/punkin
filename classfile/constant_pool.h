#ifndef CLASS_FILE_CONSTANT_POOL_H
#define CLASS_FILE_CONSTANT_POOL_H

#include <string>
#include <vector>

#include "oop/oop.h"
#include "classfile/class_file_type.h"

class Method;
class Field;

class MethodRefSymbol {
  public:
    std::string& GetMethodName();
    std::string& GetKlassName();
    std::string& GetReturnType();
    bool HasReturn();
    std::vector<std::string>& GetParameterTypes();

    void SetMethod(Method* method);
    Method* GetMethod();

  private:
    std::string methodName_;
    std::string klassName_;
    std::string returnType_;
    bool hashReturn_;
    std::vector<std::string> parameterTypes_;
    Method* method_;
};

class FieldRefSymbol {
  public:
    std::string& GetFieldName();
    std::string& GetKlass();
    std::string& GetFieldType();

    void SetField(Field* field);
    Field* GetField();

  private:
    std::string fieldName_;
    std::string klass_;
    std::string fieldType_;
    Field* field_;
};

class ConstantPool {
  public:
    ConstantPool(ClassFileInfo* classFile);

    MethodRefSymbol* ResolveMethodRef(u2 index);

    FieldRefSymbol* ResolveFieldRef(u2 index);

    ConstPoolInfo* ResolveConstantInfo(u2 index);

    const char* ResolveConstantString(u2 index);

  private:
    ClassFileInfo* classFile_;
};

#endif