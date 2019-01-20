#include "oop/field.h"
#include "oop/jobject.h"


void Field::SetIndex(int index){
	this->index_ = index;
}

int Field::GetIndex(){
	return this->index_;
}

const char* Field::GetName(){
	return this->name_;
}

void        Field::SetName(const char* name){
	this->name_ = name;
}

Klass*      Field::GetType(){
	return this->type_;
}

void        Field::SetType(Klass* type){
	this->type_ = type;
}

int         Field::GetModifier(){
	return this->modifier_;
}

void        Field::SetModifier(int modifier){
	this->modifier_ = modifier;
}

void	    Field::SetDataOffset(int offset){
	this->offset_ = offset;
}

int		    Field::GetDataOffset(){
	return this->offset_;
}

jobject     Field::Get(jobject obj){
	return *(jobject*)GetFieldData(obj);
}

jbool       Field::GetBoolean(jobject obj){
	return *(jbool*)GetFieldData(obj);
}

jbyte       Field::GetByte(jobject obj){
	return *(jbyte*)GetFieldData(obj);
}

jchar       Field::GetChar(jobject obj){
	return *(jchar*)GetFieldData(obj);
}

jshort      Field::GetShort(jobject obj){
	return *(jshort*)GetFieldData(obj);
}

jint        Field::GetInt(jobject obj){
	return *(jint*)GetFieldData(obj);
}

jlong       Field::GetLong(jobject obj){
	return *(jlong*)GetFieldData(obj);
}

jfloat      Field::GetFloat(jobject obj){
	return *(jfloat*)GetFieldData(obj);
}

jdouble     Field::GetDouble(jobject obj){
	return *(jdouble*)GetFieldData(obj);
}

void Field::Set(jobject obj, jobject val){
	*(jobject*)GetFieldData(obj) = val;
}

void Field::SetBoolean(jobject obj, jbool val){
	*(jbool*)GetFieldData(obj) = val;
}

void Field::SetByte(jobject obj, jbyte val){
	*(jbyte*)GetFieldData(obj) = val;
}

void Field::SetChar(jobject obj, jchar val){
	*(jchar*)GetFieldData(obj) = val;
}

void Field::SetShort(jobject obj, jshort val){

	*(jshort*)GetFieldData(obj) = val;
}

void Field::SetInt(jobject obj, jint val){
	*(jint*)GetFieldData(obj) = val;
}

void Field::SetLong(jobject obj, jlong val){

	*(jlong*)GetFieldData(obj) = val;
}

void Field::SetFloat(jobject obj, jfloat val){
	*(jfloat*)GetFieldData(obj) = val;
}

void Field::SetDouble(jobject obj, jdouble val){
	*(jdouble*)GetFieldData(obj) = val;
}

addr Field::GetFieldData(jobject obj){
	return (u1*)obj->GetObjectData() + offset_;
}