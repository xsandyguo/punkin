
#include "runtime/virtual_machine.h"

#include <float.h>


typedef void (VirtualMachine::*ins_fun_ptr)(void);


ins_fun_ptr INSTRUCTION_FUNS [] = {
    &VirtualMachine::nop,
    &VirtualMachine::aconst_null,
    &VirtualMachine::iconst_m1,
    &VirtualMachine::iconst_0,
    &VirtualMachine::iconst_1,
    &VirtualMachine::iconst_2,
    &VirtualMachine::iconst_3,
    &VirtualMachine::iconst_4,
    &VirtualMachine::iconst_5,
    &VirtualMachine::lconst_0,
    &VirtualMachine::lconst_1,
    &VirtualMachine::fconst_0,
    &VirtualMachine::fconst_1,
    &VirtualMachine::fconst_2,
    &VirtualMachine::dconst_0,
    &VirtualMachine::dconst_1,
    &VirtualMachine::bipush,
    &VirtualMachine::sipush,
    &VirtualMachine::ldc,
    &VirtualMachine::ldc_w,
    &VirtualMachine::ldc2_w,
    &VirtualMachine::iload,
    &VirtualMachine::lload,
    &VirtualMachine::fload,
    &VirtualMachine::dload,
    &VirtualMachine::aload,
    &VirtualMachine::iload_0,
    &VirtualMachine::iload_1,
    &VirtualMachine::iload_2,
    &VirtualMachine::iload_3,
    &VirtualMachine::lload_0,
    &VirtualMachine::lload_1,
    &VirtualMachine::lload_2,
    &VirtualMachine::lload_3,
    &VirtualMachine::fload_0,
    &VirtualMachine::fload_1,
    &VirtualMachine::fload_2,
    &VirtualMachine::fload_3,
    &VirtualMachine::dload_0,
    &VirtualMachine::dload_1,
    &VirtualMachine::dload_2,
    &VirtualMachine::dload_3,
    &VirtualMachine::aload_0,
    &VirtualMachine::aload_1,
    &VirtualMachine::aload_2,
    &VirtualMachine::aload_3,
    &VirtualMachine::iaload,
    &VirtualMachine::laload,
    &VirtualMachine::faload,
    &VirtualMachine::daload,
    &VirtualMachine::aaload,
    &VirtualMachine::baload,
    &VirtualMachine::caload,
    &VirtualMachine::saload,
    &VirtualMachine::istore,
    &VirtualMachine::lstore,
    &VirtualMachine::fstore,
    &VirtualMachine::dstore,
    &VirtualMachine::astore,
    &VirtualMachine::istore_0,
    &VirtualMachine::istore_1,
    &VirtualMachine::istore_2,
    &VirtualMachine::istore_3,
    &VirtualMachine::lstore_0,
    &VirtualMachine::lstore_1,
    &VirtualMachine::lstore_2,
    &VirtualMachine::lstore_3,
    &VirtualMachine::fstore_0,
    &VirtualMachine::fstore_1,
    &VirtualMachine::fstore_2,
    &VirtualMachine::fstore_3,
    &VirtualMachine::dstore_0,
    &VirtualMachine::dstore_1,
    &VirtualMachine::dstore_2,
    &VirtualMachine::dstore_3,
    &VirtualMachine::astore_0,
    &VirtualMachine::astore_1,
    &VirtualMachine::astore_2,
    &VirtualMachine::astore_3,
    &VirtualMachine::iastore,
    &VirtualMachine::lastore,
    &VirtualMachine::fastore,
    &VirtualMachine::dastore,
    &VirtualMachine::aastore,
    &VirtualMachine::bastore,
    &VirtualMachine::castore,
    &VirtualMachine::sastore,
    &VirtualMachine::pop__,
    &VirtualMachine::pop2,
    &VirtualMachine::dup,
    &VirtualMachine::dup_x1,
    &VirtualMachine::dup_x2,
    &VirtualMachine::dup2,
    &VirtualMachine::dup2_x1,
    &VirtualMachine::dup2_x2,
    &VirtualMachine::swap,
    &VirtualMachine::iadd,
    &VirtualMachine::ladd,
    &VirtualMachine::fadd,
    &VirtualMachine::dadd,
    &VirtualMachine::isub,
    &VirtualMachine::lsub,
    &VirtualMachine::fsub,
    &VirtualMachine::dsub,
    &VirtualMachine::imul,
    &VirtualMachine::lmul,
    &VirtualMachine::fmul,
    &VirtualMachine::dmul,
    &VirtualMachine::idiv,
    &VirtualMachine::ldiv,
    &VirtualMachine::fdiv,
    &VirtualMachine::ddiv,
    &VirtualMachine::irem,
    &VirtualMachine::lrem,
    &VirtualMachine::frem,
    &VirtualMachine::drem,
    &VirtualMachine::ineg,
    &VirtualMachine::lneg,
    &VirtualMachine::fneg,
    &VirtualMachine::dneg,
    &VirtualMachine::ishl,
    &VirtualMachine::lshl,
    &VirtualMachine::ishr,
    &VirtualMachine::lshr,
    &VirtualMachine::iushr,
    &VirtualMachine::lushr,
    &VirtualMachine::iand,
    &VirtualMachine::land,
    &VirtualMachine::ior,
    &VirtualMachine::lor,
    &VirtualMachine::ixor,
    &VirtualMachine::lxor,
    &VirtualMachine::iinc,
    &VirtualMachine::i2l,
    &VirtualMachine::i2f,
    &VirtualMachine::i2d,
    &VirtualMachine::l2i,
    &VirtualMachine::l2f,
    &VirtualMachine::l2d,
    &VirtualMachine::f2i,
    &VirtualMachine::f2l,
    &VirtualMachine::f2d,
    &VirtualMachine::d2i,
    &VirtualMachine::d2l,
    &VirtualMachine::d2f,
    &VirtualMachine::i2b,
    &VirtualMachine::i2c,
    &VirtualMachine::i2s,
    &VirtualMachine::lcmp,
    &VirtualMachine::fcmpl,
    &VirtualMachine::fcmpg,
    &VirtualMachine::dcmpl,
    &VirtualMachine::dcmpg,
    &VirtualMachine::ifeq,
    &VirtualMachine::ifne,
    &VirtualMachine::iflt,
    &VirtualMachine::ifge,
    &VirtualMachine::ifgt,
    &VirtualMachine::ifle,
    &VirtualMachine::if_icmpeq,
    &VirtualMachine::if_icmpne,
    &VirtualMachine::if_icmplt,
    &VirtualMachine::if_icmpge,
    &VirtualMachine::if_icmpgt,
    &VirtualMachine::if_icmple,
    &VirtualMachine::if_acmpeq,
    &VirtualMachine::if_acmpne,
    &VirtualMachine::goto__,
    &VirtualMachine::jsr,
    &VirtualMachine::ret__,
    &VirtualMachine::tableswitch,
    &VirtualMachine::lookupswitch,
    &VirtualMachine::ireturn,
    &VirtualMachine::lreturn,
    &VirtualMachine::freturn,
    &VirtualMachine::dreturn,
    &VirtualMachine::areturn,
    &VirtualMachine::return__,
    &VirtualMachine::getstatic,
    &VirtualMachine::putstatic,
    &VirtualMachine::getfield,
    &VirtualMachine::putfield,
    &VirtualMachine::invokevirtual,
    &VirtualMachine::invokespecial,
    &VirtualMachine::invokestatic,
    &VirtualMachine::invokeinterface,
    &VirtualMachine::new__,
    &VirtualMachine::newarray,
    &VirtualMachine::anewarray,
    &VirtualMachine::arraylength,
    &VirtualMachine::athrow,
    &VirtualMachine::checkcast,
    &VirtualMachine::instanceof,
    &VirtualMachine::monitorenter,
    &VirtualMachine::monitorexit,
    &VirtualMachine::wide,
    &VirtualMachine::multianewarray,
    &VirtualMachine::ifnull,
    &VirtualMachine::ifnonnull,
    &VirtualMachine::goto_w,
    &VirtualMachine::jsr_w

};

void VirtualMachine::InvokeMethod(Method* method) {
    Operand* args = new Operand[method->GetParameterCount()];
    for (int i = 0; i < method->GetParameterCount(); ++i) {
        args[i] = pop();
    }

    JObject* ref = pop_jobject();

    CheckNullObject(ref);


}

void VirtualMachine::Execute(Method* method) {
    while(has_more_code()) {
        byte code = next_byte();

        ins_fun_ptr fun = INSTRUCTION_FUNS[code];

        VirtualMachine& me = *this;

        (me.*fun)();
    }
}