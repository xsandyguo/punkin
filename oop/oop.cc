#include "oop/oop.h"


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