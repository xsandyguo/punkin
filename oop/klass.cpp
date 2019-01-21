#include "oop/klass.h"

#include "oop/field.h"
#include "oop/jobject.h"
#include "classfile/class_file_type.hpp"


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


Method* Klass::GetStaticConstructor() {
    return staticConstructor_;
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

addr Klass::GetStaticData() {
    return this->staticData_;
}

void Klass::SetStaticData(addr data) {
    this->staticData_ = data;
}

int Klass::GetStaticDataSize() {
    std::vector<Field*>& fields = fields_;
    std::vector<Field*>::iterator fieldItor;

    int length = 0;
    for (fieldItor = fields.begin(); fieldItor != fields.end(); ++fieldItor) {
        Field* field = *fieldItor;
        if (FIELD_INFO_ACC_STATIC | field->GetModifier()) {
            Klass* klass = field->GetType();

            if (!klass->IsPrimitive()) {
                length += 4;
                continue;
            }

            const std::string& name = klass->GetName();
            for (int i = 0; i < PRIMITIVE_TYPE_KLASS_NAME_COUNT; ++i) {
                primitive_type_klass_size& item = KLASS_TYPE_SIZE[i];
                if (!name.compare(item.name)) {
                    length += item.size;
                    break;
                }
            }
        }
    }

    staticDataSize_ = length;

    return staticDataSize_;
}

int Klass::GetInstanceDataSize() {
    int length = sizeof(JObject);
    Klass* klass = this;

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
                break;
            }
        }

        klass = klass->GetSuperKlass();
    }

    instanceDataSize_ = length;

    return instanceDataSize_;
}

const std::string& Klass::GetName() {
    return this->name_;
}

void Klass::SetName(const std::string& name) {
    this->name_ = name;
}

std::vector<Field*>& Klass::GetDeclaredFields() {
    return fields_;
}

Field* Klass::GetDeclaredField(const std::string& name) {

}

std::vector<Method*>& Klass:: GetDeclaredMethods() {
    return methods_;
}

Method* Klass::GetDeclaredMethod(const std::string& name) {

}

Method* Klass::GetDeclaredMethod(const std::string& name, std::vector<Klass*>& parameterTypes) {

}

std::vector<Constructor*>& Klass::GetDeclaredConstructors() {
    return constructors_;
}

Constructor* Klass::GetDeclaredConstructor(std::vector<Klass*>& parameterTypes) {

}

std::vector<Klass*>& Klass::GetDeclaredClasses() {
    return declaredKlasses_;
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