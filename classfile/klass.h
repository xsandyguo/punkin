#ifndef CLASSFILE_KLASS_H
#define CLASSFILE_KLASS_H

#include <string> 
#include <vector>

#include "jvm/oop.h" 

class Klass;


class ConstantPool{

};

class Klass{
public:

public:
    bool IsPrimitive();
    bool IsEnum();
    bool IsAnnotation();
    bool IsAssigableFrom(Klass* klass);
    bool IsArray();
    bool IsInterface();
    bool IsSynthetic();
    bool IsInstance(jobject obj);

    int GetModifier();


    Method* ResolveMethodByName(const char* name);  

    u1   GetValueType();

public:
    const char* GetName();
     
    std::vector<Field*> GetDeclaredFields();
    Field* GetDeclaredField(const char* name);

    std::vector<Method*> GetDeclaredMethods();
    Method* GetDeclaredMethod(const char* name);
    Method* GetDeclaredMethod(const char* name, std::vector<Klass*>& parameterTypes);

    std::vector<Constructor*> GetDeclaredConstructors();
    Constructor* GetDeclaredConstructor(std::vector<Klass*>& parameterTypes);

    std::vector<Klass*> GetDeclaredClasses(); 

    ClassLoader* GetClassLoader();
    void SetClassLoader(ClassLoader* classLoader);
    void SetConstantPool(std::vector<ConstantPool*>& constantPools);

private:
     int modifier_; 
     Klass* superKlass_; 
     ClassLoader* classLoader_;
     std::vector<Constructor*> constructors_;
     std::vector<Method*> methods_; 
     const char* name_;
     std::vector<ConstantPool*> constantPools_;
};

#endif