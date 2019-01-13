#ifndef CLASSFILE_KLASS_H
#define CLASSFILE_KLASS_H

#include <string> 
#include <vector>

#include "jvm/oop.h" 

class Klass;

 
class Method{
public:
    Method(const char* name, int modifier, Klass* returnType,
        Klass* klass_, std::vector<Klass*> parameterTypes);
    ~Method();
public:
    const char* GetName();
    void        SetName(const char* name);

    Klass*      GetDeclareClass();
    void        SetDeclareClass(Klass* klass);

    std::vector<Klass*> GetParamerterTypes(); 
    void        SetParameterTypes(std::vector<Klass*> parameterTypes);

    Klass*      GetReturnType();
    void        SetReturnType(Klass* returnType); 
    int         GetParameterCount();

    void Invoke(JObject* ref, Operand* args);
    void Invoke(Operand* args);
    jobject Invoke(jobject obj, std::vector<jobject>& parameters);
private:
    int midifers_;
    Klass* returnType_;
    Klass* klass_;
    const char* name_; 
    std::vector<Klass*> parameterTypes_;
};

class Field{
public:
    Field();
    ~Field();
public:
    const char* GetName();
    void        SetName(const char* name);

    Klass*      GetType();
    void        SetType(Klass* type);

    int         GetModifier();
    void        SetModifier(int modifier);

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
    const char* name_;
    int modifier_;
    Klass* type_;
};
  

class Constructor : public Method{

};

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