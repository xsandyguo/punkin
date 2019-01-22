#ifndef RUNTIME_JTHREAD_H
#define RUNTIME_JTHREAD_H

#include <vector>
#include <list>
#include <thread>

#include "runtime/virtual_machine.h"
#include "runtime/operand_stack.h"

class Method;
class ClassLoader;
class Operand;
class StackFrame;

class JThread {
  public:
    JThread(ClassLoader* classLoader,
            const std::string& symbol);
    ~JThread();

  public:
    void Start();
    void Join();

    void Run(Method* method);
    static std::list<JThread*> GetAllThread();
    static JThread* Current();

    std::list<StackFrame*>& GetFrames();

  private:
    void Start0();
  private:
    std::list<StackFrame*> frames_;
    static std::list<JThread*> threads_;
    std::thread* thread_;
    ClassLoader* classLoader_;
    std::string methodSymbol_;
    VirtualMachine vm_;
};

#endif