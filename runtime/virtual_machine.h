#ifndef INTERPRETER_VIRTUAL_MACHINE_H
#define INTERPRETER_VIRTUAL_MACHINE_H

#include <vector>

#include "runtime/operand.h"
#include "oop/class_loader.h"
#include "oop/klass.h"
#include "classfile/class_file_type.hpp"

#define MAX_STACK_FRAME 256


#define INSTRUCT_FUN_IF_ICMP(name, cmp)        \
void if_##name(){                       \
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
    void if_##name(){                    \
        byte offset1 = next_byte();              \
        byte offset2 = next_byte();              \
        int v1 = pop_jint();                     \
        if(v1 cmp 0){                           \
        u2 offset = offset1 << 8 | offset2;     \
        skip_ip(offset);                         \
    }                                           \
}


#define INSTRUCT_FUN_LOAD_STORE_ARRAY(prefix, type)  \
void type##aload(){                                  \
    int index = pop_jint();                          \
    JArray* ar = pop_jarray();                       \
    push_##type(get_##type_array(ar, index));       \
}                                                    \
                                                     \
void type##astore(){                                  \
    double val = pop_##type();                       \
    int index = pop_jint();                          \
    JArray* ar = pop_jarray();                       \
                                                     \
    set_##type_array(index, val)                     \
}

#define INSTRUCT_FUN_LOAD_STORE_VAR(prefix)  \
void prefix##store(int index){          \
    prefix##store(next_byte());                 \
}                                              \
void prefix##store0(int index){         \
    prefix##store(0);                          \
}                                              \
void prefix##store1(int index){         \
    prefix##store(1);                          \
}                                              \
void prefix##store2(int index){         \
    prefix##store(2);                          \
}                                              \
void prefix##store3(int index){         \
    prefix##store(3);                          \
}                                              \
void prefix##load(){                    \
    prefix##load(next_byte());                  \
}                                              \
void prefix##load0(){                   \
    prefix##load(0);                           \
}                                              \
void prefix##load1(){                   \
    prefix##load(1);                           \
}                                              \
void prefix##load2(){                   \
    prefix##load(2);                           \
}                                              \
void prefix##load3(){                   \
    prefix##load(3);                           \
}

#define INSTRUCT_FUN_MATH_CALC(prefix, type) \
void prefix##add(){                          \
    push_##type(pop##type() + pop_##type()); \
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
void prefix##rem(){                          \
    type v2 = pop_##type();                 \
    type v1 = pop_##type();                 \
    push_##type(v1 % v2);                         \
}                                            \

#define INSTRUCT_FUN_FLOAT_REM_CALC(prefix, type) \
void prefix##rem(){                          \
    type v2 = pop_##type();                 \
    type v1 = pop_##type();                 \
                                             \
    type ret = fmod(v1, v2);               \
    push_##type(ret);                         \
}                                            \



#define INSTRUCT_FUN_BIT_CALC(prefix, type) \\
void prefix##or(){                                 \
    ##type v2 = pop_##type();               \
    ##type v1 = pop_##type();               \
    push_##type(v1 | v2);                   \
}                                           \
void prefix##shl(){                                \
    ##type v2 = pop_##type();               \
    ##type v1 = pop_##type();               \
                                            \
    push_##type(v1 << (v2 & 0x2F));         \
}                                           \
void prefix##shr(){                                \
    ##type v2 = pop_##type();               \
    ##type v1 = pop_##type();               \
                                            \
    push_##type(v1 >> (v2 & 0x2F));         \
}                                           \
void prefix##ushl(){                               \
    unsigned ##type v2 = pop_##type();      \
    unsigned ##type v1 = pop_##type();      \
                                            \
    push_##type(v1 << (v2 & 0x2F));         \
}                                           \
void lushr(){                               \
    unsigned ##type v2 = pop_##type();      \
    unsigned ##type v1 = pop_##type();      \
                                            \
    push_##type(v1 >> (v2 & 0x2F));         \
}                                           \
void prefix##xor(){                                \
    ##type v2 = pop_##type();               \
    ##type v1 = pop_##type();               \
                                            \
    push_##type(v1 ^ v2);                   \
}


class NativeStack {

};

class JavaStack {

};


class VirtualMachine {
  public:
    void Execute(Method* method_);

