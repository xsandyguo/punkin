
#include "runtime/virtual_machine.h"
#include "jvm/vm_exception.h"

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


VirtualMachine::VirtualMachine() {

}

VirtualMachine::~VirtualMachine() {
}

void VirtualMachine::InvokeMethod(Method* method) {
    Operand* args = new Operand[method->GetParameterCount()];
    for (int i = 0; i < method->GetParameterCount(); ++i) {
        args[i] = pop();
    }

    JObject* ref = pop_jobject();
    method->Invoke(ref, );

    ensure_not_null(ref);
}

void VirtualMachine::Execute(Method* method) {
    u1* end = current_code().buffer() + current_code().length();

    while(current_code().current() < end) {
        ins_fun_ptr fun = INSTRUCTION_FUNS[next_byte()];
        VirtualMachine& me = *this;
        (me.*fun)();
    }
}

void VirtualMachine::align_ip(int a) {
    u1* ip = current_code().current();

    set_ip(round_to((intptr_t)ip, a));
}

void VirtualMachine::throw_java_exception(jobject ex) {
    Method* method = current_frame()->GetMethod();
    std::vector<ExceptionHandler>& handlers
        = method->GetCodeArea()->exception_table;

    std::vector<ExceptionHandler>::iterator itor;
    do {
        for (itor = handlers.begin(); itor != handlers.end(); ++itor) {
            ExceptionHandler& handler = *itor;
            Klass* type = resolve_klass_sym(handler.catch_type);
            if (!type->IsAssigableFrom(ex->GetKlass())) {
                continue;
            }

            current_frame()->ClearStack();

            set_ip(handler.start_pc);
            return;
        }
        return_frame();
    } while (frameTop_ >= 0);
}

void VirtualMachine::push_jobject(JObject* val) {
    current_frame()->Push(Operand(BASIC_TYPE_REF, val));
}

void VirtualMachine::push_jchar(jchar val) {
    current_frame()->Push(Operand(BASIC_TYPE_CHAR, val));
}

void VirtualMachine::push_jbool(jbool val) {
    current_frame()->Push(Operand(BASIC_TYPE_BOOL, val));
}

void VirtualMachine::push_jbyte(jbyte val) {
    current_frame()->Push(Operand(BASIC_TYPE_BYTE, val));
}

void VirtualMachine::push_jshort(jshort val) {
    current_frame()->Push(Operand(BASIC_TYPE_SHORT, val));
}

void VirtualMachine::push_jint(jint val) {
    current_frame()->Push(Operand(BASIC_TYPE_INTEGER, val));
}

void VirtualMachine::push_jlong(jlong val) {
    current_frame()->Push(Operand(BASIC_TYPE_LONG, val));
}

void VirtualMachine::push_jfloat(jfloat val) {
    current_frame()->Push(Operand(BASIC_TYPE_FLOAT, val));
}

void VirtualMachine::push_jdouble(jdouble val) {
    current_frame()->Push(Operand(BASIC_TYPE_DOUBLE, val));
}

void VirtualMachine::push_jretaddr(u4 val) {
    current_frame()->Push(Operand(BASIC_TYPE_INTEGER, (jint)val));
}

JArray*   VirtualMachine::pop_jarray() {
    return (JArray*)current_frame()->Pop().GetRefVal();
}

JObject*  VirtualMachine::pop_jobject() {
    return current_frame()->Pop().GetRefVal();
}

jchar     VirtualMachine::pop_jchar() {
    return current_frame()->Pop().GetCharVal();
}

jbool	  VirtualMachine::pop_jbool() {
    return current_frame()->Pop().GetBoolVal();
}

jbyte     VirtualMachine::pop_jbyte() {
    return current_frame()->Pop().GetByteVal();
}

jshort    VirtualMachine::pop_jshort() {
    return current_frame()->Pop().GetShortVal();
}

jint      VirtualMachine::pop_jint() {
    return current_frame()->Pop().GetIntVal();
}

jlong     VirtualMachine::pop_jlong() {
    return current_frame()->Pop().GetLongVal();
}

jfloat    VirtualMachine::pop_jfloat() {
    return current_frame()->Pop().GetFloatVal();
}

jdouble   VirtualMachine::pop_jdouble() {
    return current_frame()->Pop().GetDoubleVal();
}

jint      VirtualMachine::pop_jretaddr() {
    return current_frame()->Pop().GetIntVal();
}

Operand VirtualMachine::pop() {
    return current_frame()->Pop();
}

void VirtualMachine::push(const Operand& op) {
    current_frame()->Push(op);
}

Operand& VirtualMachine::load(int index) {
    return current_frame()->Load(index);
}

void VirtualMachine::store(int index, const Operand& val) {
    current_frame()->Store(index, val);
}

