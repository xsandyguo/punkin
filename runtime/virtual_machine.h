#ifndef INTERPRETER_VIRTUAL_MACHINE_H
#define INTERPRETER_VIRTUAL_MACHINE_H

#include <vector>

#include "runtime/operand.h"
#include "runtime/stack_frame.h"
#include "oop/jarray.h"
#include "oop/class_loader.h"
#include "oop/klass.h"
#include "jvm/vm_exception.h"
#include "classfile/class_file_type.h"

#define MAX_STACK_FRAME		256


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
    VirtualMachine();
    ~VirtualMachine();

    void throw_java_exception(jobject ex);

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
        u2 index =  next_u2();
        Klass* klass = resolve_klass_sym(index);

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

        throw_java_exception(obj);
    }

    void bipush() {
        push_jint(SignedExtend(next_byte()));
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
        JObject* obj = pop_jobject();

        ensure_not_null(obj);

        __get_field_val(obj, resolve_field_sym(false, next_u2()));
    }

    void getstatic() {
        __get_field_val(NULL, resolve_field_sym(true, next_u2()));;
    }

    void goto__() {
        skip_ip(next_u2());
    }

    void goto_w() {
        skip_ip(current_code().get_u4());
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
        u2 offset = next_u2();

        JObject* v2 = pop_jobject();
        JObject* v1 = pop_jobject();

        if(v1 == v2) {
            skip_ip(offset);
        }
    }

    void if_acmpne() {
        u2 offset = next_u2();

        JObject* v2 = pop_jobject();
        JObject* v1 = pop_jobject();

        if(v1 != v2) {
            skip_ip(offset);
        }
    }

    void ifnonnull() {
        u2 offset = next_u2();

        JObject* v1 = pop_jobject();
        if(v1 != NULL) {
            skip_ip(offset);
        }
    }

    void ifnull() {
        u2 offset = next_u2();

        JObject* v1 = pop_jobject();

        if(v1 == NULL) {
            skip_ip(offset);
        }
    }

    void iinc() {
        byte index = next_byte();

        byte constVal = next_byte();
        int val = SignedExtend(constVal);

        Operand ret = current_frame()->GetVar(index);
        ret.SetIntVal(ret.GetIntVal() + val);
        current_frame()->SetVar(index, ret);
    }

    void checkcast() {
        Klass * klass = resolve_klass_sym(next_u2());

        jobject obj = load(0).GetRefVal();

        if (obj == NULL) {
            return;
        }

        if (!klass->IsInstance(obj)) {
            vmExceptions::java_lang_ClassCastException();
        }
    }

    void instanceof() {
        JObject* ref = pop_jobject();
        Klass* t = resolve_klass_sym(next_u2());

        if(ref == NULL) {
            push_jint(0);
        } else {
            Klass* s = ref->GetKlass();
            push_jint(t->IsAssigableFrom(s) ? 1 : 0);
        }
    }

    void invokedynamic() {
        vmExceptions::java_lang_InternalError();
    }

    void invokeinterface() {
        u2 sym = next_u2();
        byte count = next_byte();
        next_byte();

        // Method* method = resolve_method_sym(sym);

        //  InvokeMethod(method);
    }

    void invokespecial() {
        u2 sym = next_u2();

        // Method* method = resolve_method_sym(sym);

        // InvokeMethod(method);
    }

    void invokestatic() {
        u2 sym = next_u2();

        Klass* klass = current_frame()->GetKlass();
        ConstantPool& constantPool = klass->GetConstantPool();
        ConstPoolMethodRefInfo* methodRef =(ConstPoolMethodRefInfo*)
                                           constantPool.ResolveConstantInfo(sym);
        ConstPoolUtf8Info* klassName = (ConstPoolUtf8Info*)
                                       constantPool.ResolveConstantInfo(methodRef->class_index);
        ConstPoolNameAndTypeInfo* nameAndType = (ConstPoolNameAndTypeInfo*)
                                                constantPool.ResolveConstantInfo(methodRef->name_and_type_index);
        ConstPoolUtf8Info* methodName = (ConstPoolUtf8Info*)
                                        constantPool.ResolveConstantInfo(nameAndType->name_index);
        ConstPoolUtf8Info* methodDesc= (ConstPoolUtf8Info*)
                                       constantPool.ResolveConstantInfo(nameAndType->descriptor_index);

        Klass* methodKlass = klass->GetClassLoader()->LoadClass(std::string(klassName));
        Method* method = methodKlass->GetDeclaredMethod(std::string(methodName->bytes));

        InvokeMethod(NULL, method);
    }

    void invokevirtual() {
        u2 sym = next_u2();

        // Method* method = resolve_method_sym(sym);

        // InvokeMethod(method);
    }

    void jsr() {
        push_jretaddr(next_u2());
    }

    void jsr_w() {
        push_jretaddr(current_code().get_u4());
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
        vmExceptions::java_lang_InternalError();
    }

    void monitorexit() {
        vmExceptions::java_lang_InternalError();
    }

    void multianewarray() {
        vmExceptions::java_lang_InternalError();
    }

    void newarray() {
        vmExceptions::java_lang_InternalError();
    }

    void new__() {
        u2 index = next_u2();
        JObject* ref;

        push_jobject(ref);
    }

    void nop() {
    }

    void pop__() {
        pop();
    }

    void pop2() {
        pop();
        pop();
    }

    void putfield() {
        vmExceptions::java_lang_InternalError();
    }

    void putstatic() {
        vmExceptions::java_lang_InternalError();
    }

    void ret__() {
        set_ip(pop_jretaddr());
    }

    void sipush() {
        short ret = next_u2();
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
        vmExceptions::java_lang_InternalError();
    }

    void ldc() {
        vmExceptions::java_lang_InternalError();
    }

    void ldc_w() {
        vmExceptions::java_lang_InternalError();
    }

    void ldc2_w() {
        vmExceptions::java_lang_InternalError();
    }

    void return__() {
        return_frame();
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

        return_frame();

        current_frame()->Push(op);
    }

    inline void __aload(u2 index) {
        push(get_local_var(index));
    }

    inline void __dload(u2 index) {
        push(get_local_var(index));
    }

    inline void __lload(u2 index) {
        push(get_local_var(index));
    }

    inline void __fload(u2 index) {
        push(get_local_var(index));
    }

    inline void __iload(u2 index) {
        push(get_local_var(index));
    }

    inline void __dstore(u2 index) {
        Operand val = pop();
        set_local_var(index, val );
    }

    inline void __lstore(u2 index) {
        Operand val = pop();
        set_local_var(index, val);
    }

    inline void __istore(u2 index) {
        Operand val = pop();
        set_local_var(index, val );
    }

    inline void __fstore(u2 index) {
        Operand val = pop();
        set_local_var(index, val );
    }

    inline void __astore(u2 index) {
        Operand val = pop();
        set_local_var(index, val);
    }

    void __fcmp() {
        jfloat v2 = pop_jfloat();
        jfloat v1 = pop_jfloat();

        if (v2 == v1) {
            push_jint(0);
        } else if (v1 > v2) {
            push_jint(1);
        } else {
            push_jint(-1);
        }
    }

    void __get_field_val(jobject obj, Field* field);
    void __set_field_val(jobject obj, Field* field, const Operand& val);
  private:
    void push_jobject(JObject* val);
    void push_jchar(jchar c);
    void push_jbool(jbool val);
    void push_jbyte(jbyte c);
    void push_jshort(jshort val);
    void push_jint(jint val);
    void push_jlong(jlong val);
    void push_jfloat(jfloat val);
    void push_jdouble(jdouble val);
    void push_jretaddr(u4 offset);

    JArray*   pop_jarray();
    JObject*  pop_jobject();
    jchar     pop_jchar();
    jbool	  pop_jbool();
    jbyte     pop_jbyte();
    jshort    pop_jshort();
    jint      pop_jint();
    jlong     pop_jlong();
    jfloat    pop_jfloat();
    jdouble   pop_jdouble();
    jint      pop_jretaddr();

    void align_ip(int a);


    Field* resolve_field_sym(bool isstatic, u2 index);
    //Method* resolve_method_sym(u2 index);
    Klass* resolve_klass_sym(u2 index);

    void InvokeMethod(Method* method);


    void ensure_not_null(JObject* obj);

    Operand pop();
    void push(const Operand& op);

    Operand& load(int index);
    void store(int index, const Operand& val);

    u1 next_byte();
    u2 next_u2();
    u4 next_u4();

    void skip_ip(int offset);
    void set_ip(int ip);

    void set_local_var(u2 index, const Operand& val);
    Operand get_local_var(u2 index);

    void return_frame();

    StackFrame* current_frame();
    BytecodeStream& current_code();

  private:
    int frameTop_;
    StackFrame* stackFrames_[MAX_STACK_FRAME];
};




#endif