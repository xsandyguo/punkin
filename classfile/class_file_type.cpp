#include "classfile/class_file_type.hpp"

const char* attribute_type_map[] = {
    CONST_SYMBOLE_CONSTANT_VALUE                          ,
    CONST_SYMBOLE_STACK_MAP_TABLE                         ,
    CONST_SYMBOLE_EXCEPTION                               ,
    CONST_SYMBOLE_INNER_CLASSES                           ,
    CONST_SYMBOLE_ENCLOSING_METHOD                        ,
    CONST_SYMBOLE_SYNTHETIC                               ,
    CONST_SYMBOLE_SIGNATURE                               ,
    CONST_SYMBOLE_SOURCE_FILE                             ,
    CONST_SYMBOLE_SOURCE_DEBUG_EXCEPTION                  ,
    CONST_SYMBOLE_LINE_NUMBER_TABLE                       ,
    CONST_SYMBOLE_LOCAL_VARIABLE_TABLE                    ,
    CONST_SYMBOLE_LOCAL_VARIABLE_TYPE_TABLE               ,
    CONST_SYMBOLE_DEPRECATED                              ,
    CONST_SYMBOLE_RUNTIME_VISIBLE_ANNOTATIONS             ,
    CONST_SYMBOLE_RUNTIME_INVISIBLE_ANNOTATIONS           ,
    CONST_SYMBOLE_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS   ,
    CONST_SYMBOLE_RUNTIME_INVISIBLE_PARAMETER_ANNTATIONS  ,
    CONST_SYMBOLE_ANNOTATION_DEFAULT                      ,
    CONST_SYMBOLE_BOOTSTRAP_METHODS                       ,
};