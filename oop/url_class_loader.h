#ifndef OOP_URL_CLASS_LOADER_H
#define OOP_URL_CLASS_LOADER_H

#include "oop/class_loader.h"

class UrlClassLoader : public ClassLoader{
public:
	UrlClassLoader(const char* jar);
	~UrlClassLoader();

	virtual Klass* FindClass(const char* name);
private:
	const char* jar_;
};

#endif 