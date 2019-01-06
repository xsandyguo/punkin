// punkin.cpp : Defines the entry point for the console application.
//

#include <memory>
#include <utility>
#include <stdio.h>
#include <stdlib.h>


#include "utilities\top.hpp"
#include "classfile\class_file_stream.hpp"
#include "classfile\class_file_type.hpp"

#define MAX_CLASS_FILE_SIZE  1024*1024*1024


void read_const_pool(ClassFileStream* cfs, ClassFileInfo* classFileInfo){
    classFileInfo->constant_pool_count = cfs->get_u2();

    if(classFileInfo->constant_pool_count <= 0){
        return;
    }

    classFileInfo->constant_pool = new ConstPoolInfo*[classFileInfo->constant_pool_count];
    int count = classFileInfo->constant_pool_count - 1;

    for(int i = 0; i < count; ++i){
        u1 constType = cfs->get_u1(); 
        ConstPoolInfo* constPoolInfo = NULL;
        switch(constType){
        case CONSTANT_POOL_TYPE_CLASS:
            {
                ConstPoolClassInfo* info = new ConstPoolClassInfo(); 
                info->name_index = cfs->get_u2();
                constPoolInfo = info;
            }
            break; 
        case CONSTANT_POOL_TYPE_FIELD_REF            :   
            {
                ConstPoolFieldRefInfo* info = new ConstPoolFieldRefInfo();
                info->class_index = cfs->get_u2();
                info->name_and_type_index = cfs->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_METHOD_REF           :
            {
                ConstPoolMethodRefInfo* info = new ConstPoolMethodRefInfo(); 
                info->class_index = cfs->get_u2();
                info->name_and_type_index = cfs->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_INTERFACE_METHOD_REF :
            {
                ConstPoolInterfaceMethodRefInfo* info = new ConstPoolInterfaceMethodRefInfo(); 
                info->class_index = cfs->get_u2();
                info->name_and_type_index = cfs->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_STRING               :
            {
                ConstPoolStringInfo* info = new ConstPoolStringInfo();
                info->string_index = cfs->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_INTERGER             :
            {
                ConstPoolIntegerInfo* info = new ConstPoolIntegerInfo();
                info->bytes = cfs->get_u4();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_FLOAT                :
            {
                ConstPoolFloatInfo* info = new ConstPoolFloatInfo();
                info->bytes = cfs->get_u4();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_LONG                 :
            {
                ConstPoolLongInfo* info = new ConstPoolLongInfo();
                info->high_bytes = cfs->get_u4();
                info->low_bytes = cfs->get_u4();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_DOUBLE               :
            {
                ConstPoolDoubleInfo* info = new ConstPoolDoubleInfo();
                info->high_bytes = cfs->get_u4();
                info->low_bytes = cfs->get_u4();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_NAME_AND_TYPE        :
            {
                ConstPoolNameAndTypeInfo* info = new ConstPoolNameAndTypeInfo();
                info->name_index = cfs->get_u2();
                info->descriptor_index = cfs->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_UTF8                 :
            {
                ConstPoolUtf8Info* info = new ConstPoolUtf8Info();
                info->length = cfs->get_u2();
                info->bytes = new u1[info->length];
                cfs->get_u1(info->bytes, info->length);
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_METHOD_HANDLE        :
            {
                ConstPoolMethodHandleInfo* info = new ConstPoolMethodHandleInfo();
                info->reference_kind = cfs->get_u1();
                info->reference_index = cfs->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_METHOD_TYPE          :
            {
                ConstPoolMethodTypeInfo* info = new ConstPoolMethodTypeInfo();
                info->descriptor_index = cfs->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_INVOKE_DYNAMIC       :
            {
                ConstPoolInvokeDynamicInfo* info = new ConstPoolInvokeDynamicInfo();
                info->bootstrap_method_attr_index = cfs->get_u2();
                info->name_and_type_index = cfs->get_u2();
                constPoolInfo = info;
            }
            break;
        default:
            break;
        }
        
        constPoolInfo->tag = constType;
        classFileInfo->constant_pool[i] = constPoolInfo; 
    }
}

void read_interface(ClassFileStream* cfs, ClassFileInfo* classFileInfo){
    classFileInfo->interfaces_count = cfs->get_u2();

    if(classFileInfo->interfaces_count <= 0){
        return;
    }

    u2* interfaces = new u2[classFileInfo->interfaces_count];
    cfs->get_u1((u1*)interfaces, classFileInfo->interfaces_count * 2);
    classFileInfo->interfaces = interfaces; 
}

void read_attribute(ClassFileStream* cfs, AttributeInfo** attrs, int count){
    for(int i = 0; i < count; ++i){
        AttributeInfo* attr = new AttributeInfo();
        attr->attribute_name_index = cfs->get_u2();
        attr->attribute_length = cfs->get_u4();
    }
}

void read_field(ClassFileStream* cfs, ClassFileInfo* classFileInfo){
    classFileInfo->fields_count = cfs->get_u2();
    if(classFileInfo->fields_count <= 0){
        return;
    }

    classFileInfo->fields = new FieldInfo*[classFileInfo->fields_count];
    for(int i = 0; i < classFileInfo->fields_count;i++){
        FieldInfo * field = new FieldInfo();
        field->access_flags = cfs->get_u2();
        field->name_index = cfs->get_u2();
        field->descriptor_index = cfs->get_u2();
        field->attributes_count = cfs->get_u2();

        if(field->attributes_count > 0){
            AttributeInfo** attrs = new AttributeInfo*[field->attributes_count];
            read_attribute(cfs, attrs, field->attributes_count);
            field->attributes = attrs;
        } 
    } 
}

void read_method(ClassFileStream* cfs, ClassFileInfo* classFileInfo){
    classFileInfo->methods_count = cfs->get_u2();
    if(classFileInfo->methods_count <= 0){
        return;
    }

    for(int i = 0; i < classFileInfo->methods_count; ++i){
    }

}

void read_attribute(ClassFileStream* cfs, ClassFileInfo* classFileInfo){
    classFileInfo->attributes_count = cfs->get_u2();
    if(classFileInfo->attributes_count <= 0 ){
        return;
    }

    for(int i = 0; i < classFileInfo->attributes_count; ++i){
    
    }
}

int _tmain(int argc, char** argv[])
{
    u1 a;

    FILE * file = fopen("D:\\workspace\\java\\target\\classes\\Main.class", "rb");
    char* buffer = new char[MAX_CLASS_FILE_SIZE];
    size_t length = fread(buffer, 1, MAX_CLASS_FILE_SIZE, file);

    std::auto_ptr<ClassFileStream>cfs (new ClassFileStream(buffer, length, NULL));
    std::auto_ptr<ClassFileInfo> classFileInfo(new ClassFileInfo());

    classFileInfo->magic = cfs->get_u4();
    classFileInfo->minor_version = cfs->get_u2();
    classFileInfo->major_version = cfs->get_u2();
    
    read_const_pool(cfs.get(), classFileInfo.get());

    classFileInfo->access_flags = cfs->get_u2();
    classFileInfo->this_class = cfs->get_u2();
    classFileInfo->super_class = cfs->get_u2();
    
   
    read_interface(cfs.get(), classFileInfo.get());
    read_field(cfs.get(), classFileInfo.get());
    read_method(cfs.get(), classFileInfo.get());
    read_attribute(cfs.get(), classFileInfo.get()); 

    return 0;
}

