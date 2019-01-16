#include "jvm/oop.h"
 

JArray::JArray(addr list, int count, Klass* type)
    :dataList_(list), length_(count),super(type){
}

int JArray::GetLength(){
    return length_;
}

Klass* JArray::GetComponentType(){
    return compoentType_;
}

void JArray::CheckIndex(int index){
    if(index <0 || index> length_){
        throw "out index";
    }
}



addr JObject::GetObjectData(){
	return this->data_;
}