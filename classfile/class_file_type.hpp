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


struct CONSTANT_Class_info { 
	u1 tag;
	u2 name_index; 
};

struct CONSTANT_Fieldref_info { 
	u1 tag; 
	u2 class_index; 
	u2 name_and_type_index; 
};

struct CONSTANT_Methodref_info { 
	u1 tag;
	u2 class_index;
	u2 name_and_type_index; 
};

struct CONSTANT_InterfaceMethodref_info { 
	u1 tag; 
	u2 class_index; 
	u2 name_and_type_index; 
};

struct CONSTANT_String_info {
	u1 tag;
	u2 string_index; 
};

struct CONSTANT_Integer_info {
	u1 tag; 
	u4 bytes; 
};

struct CONSTANT_Float_info {
	u1 tag; 
	u4 bytes;
};

struct CONSTANT_Long_info {
	u1 tag;
	u4 high_bytes;
	u4 low_bytes;
};

struct CONSTANT_Double_info {
	u1 tag; 
	u4 high_bytes; 
	u4 low_bytes; 
};

struct CONSTANT_NameAndType_info {
	u1 tag;
	u2 name_index; 
	u2 descriptor_index; 
};

struct CONSTANT_Utf8_info {
	u1 tag; 
	u2 length; 
	u1* bytes; //u1[length] 
};

struct CONSTANT_MethodHandle_info {
	u1 tag; 
	u1 reference_kind; 
	u2 reference_index;
};

struct CONSTANT_MethodType_info {
	u1 tag; 
	u2 descriptor_index; 
};

struct CONSTANT_InvokeDynamic_info {
	u1 tag; 
	u2 bootstrap_method_attr_index; 
	u2 name_and_type_index; 
};


struct attribute_info{
	u2 attribute_name_index;
	u4 attribute_length;
	u1* info;//u1[attribute_length]
};

struct method_info{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index; 
	u2 attributes_count;
	attribute_info* attributes; //attribute_info[arrtribute_count]
};

struct cp_info{
	u1 tag; 
	u1* info;
};

struct field_info{
	u2 access_flags; 
	u2 name_index; 
	u2 descriptor_index; 
	u2 attributes_count; 
	attribute_info* attributes;//attribute_info[arrtribute_count]
};


struct ConstantValue_attribute { 
	u2 attribute_name_index;
	u4 attribute_length; 
	u2 constantvalue_index; 
};

struct Code_attribute {
	u2 attribute_name_index;
	u4 attribute_length; 
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1* code;//code[code_length];
	u2 exception_table_length; 
	{
	u2 start_pc;
	u2 end_pc; 
	u2 handler_pc;
	u2 catch_type;
	};

	exception_table[exception_table_length];
	u2 attributes_count; 
	attribute_info attributes[attributes_count];
};

struct same_frame {
	u1 frame_type = SAME; /* 0-63 */ 
};

struct same_locals_1_stack_item_frame { 
	u1 frame_type = SAME_LOCALS_1_STACK_ITEM;/* 64-127 */ 
	verification_type_info stack[1]; 
};

struct same_locals_1_stack_item_frame_extended {
	u1 frame_type = SAME_LOCALS_1_STACK_ITEM_EXTENDED;/* 247 */ 
	u2 offset_delta; verification_type_info stack[1]; 
};

struct chop_frame { 
	u1 frame_type = CHOP;
	/* 248-250 */ u2 offset_delta; 
};

struct same_frame_extended { 
	u1 frame_type = SAME_FRAME_EXTENDED; /* 251 */
	u2 offset_delta;
};


union verification_type_info { 
	Top_variable_info; 
	Integer_variable_info;
	Float_variable_info; 
	Long_variable_info; 
	Double_variable_info;
	Null_variable_info; 
	UninitializedThis_variable_info;
	Object_variable_info;
	Uninitialized_variable_info; 
};

struct Top_variable_info { u1 tag = ITEM_Top; /* 0 */ };
struct Integer_variable_info { u1 tag = ITEM_Integer; /* 1 */ };
struct Float_variable_info { u1 tag = ITEM_Float; /* 2 */ };
struct Long_variable_info { u1 tag = ITEM_Long; /* 4 */ };
struct Double_variable_info { u1 tag = ITEM_Double; /* 3 */ };
struct Null_variable_info { u1 tag = ITEM_Null; /* 5 */ };
struct UninitializedThis_variable_info { u1 tag = ITEM_UninitializedThis; /* 6 */ };
struct Object_variable_info { u1 tag = ITEM_Object; /* 7 */ u2 cpool_index; };;
struct Uninitialized_variable_info { u1 tag = ITEM_Uninitialized /* 8 */ u2 offset; };

struct append_frame { 
	u1 frame_type = APPEND; /* 252-254 */
	u2 offset_delta; 
	verification_type_info locals[frame_type - 251]; 
};

