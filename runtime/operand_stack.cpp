#include "runtime/operand_stack.h"

Operand OperandStack::pop() {
    Operand ret = operands_.back();
    operands_.pop_back();
}

void OperandStack::push(const Operand& operand) {
    operands_.push_back(operand);
}
