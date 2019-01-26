#ifndef CLASSFILE_CLASS_FILE_TYPE_HPP
#define CLASSFILE_CLASS_FILE_TYPE_HPP

#include "utilities/top.hpp"

#define CLASS_FILE_MAGIC                0xCAFEBABE
#define CLASS_FILE_MAX_SIZE             1024*1024*1024

#define CLASS_FILE_ACC_PUBLIC			0x0001
#define CLASS_FILE_ACC_FINAL			0x0010
#define CLASS_FILE_ACC_SUPER			0x0020
#define CLASS_FILE_ACC_INTERFACE		0x0200
#define CLASS_FILE_ACC_ABSTRACT			0x0400
#define CLASS_FILE_ACC_SYNTHETIC		0x1000
#define CLASS_FILE_ACC_ANNOTATION       0x2000
#define CLASS_FILE_ACC_ENUM             0x4000


#define FIELD_INFO_ACC_PUBLIC           0x0001
#define FIELD_INFO_ACC_PRIVATE		    0x0002
#define FIELD_INFO_ACC_PROTECTED	    0x0004
#define FIELD_INFO_ACC_STATIC		    0x0008
#define FIELD_INFO_ACC_FINAL		    0x0010
#define FIELD_INFO_ACC_VOLATILE         0x0040
#define FIELD_INFO_ACC_TRANSIENT        0x0080
#define FIELD_INFO_ACC_SYNTHETIC        0x1000
#define FIELD_INFO_ACC_ENUM             0x4000


#define METHOD_INFO_ACC_PUBLIC          0x0001
#define METHOD_INFO_ACC_PRIVATE         0x0002
#define METHOD_INFO_ACC_PROTECTED       0x0004
#define METHOD_INFO_ACC_STATIC          0x0008
#define METHOD_INFO_ACC_FINAL           0x0010
#define METHOD_INFO_ACC_SYNCHRONIZED    0x0020
#define METHOD_INFO_ACC_BRIDGE          0x0040
#define METHOD_INFO_ACC_VARARGS         0x0080
#define METHOD_INFO_ACC_NATIVE          0x0100
#define METHOD_INFO_ACC_ABSTRACT        0x0400
#define METHOD_INFO_ACC_STRICT          0x0800
#define METHOD_INFO_ACC_SYNTHETIC       0x1000


#define INNER_CALSS_ACC_PUBLIC          0x0001
#define INNER_CALSS_ACC_PRIVATE         0x0002
#define INNER_CALSS_ACC_PROTECTED       0x0004
#define INNER_CALSS_ACC_STATIC          0x0008
#define INNER_CALSS_ACC_FINAL           0x0010
#define INNER_CALSS_ACC_INTERFACE       0x0200
#define INNER_CALSS_ACC_ABSTRACT        0x0400
#define INNER_CALSS_ACC_SYNTHETIC       0x1000
#define INNER_CALSS_ACC_ANNOTATION      0x2000
#define INNER_CALSS_ACC_ENUM            0x4000

#define CONSTANT_POOL_TYPE_CLASS                 7
#define CONSTANT_POOL_TYPE_FIELD_REF             9
#define CONSTANT_POOL_TYPE_METHOD_REF            10
#define CONSTANT_POOL_TYPE_INTERFACE_METHOD_REF  11
#define CONSTANT_POOL_TYPE_STRING                8
#define CONSTANT_POOL_TYPE_INTERGER              3
#define CONSTANT_POOL_TYPE_FLOAT                 4
#define CONSTANT_POOL_TYPE_LONG                  5
#define CONSTANT_POOL_TYPE_DOUBLE                6
#define CONSTANT_POOL_TYPE_NAME_AND_TYPE         12
#define CONSTANT_POOL_TYPE_UTF8                  1
#define CONSTANT_POOL_TYPE_METHOD_HANDLE         15
#define CONSTANT_POOL_TYPE_METHOD_TYPE           16
#define CONSTANT_POOL_TYPE_INVOKE_DYNAMIC        18