union stack_map_frame { 
	same_frame;
	same_locals_1_stack_item_frame;
	same_locals_1_stack_item_frame_extended;
	chop_frame;
	same_frame_extended;
	append_frame;
	full_frame; 
};

struct StackMapTable_attribute { 
	u2 attribute_name_index; 
	u4 attribute_length; 
	u2 number_of_entries; 
	stack_map_frame entries[number_of_entries];
};

struct Exceptions_attribute {
	u2 attribute_name_index; 
	u4 attribute_length; 
	u2 number_of_exceptions; 
	u2 exception_index_table[number_of_exceptions]; 
};


struct InnerClasses_attribute {
	u2 attribute_name_index; 
	u4 attribute_length;
	u2 number_of_classes;
	{ 
		u2 inner_class_info_index; 
	u2 outer_class_info_index;
	u2 inner_name_index; 
	u2 inner_class_access_flags;
	} 
	classes[number_of_classes];
};

struct EnclosingMethod_attribute { 
	u2 attribute_name_index;
	u4 attribute_length;
	u2 class_index u2 method_index;
};

struct Synthetic_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
};

struct Signature_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u2 signature_index; 
};

struct SourceFile_attribute { 
	u2 attribute_name_index; 
	u4 attribute_length; 
	u2 sourcefile_index; 
};

struct SourceDebugExtension_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 debug_extension[attribute_length];
};

struct LineNumberTable_attribute {
	u2 attribute_name_index; u4 attribute_length; 
	u2 line_number_table_length; 
	{
		u2 start_pc; 
	u2 line_number;
	}
	line_number_table[line_number_table_length]; 
};

struct LocalVariableTable_attribute { 
	u2 attribute_name_index; 
	u4 attribute_length;
	u2 local_variable_table_length; 
	{
		u2 start_pc;
		u2 length;
		u2 name_index;
		u2 descriptor_index;u2 index; 
} 
	local_variable_table[local_variable_table_length];
};

struct LocalVariableTypeTable_attribute { 
	u2 attribute_name_index;
	u4 attribute_length;
	u2 local_variable_type_table_length;
	{ 
		u2 start_pc;
	u2 length;
	u2 name_index;
	u2 signature_index; 
	u2 index;
	}

	local_variable_type_table[local_variable_type_table_length];
};

struct Deprecated_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
};

struct element_value { 
	u1 tag;
	union {
		u2 const_value_index;
		{
			u2 type_name_index;
			u2 const_name_index; 
		} 
		enum_const_value;
		u2 class_info_index; 
		annotation annotation_value; 
		{ 
			u2 num_values;
			element_value values[num_values]; 
		} array_value;
	}value;
};

struct annotation { 
	u2 type_index; 
	u2 num_element_value_pairs; 
	union { 
		u2 element_name_index;
		element_value value;
	}
	element_value_pairs[num_element_value_pairs]; 
};


struct RuntimeVisibleAnnotations_attribute { 
	u2 attribute_name_index; 
	u4 attribute_length;
	u2 num_annotations;
	annotation annotations[num_annotations];
};

struct RuntimeInvisibleAnnotations_attribute {
	u2 attribute_name_index; 
	u4 attribute_length; 
	u2 num_annotations; 
	annotation annotations[num_annotations];
};

struct RuntimeVisibleParameterAnnotations_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 num_parameters; 
	{ 
		u2 num_annotations; 
	annotation annotations[num_annotations];
	} parameter_annotations[num_parameters];
};

struct RuntimeInvisibleParameterAnnotations_attribute {
	u2 attribute_name_index;
	u4 attribute_length;
	u1 num_parameters; 
	{ 
		u2 num_annotations; 
		annotation annotations[num_annotations];
	}
	parameter_annotations[num_parameters];
};

struct AnnotationDefault_attribute { 
	u2 attribute_name_index;
	u4 attribute_length;
	element_value default_value; 
};

struct BootstrapMethods_attribute { 
	u2 attribute_name_index;
	u4 attribute_length;
	u2 num_bootstrap_methods; 
	union{ u2 bootstrap_method_ref;
	u2 num_bootstrap_arguments; 
	u2 bootstrap_arguments[num_bootstrap_arguments];
	} bootstrap_methods[num_bootstrap_methods];
};

struct ClassFileMeta{
	u4 magic;
	u2 minor_version;
	u2 major_version; 
	u2 constant_pool_count; 
	cp_info constant_pool[constant_pool_count-1]; 
	u2 access_flags; 
	u2 this_class; 
	u2 super_class; 
	u2 interfaces_count; 
	u2 interfaces[interfaces_count]; 
	u2 fields_count; 
	field_info fields[fields_count]; 
	u2 methods_count; 
	method_info methods[methods_count]; 
	u2 attributes_count; 
	attribute_info attributes[attributes_count];
};


#endif