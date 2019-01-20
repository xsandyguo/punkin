#include "oop/klass.h"
#include "oop/class_loader.h"
#include "classfile/class_file_reader.hpp"


std::vector<ClassLoader*> ClassLoader::instances_;

ClassLoader::ClassLoader()
	:parent_(NULL){ 
}

ClassLoader::ClassLoader(ClassLoader* parent)
	:parent_(parent){

}

ClassLoader::~ClassLoader(){

}

std::vector<ClassLoader*>& ClassLoader::GetAllInstance(){
	return instances_;
}

Klass* ClassLoader::DefineClass(const char* name, byte* codes, int length){
	ClassFileReader reader(codes, length);
	Klass* klass = reader.Read();
	klass->SetName(name);
	klass->SetClassLoader(this);

	return klass;
}

Klass* ClassLoader::LoadClass(const char* name){
	Klass* klass = FindLoadedKlass(name);

	if(parent_ == NULL){
		klass = parent_->LoadClass(name);
	}

	if(klass == NULL){
		klass = FindClass(name);
	}

	if(klass == NULL){
		throw "not found klass";
	}

	return klass;
}

Klass* ClassLoader::FindLoadedKlass(const char* name){
	for(std::vector<Klass*>::iterator itor = loadedKlass_.begin();
		itor != loadedKlass_.end(); itor++){
		Klass* klass = *itor;

		if(!strcmp(klass->GetName(), name)){
			return klass;
		}
	}

	return NULL;
}

void ClassLoader::ResolveKlass(Klass* klass){

}