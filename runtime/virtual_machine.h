#ifndef INTERPRETER_VIRTUAL_MACHINE_H
#define INTERPRETER_VIRTUAL_MACHINE_H

#include <vector>

#include "runtime/operand.h"
#include "runtime/stack_frame.h"
#include "oop/jarray.h"
#include "oop/class_loader.h"
#include "oop/klass.h"
#include "classfile/class_file_type.hpp"

#define MAX_STACK_FRAME 256


#define INSTRUCT_FUN_IF_ICMP(name, cmp)        \
void if_icmp##name(){							\
    byte offset1 = next_byte();                 \
    byte offset2 = next_byte();                 \
    int v2 = pop_jint();                        \
    int v1 = pop_jint();                        \
    if(v1 cmp v2){                             \
        u2 offset = offset1 << 8 | offset2;    \
        skip_ip(offset);                        \
    }                                          \
}

#define INSTRUCT_FUN_IF_0CMP(name, cmp)         \
    void if##name(){							\
        byte offset1 = next_byte();              \
        byte offset2 = next_byte();              \
        int v1 = pop_jint();                     \
        if(v1 cmp 0){                           \
        u2 offset = offset1 << 8 | offset2;     \
        skip_ip(offset);                         \
    }                                           \
}


#define INSTRUCT_FUN_LOAD_STORE_ARRAY(prefix, type)  \
void prefix##aload(){                                \
    int index = pop_jint();                          \
    JArray* ar = pop_jarray();                       \
    push_##type(ar->get_##type(index));				 \
}                                                    \
                                                     \
void prefix##astore(){                               \
    type val = pop_##type();                         \
    int index = pop_jint();                          \
    JArray* ar = pop_jarray();                       \
    ar->set_##type(index, val);                      \
}


#define INSTRUCT_FUN_LOAD_STORE_X(prefix, num) \
void prefix##store_##num() {	  \
		__##prefix##store(num);   \
}								  \
void prefix##load_##num() {	      \
		__##prefix##load(num);    \
}

#define INSTRUCT_FUN_LOAD_STORE_VAR(prefix)	   \
void prefix##store(){				           \
    __##prefix##store(next_byte());            \
}                                              \
void prefix##load(){						   \
    __##prefix##load(next_byte());             \
}											   \
INSTRUCT_FUN_LOAD_STORE_X(prefix, 0)		   \
INSTRUCT_FUN_LOAD_STORE_X(prefix, 1)		   \
INSTRUCT_FUN_LOAD_STORE_X(prefix, 2)		   \
INSTRUCT_FUN_LOAD_STORE_X(prefix, 3)


#define INSTRUCT_FUN_MATH_CALC(prefix, type) \
void prefix##add(){                          \
    push_##type(pop_##type() + pop_##type()); \
}                                            \
void prefix##sub(){                          \
    type v2 = pop_##type();                  \
    type v1 = pop_##type();                  \
                                             \
    push_##type(v1 - v2);                    \
}                                            \
void prefix##div(){                          \
    type v2 = pop_##type();                  \
    type v1 = pop_##type();                  \
    type ret = v1 / v2;                      \
                                             \
    push_##type(ret);                        \
}                                            \
void prefix##mul(){                          \
    type v2 = pop_##type();                  \
    type v1 = pop_##type();                  \
                                             \
    push_##type(v1*v2);                      \
}                                            \
void prefix##neg(){                          \
    type v1 = pop_##type();                  \
    push_##type(-v1);                        \
}


#define INSTRUCT_FUN_INT_REM_CALC(prefix, type) \
void prefix##rem(){                             \
    type v2 = pop_##type();                     \
    type v1 = pop_##type();                     \
    push_##type(v1 % v2);                       \
}

#define INSTRUCT_FUN_FLOAT_REM_CALC(prefix, type)   \
void prefix##rem(){									\
    type v2 = pop_##type();							\
    type v1 = pop_##type();							\
													\
    type ret = fmod(v1, v2);						\
    push_##type(ret);								\
}


#define INSTRUCT_FUN_BIT_AND(prefix, type)  \
void prefix##and(){                         \
    type v2 = pop_##type();                 \
    type v1 = pop_##type();                 \
    push_##type(v1 & v2);                   \
}                                           \