  public:

    INSTRUCT_FUN_LOAD_STORE_VAR(a)
    INSTRUCT_FUN_LOAD_STORE_VAR(d)
    INSTRUCT_FUN_LOAD_STORE_VAR(f)
    INSTRUCT_FUN_LOAD_STORE_VAR(i)
    INSTRUCT_FUN_LOAD_STORE_VAR(l)

    INSTRUCT_FUN_LOAD_STORE_ARRAY(i, jint)
    INSTRUCT_FUN_LOAD_STORE_ARRAY(l, jlong)
    INSTRUCT_FUN_LOAD_STORE_ARRAY(f, jfloat)
    INSTRUCT_FUN_LOAD_STORE_ARRAY(d, jdouble)

    INSTRUCT_FUN_MATH_CALC(d, jdouble)
    INSTRUCT_FUN_MATH_CALC(f, jfloat)
    INSTRUCT_FUN_MATH_CALC(i, jint)
    INSTRUCT_FUN_MATH_CALC(l, jlong)

    INSTRUCT_FUN_FLOAT_REM_CALC(d, jdouble)
    INSTRUCT_FUN_FLOAT_REM_CALC(f, jfloat)

    INSTRUCT_FUN_INT_REM_CALC(i, jint)
    INSTRUCT_FUN_INT_REM_CALC(l, jlnt)

    INSTRUCT_FUN_IF_ICMP(icmp_eq, ==)
    INSTRUCT_FUN_IF_ICMP(icmp_ne, !=)
    INSTRUCT_FUN_IF_ICMP(icmp_lt, <)
    INSTRUCT_FUN_IF_ICMP(icmp_le, <=)
    INSTRUCT_FUN_IF_ICMP(icmp_gt, >)
    INSTRUCT_FUN_IF_ICMP(icmp_ge, >=)

    INSTRUCT_FUN_IF_0CMP(eq, ==)
    INSTRUCT_FUN_IF_0CMP(ne, !=)
    INSTRUCT_FUN_IF_0CMP(lt, <)
    INSTRUCT_FUN_IF_0CMP(le, <=)
    INSTRUCT_FUN_IF_0CMP(gt, >)
    INSTRUCT_FUN_IF_0CMP(ge, >=)

    INSTRUCT_FUN_BIT_CALC(l, jlong)
    INSTRUCT_FUN_BIT_CALC(i, jint)

    void aaload() {
        int index = pop_jint();
        JArray* ar =  pop_jarray();

        BasicDataType type = ar->GetComponentType();

        switch(type) {
        case BASIC_TYPE_CHAR:
            push_jchar(ar->GetCharItem(index));
            break;
        case BASIC_TYPE_SHORT:
            push_jshort(ar->GetShortItem(index));
            break;
        case BASIC_TYPE_INTEGER:
            push_jint(ar->GetIntItem(index));
            break;
        case BASIC_TYPE_LONG:
            push_jlong(ar->GetLongItem(index));
            break;
        case BASIC_TYPE_FLOAT:
            push_jfloat(ar->GetFloatItem(index));
            break;
        case BASIC_TYPE_DOUBLE:
            push_jdouble(ar->GetDoubleItem(index));
            break;
        case BASIC_TYPE_REF:
            push_jref(ar->GetRefItem(index));
            break;
        }
    }

    void aastore() {
        JObject* val = pop_jref();
        int index = pop_jint();
        pop_jarray()->SetRefItem(index, val);
    }

    void aconst_null() {
        push_jref(NULL);
    }


    void anewarray() {
        u2 index =  ReadU2AsSymIndex();
        Klass* klass = ResolveKlassType(index);

        int count = pop_jint();
        if(count < 0) {
            throw "invalid count";
        }

        push_jref(new JArray(new JObject*[count], count, BASIC_TYPE_REF, klass));
    }

    void areturn() {
        Operand op = pop();

        DestoryFrame(stackFrames_[framePos_--]);

        StackFrame* frame = currentFrame();
        frame->GetOperandStack().push(op);
    }

    void arraylength() {
        push_jint(pop_jarray()->GetLength());
    }



    void athrow() {
        THROW_UNSUPPORTED();
    }

