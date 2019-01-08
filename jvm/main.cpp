// punkin.cpp : Defines the entry point for the console application.
//
 
#include <utility>
#include <stdio.h>
#include <stdlib.h>


#include "utilities\top.hpp"
#include "classfile\class_file_reader.hpp"

int _tmain(int argc, char** argv[])
{ 
    ClassFileReader* reader = new ClassFileReader();

    ClassFileInfo* classFileInfo = new ClassFileInfo();

    reader->ReadFile("D:\\workspace\\java\\target\\classes\\Main.class",
        classFileInfo);
     

    return 0;
}