#define ELEMENT_VALUE_TAG_BYTE          'B'
#define ELEMENT_VALUE_TAG_CHAR          'C'
#define ELEMENT_VALUE_TAG_DOUBLE        'D'
#define ELEMENT_VALUE_TAG_FLOAT         'F'
#define ELEMENT_VALUE_TAG_INT           'I'
#define ELEMENT_VALUE_TAG_LONG          'J'
#define ELEMENT_VALUE_TAG_SHORT         'S'
#define ELEMENT_VALUE_TAG_BOOL          'Z'
#define ELEMENT_VALUE_TAG_REF           'L'
#define ELEMENT_VALUE_TAG_STRING			  's'
#define ELEMENT_VALUE_TAG_ENUM_CONST		'e'
#define ELEMENT_VALUE_TAG_CLASS				  'c'
#define ELEMENT_VALUE_TAG_ANNO_TYPE	    '@'
#define ELEMENT_VALUE_TAG_ARRAY				  '['



#define ARRAY_ELE_TYPE_MIN               4
#define ARRAY_ELE_TYPE_BOOLEAN           4
#define ARRAY_ELE_TYPE_CHAR              5
#define ARRAY_ELE_TYPE_FLOAT             6
#define ARRAY_ELE_TYPE_DOUBLE            7
#define ARRAY_ELE_TYPE_BYTE              8
#define ARRAY_ELE_TYPE_SHORT             9
#define ARRAY_ELE_TYPE_INT               10
#define ARRAY_ELE_TYPE_LONG              11
#define ARRAY_ELE_TYPE_MAX               11

#define ATTRIBUTE_TYPE_CONSTANT_VALUE                         1
#define ATTRIBUTE_TYPE_CODE                                   2
#define ATTRIBUTE_TYPE_STACK_MAP_TABLE                        3
#define ATTRIBUTE_TYPE_EXCEPTION                              4
#define ATTRIBUTE_TYPE_INNER_CLASSES                          5
#define ATTRIBUTE_TYPE_ENCLOSING_METHOD                       6
#define ATTRIBUTE_TYPE_SYNTHETIC                              7
#define ATTRIBUTE_TYPE_SIGNATURE                              8
#define ATTRIBUTE_TYPE_SOURCE_FILE                            9
#define ATTRIBUTE_TYPE_SOURCE_DEBUG_EXCEPTION                 10
#define ATTRIBUTE_TYPE_LINE_NUMBER_TABLE                      11
#define ATTRIBUTE_TYPE_LOCAL_VARIABLE_TABLE                   12
#define ATTRIBUTE_TYPE_LOCAL_VARIABLE_TYPE_TABLE              13
#define ATTRIBUTE_TYPE_DEPRECATED                             14
#define ATTRIBUTE_TYPE_RUNTIME_VISIBLE_ANNOTATIONS            15
#define ATTRIBUTE_TYPE_RUNTIME_INVISIBLE_ANNOTATIONS          16
#define ATTRIBUTE_TYPE_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS  17
#define ATTRIBUTE_TYPE_RUNTIME_INVISIBLE_PARAMETER_ANNTATIONS 18
#define ATTRIBUTE_TYPE_ANNOTATION_DEFAULT                     19
#define ATTRIBUTE_TYPE_BOOTSTRAP_METHODS                      20
#define ATTRIBUTE_TYPE_MAX                                    20

