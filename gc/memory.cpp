#include "gc/memory.h"

#include "runtime/jthread.h"
#include "oop/class_loader.h"

MemoryGC* MemoryGC::instance_ = NULL;

addr MemoryGC::Alloc(int length) {
    return NULL;
}

void MemoryGC::Recycle() {
    MarkLocalVar();
    MarkStaticMember();
    Clean();
}

void MemoryGC::Clean() {

}

void MemoryGC::MarkLocalVar() {
    std::list<JThread*> threads = JThread::GetAllThread();
    std::list<JThread*>::iterator itor;

    for(itor = threads.begin(); itor != threads.end(); ++ itor) {
        JThread* thread = *itor;
        thread->GetFrames();
    }
}

void MemoryGC::MarkStaticMember() {
    std::list<ClassLoader*>& classLoaders = ClassLoader::GetAllInstance();
    std::list<ClassLoader*>::iterator itor;
    for(itor = classLoaders.begin(); itor != classLoaders.end(); ++itor) {
        ClassLoader* loader = *itor;

        std::map<std::string, Klass*>& klasses = loader->GetLoadedKlass();
        std::map<std::string, Klass*>::iterator itor;
        for (itor = klasses.begin(); itor != klasses.end(); ++itor) {
            Klass* klass = itor->second;


        }
    }

}