#ifndef CLASSFILE_CLASS_LOADER_H
#define CLASSFILE_CLASS_LOADER_H

class Klass;

class ClassLoader{
public:
    Klass* LoadClass(const char* name);

private:
    Klass* DefineClass(const char* name, byte* codes, int length);

private:
    const char* file_;
};

#endif