#define CONST_SYMBOLE_CONSTANT_VALUE                            "ConstantValue"
#define CONST_SYMBOLE_CODE                                      "Code"
#define CONST_SYMBOLE_STACK_MAP_TABLE                           "StackMapTable"
#define CONST_SYMBOLE_EXCEPTION                                 "Exceptions"
#define CONST_SYMBOLE_INNER_CLASSES                             "InnerClasses"
#define CONST_SYMBOLE_ENCLOSING_METHOD                          "EnclosingMethod"
#define CONST_SYMBOLE_SYNTHETIC                                 "Synthetic"
#define CONST_SYMBOLE_SIGNATURE                                 "Signature"
#define CONST_SYMBOLE_SOURCE_FILE                               "SourceFile"
#define CONST_SYMBOLE_SOURCE_DEBUG_EXCEPTION                    "SourceDebugExtension"
#define CONST_SYMBOLE_LINE_NUMBER_TABLE                         "LineNumberTable"
#define CONST_SYMBOLE_LOCAL_VARIABLE_TABLE                      "LocalVariableTable"
#define CONST_SYMBOLE_LOCAL_VARIABLE_TYPE_TABLE                 "LocalVariableTypeTable"
#define CONST_SYMBOLE_DEPRECATED                                "Deprecated"
#define CONST_SYMBOLE_RUNTIME_VISIBLE_ANNOTATIONS               "RuntimeVisibleAnnotations"
#define CONST_SYMBOLE_RUNTIME_INVISIBLE_ANNOTATIONS             "RuntimeInvisibleAnnotations"
#define CONST_SYMBOLE_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS     "RuntimeVisibleParameterAnnotations"
#define CONST_SYMBOLE_RUNTIME_INVISIBLE_PARAMETER_ANNTATIONS    "RuntimeInvisibleParameterAnnotations"
#define CONST_SYMBOLE_ANNOTATION_DEFAULT                        "AnnotationDefault"
#define CONST_SYMBOLE_BOOTSTRAP_METHODS                         "BootstrapMethods"

extern const char* attribute_type_map[];

#define METHOD_REF_KIND_getField            1
#define METHOD_REF_KIND_getStatic           2
#define METHOD_REF_KIND_putField            3
#define METHOD_REF_KIND_putStatic           4
#define METHOD_REF_KIND_invokeVirtual       5
#define METHOD_REF_KIND_invokeStatic        6
#define METHOD_REF_KIND_invokeSpecial       7
#define METHOD_REF_KIND_newInvokeSpecial    8
#define METHOD_REF_KIND_invokeInterface     9


struct ConstPoolInfo {
    u1 tag;
};

struct ConstPoolClassInfo : ConstPoolInfo {
    u2 name_index;
};

struct ConstPoolFieldRefInfo : ConstPoolInfo {
    u2 class_index;
    u2 name_and_type_index;
};

struct ConstPoolMethodRefInfo : ConstPoolInfo {
    u2 class_index;
    u2 name_and_type_index;
};

struct ConstPoolInterfaceMethodRefInfo : ConstPoolInfo {
    u2 class_index;
    u2 name_and_type_index;
};

struct ConstPoolStringInfo: ConstPoolInfo {
    u2 string_index;
};

struct ConstPoolIntegerInfo: ConstPoolInfo {
    u4 bytes;
};

struct ConstPoolFloatInfo: ConstPoolInfo {
    u4 bytes;
};

struct ConstPoolLongInfo : ConstPoolInfo {
    u4 high_bytes;
    u4 low_bytes;
};

struct ConstPoolDoubleInfo : ConstPoolInfo {
    u4 high_bytes;
    u4 low_bytes;
};

struct ConstPoolNameAndTypeInfo: ConstPoolInfo {
    u2 name_index;
    u2 descriptor_index;
};

struct ConstPoolUtf8Info: ConstPoolInfo {
    u2 length;
    u1* bytes; //u1[length]
};

struct ConstPoolMethodHandleInfo : ConstPoolInfo {
    u1 reference_kind;
    u2 reference_index;
};

struct ConstPoolMethodTypeInfo: ConstPoolInfo {
    u2 descriptor_index;
};

struct ConstPoolInvokeDynamicInfo : ConstPoolInfo {
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
};

struct AttributeInfo {
    u2 attribute_name_index;
    u4 attribute_length;
    u1 type;
};

struct FieldInfo {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    AttributeInfo** attributes;//attribute_info[arrtribute_count]
};

struct MethodInfo {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    AttributeInfo** attributes; //attribute_info[arrtribute_count]
};

struct ConstantValueAttribute : AttributeInfo {
    u2 constantvalue_index;
};

struct CodeAttribute : AttributeInfo {
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1* code;//code[code_length];
    u2 exception_table_length;
    struct ExceptionTable {
        u2 start_pc;
        u2 end_pc;
        u2 handler_pc;
        u2 catch_type;
    }*exception_table;//exception_table[exception_table_length];
    u2 attributes_count;
    AttributeInfo** attributes;//attributes[attributes_count];
};

