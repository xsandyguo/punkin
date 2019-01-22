#ifndef RUNTIME_STACK_FRAME_H
#define RUNTIME_STACK_FRAME_H

#include "runtime/operand_stack.h"

class Method;
class Operand;

struct StackFrame {
    Method* method;
    OperandStack stack;
    int maxVar;
    Operand* vars;
};


#endif