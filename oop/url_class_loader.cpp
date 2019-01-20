#include "oop/url_class_loader.h"

#include <windows.h>
#include "utilities/unzip.h"


UrlClassLoader::UrlClassLoader(const std::string& jar)
	:jar_(jar) {

}

UrlClassLoader::~UrlClassLoader() {

}

Klass* UrlClassLoader::FindClass(const std::string& name){
	return NULL;
}