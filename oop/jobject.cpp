#include "oop/jobject.h"

JObject::JObject(Klass* klass, addr data)
	:klass_(klass),
	data_(data){

}