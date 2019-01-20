#include "oop/klass.h"
#include "oop/class_loader.h"
#include "classfile/class_file_reader.hpp"


std::list<ClassLoader*> ClassLoader::instances_;

ClassLoader::ClassLoader()
    :parent_(NULL) {
}

ClassLoader::ClassLoader(ClassLoader* parent)
    :parent_(parent) {

}

ClassLoader::~ClassLoader() {

}

std::list<ClassLoader*>& ClassLoader::GetAllInstance() {
    return instances_;
}

Klass* ClassLoader::DefineClass(const std::string& name, byte* codes, int length) {
    ClassFileReader reader(codes, length);
    Klass* klass = reader.Read();
    klass->SetName(name);
    klass->SetClassLoader(this);

    return klass;
}

Klass* ClassLoader::LoadClass(const std::string& name) {
    Klass* klass = FindLoadedKlass(name);

    if(parent_ == NULL) {
        klass = parent_->LoadClass(name);
    }

    if(klass == NULL) {
        klass = FindClass(name);
    }

    if(klass == NULL) {
        throw "not found klass";
    }

    return klass;
}

Klass* ClassLoader::FindLoadedKlass(const std::string& name) {
    std::map<std::string, Klass*>::iterator itor = loadedKlass_.find(name);
    if (itor != loadedKlass_.end()) {
        return itor->second;
    }

    return NULL;
}

void ClassLoader::ResolveKlass(Klass* klass) {

}