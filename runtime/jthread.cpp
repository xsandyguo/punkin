#include "runtime/jthread.h"

#include "runtime/virtual_machine.h"

#include <thread>

std::vector<JThread*> JThread::threads_;


JThread::JThread(Method* method):
entry_(method){
	threads_.push_back(this);
}

JThread::~JThread(){

}

void JThread::Start(){
	VirtualMachine vm;
	vm.Execute(entry_);
}

JThread* JThread::Current(){
	return NULL;
}

std::vector<JThread*> JThread::GetAllThread(){
	return threads_;
}

std::vector<StackFrame*>& JThread::GetFrames(){
	return frames_;
}

Operand OperandStack::pop(){
	Operand ret = operands_.back();
	operands_.pop_back();
}

void OperandStack::push(Operand operand){
	operands_.push_back(operand);
}
