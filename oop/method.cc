#include "oop/method.h"

#include "gc/memory.h"
#include "oop/jobject.h"
#include "oop/klass.h"

jobject Constructor::NewInstance() {
    int length = this->GetType()->GetInstanceDataSize();
    jobject obj = (jobject) MemoryGC::Instance().Alloc(length);



    return obj;
}

Executable::Executable() {
}

Executable::~Executable() {
}

const std::string& Executable::GetName() {
    return this->name_;
}

void Executable::SetName(const std::string& name) {
    this->name_ = name;
}

int Executable::GetModifier() {
    return modifier_;
}

void Executable::SetModifier(int modifier) {
    this->modifier_ = modifier;
}

Klass* Executable::GetDeclareClass() {
    return NULL;
}

void Executable::SetDeclareClass(Klass* klass) {

}

const std::vector<Klass*>& Executable::GetParamerterTypes() {
    return parameterTypes_;
}

void Executable::SetParameterTypes(const std::vector<Klass*>& parameterTypes) {
    this->parameterTypes_ = parameterTypes;
}

int Executable::GetParameterCount() {
    return this->parameterTypes_.size();
}

Klass* Executable::GetReturnType() {
    return returnType_;
}

void Executable::SetReturnType(Klass* returnType) {
    returnType_ = returnType;
}

Klass* Executable::GetType() {
    return this->klass_;
}

void Executable::SetType(Klass* klass) {
    this->klass_ = klass;
}

CodeArea* Executable::GetCodeArea() {
    return this->codeArea_;
}

jobject Executable::Invoke(jobject obj, const std::vector<jobject>& parameters) {
    return NULL;
}
