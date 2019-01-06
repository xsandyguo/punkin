#ifndef CLASS_FILE_TYPE_HPP
#define CLASS_FILE_TYPE_HPP

#include "utilities/top.hpp"


#define ACC_PUBLIC				0x0001
#define ACC_FINAL				0x0010
#define ACC_SUPER				0x0020
#define ACC_INTERFACE			0x0200
#define ACC_ABSTRACT			0x0400 
#define ACC_SYNTHETIC			0x1000


#define FIELD_INFO_ACC_PUBLIC		0x0001
#define FIELD_INFO_ACC_PRIVATE		0x0002
#define FIELD_INFO_ACC_PROTECTED	0x0004
#define FIELD_INFO_ACC_STATIC		0x0008
#define FIELD_INFO_ACC_FINAL		0x0010
#define FIELD_INFO_ACC_VOLATILE 0x0040
#define FIELD_INFO_ACC_TRANSIENT 0x0080
#define FIELD_INFO_ACC_SYNTHETIC 0x1000 
#define FIELD_INFO_ACC_ENUM 0x4000


#define METHOD_INFO_ACC_PUBLIC 0x0001
#define METHOD_INFO_ACC_PRIVATE 0x0002
#define METHOD_INFO_ACC_PROTECTED 0x0004
#define METHOD_INFO_ACC_STATIC 0x0008
#define METHOD_INFO_ACC_FINAL 0x0010
#define METHOD_INFO_ACC_SYNCHRONIZED 0x0020
#define METHOD_INFO_ACC_BRIDGE 0x0040
#define METHOD_INFO_ACC_VARARGS 0x0080
#define METHOD_INFO_ACC_NATIVE 0x0100
#define METHOD_INFO_ACC_ABSTRACT 0x0400
#define METHOD_INFO_ACC_STRICT 0x0800
#define METHOD_INFO_ACC_SYNTHETIC 0x1000

#define  CONSTANT_Class 7
#define 	CONSTANT_Fieldref 9 
#define 	CONSTANT_Methodref 10 
#define 	CONSTANT_InterfaceMethodref 11 
#define 	CONSTANT_String 8 
#define 	CONSTANT_Integer 3 
#define 	CONSTANT_Float 4 
#define 	CONSTANT_Long 5 
#define 	CONSTANT_Double 6 
#define 	CONSTANT_NameAndType 12 
#define 	CONSTANT_Utf8 1 
#define 	CONSTANT_MethodHandle 15 
#define 	CONSTANT_MethodType 16 
#define 	CONSTANT_InvokeDynamic 18

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
u1 bytes[length]; 
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

struct method_info{
	u2 access_flags;
	u2 name_index;
	u2 descriptor_index; 
	u2 attributes_count;
	attribute_info attributes[attributes_count];
};

struct cp_info{
	u1 tag; 
	u1 info[];
};

struct field_info{
	u2 access_flags; 
	u2 name_index; 
	u2 descriptor_index; 
	u2 attributes_count; 
	attribute_info attributes[attributes_count];
};

struct attribute_info{
	u2 attribute_name_index;
	u4 attribute_length;
	u1 info[attribute_length];
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
	u1 code[code_length];
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