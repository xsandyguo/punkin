#ifndef CLASSFILE_CLASS_FILE_READER_HPP
#define CLASSFILE_CLASS_FILE_READER_HPP

#include <stdio.h>

#include "utilities/top.hpp"
#include "classfile/class_file_stream.hpp"
#include "classfile/class_file_type.hpp"

#include "oop/klass.h"

class ClassFileReader {
  public:
    ClassFileReader(byte* code, int count);
    ~ClassFileReader();
    void ReadFile(const std::string& file, ClassFileInfo* classFileInfo);

    Klass* Read();

  private:
    void ReadConstPool();
    void ReadInterface();

    Annotation** ReadAnnotation(int count);
    Annotation* ReadAnnotationItem();
    void ReadField();
    void ReadMethod();
    void ReadAttribute();
    AttributeInfo** ReadAttribute(int count);
    AttributeInfo* ReadAttributeItem();

    u1 ResolveAttributeType(u2 nameIndex);
    ParameterAnnotation* ReadParamAnnotation(int count);
    VerificationTypeInfo** ReadVerificationTypeInfo(int count);
    ElementValue* ReadElementValue();

  private:
    ClassFileStream* fileStream_;
    ClassFileInfo* classFileInfo_;
    char* fileBuffer_;
    FILE * file_;
};

#endif