    void baload() {
        int index = pop_jint();
        JArray* ar = pop_jarray();

        push_jint(SignedExtend(ar->GetByteItem(index)));
    }

    void bastore() {
        jbyte c = pop_jbyte();
        int index = pop_jint();
        JArray* ar = pop_jarray();

        ar->SetByteItem(index, c);
    }

    void bipush() {
        push_jint(SignedExtend(next_byte()));
    }

    void caload() {
        int index = pop_jint();
        char c = pop_jarray()->GetCharItem(index);
        push_jint(ZeroExtend(c));
    }

    void castore() {
        char c = pop_jchar();
        int index = pop_jint();
        pop_jarray()->SetCharItem(index, c);
    }

    void cheeckcast() {
        byte byte1 = next_byte();
        byte byte2 = next_byte();

        u2 index = byte1 << 8 | byte2;

        ChecJObjectType(top().GetRefVal(), index);
    }

    void d2f() {
        push_jfloat((float)pop_jdouble());
    }

    void d2i() {
        push_jint((int)pop_jdouble());
    }

    void d2l() {
        push_jlong((long)pop_jdouble());
    }


    void dcmp() {
        double val2 = pop_jdouble();
        double val1 = pop_jdouble();

        if(val1 == val2) {
            push_jint(1);
        } else if(val1 > val2) {
            push_jint(1);
        } else {
            push_jint(-1);
        }
    }

    void dcmp1() {
        dcmp();
    }

    void dconst_0() {
        push_jdouble(0.0);
    }

    void dconst_1() {
        push_jdouble(1.0);
    }


    void dreturn() {
        Operand op = pop();

        DestoryFrame(stackFrames_[framePos_--]);

        StackFrame* frame = currentFrame();
        frame->GetOperandStack().push(op);
    }


    void dup() {
        Operand val = top();
        push(val);
    }

    void dup_x1() {
        Operand op1 = pop();
        Operand op2 = pop();

        if(!op1.IsFirstDataType() || !op2.IsFirstDataType()) {
            throw "unsupported";
        }

        push(op1);
        push(op2);
        push(op1);
    }


    void dup_x2() {
        if(GetOperandCount() >= 3 ) {
            Operand& ref1 = top();
            Operand& ref2 = top();
            Operand& ref3 = top();

            if(ref1.IsFirstDataType() && ref2.IsFirstDataType()
                    && ref3.IsFirstDataType()) {
                Operand op1 = pop();
                Operand op2 = pop();
                Operand op3 = pop();
                push(op1);
                push(op3);
                push(op2);
                push(op1);
                return;
            }
        }

        dup_x1();
    }

    void dup2_x1() {
        if(GetOperandCount() >= 3 ) {
            Operand& ref1 = top();
            Operand& ref2 = top();
            Operand& ref3 = top();

            if(ref1.IsFirstDataType() && ref2.IsFirstDataType()
                    && ref3.IsFirstDataType()) {
                Operand op1 = pop();
                Operand op2 = pop();
                Operand op3 = pop();
                push(op2);
                push(op1);
                push(op3);
                push(op2);
                push(op1);
            }
        }

        dup_x1();
    }

    void dup2_x2() {
        if(GetOperandCount()>= 4) {
            Operand& ref1 = top();
            Operand& ref2 = top();
            Operand& ref3 = top();
            Operand& ref4 = top();

            if(ref1.IsFirstDataType() && ref2.IsFirstDataType()
                    && ref3.IsFirstDataType() && ref4.IsFirstDataType()) {
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
                return;
            }
        }

        if(GetOperandCount() >= 3) {
            Operand& ref1 = top();
            Operand& ref2 = top();
            Operand& ref3 = top();

            if(!ref1.IsFirstDataType() && ref2.IsFirstDataType() && ref3.IsFirstDataType()) {
                Operand op1 = pop();
                Operand op2 = pop();
                Operand op3 = pop();
                push(op1);
                push(op3);
                push(op2);
                push(op1);
                return;
            }

            if(ref1.IsFirstDataType() && ref2.IsFirstDataType() && !ref3.IsFirstDataType()) {
                Operand op1 = pop();
                Operand op2 = pop();
                Operand op3 = pop();
                push(op2);
                push(op1);
                push(op3);
                push(op2);
                push(op1);
                return;
            }
        }

        dup_x1();
    }

