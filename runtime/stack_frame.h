#ifndef RUNTIME_STACK_FRAME_H
#define RUNTIME_STACK_FRAME_H


#include "runtime/operand.h"
#include "oop/method.h"
#include "interpreter/byte_code_stream.h"

class Method;

class StackFrame {
  public:
    StackFrame(Method* method);
    ~StackFrame();

    inline  Method* GetMethod() {
        return method_;
    }

    inline Klass* GetKlass() {
        return method_->GetType();
    }

    inline void Push(const Operand& operand) {
        stack_[sp_++] = operand;
    }

    inline Operand& Load(int top) {
        return stack_[sp_ - top - 1];
    }

    inline void Store(int top, const Operand& operand) {
        stack_[sp_ - top - 1] = operand;
    }

    inline Operand& Pop() {
        assert(sp_ >= 0);

        return stack_[sp_--];
    }

    inline void SetVar(int index, const Operand& operand) {
        assert(index < method_->GetCodeArea()->max_locals);

        vars_[index] = operand;
    }

    inline Operand& GetVar(int index) {
        return vars_[index];
    }

    inline void ClearStack() {
        sp_ = 0;
    }

    inline BytecodeStream& GetCodeStream() {
        return codeStream_;
    }

  private:
    Method* method_;

    int sp_;
    Operand* stack_;
    Operand* vars_;

    BytecodeStream codeStream_;
};


#endif