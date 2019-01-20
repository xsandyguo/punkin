#include "oop/oop.h"


JArray::JArray(addr list, int count, Klass* type)
    :dataList_(list), length_(count),super(type) {
}

int JArray::GetLength() {
    return length_;
}

Klass* JArray::GetComponentType() {
    return compoentType_;
}

void JArray::CheckIndex(int index) {
    if(index <0 || index> length_) {
        throw "out index";
    }
}



primitive_type_klass_size KLASS_TYPE_SIZE [] = {
    {PRIMITIVE_TYPE_KLASS_NAME_BOOL, 1},
    {PRIMITIVE_TYPE_KLASS_NAME_CHAR, 2},
    {PRIMITIVE_TYPE_KLASS_NAME_BYTE, 1},
    {PRIMITIVE_TYPE_KLASS_NAME_SHORT, 2},
    {PRIMITIVE_TYPE_KLASS_NAME_INT, 4},
    {PRIMITIVE_TYPE_KLASS_NAME_LONG, 8},
    {PRIMITIVE_TYPE_KLASS_NAME_FLOAT, 4},
    {PRIMITIVE_TYPE_KLASS_NAME_DOUBLE, 8}
};
