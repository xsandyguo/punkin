#ifndef CLASS_FILE_TYPE_HPP
#define CLASS_FILE_TYPE_HPP

#include "utilities/top.hpp"


#define CLASS_FILE_ACC_PUBLIC				    0x0001
#define CLASS_FILE_ACC_FINAL				    0x0010
#define CLASS_FILE_ACC_SUPER				    0x0020
#define CLASS_FILE_ACC_INTERFACE		    0x0200
#define CLASS_FILE_ACC_ABSTRACT			    0x0400 
#define CLASS_FILE_ACC_SYNTHETIC		    0x1000
#define CLASS_FILE_ACC_ANNOTATION       0x2000
#define CLASS_FILE_ACC_ENUM             0x4000


#define FIELD_INFO_ACC_PUBLIC           0x0001
#define FIELD_INFO_ACC_PRIVATE		      0x0002
#define FIELD_INFO_ACC_PROTECTED	      0x0004
#define FIELD_INFO_ACC_STATIC		        0x0008
#define FIELD_INFO_ACC_FINAL		        0x0010
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

#define CONSTANT_POOL_TAG_CLASS                 7
#define CONSTANT_POOL_TAG_FIELD_REF             9 
#define CONSTANT_POOL_TAG_METHOD_REF            10 
#define CONSTANT_POOL_TAG_INTERFACE_METHOD_REF  11
#define CONSTANT_POOL_TAG_STRING                8 
#define CONSTANT_POOL_TAG_INTERGER              3 
#define CONSTANT_POOL_TAG_FLOAT                 4 
#define CONSTANT_POOL_TAG_LONG                  5 
#define CONSTANT_POOL_TAG_DOUBLE                6 
#define CONSTANT_POOL_TAG_NAME_AND_TYPE         12 
#define CONSTANT_POOL_TAG_UTF8                  1 
#define CONSTANT_POOL_TAG_METHOD_HANDLE         15 
#define CONSTANT_POOL_TAG_METHOD_TYPE           16 
#define CONSTANT_POOL_TAG_INVOKE_DYNAMIC        18


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


#define METHOD_REF_KIND_getField            1
#define METHOD_REF_KIND_getStatic           2
#define METHOD_REF_KIND_putField            3
#define METHOD_REF_KIND_putStatic           4
#define METHOD_REF_KIND_invokeVirtual       5
#define METHOD_REF_KIND_invokeStatic        6
#define METHOD_REF_KIND_invokeSpecial       7
#define METHOD_REF_KIND_newInvokeSpecial    8
#define METHOD_REF_KIND_invokeInterface     9

struct Const_Pool_Class_Info { 
	u1 tag;
	u2 name_index; 
};

struct Const_Pool_Fieldref_Info { 
	u1 tag; 
	u2 class_index; 
	u2 name_and_type_index; 
};

struct Const_Pool_Methodref_Info { 
	u1 tag;
	u2 class_index;
	u2 name_and_type_index; 
};

struct Const_Pool_InterfaceMethodref_Info { 
	u1 tag; 
	u2 class_index; 
	u2 name_and_type_index; 
};

struct Const_Pool_String_Info {
	u1 tag;
	u2 string_index; 
};

struct Const_Pool_Integer_Info {
	u1 tag; 
	u4 bytes; 
};

struct Const_Pool_Float_Info {
	u1 tag; 
	u4 bytes;
};

struct Const_Pool_Long_Info {
	u1 tag;
	u4 high_bytes;
	u4 low_bytes;
};

struct Const_Pool_Double_Info {
	u1 tag; 
	u4 high_bytes; 
	u4 low_bytes; 
};

struct Const_Pool_NameAndType_Info {
	u1 tag;
	u2 name_index; 
	u2 descriptor_index; 
};

struct Const_Pool_Utf8_Info {
	u1 tag; 
	u2 length; 
	u1* bytes; //u1[length] 
};

struct Const_Pool_MethodHandle_Info {
	u1 tag; 
	u1 reference_kind; 
	u2 reference_index;
};

struct Const_Pool_MethodType_Info {
	u1 tag; 
	u2 descriptor_index; 
};

struct Const_Pool_InvokeDynamic_Info {
	u1 tag; 
	u2 bootstrap_method_attr_index; 
	u2 name_and_type_index; 
};


struct const_pool_info {
	u1 tag; 
	u1* info;
};

struct attribute_info {
	u2 attribute_name_index;
	u4 attribute_length;
	u1* info;//u1[attribute_length]
};

