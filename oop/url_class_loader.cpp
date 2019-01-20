#include "oop/url_class_loader.h"

#include <windows.h>
#include "utilities/unzip.h"


UrlClassLoader::UrlClassLoader(const char* jar):jar_(jar){

}

Klass* UrlClassLoader::FindClass(const char* name){
	 
	return NULL;
}