#define STACK_MAP_FRAME_TYPE_SAME_START                         0
#define STACK_MAP_FRAME_TYPE_SAME_END                           63
#define STACK_MAP_FRAME_TYPE_SAME_LOCALS_1_STACK_ITEM_START     64
#define STACK_MAP_FRAME_TYPE_SAME_LOCALS_1_STACK_ITEM_END       127
#define STACK_MAP_FRAME_TYPE_SAME_LOCALS_1_STACK_ITEM_EXTENDED  247
#define STACK_MAP_FRAME_TYPE_CHOP_BEGIN                         248
#define STACK_MAP_FRAME_TYPE_CHOP_END                           250
#define STACK_MAP_FRAME_TYPE_SAME_FRAME_EXTENDED                251
#define STACK_MAP_FRAME_TYPE_APPEND_BEGIN                       252
#define STACK_MAP_FRAME_TYPE_APPEND_END                         254
#define STACK_MAP_FRAME_TYPE_FULL                               255

#define STACK_MAP_FRAME_VARIFY_TYPE_TOP           0
#define STACK_MAP_FRAME_VARIFY_TYPE_INTEGER       1
#define STACK_MAP_FRAME_VARIFY_TYPE_FLOAT         2
#define STACK_MAP_FRAME_VARIFY_TYPE_LONG          3
#define STACK_MAP_FRAME_VARIFY_TYPE_DOUBLE        4
#define STACK_MAP_FRAME_VARIFY_TYPE_NULL          5
#define STACK_MAP_FRAME_VARIFY_TYPE_UNINIT_THIS   6
#define STACK_MAP_FRAME_VARIFY_TYPE_OBJECT        7
#define STACK_MAP_FRAME_VARIFY_TYPE_UNINIT        8

struct VerificationTypeInfo {
    u1 tag;
};

struct TopVariableInfo :VerificationTypeInfo {
};

struct IntegerVariableInfo:VerificationTypeInfo {
};

struct FloatVariableInfo:VerificationTypeInfo {
};

struct LongVariableInfo:VerificationTypeInfo {
};

struct DoubleVariableInfo:VerificationTypeInfo {
};

struct NullVariableInfo : VerificationTypeInfo {
};

struct UninitializedThisVariableInfo :VerificationTypeInfo {
};

struct ObjectVariableInfo :VerificationTypeInfo {
    u2 cpool_index;
};

struct UninitializedVariableInfo :VerificationTypeInfo {
    u2 offset;
};


struct StackMapFrame {
    u1 frame_type;
};

struct SameFrame : StackMapFrame {
    /* 0-63 */
};

struct SameLocals1StackItemFrame : StackMapFrame {
    /* 64-127 */
    VerificationTypeInfo** stack;//stack[1];
};

struct SameLocals1StackItemFrameExtended : StackMapFrame {
    /* 247 */
    u2 offset_delta;
    VerificationTypeInfo** stack;// stack[1];
};

struct ChopFrame : StackMapFrame {
    /* 248-250 */
    u2 offset_delta;
};

struct SameFrameExtended : StackMapFrame {
    /* 251 */
    u2 offset_delta;
};

struct AppendFrame : StackMapFrame {
    /* 252-254 */
    u2 offset_delta;
    VerificationTypeInfo ** locals;// locals[frame_type - 251];
};

struct FullFrame : StackMapFrame {
    /* 255 */
    u2 offset_delta;
    u2 number_of_locals;
    VerificationTypeInfo** locals;// locals[number_of_locals];
    u2 number_of_stack_items;
    VerificationTypeInfo** stack;// stack[number_of_stack_items];
};

struct StackMapTableAttribute : AttributeInfo {
    u2 number_of_entries;
    StackMapFrame* entries; // entries[number_of_entries];
};

struct ExceptionsAttribute : AttributeInfo {
    u2 number_of_exceptions;
    u2* exception_index_table;// exception_index_table[number_of_exceptions];
};

