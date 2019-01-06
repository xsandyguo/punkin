
#include <memory> 
#include <stdlib.h>

#include "class_file_reader.hpp"


ClassFileReader::ClassFileReader(){
    this->fileBuffer_ = NULL;
    this->classFileInfo_ = NULL;
    this->file_ = NULL;
    this->fileStream_ = NULL;
}

ClassFileReader::~ClassFileReader(){
    delete fileBuffer_;
    delete fileStream_; 

    fclose(file_);
}

void ClassFileReader::readFile(const char* path,ClassFileInfo* classFileInfo){
    classFileInfo_ = classFileInfo;

    file_ = fopen(path, "rb");
    fileBuffer_ = new char[CLASS_FILE_MAX_SIZE];
    size_t length = fread(fileBuffer_, 1, CLASS_FILE_MAX_SIZE, file_);

    fileStream_ = new ClassFileStream(fileBuffer_, length, NULL);
    classFileInfo_ = new ClassFileInfo();

    classFileInfo_->magic = fileStream_->get_u4();
    classFileInfo_->minor_version = fileStream_->get_u2();
    classFileInfo_->major_version = fileStream_->get_u2();

    readConstPool();

    classFileInfo_->access_flags = fileStream_->get_u2();
    classFileInfo_->this_class = fileStream_->get_u2();
    classFileInfo_->super_class = fileStream_->get_u2();

    readInterface();
    readField();
    readMethod();
    readAttribute(); 
}