    void dup_2() {
        if(GetOperandCount() >= 2) {
            Operand& ref1 = top();
            Operand& ref2 = top();

            if(ref1.IsFirstDataType() && ref2.IsFirstDataType()) {
                Operand op1 = pop();
                Operand op2 = pop();

                push(op2);
                push(op1);
                push(op2);
                push(op1);
                return;
            }
        }


        Operand op1 = pop();
        if(!op1.IsFirstDataType()) {
            push(op1);
            push(op1);
            return;
        }

        throw "unsupported";
    }

    void f2d() {
        float val = pop_jfloat();
        push_jdouble((double)val);
    }

    void f2i() {
        float val = pop_jfloat();
        push_jint((int)val);
    }

    void f2l() {
        float val = pop_jfloat();
        push_jlong((long)val);
    }


    void fcmp() {
        float v2 = pop_jfloat();
        float v1 = pop_jfloat();

        if(v2 == v1) {
            push_jint(0);
        } else if(v1 > v2) {
            push_jint(1);
        } else {
            push_jint(-1);
        }
    }

    void fcmp1() {
        fcmp();
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



    void freturn() {
        Operand op = pop();

        DestoryFrame(stackFrames_[framePos_--]);

        StackFrame* frame = currentFrame();
        frame->GetOperandStack().push(op);
    }



    void getfield() {
        byte index1 = next_byte();
        byte index2 = next_byte();
        JObject* obj = pop_jref();

        u2 index = index1 << 8 | index2;
        JObject* val =  obj->GetRefFieldVal(index);
        push_jref(val);
    }

    void getstatic() {
        byte index1 = next_byte();
        byte index2 = next_byte();

        u2 index = index1 << 8 | index2;

        push(GetStaticVal(index));
    }

    void goto_() {
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
        byte ret = (byte)val;

        push_jint(SignedExtend(ret));
    }

    void i2c() {
        int val = pop_jint();
        char ret = (char)val;

        push_jint(ZeroExtend(ret));
    }

    void i2d() {
        int val = pop_jint();
        double ret = val;
        push_jdouble(ret);
    }

    void i2f() {
        int val = pop_jint();
        float ret = val;
        push_jfloat(ret);
    }

    void i2l() {
        int val = pop_jint();
        long ret = val;
        push_jlong(ret);
    }

    void i2s() {
        int val = pop_jint();
        short ret = val;
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

    void if_acmp_eq() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        JObject* v2 = pop_jref();
        JObject* v1 = pop_jref();

        if(v1 == v2) {
            u2 offset = offset1 << 8 | offset2;
            skip_ip(offset);
        }
    }


    void if_acmp_ne() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        JObject* v2 = pop_jref();
        JObject* v1 = pop_jref();

        if(v1 != v2) {
            u2 offset = offset1 << 8 | offset2;
            skip_ip(offset);
        }
    }

