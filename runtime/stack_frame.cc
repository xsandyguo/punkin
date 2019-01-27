#include "runtime/stack_frame.h"

StackFrame::StackFrame(Method* method)
    :method_(method),
     stack_(NULL),
     vars_(NULL),
     codeStream_(method->GetCodeArea()->code, method->GetCodeArea()->code_length) {

    CodeArea* code_ = method_->GetCodeArea();

    if (code_->max_stack >= 0) {
        stack_ = new Operand[code_->max_stack];
    }

    if (code_->max_locals) {
        vars_ = new Operand[code_->max_locals];
    }
}

StackFrame::~StackFrame() {
    delete stack_;
    delete vars_;
}