BytecodeStream& VirtualMachine::current_code() {
    return current_frame()->GetCodeStream();
}

u1 VirtualMachine::next_byte() {
    return current_code().get_u1();
}

u2 VirtualMachine::next_u2() {
    return current_code().get_u2();
}

u4 VirtualMachine::next_u4() {
    return current_code().get_u4();
}

inline void VirtualMachine::skip_ip(int offset) {
    current_code().skip_u1(offset);
}

void VirtualMachine::set_ip(int ip) {
    u1* current = current_code().buffer();
    current_code().set_current(current + ip);
}

void VirtualMachine::return_frame() {
    delete current_frame();
    frameTop_--;
}

StackFrame* VirtualMachine::current_frame() {
    return stackFrames_[frameTop_];
}

void VirtualMachine::set_local_var(u2 index,const Operand& val) {
    current_frame()->SetVar(index, val);
}

Operand VirtualMachine::get_local_var(u2 index) {
    return current_frame()->GetVar(index);
}

void VirtualMachine::ensure_not_null(JObject* obj) {
    if (!obj) {
        vmExceptions::java_lang_NullPointerException();
    }
}

void VirtualMachine::__get_field_val(jobject obj, Field* field) {
    Klass* klass = field->GetType();

    switch (klass->GetType()) {
    case BASIC_TYPE_BOOL:
        push_jbool(field->GetBoolean(obj));
        break;
    case BASIC_TYPE_BYTE:
        push_jbool(field->GetByte(obj));
        break;
    case BASIC_TYPE_CHAR:
        push_jchar(field->GetChar(obj));
        break;
    case BASIC_TYPE_SHORT:
        push_jshort(field->GetShort(obj));
        break;
    case BASIC_TYPE_INTEGER:
        push_jint(field->GetInt(obj));
        break;
    case BASIC_TYPE_LONG:
        push_jlong(field->GetLong(obj));
        break;
    case BASIC_TYPE_FLOAT:
        push_jfloat(field->GetFloat(obj));
        break;
    case BASIC_TYPE_DOUBLE:
        push_jdouble(field->GetDouble(obj));
        break;
    case BASIC_TYPE_REF:
        push_jobject(field->Get(obj));
        break;
    }
}

void VirtualMachine::__set_field_val(jobject obj, Field* field, const Operand& val) {
    Klass* klass = field->GetType();
    BasicDataType type = klass->GetType();

    switch (type) {
    case BASIC_TYPE_BOOL:
        field->SetBoolean(NULL, pop_jbool());
        break;
    case BASIC_TYPE_CHAR:
        field->SetChar(NULL, pop_jchar());
        break;
    case BASIC_TYPE_BYTE:
        field->SetByte(NULL, pop_jbyte());
        break;
    case BASIC_TYPE_SHORT:
        field->SetShort(NULL, pop_jshort());
        break;
    case BASIC_TYPE_INTEGER:
        field->SetInt(NULL, pop_jint());
        break;
    case BASIC_TYPE_LONG:
        field->SetLong(NULL, pop_jlong());
        break;
    case BASIC_TYPE_FLOAT:
        field->SetFloat(NULL, pop_jfloat());
        break;
    case BASIC_TYPE_DOUBLE:
        field->SetDouble(NULL, pop_jdouble());
        break;
    case BASIC_TYPE_REF:
        field->Set(NULL, pop_jobject());
        break;
    }

    THROW_ILLEGAL_OPERATE();
}


Klass* VirtualMachine::resolve_klass_sym(u2 index) {
    Klass* klass = current_frame()->GetKlass();

    ConstantPool& constantPool = klass->GetConstantPool();
    ConstPoolClassInfo* info = (ConstPoolClassInfo*)constantPool.ResolveConstantInfo(index);
    ConstPoolUtf8Info* name =(ConstPoolUtf8Info*)constantPool.ResolveConstantInfo(info->name_index);

    return klass->GetClassLoader()->LoadClass(std::string((const char*)name->bytes));
}

Field* VirtualMachine::resolve_field_sym(bool isstatic, u2 index) {
    Klass* klass = current_frame()->GetKlass();
    FieldRefSymbol* sym = klass->GetConstantPool().ResolveFieldRef(index);
    if (sym->GetField()) {
        return sym->GetField();
    }

    klass = klass->GetClassLoader()->LoadClass(sym->GetKlass());

    do {
        Field* field = klass->GetDeclaredField(sym->GetFieldName());
        if (isstatic) {
            sym->SetField(field);
            return field;
        }

        if (field) {
            sym->SetField(field);
            return field;
        }
    } while(klass = klass->GetSuperKlass());

    vmExceptions::java_lang_NoSuchFieldException();

    return NULL;
}