#define INSTRUCT_FUN_BIT_CALC(prefix, type, orgin) \
void prefix##or(){                          \
    type v2 = pop_##type();                 \
    type v1 = pop_##type();                 \
    push_##type(v1 | v2);                   \
}                                           \
void prefix##shl(){                         \
    type v2 = pop_##type();                 \
    type v1 = pop_##type();                 \
    push_##type(v1 << (v2 & 0x2F));         \
}                                           \
void prefix##shr(){                         \
    type v2 = pop_##type();                 \
    type v1 = pop_##type();                 \
    push_##type(v1 >> (v2 & 0x2F));         \
}                                           \
void prefix##xor(){                         \
    type v2 = pop_##type();                 \
    type v1 = pop_##type();                 \
    push_##type(v1 ^ v2);                   \
}											\
void prefix##ushl(){                        \
    unsigned orgin v2 = pop_##type();        \
    unsigned orgin v1 = pop_##type();        \
    push_##type(v1 << (v2 & 0x2F));         \
}                                           \
void prefix##ushr(){                        \
    unsigned orgin v2 = pop_##type();        \
    unsigned orgin v1 = pop_##type();        \
    push_##type(v1 >> (v2 & 0x2F));         \
}


class VirtualMachine {
  public:
    void Execute(Method* method_);

  public:
    INSTRUCT_FUN_LOAD_STORE_VAR(a)
    INSTRUCT_FUN_LOAD_STORE_VAR(d)
    INSTRUCT_FUN_LOAD_STORE_VAR(f)
    INSTRUCT_FUN_LOAD_STORE_VAR(i)
    INSTRUCT_FUN_LOAD_STORE_VAR(l)

    INSTRUCT_FUN_MATH_CALC(d, jdouble)
    INSTRUCT_FUN_MATH_CALC(f, jfloat)
    INSTRUCT_FUN_MATH_CALC(i, jint)
    INSTRUCT_FUN_MATH_CALC(l, jlong)

    INSTRUCT_FUN_FLOAT_REM_CALC(d, jdouble)
    INSTRUCT_FUN_FLOAT_REM_CALC(f, jfloat)

    INSTRUCT_FUN_INT_REM_CALC(i, jint)
    INSTRUCT_FUN_INT_REM_CALC(l, jlong)

    INSTRUCT_FUN_IF_ICMP(eq, == )
    INSTRUCT_FUN_IF_ICMP(ne, != )
    INSTRUCT_FUN_IF_ICMP(lt, < )
    INSTRUCT_FUN_IF_ICMP(le, <= )
    INSTRUCT_FUN_IF_ICMP(gt, > )
    INSTRUCT_FUN_IF_ICMP(ge, >= )

    INSTRUCT_FUN_IF_0CMP(eq, == )
    INSTRUCT_FUN_IF_0CMP(ne, != )
    INSTRUCT_FUN_IF_0CMP(lt, < )
    INSTRUCT_FUN_IF_0CMP(le, <= )
    INSTRUCT_FUN_IF_0CMP(gt, > )
    INSTRUCT_FUN_IF_0CMP(ge, >= )

    INSTRUCT_FUN_BIT_CALC(l, jlong, __int64)
    INSTRUCT_FUN_BIT_CALC(i, jint, int)

    INSTRUCT_FUN_BIT_AND(l, jlong)
    INSTRUCT_FUN_BIT_AND(i, jint)

    INSTRUCT_FUN_LOAD_STORE_ARRAY(a, jobject)
    INSTRUCT_FUN_LOAD_STORE_ARRAY(i, jint)
    INSTRUCT_FUN_LOAD_STORE_ARRAY(l, jlong)
    INSTRUCT_FUN_LOAD_STORE_ARRAY(f, jfloat)
    INSTRUCT_FUN_LOAD_STORE_ARRAY(d, jdouble)

    void baload() {
        int index = pop_jint();
        JArray* ar = pop_jarray();
        push_jint(SignedExtend(ar->get_jbyte(index)));
    }

    void bastore() {
        jbyte val = pop_jbyte();
        int index = pop_jint();
        pop_jarray()->set_jbyte(index, val);
    }

    void saload() {
        int index = pop_jint();
        jshort val = pop_jarray()->get_jshort(index);
        push_jint(ZeroExtend(val));
    }

    void sastore() {
        jshort val = pop_jchar();
        int index = pop_jint();
        pop_jarray()->set_jchar(index, val);
    }