struct InnerClassesAttribute : AttributeInfo {
    u2 number_of_classes;
    struct Item {
        u2 inner_class_info_index;
        u2 outer_class_info_index;
        u2 inner_name_index;
        u2 inner_class_access_flags;
    }* classes;// classes[number_of_classes];
};

struct EnclosingMethodAttribute : AttributeInfo {
    u2 class_index;
    u2 method_index;
};

struct SyntheticAttribute : AttributeInfo {
};

struct SignatureAttribute : AttributeInfo {
    u2 signature_index;
};

struct SourceFileAttribute : AttributeInfo {
    u2 sourcefile_index;
};

struct SourceDebugExtensionAttribute : AttributeInfo {
    u1* debug_extension;// debug_extension[attribute_length];
};

struct LineNumberTableAttribute: AttributeInfo {
    u2 line_number_table_length;
    struct Item {
        u2 start_pc;
        u2 line_number;
    }* line_number_table;//line_number_table[line_number_table_length];
};

struct LocalVariableTableAttribute: AttributeInfo {
    u2 local_variable_table_length;
    struct Item {
        u2 start_pc;
        u2 length;
        u2 name_index;
        u2 descriptor_index;
        u2 index;
    }* local_variable_table;//local_variable_table[local_variable_table_length];
};

struct LocalVariableTypeTableAttribute: AttributeInfo {
    u2 local_variable_type_table_length;
    struct Item {
        u2 start_pc;
        u2 length;
        u2 name_index;
        u2 signature_index;
        u2 index;
    }*local_variable_type_table;//local_variable_type_table[local_variable_type_table_length];
};

struct DeprecatedAttribute: AttributeInfo {
};

struct Annotation;

struct ElementValue {
    u1 tag;
    union {
        u2 const_value_index;
        struct {
            u2 type_name_index;
            u2 const_name_index;
        } enum_const_value;

        u2 class_info_index;
        Annotation* annotation_value; //trick
        struct {
            u2 num_values;
            ElementValue** values;// values[num_values];
        } array_value;
    } value;
};

struct Annotation {
    u2 type_index;
    u2 num_element_value_pairs;
    struct Pair {
        u2 element_name_index;
        ElementValue* value;
    }* element_value_pairs;// element_value_pairs[num_element_value_pairs];
};

struct RuntimeVisibleAnnotationsAttribute : AttributeInfo {
    u2 num_annotations;
    Annotation** annotations;// annotations[num_annotations];
};

struct RuntimeInvisibleAnnotationsAttribute: AttributeInfo {
    u2 num_annotations;
    Annotation** annotations;// annotations[num_annotations];
};

struct ParameterAnnotation {
    u2 num_annotations;
    Annotation** annotations;
};

struct RuntimeVisibleParameterAnnotationsAttribute: AttributeInfo {
    u2 num_parameters;
    ParameterAnnotation* parameter_annotations;// parameter_annotations[num_parameters];
};

struct RuntimeInvisibleParameterAnnotationsAttribute : AttributeInfo {
    u2 num_parameters;
    ParameterAnnotation* parameter_annotations;//parameter_annotations[num_parameters];
};

struct AnnotationDefaultAttribute : AttributeInfo {
    ElementValue default_value;
};

struct BootstrapMethodsAttribute : AttributeInfo {
    u2 num_bootstrap_methods;
    struct Item {
        u2 bootstrap_method_ref;
        u2 num_bootstrap_arguments;
        u2* bootstrap_arguments;// bootstrap_arguments[num_bootstrap_arguments];
    }*bootstrap_methods;// bootstrap_methods[num_bootstrap_methods];
};

struct ClassFileInfo {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    ConstPoolInfo** constant_pool;// constant_pool[constant_pool_count-1];
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2* interfaces;//interfaces[interfaces_count];
    u2 fields_count;
    FieldInfo** fields;// fields[fields_count];
    u2 methods_count;
    MethodInfo** methods;// methods[methods_count];
    u2 attributes_count;
    AttributeInfo** attributes; //attributes[attributes_count];
};


#endif