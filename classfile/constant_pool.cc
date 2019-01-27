#include "classfile/constant_pool.h"


std::string& MethodRefSymbol::GetMethodName() {
    return methodName_;
}
std::string& MethodRefSymbol::GetKlassName() {
    return klassName_;
}

std::string& MethodRefSymbol::GetReturnType() {
    return returnType_;
}

bool MethodRefSymbol::HasReturn() {
    return hashReturn_;
}
std::vector<std::string>& MethodRefSymbol::GetParameterTypes() {
    return parameterTypes_;
}

void MethodRefSymbol::SetMethod(Method* method) {
    method_ = method;
}

Method* MethodRefSymbol::GetMethod() {
    return method_;
}

std::string& FieldRefSymbol::GetFieldName() {
    return fieldName_;
}
std::string& FieldRefSymbol::GetKlass() {
    return klass_;
}
std::string& FieldRefSymbol::GetFieldType() {
    return fieldType_;
}

void FieldRefSymbol::SetField(Field* field) {
    field_ = field;
}
Field* FieldRefSymbol::GetField() {
    return field_;
}

ConstantPool::ConstantPool(ClassFileInfo* classFile)
    :classFile_(classFile) {
}

MethodRefSymbol* ConstantPool::ResolveMethodRef(u2 index) {
    return NULL;
}

FieldRefSymbol* ConstantPool::ResolveFieldRef(u2 index) {

    return NULL;
}

ConstPoolInfo* ConstantPool::ResolveConstantInfo(u2 index) {
    assert(index < classFile_->constant_pool_count);

    return classFile_->constant_pool[index];
}

const char* ConstantPool::ResolveConstantString(u2 index) {
    return NULL;
}
