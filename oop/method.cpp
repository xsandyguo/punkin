#include "oop/method.h"

#include "gc/memory.h"
#include "oop/jobject.h"
#include "oop/klass.h"

jobject Constructor::New(){
	int length = sizeof(JObject);

	Klass* klass = this->GetType(); 
	while(klass){ 
		if(!klass->IsPrimitive()){
			length += 4;
			continue;
		}

		const char* name = klass->GetName(); 
		for(int i = 0; i < PRIMITIVE_TYPE_KLASS_NAME_COUNT; ++i){
			primitive_type_klass_size& item = KLASS_TYPE_SIZE[i];
			if(!strcmp(name, item.name)){
				length += item.size;
			}
		}

		klass = klass->GetSuperKlass();
	}

	addr data = MemoryGC::Instance().Alloc(length);

	return (jobject)data;
}