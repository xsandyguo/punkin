#include "oop/jarray.h"

void JArray::check_index(int index) {
    if (index < 0 || index >= length_) {
        throw "ArrayOutOfIndex";
    }
}