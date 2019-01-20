#ifndef RUNTIME_OPERAND_STACK_H
#define RUNTIME_OPERAND_STACK_H

#include <vector>
#include "runtime/operand.h"

class OperandStack {
  public:
    Operand pop();
    void push(const Operand& operand);

  private:
    std::vector<Operand> operands_;
};


#endif // 
