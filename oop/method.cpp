#include "oop/method.h"

#include "gc/memory.h"
#include "oop/jobject.h"
#include "oop/klass.h"

jobject Constructor::New() {
    int length = sizeof(JObject);

    Klass* klass = this->GetType();
    while (klass) {
        if (!klass->IsPrimitive()) {
            length += 4;
            continue;
        }

        const std::string& name = klass->GetName();
        for (int i = 0; i < PRIMITIVE_TYPE_KLASS_NAME_COUNT; ++i) {
            primitive_type_klass_size& item = KLASS_TYPE_SIZE[i];

            if (!name.compare(item.name)) {
                length += item.size;
            }
        }

        klass = klass->GetSuperKlass();
    }

    return (jobject) MemoryGC::Instance().Alloc(length);
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

jobject Executable::Invoke(jobject obj, const std::vector<jobject>& parameters) {

}
