#include "oop/bootstrap_class_loader.h"

BootstrapClassLoader::BootstrapClassLoader(const std::string& path)
	:UrlClassLoader(path) {

}