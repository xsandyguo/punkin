#include "runtime/jthread.h"

#include "runtime/virtual_machine.h"

#include <thread>

std::list<JThread*> JThread::threads_;


JThread::JThread(Method* method):
    entry_(method) {
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

void JThread::Start0() {
    VirtualMachine vm;
    vm.Execute(entry_);
}

JThread* JThread::Current() {
    return NULL;
}

std::list<JThread*> JThread::GetAllThread() {
    return threads_;
}

std::list<StackFrame*>& JThread::GetFrames() {
    return frames_;
}