struct field_info {
	u2 access_flags; 
	u2 name_index; 
	u2 descriptor_index; 
	u2 attributes_count; 
	attribute_info* attributes;//attribute_info[arrtribute_count]
};

struct method_info {
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index; 
	u2 attributes_count;
	attribute_info* attributes; //attribute_info[arrtribute_count]
};

struct ConstantValueAttribute { 
	u2 attribute_name_index;
	u4 attribute_length; 
	u2 constantvalue_index; 
};

struct CodeAttribute {
	u2 attribute_name_index;
	u4 attribute_length; 
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1* code;//code[code_length];
	u2 exception_table_length; 
	union{
	    u2 start_pc;
	    u2 end_pc; 
	    u2 handler_pc;
	    u2 catch_type;
	}*exception_table;//exception_table[exception_table_length];

	u2 attributes_count; 
	attribute_info* attributes;//attributes[attributes_count];
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

#define VARIFICATION_TYPE_TAG_TOP           0
#define VARIFICATION_TYPE_TAG_INTEGER       1
#define VARIFICATION_TYPE_TAG_FLOAT         2
#define VARIFICATION_TYPE_TAG_LONG          3
#define VARIFICATION_TYPE_TAG_DOUBLE        4
#define VARIFICATION_TYPE_TAG_NULL          5
#define VARIFICATION_TYPE_TAG_UNINIT_THIS   6
#define VARIFICATION_TYPE_TAG_OBJECT        7
#define VARIFICATION_TYPE_TAG_UNINIT        8

struct TopVariableInfo { 
    u1 tag; /* 0 */
};

struct IntegerVariableInfo { 
    u1 tag; /* 1 */ 
};

struct FloatVariableInfo {
    u1 tag; /* 2 */ 
};

struct LongVariableInfo { 
    u1 tag; /* 4 */ 
};

struct DoubleVariableInfo { 
    u1 tag; /* 3 */ 
};

struct NullVariableInfo {
    u1 tag; /* 5 */ 
};

struct UninitializedThisVariableInfo {
    u1 tag; /* 6 */ 
};

struct ObjectVariableInfo { 
    u1 tag; /* 7 */ 
    u2 cpool_index; 
};

struct UninitializedVariableInfo { 
    u1 tag; /* 8 */
    u2 offset; 
};

union verification_type_info { 
	TopVariableInfo top_info; 
	IntegerVariableInfo integer_info;
	FloatVariableInfo float_info; 
	LongVariableInfo long_info; 
	DoubleVariableInfo double_info;
	NullVariableInfo null_info; 
	UninitializedThisVariableInfo uninit_this_info;
	ObjectVariableInfo object_info;
	UninitializedVariableInfo uninit_info; 
};

struct SameFrame {
	u1 frame_type; /* 0-63 */ 
};

struct SameLocals1StackItemFrame { 
	u1 frame_type;/* 64-127 */ 
	verification_type_info stack[1]; 
};

struct SameLocals1StackItemFrameExtended {
	u1 frame_type;/* 247 */ 
	u2 offset_delta; 
  verification_type_info stack[1]; 
};

struct ChopFrame { 
	u1 frame_type;/* 248-250 */ 
  u2 offset_delta; 
};

struct SameFrameExtended { 
	u1 frame_type; /* 251 */
	u2 offset_delta;
};

struct AppendFrame { 
	u1 frame_type; /* 252-254 */
	u2 offset_delta; 
	verification_type_info * locals;// locals[frame_type - 251]; 
};

union stack_map_frame { 
	SameFrame same_frame;
	SameLocals1StackItemFrame same_locals_1_stack_item_frame;
	SameLocals1StackItemFrameExtended same_locals_1_stack_item_frame_extended;
	ChopFrame chop_frame;
	SameFrameExtended same_frame_extended;
	AppendFrame append_frame;
	//full_frame; 
};

struct StackMapTableAttribute { 
	u2 attribute_name_index; 
	u4 attribute_length; 
	u2 number_of_entries; 
	stack_map_frame* entries; // entries[number_of_entries];
};

struct ExceptionsAttribute {
	u2 attribute_name_index; 
	u4 attribute_length; 
	u2 number_of_exceptions; 
	u2* exception_index_table;// exception_index_table[number_of_exceptions]; 
};


struct InnerClassesAttribute {
	u2 attribute_name_index; 
	u4 attribute_length;
	u2 number_of_classes;
	union{ 
    u2 inner_class_info_index; 
    u2 outer_class_info_index;
    u2 inner_name_index; 
    u2 inner_class_access_flags;
	}* classes;// classes[number_of_classes];
};

struct EnclosingMethodAttribute { 
	u2 attribute_name_index;
	u4 attribute_length;
	u2 class_index;
  u2 method_index;
};

struct SyntheticAttribute {
	u2 attribute_name_index;
	u4 attribute_length;
};

struct SignatureAttribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 signature_index; 
};