    void caload() {
        int index = pop_jint();
        jchar val = pop_jarray()->get_jchar(index);
        push_jint(ZeroExtend(val));
    }

    void castore() {
        jchar c = pop_jchar();
        int index = pop_jint();
        pop_jarray()->set_jchar(index, c);
    }

    void aconst_null() {
        push_jobject(NULL);
    }

    void anewarray() {
        u2 index =  next_u2_sym_index();
        Klass* klass = ResolveKlassType(index);

        int count = pop_jint();
        if(count < 0) {
            throw "invalid count";
        }

        push_jobject(new JArray(new JObject*[count], count, klass));
    }

    void arraylength() {
        push_jint(pop_jarray()->get_length());
    }

    void athrow() {
        jobject obj = pop_jobject();

        ensure_not_null(obj);

        Method* method = current_frame()->method;
        std::vector<ExceptionHandler>& handlers
            = method->GetCodeArea()->exception_table;

        std::vector<ExceptionHandler>::iterator itor;
        bool handled = false;

        do {}
        for (itor = handlers.begin(); itor != handlers.end(); ++itor) {
            ExceptionHandler& handler = *itor;
            Klass* type = ResolveKlassType(handler.catch_type);
            if (!type->IsAssigableFrom(obj->GetKlass())) {
                continue;
            }

            clear_operand_stack();

            set_ip(handler.start_pc);
            handled = true;
        }

        if (!handled) {
            handle_return();
        }
    }

    void bipush() {
        push_jint(SignedExtend(next_byte()));
    }

    void checkcast() {
        byte byte1 = next_byte();
        byte byte2 = next_byte();

        u2 index = byte1 << 8 | byte2;

        check_object_type(load(0).GetRefVal(), index);
    }

    void d2f() {
        push_jfloat((jfloat)pop_jdouble());
    }

    void d2i() {
        push_jint((jint)pop_jdouble());
    }

    void d2l() {
        push_jlong((jlong)pop_jdouble());
    }

    void __dcmp(int direction) {
        jdouble val2 = pop_jdouble();
        jdouble val1 = pop_jdouble();

        if(val1 == val2) {
            push_jint(0);
        } else if(val1 > val2) {
            push_jint(1);
        } else if(val1 < val2) {
            push_jint(-1);
        } else if (direction == -1 || direction == 1) {
            push_jint(direction);
        } else {
            push_jint(0);
        }
    }

    void dcmpl() {
        __dcmp(-1);
    }

    void dcmpg() {
        __dcmp(1);
    }

    void dconst_0() {
        push_jdouble(0.0);
    }

    void dconst_1() {
        push_jdouble(1.0);
    }

    void dup() {
        push(load(0));
    }

    void dup_x1() {
        //..a b
        Operand& b = load(0);
        Operand& a = load(1);

        store(0, a);
        store(1, b);

        push(b);
        // b a b
    }

    void dup_x2() {
        //a, b, c
        Operand& c = load(0);
        Operand& a = load(2);

        store(2, c);
        push(c);
        //c b c c

        Operand& b = load(2);
        store(2, a);
        //c a c c

        store(1, b);
        //c, a, b, c
    }

    void dup2_x1() {
        Operand op1 = pop();
        Operand op2 = pop();
        Operand op3 = pop();
        push(op2);
        push(op1);
        push(op3);
        push(op2);
        push(op1);
    }

    void dup2_x2() {
        Operand op1 = pop();
        Operand op2 = pop();
        Operand op3 = pop();
        Operand op4 = pop();
        push(op2);
        push(op1);
        push(op4);
        push(op3);
        push(op2);
        push(op1);
    }

    void dup2() {
        //a b
        Operand& b = load(0);
        Operand& a = load(1);

        push(a);
        push(b);
        //a b a b
    }

    void f2d() {
        jfloat val = pop_jfloat();
        push_jdouble((double)val);
    }

    void f2i() {
        jfloat val = pop_jfloat();
        push_jint((int)val);
    }

    void f2l() {
        jfloat val = pop_jfloat();
        push_jlong((long)val);
    }

    void __fcmp() {
        jfloat v2 = pop_jfloat();
        jfloat v1 = pop_jfloat();

        if(v2 == v1) {
            push_jint(0);
        } else if(v1 > v2) {
            push_jint(1);
        } else {
            push_jint(-1);
        }
    }

