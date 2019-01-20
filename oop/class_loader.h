#ifndef OOP_CLASS_LOADER_H
#define OOP_CLASS_LOADER_H

#include "utilities/top.hpp"
#include <vector>

class Klass;

class ClassLoader{
public:
	ClassLoader();
	ClassLoader(ClassLoader* parent);
	~ClassLoader();
public:
    Klass* LoadClass(const char* name);

	static std::vector<ClassLoader*>& GetAllInstance();

protected:
	virtual Klass* FindClass(const char* name) = 0;
    Klass* DefineClass(const char* name, byte* codes, int length);

	void ResolveKlass(Klass* klass);

private:
	Klass* FindLoadedKlass(const char* name);

private:
    const char* file_;
	ClassLoader* parent_;
	std::vector<Klass*> loadedKlass_;
	static std::vector<ClassLoader*> instances_;
};

#endif