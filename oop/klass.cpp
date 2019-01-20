#include "oop/field.h"

#include "oop/klass.h"


Klass::Klass(){

}

Klass::~Klass(){

}

bool Klass::IsPrimitive(){

}

bool Klass::IsEnum(){

}

bool Klass::IsAnnotation(){

}

bool Klass::IsAssigableFrom(Klass* klass){

}

bool Klass::IsArray(){

}

bool Klass::IsInterface(){

}

bool Klass::IsSynthetic(){

}

bool Klass::IsInstance(jobject obj){

}

int Klass::GetModifier(){
	return modifier_;
}

void Klass::SetModifier(int modifier){
	this->modifier_ = modifier;
}


Method* ResolveMethodByName(const char* name){

}

u1   Klass::GetValueType(){

}

Klass* Klass::GetSuperKlass(){
	return this->superKlass_;
}

void Klass::SetSuperKlass(Klass* superKlass){
	this->superKlass_ = superKlass;
}

const char* Klass::GetName(){
	return this->name_;
}

void Klass::SetName(const char* name){
	this->name_ = name;
}

std::vector<Field*> Klass::GetDeclaredFields(){
	return fields_;
}

Field* Klass::GetDeclaredField(const char* name){
	 
}

std::vector<Method*>Klass:: GetDeclaredMethods(){

}

Method* Klass::GetDeclaredMethod(const char* name){

}

Method* Klass::GetDeclaredMethod(const char* name, std::vector<Klass*>& parameterTypes){

}

std::vector<Constructor*> Klass::GetDeclaredConstructors(){

}

Constructor* Klass::GetDeclaredConstructor(std::vector<Klass*>& parameterTypes){

}

std::vector<Klass*> Klass::GetDeclaredClasses(){
	 
}

ClassLoader* Klass::GetClassLoader(){
	return this->classLoader_;
}

void Klass::SetClassLoader(ClassLoader* classLoader){
	this->classLoader_ = classLoader;
}

void Klass::SetConstantPool(std::vector<ConstantPool*>& constantPools){

}

jobject Klass::NewInstance(){

}