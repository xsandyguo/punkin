#ifndef OOP_BOOTSTRAP_CLASS_LOADER_H
#define OOP_BOOTSTRAP_CLASS_LOADER_H

#include "oop/url_class_loader.h"

#include <string>

class BootstrapClassLoader : public UrlClassLoader{
public:
	BootstrapClassLoader(const std::string& path); 
};

#endif