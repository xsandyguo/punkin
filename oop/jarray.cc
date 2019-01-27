#include "oop/jarray.h"

JArray::JArray(addr list, int count, Klass* type)
    :JObject(type, list)
    , length_(count) {
}

void JArray::check_index(int index) {
    if (index < 0 || index >= length_) {
        throw "ArrayOutOfIndex";
    }
}

