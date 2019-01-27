#include "oop/klass.h"

#include "oop/field.h"
#include "oop/jobject.h"
#include "classfile/class_file_type.h"


Klass::Klass(ClassFileInfo* classFile):
    classFile_(classFile),
    constantPool_(classFile),
    instanceDataSize_(0),
    staticDataSize_(0) {
}

Klass::~Klass() {

}

void Klass::Init() {
    this->ComputeInstanceSize();
    this->ComputeStaticSize();
}

bool Klass::IsPrimitive() {
    return false;
}

bool Klass::IsEnum() {

    return false;
}

bool Klass::IsAnnotation() {

    return false;
}

bool Klass::IsAssigableFrom(Klass* klass) {

    return false;
}

bool Klass::IsArray() {

    return false;
}

bool Klass::IsKlass() {
    return !IsPrimitive() && !IsInterface();
}

bool Klass::IsInterface() {

    return false;
}

bool Klass::IsSynthetic() {

    return false;
}

bool Klass::IsInstance(jobject obj) {

    return false;
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

bool Klass::IsResolved() {
    return resolved_;
}

BasicDataType Klass::GetType() {
    return type_;
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
    return staticDataSize_;
}

void Klass::ComputeStaticSize() {
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
}



int Klass::GetInstanceDataSize() {
    return instanceDataSize_;
}

void Klass::ComputeInstanceSize() {
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
    std::vector<Field*>::iterator itor;
    for (itor = fields_.begin(); itor != fields_.end(); ++itor) {
        Field* field = *itor;
        if (!field->GetName().compare(name)) {
            return *itor;
        }
    }

    return NULL;
}

std::vector<Method*>& Klass:: GetDeclaredMethods() {
    return methods_;
}

Method* Klass::GetDeclaredMethod(const std::string& name) {
    return GetDeclaredMethod(name, std::vector<Klass*>());
}

Method* Klass::GetDeclaredMethod(const std::string& name, std::vector<Klass*>& parameterTypes) {
    std::vector<Method*>::iterator itor;
    for (itor = methods_.begin(); itor != methods_.end(); ++itor) {
        Method* method = *itor;
        if (method->GetName().compare(name)) {
            continue;
        }

        const std::vector<Klass*>& types = method->GetParamerterTypes();
        if (types.size() != parameterTypes.size()) {
            continue;
        }

        if (types.empty()) {
            return method;
        }

        bool match = true;
        for (size_t i = 0; i < types.size(); ++i) {
            Klass* a = types.at(i);
            Klass* b = parameterTypes.at(i);

            if (a != b) {
                match = false;
                break;
            }
        }

        if (match) {
            return method;
        }
    }

    return NULL;
}

std::vector<Constructor*>& Klass::GetDeclaredConstructors() {
    return constructors_;
}

Constructor* Klass::GetDeclaredConstructor(std::vector<Klass*>& parameterTypes) {
    std::vector<Constructor*>::iterator itor;
    for (itor = constructors_.begin(); itor != constructors_.end(); ++itor) {
        Constructor* method = *itor;

        const std::vector<Klass*>& types = method->GetParamerterTypes();
        if (types.size() != parameterTypes.size()) {
            continue;
        }

        if (types.empty()) {
            return method;
        }

        bool match = true;
        for (size_t i = 0; i < types.size(); ++i) {
            Klass* a = types.at(i);
            Klass* b = parameterTypes.at(i);

            if (a != b) {
                match = false;
                break;
            }
        }

        if (match) {
            return method;
        }
    }

    return NULL;
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

ConstantPool& Klass::GetConstantPool() {
    return constantPool_;
}
