#include "jvm/oop.h"
 

JArray::JArray(void* list, int count, BasicDataType type)
    :dataList__(list), length__(count), compoentType_(type){ 
}

int JArray::GetCount(){
    return count_;
}

BasicDataType JArray::GetComponentType(){
    return compoentType_;
}

void JArray::CheckIndex(int index){
    if(index <0 || index> count_){
        throw "out index";
    }
}