struct SourceFileAttribute { 
	u2 attribute_name_index; 
	u4 attribute_length; 
	u2 sourcefile_index; 
};

struct SourceDebugExtensionAttribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u1* debug_extension;// debug_extension[attribute_length];
};

struct LineNumberTableAttribute {
	u2 attribute_name_index; 
  u4 attribute_length; 
	u2 line_number_table_length; 
	union{
		u2 start_pc; 
	  u2 line_number;
	}* line_number_table;//line_number_table[line_number_table_length]; 
};

struct LocalVariableTableAttribute { 
	u2 attribute_name_index; 
	u4 attribute_length;
	u2 local_variable_table_length; 
	union{
		u2 start_pc;
		u2 length;
		u2 name_index;
		u2 descriptor_index;u2 index; 
    }* local_variable_table;//local_variable_table[local_variable_table_length];
};

struct LocalVariableTypeTableAttribute { 
	u2 attribute_name_index;
	u4 attribute_length;
	u2 local_variable_type_table_length;
	union{ 
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 signature_index; 
    u2 index;
	}*local_variable_type_table;//local_variable_type_table[local_variable_type_table_length];
};

struct DeprecatedAttribute {
	u2 attribute_name_index;
	u4 attribute_length;
};

struct annotation;
struct element_value { 
	u1 tag;
	union {
		u2 const_value_index;
		union{
			u2 type_name_index;
			u2 const_name_index; 
		}enum_const_value;
		u2 class_info_index; 
		annotation* annotation_value; //trick
		union{ 
			u2 num_values;
			element_value* values;// values[num_values]; 
		} array_value;
	}value;
};

struct annotation { 
	u2 type_index; 
	u2 num_element_value_pairs; 
	union { 
		u2 element_name_index;
		element_value value;
	}* element_value_pairs;// element_value_pairs[num_element_value_pairs]; 
};


struct RuntimeVisibleAnnotationsAttribute { 
	u2 attribute_name_index; 
	u4 attribute_length;
	u2 num_annotations;
	annotation* annotations;// annotations[num_annotations];
};

struct RuntimeInvisibleAnnotationsAttribute {
	u2 attribute_name_index; 
	u4 attribute_length; 
	u2 num_annotations; 
	annotation* annotations;// annotations[num_annotations];
};

struct RuntimeVisibleParameterAnnotationsAttribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 num_parameters; 
	union{ 
		u2 num_annotations; 
	  annotation* annotations;// annotations[num_annotations];
	}*parameter_annotations;// parameter_annotations[num_parameters];
};

struct RuntimeInvisibleParameterAnnotationsAttribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 num_parameters; 
	union{ 
		u2 num_annotations; 
		annotation*annotations;// annotations[num_annotations];
	}*parameter_annotations;//parameter_annotations[num_parameters];
};

struct AnnotationDefaultAttribute { 
	u2 attribute_name_index;
	u4 attribute_length;
	element_value default_value; 
};

struct BootstrapMethodsAttribute { 
	u2 attribute_name_index;
	u4 attribute_length;
	u2 num_bootstrap_methods; 
	union{
      u2 bootstrap_method_ref;
	    u2 num_bootstrap_arguments; 
	    u2* bootstrap_arguments;// bootstrap_arguments[num_bootstrap_arguments];
	}*bootstrap_methods;// bootstrap_methods[num_bootstrap_methods];
};

struct ClassFileInfo{
	u4 magic;
	u2 minor_version;
	u2 major_version; 
	u2 constant_pool_count; 
	const_pool_info* constant_pool;// constant_pool[constant_pool_count-1]; 
	u2 access_flags; 
	u2 this_class; 
	u2 super_class; 
	u2 interfaces_count; 
	u2* interfaces;//interfaces[interfaces_count]; 
	u2 fields_count; 
	field_info* fields;// fields[fields_count]; 
	u2 methods_count; 
	method_info *methods;// methods[methods_count]; 
	u2 attributes_count; 
	attribute_info * attributes; //attributes[attributes_count];
};


#endif