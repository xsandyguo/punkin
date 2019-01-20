// punkin.cpp : Defines the entry point for the console application.
//
 
#include <utility>
#include <stdio.h>
#include <stdlib.h>


#include "utilities\top.hpp"
#include "classfile\class_file_reader.hpp"
#include "oop/bootstrap_class_loader.h"

int _tmain(int argc, char** argv[])
{ 
    ClassFileReader* reader = new ClassFileReader();

    ClassFileInfo* classFileInfo = new ClassFileInfo();

    reader->ReadFile("D:\\workspace\\java\\target\\classes\\Main.class",
        classFileInfo);
     
	ClassLoader* classLoader = new BootstrapClassLoader();
	Klass* klass = classLoader->LoadClass(entrySym_);
	Method* method = klass->GetDeclaredMethod("main");


    return 0;
}