void ClassFileReader::readConstPool(){
    classFileInfo_->constant_pool_count = fileStream_->get_u2();

    if(classFileInfo_->constant_pool_count <= 0){
        return;
    }

    classFileInfo_->constant_pool = new ConstPoolInfo*[classFileInfo_->constant_pool_count];
    int count = classFileInfo_->constant_pool_count - 1;

    for(int i = 0; i < count; ++i){
        u1 constType = fileStream_->get_u1(); 
        ConstPoolInfo* constPoolInfo = NULL;
        switch(constType){
        case CONSTANT_POOL_TYPE_CLASS:
            {
                ConstPoolClassInfo* info = new ConstPoolClassInfo(); 
                info->name_index = fileStream_->get_u2();
                constPoolInfo = info;
            }
            break; 
        case CONSTANT_POOL_TYPE_FIELD_REF            :   
            {
                ConstPoolFieldRefInfo* info = new ConstPoolFieldRefInfo();
                info->class_index = fileStream_->get_u2();
                info->name_and_type_index = fileStream_->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_METHOD_REF           :
            {
                ConstPoolMethodRefInfo* info = new ConstPoolMethodRefInfo(); 
                info->class_index = fileStream_->get_u2();
                info->name_and_type_index = fileStream_->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_INTERFACE_METHOD_REF :
            {
                ConstPoolInterfaceMethodRefInfo* info = new ConstPoolInterfaceMethodRefInfo(); 
                info->class_index = fileStream_->get_u2();
                info->name_and_type_index = fileStream_->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_STRING               :
            {
                ConstPoolStringInfo* info = new ConstPoolStringInfo();
                info->string_index = fileStream_->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_INTERGER             :
            {
                ConstPoolIntegerInfo* info = new ConstPoolIntegerInfo();
                info->bytes = fileStream_->get_u4();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_FLOAT                :
            {
                ConstPoolFloatInfo* info = new ConstPoolFloatInfo();
                info->bytes = fileStream_->get_u4();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_LONG                 :
            {
                ConstPoolLongInfo* info = new ConstPoolLongInfo();
                info->high_bytes = fileStream_->get_u4();
                info->low_bytes = fileStream_->get_u4();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_DOUBLE               :
            {
                ConstPoolDoubleInfo* info = new ConstPoolDoubleInfo();
                info->high_bytes = fileStream_->get_u4();
                info->low_bytes = fileStream_->get_u4();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_NAME_AND_TYPE        :
            {
                ConstPoolNameAndTypeInfo* info = new ConstPoolNameAndTypeInfo();
                info->name_index = fileStream_->get_u2();
                info->descriptor_index = fileStream_->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_UTF8                 :
            {
                ConstPoolUtf8Info* info = new ConstPoolUtf8Info();
                info->length = fileStream_->get_u2();
                info->bytes = new u1[info->length + 1];
                memset(info->bytes, 0, info->length + 1);
                fileStream_->get_u1(info->bytes, info->length);
                constPoolInfo = info;

                printf("%s\n", info->bytes);
            }
            break;
        case CONSTANT_POOL_TYPE_METHOD_HANDLE        :
            {
                ConstPoolMethodHandleInfo* info = new ConstPoolMethodHandleInfo();
                info->reference_kind = fileStream_->get_u1();
                info->reference_index = fileStream_->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_METHOD_TYPE          :
            {
                ConstPoolMethodTypeInfo* info = new ConstPoolMethodTypeInfo();
                info->descriptor_index = fileStream_->get_u2();
                constPoolInfo = info;
            }
            break;
        case CONSTANT_POOL_TYPE_INVOKE_DYNAMIC       :
            {
                ConstPoolInvokeDynamicInfo* info = new ConstPoolInvokeDynamicInfo();
                info->bootstrap_method_attr_index = fileStream_->get_u2();
                info->name_and_type_index = fileStream_->get_u2();
                constPoolInfo = info;
            }
            break;
        default:
            break;
        }

        constPoolInfo->tag = constType;
        classFileInfo_->constant_pool[i] = constPoolInfo; 
    }
}

void ClassFileReader::readInterface(){
    classFileInfo_->interfaces_count = fileStream_->get_u2();

    if(classFileInfo_->interfaces_count <= 0){
        return;
    }

    u2* interfaces = new u2[classFileInfo_->interfaces_count];
    fileStream_->get_u1((u1*)interfaces, classFileInfo_->interfaces_count * 2);
    classFileInfo_->interfaces = interfaces; 
}


u1 ClassFileReader::resolveAttributeType(u2 nameIndex){
    ConstPoolInfo* info = classFileInfo_->constant_pool[nameIndex];
    ConstPoolUtf8Info* utf8Info = (ConstPoolUtf8Info*)info;

    for(int i = 0; i < ATTRIBUTE_TYPE_MAX; ++i){
        const char* name = attribute_type_map[i];
        int ret = strcmp(utf8Info->bytes, name);
        if(!ret){
            return i + 1;
        }
    }

    return 0;
}

void ClassFileReader::readAttributeItem(AttributeInfo** attrs, int count){
    for(int i = 0; i < count; ++i){
        u2 nameIndex = fileStream_->get_u2();
        u1 type = resolveAttributeType(nameIndex);
        u2 length = fileStream_->get_u4();

        if(!type){
        
        }

        AttributeInfo* attr = NULL;

        switch(type){
        case ATTRIBUTE_TYPE_CONSTANT_VALUE                         :
            {
              ConstantValueAttribute* info = new ConstantValueAttribute(); 
              info->constantvalue_index = fileStream_->get_u2();
              attr = info;
            }
            break;
        case ATTRIBUTE_TYPE_STACK_MAP_TABLE                        :
            {
                
            }
            break;
        case ATTRIBUTE_TYPE_EXCEPTION                              :
            { 
              ExceptionsAttribute* info = new ExceptionsAttribute(); 
              info->number_of_exceptions = fileStream_->get_u2();

              u2* table = new u2[info->number_of_exceptions];
              fileStream_->get_u1((u1*)table, info->number_of_exceptions * 2);
              attr = info;
            }
            break;
        case ATTRIBUTE_TYPE_INNER_CLASSES                          :
            {
                 
            }
            break;
        case ATTRIBUTE_TYPE_ENCLOSING_METHOD                       :
            {
                EnclosingMethodAttribute* info = new EnclosingMethodAttribute();
                info->class_index = fileStream_->get_u2();
                info->method_index = fileStream_->get_u2();
                attr = info;
            }
            break;
        case ATTRIBUTE_TYPE_SYNTHETIC                              :
            {
                SyntheticAttribute* info = new SyntheticAttribute();
                attr = info;
            }
            break;
        case ATTRIBUTE_TYPE_SIGNATURE                              :
            {
                SignatureAttribute* info = new SignatureAttribute();
                info->signature_index = fileStream_->get_u2();
                attr = info;
            }
            break;
        case ATTRIBUTE_TYPE_SOURCE_FILE                            :
            {
                SourceFileAttribute* info = new SourceFileAttribute();
                info->sourcefile_index = fileStream_->get_u2();
                attr = info;
            }
            break;
        case ATTRIBUTE_TYPE_SOURCE_DEBUG_EXCEPTION                 :
            {
            }
            break;
        case ATTRIBUTE_TYPE_LINE_NUMBER_TABLE                      :
            {
            }
            break;
        case ATTRIBUTE_TYPE_LOCAL_VARIABLE_TABLE                   :
            {
            }
            break;
        case ATTRIBUTE_TYPE_LOCAL_VARIABLE_TYPE_TABLE              :
            {
            }
            break;
        case ATTRIBUTE_TYPE_DEPRECATED                             :
            {
                DeprecatedAttribute* info = new DeprecatedAttribute();
                attr = info;
            }
            break;
        case ATTRIBUTE_TYPE_RUNTIME_VISIBLE_ANNOTATIONS            :
            {
            }
            break;
        case ATTRIBUTE_TYPE_RUNTIME_INVISIBLE_ANNOTATIONS          :
            {
            }
            break;
        case ATTRIBUTE_TYPE_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS  :
            {
            }
            break;
        case ATTRIBUTE_TYPE_RUNTIME_INVISIBLE_PARAMETER_ANNTATIONS :
            {
            }
            break;
        case ATTRIBUTE_TYPE_ANNOTATION_DEFAULT                     :
            {
            }
            break;
        case ATTRIBUTE_TYPE_BOOTSTRAP_METHODS                      :
            {
                                                                    
            }
            break;
        default:
            break;
        }
         
        attr->attribute_length = length;
        attr->attribute_name_index = nameIndex; 
        attr->type = type;
    }
}

void ClassFileReader::readField(){
    classFileInfo_->fields_count = fileStream_->get_u2();
    if(classFileInfo_->fields_count <= 0){
        return;
    }

    classFileInfo_->fields = new FieldInfo*[classFileInfo_->fields_count];
    for(int i = 0; i < classFileInfo_->fields_count;i++){
        FieldInfo * field = new FieldInfo();
        field->access_flags = fileStream_->get_u2();
        field->name_index = fileStream_->get_u2();
        field->descriptor_index = fileStream_->get_u2();
        field->attributes_count = fileStream_->get_u2();

        if(field->attributes_count > 0){
            AttributeInfo** attrs = new AttributeInfo*[field->attributes_count];
            readAttributeItem(attrs, field->attributes_count);
            field->attributes = attrs;
        } 

        classFileInfo_->fields[i] = field;
    } 
}

void ClassFileReader::readMethod(){
    classFileInfo_->methods_count = fileStream_->get_u2();
    if(classFileInfo_->methods_count <= 0){
        return;
    }

    for(int i = 0; i < classFileInfo_->methods_count; ++i){
        MethodInfo * method = new MethodInfo();
        method->access_flags = fileStream_->get_u2();
        method->name_index = fileStream_->get_u2();
        method->descriptor_index = fileStream_->get_u2();
        method->attributes_count = fileStream_->get_u2();

        if(method->attributes_count > 0){
            AttributeInfo** attrs = new AttributeInfo*[method->attributes_count];
            readAttributeItem(attrs, method->attributes_count);
            method->attributes = attrs;
        }

        classFileInfo_->methods[i] = method;
    }
}

void ClassFileReader::readAttribute(){
    classFileInfo_->attributes_count = fileStream_->get_u2();
    if(classFileInfo_->attributes_count <= 0 ){
        return;
    }

    for(int i = 0; i < classFileInfo_->attributes_count; ++i){

    }
}