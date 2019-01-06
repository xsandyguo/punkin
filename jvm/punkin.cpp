// punkin.cpp : Defines the entry point for the console application.
//
 
#include <memory>
#include <utility>
#include "utilities\top.hpp"
#include "classfile\class_file_stream.hpp"
#include <stdio.h>
#include <stdlib.h>

#define MAX_CLASS_FILE_SIZE  1024*1024*1024

int _tmain(int argc, _TCHAR* argv[])
{
	u1 a;

	FILE * file = fopen("D:\\workspace\\java\\target\\classes\\Main.class", "rb");
	char* buffer = new char[MAX_CLASS_FILE_SIZE];
	size_t length = fread(buffer, 1, MAX_CLASS_FILE_SIZE, file);

	std::auto_ptr<ClassFileStream>cfs (new ClassFileStream(buffer, length, NULL));
	 
	


	return 0;
}

