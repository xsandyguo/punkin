#include "oop/field.h"

#include "oop/klass.h"


Klass::Klass() {

}

Klass::~Klass() {

}

bool Klass::IsPrimitive() {

}

bool Klass::IsEnum() {

}

bool Klass::IsAnnotation() {

}

bool Klass::IsAssigableFrom(Klass* klass) {

}

bool Klass::IsArray() {

}

bool Klass::IsInterface() {

}

bool Klass::IsSynthetic() {

}

bool Klass::IsInstance(jobject obj) {

}

int Klass::GetModifier() {
    return modifier_;
}

void Klass::SetModifier(int modifier) {
    this->modifier_ = modifier;
}

Method * Klass::ResolveMethodByName(const std::string & name) {
    return nullptr;
}


Method* ResolveMethodByName(const std::string& name) {
    return NULL;
}

bool Klass::IsResolved() {
    return resolved_;
}

u1   Klass::GetValueType() {

}

Klass* Klass::GetSuperKlass() {
    return this->superKlass_;
}

void Klass::SetSuperKlass(Klass* superKlass) {
    this->superKlass_ = superKlass;
}

const std::string& Klass::GetName() {
    return this->name_;
}

void Klass::SetName(const std::string& name) {
    this->name_ = name;
}

std::vector<Field*> Klass::GetDeclaredFields() {
    return fields_;
}

Field* Klass::GetDeclaredField(const std::string& name) {

}

std::vector<Method*>Klass:: GetDeclaredMethods() {

}

Method* Klass::GetDeclaredMethod(const std::string& name) {

}

Method* Klass::GetDeclaredMethod(const std::string& name, std::vector<Klass*>& parameterTypes) {

}

std::vector<Constructor*> Klass::GetDeclaredConstructors() {

}

Constructor* Klass::GetDeclaredConstructor(std::vector<Klass*>& parameterTypes) {

}

std::vector<Klass*> Klass::GetDeclaredClasses() {

}

ClassLoader* Klass::GetClassLoader() {
    return this->classLoader_;
}

void Klass::SetClassLoader(ClassLoader* classLoader) {
    this->classLoader_ = classLoader;
}

void Klass::SetConstantPool(std::vector<ConstantPool*>& constantPools) {

}

jobject Klass::NewInstance() {

}