    void fcmpl() {
        __fcmp();
    }

    void fcmpg() {
        __fcmp();
    }

    void fconst_0() {
        push_jfloat(0.0f);
    }

    void fconst_1() {
        push_jfloat(1.0f);
    }

    void fconst_2() {
        push_jfloat(2.0f);
    }

    void getfield() {
        byte index1 = next_byte();
        byte index2 = next_byte();
        JObject* obj = pop_jobject();

        ensure_not_null(obj);

        u2 index = index1 << 8 | index2;

        JObject* val = ResolveField(index)->Get(obj);

        push_jobject(val);
    }

    void getstatic() {
        byte index1 = next_byte();
        byte index2 = next_byte();

        u2 index = index1 << 8 | index2;

        push(GetStaticVal(index));
    }

    void goto__() {
        byte index1 = next_byte();
        byte index2 = next_byte();

        u2 offset = index1 << 8 | index2;

        skip_ip(offset);
    }

    void goto_w() {
        byte index1 = next_byte();
        byte index2 = next_byte();
        byte index3 = next_byte();
        byte index4 = next_byte();

        int offset = (index1 << 24) | (index2 << 16) | (index3 << 8) | index4;

        skip_ip(offset);
    }

    void i2b() {
        int val = pop_jint();
        jbyte ret = (jbyte)val;

        push_jint(SignedExtend(ret));
    }

    void i2c() {
        int val = pop_jint();
        jchar ret = (jchar)val;

        push_jint(ZeroExtend(ret));
    }

    void i2d() {
        int val = pop_jint();
        jdouble ret = val;
        push_jdouble(ret);
    }

    void i2f() {
        int val = pop_jint();
        jfloat ret = (jfloat)val;
        push_jfloat(ret);
    }

    void i2l() {
        int val = pop_jint();
        jlong ret = val;
        push_jlong(ret);
    }

    void i2s() {
        int val = pop_jint();
        jshort ret = val;
        push_jshort(SignedExtend(ret));
    }

    void iconst_m1() {
        push_jint(-1);
    }

    void iconst_0() {
        push_jint(0);
    }

    void iconst_1() {
        push_jint(1);
    }

    void iconst_2() {
        push_jint(2);
    }

    void iconst_3() {
        push_jint(3);
    }

    void iconst_4() {
        push_jint(4);
    }

    void iconst_5() {
        push_jint(5);
    }

    void if_acmpeq() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        JObject* v2 = pop_jobject();
        JObject* v1 = pop_jobject();

