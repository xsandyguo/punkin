
#include <memory> 
#include <stdlib.h>

#include "class_file_reader.hpp"


ClassFileReader::ClassFileReader(byte* code, int count){
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

void ClassFileReader::ReadFile(const char* path,ClassFileInfo* classFileInfo){
    classFileInfo_ = classFileInfo;

    file_ = fopen(path, "rb");
    fileBuffer_ = new char[CLASS_FILE_MAX_SIZE];
    size_t length = fread(fileBuffer_, 1, CLASS_FILE_MAX_SIZE, file_);

    fileStream_ = new ClassFileStream(fileBuffer_, length, NULL);
    classFileInfo_ = new ClassFileInfo();

    classFileInfo_->magic = fileStream_->get_u4();
    classFileInfo_->minor_version = fileStream_->get_u2();
    classFileInfo_->major_version = fileStream_->get_u2();

    ReadConstPool();

    classFileInfo_->access_flags = fileStream_->get_u2();
    classFileInfo_->this_class = fileStream_->get_u2();
    classFileInfo_->super_class = fileStream_->get_u2();

    ReadInterface();
    ReadField();
    ReadMethod();
    ReadAttribute(); 
}

void ClassFileReader::ReadConstPool(){
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

void ClassFileReader::ReadInterface(){
    classFileInfo_->interfaces_count = fileStream_->get_u2();

    if(classFileInfo_->interfaces_count <= 0){
        return;
    }

    u2* interfaces = new u2[classFileInfo_->interfaces_count];
    fileStream_->get_u1((u1*)interfaces, classFileInfo_->interfaces_count * 2);
    classFileInfo_->interfaces = interfaces; 
}


u1 ClassFileReader::ResolveAttributeType(u2 nameIndex){
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


VerificationTypeInfo** ClassFileReader::ReadVerificationTypeInfo(int count){
    if(count <= 0){
        return NULL;
    }

    VerificationTypeInfo** ret = new VerificationTypeInfo*[count];
    for(int i = 0; i < count ; ++i){
        u1 type = fileStream_->get_u1();
        VerificationTypeInfo* info = NULL;

        switch(type){
        case STACK_MAP_FRAME_VARIFY_TYPE_TOP        :
            { info = new TopVariableInfo();}
            break;
        case STACK_MAP_FRAME_VARIFY_TYPE_INTEGER    :
            {info = new IntegerVariableInfo();} 
            break;
        case STACK_MAP_FRAME_VARIFY_TYPE_FLOAT      :
            {info = new FloatVariableInfo();}
            break;
        case STACK_MAP_FRAME_VARIFY_TYPE_LONG       :
            {info = new LongVariableInfo();}
            break;
        case STACK_MAP_FRAME_VARIFY_TYPE_DOUBLE     :
            {info = new DoubleVariableInfo();}
            break;
        case STACK_MAP_FRAME_VARIFY_TYPE_NULL       :
            {info = new NullVariableInfo();}
            break;
        case STACK_MAP_FRAME_VARIFY_TYPE_UNINIT_THIS:
            {info = new UninitializedThisVariableInfo();}
            break;
        case STACK_MAP_FRAME_VARIFY_TYPE_OBJECT     :
            {
                ObjectVariableInfo* o = new ObjectVariableInfo();
                o->cpool_index = fileStream_->get_u2();
                info = 0;
            } 
            break;
        case STACK_MAP_FRAME_VARIFY_TYPE_UNINIT     :
            {
                UninitializedVariableInfo* o = new UninitializedVariableInfo();
                o->offset = fileStream_->get_u2();
                info = o;
            }
            break;
        }

        ret[i] = info; 
    }

    return ret;
}


ParameterAnnotation* ClassFileReader::ReadParamAnnotation(int count){
    if(count <= 0){
        return NULL;
    }

    ParameterAnnotation* paramAnnos = new ParameterAnnotation[count];

    for(int i = 0; i < count; ++i){
        ParameterAnnotation& anno = paramAnnos[i];
        anno.num_annotations = fileStream_->get_u2();
        anno.annotations = ReadAnnotation(anno.num_annotations);
    }

    return paramAnnos;
}

Annotation** ClassFileReader::ReadAnnotation(int count){
    if(count <= 0){
        return NULL;
    }

    Annotation** annotations = new Annotation*[count]; 
    for(int i = 0; i < count ; ++i){
        annotations[i] = ReadAnnotationItem();
    }

    return annotations;

}

Annotation* ClassFileReader::ReadAnnotationItem(){
    Annotation* ann = new Annotation();
    ann->type_index = fileStream_->get_u2();
    ann->num_element_value_pairs = fileStream_->get_u2();

    Annotation::Pair* pairs = new Annotation::Pair[ann->num_element_value_pairs];
    for(int i =0; i < ann->num_element_value_pairs;++i){
        Annotation::Pair& pair = pairs[i];
        pair.element_name_index = fileStream_->get_u2();
        pair.value = ReadElementValue();
    }

    return ann;
}

ElementValue* ClassFileReader::ReadElementValue(){
    ElementValue* e = new ElementValue();
    e->tag = fileStream_->get_u1();

    switch(e->tag){
    case ELEMENT_VALUE_TAG_BYTE      :   
    case ELEMENT_VALUE_TAG_CHAR      :  
    case ELEMENT_VALUE_TAG_DOUBLE    : 
    case ELEMENT_VALUE_TAG_FLOAT     : 
    case ELEMENT_VALUE_TAG_INT       : 
    case ELEMENT_VALUE_TAG_LONG      :  
    case ELEMENT_VALUE_TAG_SHORT     :  
    case ELEMENT_VALUE_TAG_BOOL      : 
    case ELEMENT_VALUE_TAG_STRING		 :
        {
            e->value.const_value_index = fileStream_->get_u2();
        }
        break;
    case ELEMENT_VALUE_TAG_ENUM_CONST: 
        {
            e->value.enum_const_value.type_name_index = fileStream_->get_u2();
            e->value.enum_const_value.const_name_index = fileStream_->get_u2();
        }                 
        break;
    case ELEMENT_VALUE_TAG_CLASS			: 
        {
            e->value.class_info_index = fileStream_->get_u2();
        }
        break;
    case ELEMENT_VALUE_TAG_ANNO_TYPE	: 
        {
            e->value.annotation_value = ReadAnnotationItem();
        }
        break;
    case ELEMENT_VALUE_TAG_ARRAY			: 
        {
            u2 num = fileStream_->get_u2();
            for(int i =0; i < num;++i){
                e->value.array_value.values[i]= ReadElementValue();
            }
            e->value.array_value.num_values = num;
        }
        break;
    case ELEMENT_VALUE_TAG_REF       : 
        {
            throw "unsupported";
        }
        break;
    }

    return e;
}

void ClassFileReader::ReadField(){
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
            field->attributes = ReadAttribute( field->attributes_count);
        } 

        classFileInfo_->fields[i] = field;
    } 
}

void ClassFileReader::ReadMethod(){
    classFileInfo_->methods_count = fileStream_->get_u2();
    if(classFileInfo_->methods_count <= 0){
        return;
    }

    classFileInfo_->methods = new MethodInfo*[classFileInfo_->methods_count];
    for(int i = 0; i < classFileInfo_->methods_count; ++i){
        MethodInfo * method = new MethodInfo();
        method->access_flags = fileStream_->get_u2();
        method->name_index = fileStream_->get_u2();
        method->descriptor_index = fileStream_->get_u2();
        method->attributes_count = fileStream_->get_u2();

        if(method->attributes_count > 0){
            method->attributes = ReadAttribute(method->attributes_count);
        }

        classFileInfo_->methods[i] = method;
    }
}

AttributeInfo** ClassFileReader::ReadAttribute(int count){
    if(count <= 0){
        return NULL;
    }

    AttributeInfo** attrs = new AttributeInfo*[count];
    for(int i = 0; i < count; ++i){
        attrs[i] = ReadAttributeItem();
    }

    return attrs;
}

void ClassFileReader::ReadAttribute(){
    classFileInfo_->attributes_count = fileStream_->get_u2();
    if(classFileInfo_->attributes_count <= 0 ){
        return;
    }

    classFileInfo_->attributes = ReadAttribute(classFileInfo_->attributes_count);
}


AttributeInfo* ClassFileReader::ReadAttributeItem(){
    u2 nameIndex = fileStream_->get_u2();
    u1 type = ResolveAttributeType(nameIndex);
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
    case ATTRIBUTE_TYPE_CODE                                   :
        {
            CodeAttribute* info = new CodeAttribute();
            info->max_stack = fileStream_->get_u2();
            info->max_locals = fileStream_->get_u2();
            info->code_length = fileStream_->get_u4();

            u1* code = new u1[info->code_length];
            fileStream_->get_u1(code, info->code_length);
            info->code = code;

            info->exception_table_length = fileStream_->get_u2();
            CodeAttribute::ExceptionTable* table =
                new CodeAttribute::ExceptionTable[info->exception_table_length];
            fileStream_->get_u1((u1*)table, 
                info->exception_table_length * sizeof(CodeAttribute::ExceptionTable));
            info->exception_table = table;

            info->attributes_count = fileStream_->get_u2();
            info->attributes = ReadAttribute(info->attributes_count);
        }
        break;
    case ATTRIBUTE_TYPE_STACK_MAP_TABLE                        :
        {
            StackMapTableAttribute* info = new StackMapTableAttribute();
            info->number_of_entries = fileStream_->get_u2();
            StackMapFrame** entries = new StackMapFrame*[info->number_of_entries];
            for(int i = 0; i < info->number_of_entries; ++i){
                StackMapFrame* frame  = NULL;
                u1 type = fileStream_->get_u1();

                if(type <= STACK_MAP_FRAME_TYPE_SAME_END){
                    frame = new SameFrame();
                }else if(type >= STACK_MAP_FRAME_TYPE_SAME_LOCALS_1_STACK_ITEM_START
                    && type <= STACK_MAP_FRAME_TYPE_SAME_LOCALS_1_STACK_ITEM_END){
                        SameLocals1StackItemFrame* f = new SameLocals1StackItemFrame();
                        f->stack = ReadVerificationTypeInfo(1);
                        frame = f;
                }else if(type == STACK_MAP_FRAME_TYPE_SAME_LOCALS_1_STACK_ITEM_EXTENDED){
                    SameLocals1StackItemFrameExtended* f = new SameLocals1StackItemFrameExtended();
                    f->offset_delta = fileStream_->get_u2();
                    f->stack = ReadVerificationTypeInfo(1);
                    frame = f;
                }else if(type >= STACK_MAP_FRAME_TYPE_CHOP_BEGIN
                    && type <= STACK_MAP_FRAME_TYPE_CHOP_END){
                        ChopFrame* f = new ChopFrame();
                        f->offset_delta = fileStream_->get_u2();
                        frame = f;
                }else if(type == STACK_MAP_FRAME_TYPE_SAME_FRAME_EXTENDED){
                    SameFrameExtended* f = new SameFrameExtended();
                    f->offset_delta = fileStream_->get_u2();
                    frame = f;
                }else if(type >= STACK_MAP_FRAME_TYPE_APPEND_BEGIN
                    && type <= STACK_MAP_FRAME_TYPE_APPEND_END){
                        AppendFrame* f = new AppendFrame();
                        f->offset_delta = fileStream_->get_u2();
                        f->locals = ReadVerificationTypeInfo(type - 251);
                        frame =f ;
                }else if(type == STACK_MAP_FRAME_TYPE_FULL){
                    FullFrame* f = new FullFrame();
                    f->offset_delta = fileStream_->get_u2();
                    f->number_of_locals = fileStream_->get_u2();
                    f->locals = ReadVerificationTypeInfo(f->number_of_locals);
                    f->number_of_stack_items = fileStream_->get_u2();
                    f->stack = ReadVerificationTypeInfo(f->number_of_stack_items);
                    frame = f;
                }

                frame->frame_type = type;
                entries[i] = frame ;
            }
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
            InnerClassesAttribute* info = new InnerClassesAttribute();
            info->number_of_classes = fileStream_->get_u2();
            InnerClassesAttribute::Item* classes = 
                new InnerClassesAttribute::Item[info->number_of_classes];
            fileStream_->get_u1((u1*)classes, 
                info->number_of_classes * sizeof(InnerClassesAttribute::Item));
            info->classes = classes;
            attr = info;
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
            SourceDebugExtensionAttribute* info = new SourceDebugExtensionAttribute();
            u1* ext = new u1[length];
            fileStream_->get_u1(ext, length);
            info->debug_extension = ext;
        }
        break;
    case ATTRIBUTE_TYPE_LINE_NUMBER_TABLE                      :
        {
            LineNumberTableAttribute* info  = new LineNumberTableAttribute();
            info->line_number_table_length = fileStream_->get_u2();
            LineNumberTableAttribute::Item * table = 
                new LineNumberTableAttribute::Item[info->line_number_table_length];
            fileStream_->get_u1((u1*)table, 
                info->line_number_table_length * sizeof(LineNumberTableAttribute::Item));
            info->line_number_table = table;
            attr = info;
        }
        break;
    case ATTRIBUTE_TYPE_LOCAL_VARIABLE_TABLE                   :
        {
            LocalVariableTableAttribute* info = new LocalVariableTableAttribute();
            info->local_variable_table_length = fileStream_->get_u2();
            LocalVariableTableAttribute::Item* table = 
                new LocalVariableTableAttribute::Item[info->local_variable_table_length];
            fileStream_->get_u1((u1*)table,
                info->local_variable_table_length * sizeof(LocalVariableTableAttribute::Item));
            info->local_variable_table = table;
            attr = info;
        }
        break;
    case ATTRIBUTE_TYPE_LOCAL_VARIABLE_TYPE_TABLE              :
        {
            LocalVariableTypeTableAttribute* info = new LocalVariableTypeTableAttribute();
            info->local_variable_type_table_length = fileStream_->get_u2();
            LocalVariableTypeTableAttribute::Item* table =
                new LocalVariableTypeTableAttribute::Item[info->local_variable_type_table_length];
            fileStream_->get_u1((u1*)table, 
                info->local_variable_type_table_length * sizeof(LocalVariableTypeTableAttribute::Item));
            info->local_variable_type_table = table;
            attr = info;
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
            RuntimeVisibleAnnotationsAttribute* info = new RuntimeVisibleAnnotationsAttribute();
            info->num_annotations = fileStream_->get_u2();
            info->annotations = ReadAnnotation(info->num_annotations);
        }
        break;
    case ATTRIBUTE_TYPE_RUNTIME_INVISIBLE_ANNOTATIONS          :
        {
            RuntimeInvisibleAnnotationsAttribute* info = new RuntimeInvisibleAnnotationsAttribute();
            info->num_annotations = fileStream_->get_u2();
            info->annotations = ReadAnnotation(info->num_annotations);
        }
        break;
    case ATTRIBUTE_TYPE_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS  :
        {
            RuntimeVisibleParameterAnnotationsAttribute* info = new RuntimeVisibleParameterAnnotationsAttribute();
            info->num_parameters = fileStream_->get_u2();
            info->parameter_annotations = ReadParamAnnotation(info->num_parameters);
            attr = info;
        }
        break;
    case ATTRIBUTE_TYPE_RUNTIME_INVISIBLE_PARAMETER_ANNTATIONS :
        {
            RuntimeInvisibleParameterAnnotationsAttribute* info = new RuntimeInvisibleParameterAnnotationsAttribute();
            info->num_parameters = fileStream_->get_u2();
            info->parameter_annotations = ReadParamAnnotation(info->num_parameters);
            attr = info;
        }
        break;
    case ATTRIBUTE_TYPE_ANNOTATION_DEFAULT                     :
        {
            AnnotationDefaultAttribute* info = new AnnotationDefaultAttribute(); 

            attr = info;
        }
        break;
    case ATTRIBUTE_TYPE_BOOTSTRAP_METHODS                      :
        {
            BootstrapMethodsAttribute* info = new BootstrapMethodsAttribute();
            info->num_bootstrap_methods = fileStream_->get_u2();
            BootstrapMethodsAttribute::Item* items =
                new BootstrapMethodsAttribute::Item[info->num_bootstrap_methods];

            for(int i = 0; i < info->num_bootstrap_methods; ++i){
                BootstrapMethodsAttribute::Item& item = items[i];
                item.bootstrap_method_ref = fileStream_->get_u2();
                item.num_bootstrap_arguments = fileStream_->get_u2();
                u2* args  = new u2[item.num_bootstrap_arguments];
                fileStream_->get_u1((u1*)args, item.num_bootstrap_arguments * 2);
                item.bootstrap_arguments = args;
            }
        }
        break;
    }

    attr->attribute_length = length;
    attr->attribute_name_index = nameIndex; 
    attr->type = type;

    return attr;
    
}
