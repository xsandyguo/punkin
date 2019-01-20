#include "gc/memory.h"

#include "runtime/jthread.h"
#include "oop/class_loader.h"

MemoryGC* MemoryGC::instance_ = NULL;

addr MemoryGC::Alloc(int length){
	return NULL;
}

void MemoryGC::Recycle(){
	MarkLocalVar();
	MarkStaticMember();
	Clean();
}

void MemoryGC::Clean(){

}

void MemoryGC::MarkLocalVar(){
	std::vector<JThread*> threads = JThread::GetAllThread();
	std::vector<JThread*>::iterator itor;

	for(itor = threads.begin(); itor != threads.end(); ++ itor){
		JThread* thread = *itor;

	}
}

void MemoryGC::MarkStaticMember(){
	std::vector<ClassLoader*>& classLoaders = ClassLoader::GetAllInstance();
	std::vector<ClassLoader*>::iterator itor;
	for(itor = classLoaders.begin(); itor != classLoaders.end();++itor){
		ClassLoader* loader = *itor;

	}
	
}