        if(v1 == v2) {
            u2 offset = offset1 << 8 | offset2;
            skip_ip(offset);
        }
    }

    void if_acmpne() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        JObject* v2 = pop_jobject();
        JObject* v1 = pop_jobject();

        if(v1 != v2) {
            u2 offset = offset1 << 8 | offset2;
            skip_ip(offset);
        }
    }

    void ifnonnull() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        JObject* v1 = pop_jobject();
        if(v1 != NULL) {
            u2 offset = offset1 << 8 | offset2;
            skip_ip(offset);
        }
    }

    void ifnull() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        JObject* v1 = pop_jobject();
        if(v1 == NULL) {
            u2 offset = offset1 << 8 | offset2;
            skip_ip(offset);
        }
    }

    void iinc() {
        byte index = next_byte();
        byte constVal = next_byte();

        int val = SignedExtend(constVal);

        int ret = GetLocalInt(index);
        ret += val;
        SetLocalInt(index, ret);
    }

    void instanceof() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        u2 sym = offset1 << 8 | offset2;

        JObject* ref = pop_jobject();
        if(ref == NULL || !IsInstanceOf(ref, sym)) {
            push_jint(0);
        } else {
            push_jint(1);
        }
    }

    void invokedynamic() {
        THROW_UNSUPPORTED()
    }

    void invokeinterface() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();
        byte count = next_byte();
        next_byte();

        u2 sym = offset1 << 8 | offset2;

        Method* method = ResolveMethod(sym);

        InvokeMethod(method);
    }

    void invokespecial() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        u2 sym = offset1 << 8 | offset2;

        Method* method = ResolveMethod(sym);

        InvokeMethod(method);
    }

    void invokestatic() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        u2 sym = offset1 << 8 | offset2;

        Method* method = ResolveMethod(sym);
        InvokeMethod(method);
    }

    void invokevirtual() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        u2 sym = offset1 << 8 | offset2;

        Method* method = ResolveMethod(sym);

        InvokeMethod(method);
    }

    void jsr() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();
        u2 offset = offset1 << 8 | offset2;

        push_jretaddr(offset);
    }

    void jsr_w() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();
        byte offset3 = next_byte();
        byte offset4 = next_byte();

        u4 offset = (offset1 << 24) | (offset2 << 16) | (offset3 << 8) | offset4;

        push_jretaddr(offset);
    }

    void l2d() {
        jlong val = pop_jlong();
        push_jdouble((jdouble)val);
    }

    void l2f() {
        jlong val = pop_jlong();
        push_jfloat((jfloat)val);
    }

    void l2i() {
        jlong val = pop_jlong();
        push_jint((jint)val);
    }

    void lcmp() {
        jlong v2 = pop_jlong();
        jlong v1 = pop_jlong();
        if(v1 == v2) {
            push_jint(0);
        } else if(v1 > v2) {
            push_jint(1);
        } else {
            push_jint(-1);
        }
    }

    void lconst_0() {
        push_jlong(0L);
    }

    void lconst_1() {
        push_jlong(1L);
    }

    void monitorenter() {
        THROW_UNSUPPORTED();
    }

    void monitorexit() {
        THROW_UNSUPPORTED();
    }

    void multianewarray() {
        THROW_UNSUPPORTED();
    }

    void newarray() {

        THROW_UNSUPPORTED();
        /*   int count = pop_jint();
        byte type = next_byte();

        void* list = NULL;

        switch(type){
        case AIT_CHAR:
        case AIT_BYTE:
        case AIT_BOOLEAN:
        case AIT_SHORT:
        case AIT_INT:
        case AIT_LONG:
        case AIT_FLOAT:
        case AIT_DOUBLE:
        }


        JArray* ar = new JArray();

        push_jobject(ar);*/
    }

    void new__() {
        THROW_UNSUPPORTED();

        u2 index = next_u2_sym_index();
        JObject* ref;

        push_jobject(ref);
    }

    void nop() {
        //do nothing
    }

    void pop__() {
        pop();
    }

    void pop2() {
        pop();
        pop();
    }

    void putfield() {
        THROW_UNSUPPORTED();
    }

    void putstatic() {
        THROW_UNSUPPORTED();
    }

    void putfieldVal(jobject obj,  u2 sym, Operand& val) {
        sym = next_u2_sym_index();

        Field* field = ResolveField(sym);
        Klass* klass = field->GetType();

        CheckOperandType(load(0), klass);

        if(!klass->IsPrimitive()) {
            field->Set(NULL, pop_jobject());
            return;
        }

        BasicDataType type = klass->GetType();
        switch(type) {
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
        }

        THROW_ILLEGAL_OPERATE();
    }

    void ret__() {
        set_ip(pop_jretaddr());
    }

    void sipush() {
        byte v1 = next_byte();
        byte v2 = next_byte();
        short ret = v1 << 8 | v2;
        push_jshort(SignedExtend(ret));
    }

    void swap() {
        Operand v1 = pop();
        Operand v2 = pop();

        push(v1);
        push(v2);
    }

    void lookupswitch() {
        align_ip(4);

        int def = next_u4();
        int npair = next_u4();
        int key = pop_jint();

        for (int i = 0; i < npair; ++i) {
            int matchVal = next_u4();
            int offset = next_u4();
            if (key == matchVal) {
                set_ip(offset);
                return;
            }
        }

        set_ip(def);
    }

    void tableswitch() {
        align_ip(4);

        int def = next_u4();
        int low = next_u4();
        int high = next_u4();

        int index = pop_jint();

        if (index < low || index > high) {
            set_ip(def);
        } else {
            skip_ip(index - low);
            set_ip(next_u4());
        }
    }

    void wide() {
        THROW_UNSUPPORTED();
    }

    void ldc() {
        THROW_UNSUPPORTED();
    }

    void ldc_w() {
        THROW_UNSUPPORTED();
    }

    void ldc2_w() {
        THROW_UNSUPPORTED();
    }

    void return__() {
        handle_return();
    }

    void lreturn() {
        __return_val();
    }

    void areturn() {
        __return_val();
    }

    void ireturn() {
        __return_val();
    }

    void dreturn() {
        __return_val();
    }

    void freturn() {
        __return_val();
    }

  private:
    //bool IsIIncWide(byte code);
    //bool IsMuliWide(byte code);

    inline void __return_val() {
        Operand op = pop();

        handle_return();

        current_frame()->stack.push(op);
    }

    inline void __aload(u2 index) {
        push(GetLocalVar(index));
    }

    inline void __dload(u2 index) {
        push(GetLocalVar(index));
    }

    inline void __lload(u2 index) {
        push(GetLocalVar(index));
    }

    inline void __fload(u2 index) {
        push(GetLocalVar(index));
    }

    inline void __iload(u2 index) {
        push(GetLocalVar(index));
    }

    inline void __dstore(u2 index) {
        Operand val = pop();
        SetLocalVar(index, val );
    }

    inline void __lstore(u2 index) {
        Operand val = pop();
        SetLocalVar(index, val);
    }

    inline void __istore(u2 index) {
        Operand val = pop();
        SetLocalVar(index, val );
    }

    inline void __fstore(u2 index) {
        Operand val = pop();
        SetLocalVar(index, val );
    }

    inline void __astore(u2 index) {
        Operand val = pop();
        SetLocalVar(index, val);
    }


  private:

    Operand GetStaticVal(u2 symIdx);

    inline void ensure_not_null(JObject* ref);
    bool IsInstanceOf(JObject* obj, u2 symIdx);
    inline void clear_operand_stack();

    inline void align_ip(int a) {
        set_ip(round_to(current_ip(), 4));
    }

    inline void push_jobject(JObject* val);
    inline void push_jchar(jchar c);
    inline void push_jbool(jbool val);
    inline void push_jbyte(jbyte c);
    inline void push_jshort(jshort val);
    inline void push_jint(jint val);
    inline void push_jlong(jlong val);
    inline void push_jfloat(jfloat val);
    inline void push_jdouble(jdouble val);
    inline void push_jretaddr(u4 offset);

    inline JArray*   pop_jarray();
    inline JObject*  pop_jobject();
    inline jchar     pop_jchar();
    inline jbool	 pop_jbool();
    inline jbyte     pop_jbyte();
    inline jshort    pop_jshort();
    inline jint      pop_jint();
    inline jlong     pop_jlong();
    inline jfloat    pop_jfloat();
    inline jdouble   pop_jdouble();
    inline jint      pop_jretaddr();

    inline jdouble   GetLocalDouble(int index);
    inline jfloat    GetLocalFloat(int index);
    inline jint      GetLocalInt(int index);
    inline void      SetLocalInt(int index, int val);
    inline jbyte     GetLocalByte(int index);


    inline jchar     GetLocalChar(int index);
    inline jlong     GetLocalLong(int index);

    void CheckOperandType(Operand& op, Klass* klass);

    Method* ResolveMethod(u2 sym);
    Field* ResolveField(u2 sym);


    void InvokeMethod(Method* method);

    Operand pop();
    void push(const Operand& op);

    Operand& load(int index);
    void store(int index, const Operand& val);

    byte next_byte();

    inline u4 next_u4();

    inline u2   next_u2_sym_index() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        return offset1 << 8 | offset2;
    }

    int current_ip();
    void skip_ip(int offset);
    void set_ip(int ip);

    void check_object_type(JObject* obj, u2 index);

    inline int ZeroExtend(byte c);
    inline int SignedExtend(byte c);

    inline int ZeroExtend(jbyte c);
    inline int SignedExtend(jbyte c);

    inline int ZeroExtend(jshort c);
    inline int SignedExtend(jshort c);

    inline int ZeroExtend(jchar c);
    inline int SignedExtend(jchar c);

    Klass* ResolveKlassType(u2 index);
    void SetLocalVar(u2 index, Operand val);
    Operand GetLocalVar(u2 index);

    inline void handle_return() {
        delete current_frame();
        framePos_--;
    }

    inline StackFrame* current_frame() {
        return stackFrames_[framePos_];
    }

    bool has_more_code();


  private:
    OperandStack operandStack_;
    int framePos_;
    StackFrame* stackFrames_[MAX_STACK_FRAME];
};




#endif