    void ifnonnull() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        JObject* v1 = pop_jref();
        if(v1 != NULL) {
            u2 offset = offset1 << 8 | offset2;
            skip_ip(offset);
        }
    }

    void ifnull() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        JObject* v1 = pop_jref();
        if(v1 == NULL) {
            u2 offset = offset1 << 8 | offset2;
            skip_ip(offset);
        }
    }

    void iinc() {
        byte index = next_byte();
        char constVal = next_byte();

        int val = SignedExtend(constVal);

        int ret = GetLocalInt(index);
        ret += val;
        SetLocalInt(index, ret);
    }



    void instanceof() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        u2 sym = offset1 << 8 | offset2;

        JObject* ref = pop_jref();
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
        MethodMeta* meta = method->GetMeta();

        Operand* args = new Operand[meta->GetParameterCount()];
        for(int i = 0; i < meta->GetParameterCount(); ++i) {
            args[i] = pop();
        }

        JObject* ref = pop_jref();

        CheckNullObject(ref);

        StackFrame* frame = new StackFrame();
        stackFrames_[framePos_++] = frame;
        method->Invoke(ref, args);

        framePos_--;
        DestoryFrame(frame);
    }

    void invokespecial() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();


        u2 sym = offset1 << 8 | offset2;

        Method* method = ResolveMethod(sym);
        MethodMeta* meta = method->GetMeta();

        Operand* args = new Operand[meta->GetParameterCount()];
        for(int i = 0; i < meta->GetParameterCount(); ++i) {
            args[i] = pop();
        }

        JObject* ref = pop_jref();

        CheckNullObject(ref);

        StackFrame* frame = new StackFrame();
        stackFrames_[framePos_++] = frame;
        method->Invoke(ref, args);

        framePos_--;
        DestoryFrame(frame);
    }

    void invokestatic() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();


        u2 sym = offset1 << 8 | offset2;

        Method* method = ResolveMethod(sym);
        MethodMeta* meta = method->GetMeta();

        Operand* args = new Operand[meta->GetParameterCount()];
        for(int i = 0; i < meta->GetParameterCount(); ++i) {
            args[i] = pop();
        }

        StackFrame* frame = new StackFrame();
        stackFrames_[framePos_++] = frame;
        method->Invoke(args);

        framePos_--;
        DestoryFrame(frame);
    }

    void invokevirtual() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();


        u2 sym = offset1 << 8 | offset2;

        Method* method = ResolveMethod(sym);
        MethodMeta* meta = method->GetMeta();

        Operand* args = new Operand[meta->GetParameterCount()];
        for(int i = 0; i < meta->GetParameterCount(); ++i) {
            args[i] = pop();
        }

        JObject* ref = pop_jref();

        CheckNullObject(ref);

        StackFrame* frame = new StackFrame();
        stackFrames_[framePos_++] = frame;
        method->Invoke(ref, args);

        framePos_--;
        DestoryFrame(frame);
    }


    void ireturn() {
        Operand op = pop();

        DestoryFrame(stackFrames_[framePos_--]);

        StackFrame* frame = currentFrame();
        frame->GetOperandStack().push(op);
    }

    void jsr() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();
        u2 offset = offset1 << 8 | offset2;

        PushRetAddr(offset);
    }

    void jsr_w() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();
        byte offset3 = next_byte();
        byte offset4 = next_byte();

        u4 offset = (offset1 << 24) | (offset2 << 16) | (offset3 << 8) | offset4;

        PushRetAddr(offset);
    }

    void l2d() {
        long val = pop_jlong();
        push_jdouble(val);
    }

    void l2f() {
        long val = pop_jlong();
        push_jfloat(val);
    }

    void l2i() {
        long val = pop_jlong();
        push_jint(val);
    }

    void lcmp() {
        long v2 = pop_jlong();
        long v1 = pop_jlong();
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


    void lreturn() {

    }

    void lookupswitch() {

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

        push_jref(ar);*/
    }

    void new_obj() {
        u2 index = ReadU2AsSymIndex();
        JObject* ref;

        push_jref(ref);
    }

    void nop() {

    }

    void pop() {
        if(top().IsFirstDataType()) {
            pop();
        } else {
            THROW_ILLEGAL_OPERATE();
        }
    }

    void pop2() {
        if(GetOperandCount() >= 2) {
            Operand& v1 = top();
            Operand& v2 = top(1);

            if(v1.IsFirstDataType() && v2.IsFirstDataType()) {
                pop();
                pop();
                return;
            }
        }


        Operand& v1 = top();
        if(!v1.IsFirstDataType()) {
            pop();
            return;
        }

        THROW_ILLEGAL_OPERATE();
    }

    void putfield() {

    }

    void putstatic() {

    }

    void putfieldVal(jobject obj,  u2 sym, Operand& val) {
        u2 sym = ReadU2AsSymIndex();

        Field* field = ResolveField(sym);
        Klass* klass = field->GetType();


        CheckOperandType(top(), klass);


        if(!klass->IsPrimitiveType()) {
            field->Set(NULL, pop_jref());
            return;
        }


        u1 type = klass->GetValueType();

        switch(type) {
        case JVT_CHAR:
            field->SetChar(NULL, pop_jchar());
            break;
        case JVT_BYTE:
            field->SetByte(NULL, PopByte());
            break;
        case JVT_SHORT:
            field->SetShort(NULL, PopShort());
            break;
        case JVT_INTEGER:
            field->SetInt(NULL, pop_jint());
            break;
        case JVT_LONG:
            field->SetLong(NULL, pop_jlong());
            break;
        case JVT_FLOAT:
            field->SetFloat(NULL, pop_jfloat());
            break;
        case JVT_DOUBLE:
            field->SetDouble(NULL, pop_jdouble());
            break;
        }

        THROW_ILLEGAL_OPERATE();
    }



    void ret_0() {
        SetIP(PopRetAddr());
    }

    void return_0() {
        StackFrame* frame = currentFrame();
        framePos_--;

        DestoryFrame(frame);
    }

    void saload() {

    }
    void sastore() {

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

        if(!v1.IsFirstDataType() || !v2.IsFirstDataType()) {
            THROW_ILLEGAL_OPERATE();
        }

        push(v1);
        push(v2);
    }

    void tableswitch() {
        THROW_UNSUPPORTED();
    }

    void wide() {
        THROW_UNSUPPORTED();
    }


  private:

    bool IsIIncWide(byte code);
    boolean IsMuliWide(byte code);

    void ldc() {
        byte index = next_byte();

    }

    void ldc_w() {

    }

    void ldc2_w() {

    }

    void CheckOperandType(Operand& op, Klass* klass);

    Method* ResolveMethod(u2 sym);
    Field* ResolveField(u2 sym);

    inline void aload(u2 index) {
        push(GetLocalVar(index));
    }

    inline void dload(u2 index) {
        push(GetLocalVar(index));
    }

    inline void lload(u2 index) {
        push(GetLocalVar(index));
    }

    inline void fload(u2 index) {
        push(GetLocalVar(index));
    }

    void iload(u2 index) {
        byte index = next_byte();
        push(GetLocalVar(index));
    }

    inline void dstore(u2 index) {
        Operand val = pop();
        SetLocalVar(index, val );
    }

    inline void lstore(u2 index) {
        Operand val = pop();
        SetLocalVar(index, val);
    }

    inline void istore(u2 index) {
        Operand val = pop();
        SetLocalVar(index, val );
    }

    inline void fstore(u2 index) {
        Operand val = pop();
        SetLocalVar(index, val );
    }


    Operand GetStaticVal(u2 symIdx);

    inline void CheckNullObject(JObject* ref);
    bool IsInstanceOf(JObject* obj, u2 symIdx);
  private:
    inline void push_jref(JObject* val);
    inline void push_jchar(char c);
    inline void push_jbyte(byte c);
    inline void push_jshort(short val);
    inline void push_jint(int val);
    inline void push_jlong(long val);
    inline void push_jfloat(float val);
    inline void push_jdouble(double val);
    inline void push_jretaddr(u4 offset);

    inline JArray*      pop_jarray();
    inline JObject*     pop_jref();
    inline char         pop_jchar();
    inline byte         pop_jbyte();
    inline short        pop_jshort();
    inline int          pop_jint();
    inline long         pop_jlong();
    inline float        pop_jfloat();
    inline double       pop_jdouble();
    inline int          pop_jretaddr();

    inline double       GetLocalDouble(int index);
    inline float        GetLocalFloat(int index);
    inline int          GetLocalInt(int index);
    inline void         SetLocalInt(int index, int val);
    inline byte         GetLocalByte(int index);


    inline char      GetLocalChar(int index);
    inline long      GetLocalLong(int index);
  private:
    Operand pop();
    Operand& top();
    Operand& top(int index);
    Operand& top1();
    Operand& top2();

    int GetOperandCount();
    void push(Operand op);

    byte next_byte();

    inline u2   ReadU2AsSymIndex() {
        byte offset1 = next_byte();
        byte offset2 = next_byte();

        return offset1 << 8 | offset2;
    }

    void skip_ip(int offset);
    void SetIP(int ip);

    void ChecJObjectType(JObject* obj, u2 index);

    inline int ZeroExtend(byte c);
    inline int SignedExtend(byte c);

    Klass* ResolveKlassType(u2 index);
    void SetLocalVar(u2 index, Operand val);
    Operand GetLocalVar(u2 index);
    void PopFrame();
    void DestoryFrame(StackFrame* frame);
    StackFrame* currentFrame();

    bool has_more_code();

  private:
    OperandStack operandStack_;
    JavaStack javaStack_;
    LocalVariableSolt localVars_;

    int framePos_;
    StackFrame* stackFrames_[MAX_STACK_FRAME];
};



#endif