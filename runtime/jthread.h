#ifndef RUNTIME_JTHREAD_H
#define RUNTIME_JTHREAD_H

#include <vector>

class Method;
class ClassLoader;
class Operand;

class StackFrame{
	Method* method;
	OperandStack stack; 
	int maxVar;
	Operand* varSolts;
};

class OperandStack {
public:
	Operand pop();
	void push(Operand operand);
private:
	std::vector<Operand> operands_;
};


class JThread{
public:
	JThread(Method* entry);
	~JThread();

public:

	void Start();

	static std::vector<JThread*> GetAllThread();
	static JThread* Current();

	std::vector<StackFrame*>& GetFrames();

private:
	std::vector<StackFrame*> frames_;
	static std::vector<JThread*> threads_;
	Method* entry_;
};

#endif