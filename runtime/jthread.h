#ifndef RUNTIME_JTHREAD_H
#define RUNTIME_JTHREAD_H

#include <vector>
#include <list>
#include <thread>

#include "runtime/operand_stack.h"

class Method;
class ClassLoader;
class Operand;

class StackFrame {
    Method* method;
    OperandStack stack;
    int maxVar;
    Operand* varSolts;
};


class JThread {
  public:
    JThread(Method* entry);
    ~JThread();

  public:
    void Start();
    void Join();

    static std::list<JThread*> GetAllThread();
    static JThread* Current();

    std::list<StackFrame*>& GetFrames();

  private:
    void Start0();

  private:
    std::list<StackFrame*> frames_;
    static std::list<JThread*> threads_;
    Method* entry_;
    std::thread* thread_;
};

#endif