#include "runtime/jthread.h"

#include "runtime/virtual_machine.h"

#include <exception>
#include <thread>

std::list<JThread*> JThread::threads_;


thread_local JThread* tls;

JThread::JThread(ClassLoader* classLoader,
                 const std::string& symbol) :
    classLoader_(classLoader), methodSymbol_(symbol) {
    threads_.push_back(this);
}

JThread::~JThread() {
    threads_.remove(this);

    if (thread_->joinable()) {
        thread_->join();
    }
}

void JThread::Start() {
    thread_ = new std::thread(std::bind(&JThread::Start0, this));
}

void JThread::Join() {
    thread_->join();
}

ClassLoader* JThread::GetClassLoader() {
    return classLoader_;
}

VirtualMachine& JThread::GetVM() {
    return vm_;
}

void JThread::Start0() {
    tls = this;

    try {
        Klass* klass = classLoader_->LoadClass(methodSymbol_);
        Method* method = klass->GetDeclaredMethod("main");
        vm_.Execute(method);
    } catch (...) {
        tls = NULL;
    }
}

void JThread::Run(Method* method) {
    vm_.Execute(method);
}

JThread* JThread::Current() {
    return tls;
}

std::list<JThread*> JThread::GetAllThread() {
    return threads_;
}

std::list<StackFrame*>& JThread::GetFrames() {
    return frames_;
}
