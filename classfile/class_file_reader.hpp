#ifndef CLASSFILE_CLASS_FILE_READER_HPP
#define CLASSFILE_CLASS_FILE_READER_HPP

#include <stdio.h>

#include "utilities/top.hpp"
#include "classfile\class_file_stream.hpp"
#include "classfile\class_file_type.hpp"

class ClassFileReader{
public:
    ClassFileReader();
    ~ClassFileReader();
    void readFile(const char* file, ClassFileInfo* classFileInfo);

private:
    void readConstPool();
    void readInterface();

    Annotation** readAnnotation(int count);
    void readField();
    void readMethod();
    void readAttribute();
    AttributeInfo** readAttribute(int count);
    void readAttributeItem(AttributeInfo** attrs, int count);
    
    u1 resolveAttributeType(u2 nameIndex);
    ParameterAnnotation* readParamAnnotation(int count);
    VerificationTypeInfo** readVerificationTypeInfo(int count);
private:
    ClassFileStream* fileStream_;
    ClassFileInfo* classFileInfo_;
    char* fileBuffer_;
    FILE * file_;
};

#endif