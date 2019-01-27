#ifndef CLASSFILE_KLASS_H
#define CLASSFILE_KLASS_H

#include <string>
#include <vector>

#include "classfile/constant_pool.h"
#include "classfile/class_file_type.h"
#include "oop/oop.h"
#include "oop/field.h"
#include "oop/method.h"

class ClassLoader;

class Klass {
  public:
    Klass(ClassFileInfo* classFile);
    ~Klass();
  public:
    void Init();

    bool IsPrimitive();
    bool IsEnum();
    bool IsAnnotation();
    bool IsAssigableFrom(Klass* klass);
    bool IsArray();
    bool IsInterface();
    bool IsSynthetic();
    bool IsInstance(jobject obj);
    bool IsKlass();
    bool IsAbstract();
    bool IsFinal();
    bool IsPublic();

    int GetModifier();
    void SetModifier(int modifier);

    Method* ResolveMethodByName(const std::string& name);
    Method* GetStaticConstructor();

    BasicDataType GetType();
    bool IsResolved();

  public:
    const std::string& GetName();
    void SetName(const std::string& name);

    std::vector<Field*>& GetDeclaredFields();
    Field* GetDeclaredField(const std::string& name);

    std::vector<Method*>& GetDeclaredMethods();
    Method* GetDeclaredMethod(const std::string& name);
    Method* GetDeclaredMethod(const std::string& name, std::vector<Klass*>& parameterTypes);

    std::vector<Constructor*>& GetDeclaredConstructors();
    Constructor* GetDeclaredConstructor(std::vector<Klass*>& parameterTypes);

    std::vector<Klass*>& GetDeclaredClasses();

    ClassLoader* GetClassLoader();
    void SetClassLoader(ClassLoader* classLoader);

    Klass* GetSuperKlass();
    void SetSuperKlass(Klass* superKlass);

    addr GetStaticData();
    void SetStaticData(addr data);

    int GetStaticDataSize();
    int GetInstanceDataSize();

    void ComputeStaticSize();
    void ComputeInstanceSize();

    ConstantPool& GetConstantPool();

  private:
    int modifier_;
    Klass* superKlass_;
    ClassLoader* classLoader_;

    std::vector<Constructor*> constructors_;
    std::vector<Method*> methods_;
    std::vector<Field*> fields_;
    std::string name_;

    ConstantPool constantPool_;

    ClassFileInfo* classFile_;
    std::vector<Klass*> declaredKlasses_;

    bool resolved_;

    addr staticData_;
    int staticDataSize_;
    int instanceDataSize_;

    Method* staticConstructor_;
    BasicDataType type_;
};

#endif