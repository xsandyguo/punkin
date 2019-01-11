#ifndef INTERPRETER_INTERPRETER_H
#define INTERPRETER_INTERPRETER_H

#include <vector>

#include "classfile/class_file_type.hpp"

#define MAX_STACK_FRAME 256

enum OperandType{
    OP_CHAR         = 1,
    OP_BYTE         ,
    OP_SHORT        ,
    OP_INTEGER      ,
    OP_FLOAT        ,
    OP_LONG         ,
    OP_DOUBLE        ,
    OP_REF          ,
    OP_MAX 
};

class ClassLoader{

};

class Method{
private:
    u1 accessFlags_;
};

class Field{

private:
    u1 accessFlags_;
};

class Klass{
public:
    Klass();
    ~Klass();

    Method* ResolveMethodByName(const char* name);

    void SetMethods(Method** methods, int count);
    void SetFields(Field** fields, int count);
private:
    ClassLoader* classLoader_;
    Method** methods_;
    Field** fields_; 
    ClassFileInfo* classInfo_;
    int fieldCount_;
    int methodCount_;
    char* name_;
};

class KObject{
public:
    KObject(Klass* klass);
    bool IsPrimativeType(); 
private:

    Klass* klass_;
};


KObject::KObject(Klass* klass):klass_(klass){

}

struct ArrayItem{

}


class ArrayObject: public KObject {
public:
    ArrayObject(void* list, int count, OperandType type, Klass* componentType);

public:
    int GetCount();
    OperandType GetItemType();

    inline KObject* GetRefItem(int index) {
        CheckIndex(index);

        KObject** ar = (KObject**) list_;
        return ar[index];
    }
     
    inline byte     GetByteItem(int index){
        CheckIndex(index);

        byte* ar = (byte*)list_;
        return ar[index];
    }
     
    inline char     GetCharItem(int index){
        CheckIndex(index);

        char* ar = (char*)list_;
        return ar[index];
    }

    inline short    GetShortItem(int index){
        CheckIndex(index);
        short* ar = (short*)list_;
        return ar[index];
    }

    inline int      GetIntItem(int index){
        CheckIndex(index);
        int* ar = (int*)list_;
        return ar[index];
    }

    inline long     GetLongItem(int index){
        CheckIndex(index);
        long* ar = (long*)list_;
        return ar[index];
    }

    inline float    GetFloatItem(int index){
        CheckIndex(index);
        float* ar = (float*)list_;
        return ar[index];
    }

    inline double   GetDoubleItem(int index){
        CheckIndex(index);
        double* ar = (double*)list_;
        return ar[index];
    }
     
    inline void SetRefItem(int index, KObject* val){
        CheckIndex(index);
        KObject** ar = (KObject**) list_;
        ar[index] = val;
    }

    inline void SetCharItem(int index, char val){ 
        CheckIndex(index);
        char* ar = (char*)list_;
        ar[index] = val;
    }

    inline void SetByteItem(int index, byte val){ 
        CheckIndex(index);
        byte* ar = (byte*)list_;
        ar[index] = val;
    }

    inline void SetShortItem(int index, short val){ 
        CheckIndex(index);
        short* ar = (short*)list_;
        ar[index] = val;
    }
    inline void SetIntItem(int index, int val){
        CheckIndex(index);
        int* ar = (int*)list_;
        ar[index] = val;
    }
    inline void SetLongItem(int index, long val){ 
        CheckIndex(index);
        long* ar = (long*)list_;
        ar[index] = val;
    }
    inline void SetFloatItem(int index, float val){
        CheckIndex(index);
        float* ar = (float*)list_;
        [index] = val;
    }
    inline void SetDoubleItem(int index, double val){
        CheckIndex(index);
        double* ar = (double*)list_;
        ar[index] = val;
    }

private:
    void CheckIndex(int index);

private:
    int count_;
    void* list_;
    OperandType itemType_;
};


ArrayObject::ArrayObject(void* list, int count, OperandType type)
:list_(list), count_(count), itemType_(type){

}

int ArrayObject::GetCount(){
    return count_;
}

OperandType ArrayObject::GetItemType(){
    return itemType_;
}

void ArrayObject::CheckIndex(int index){
    if(index <0 || index> count_){
        throw "out index";
    }
}


class NativeStack {

};

class JavaStack {

};


struct Operand{
    OperandType type;

    union{
        KObject* refVal;
        char charVal;
        byte byteVal;
        short shortVal;
        int intVal;
        long longVal;
        float floatVal;
        double doubleVal;
    }val;

    void InitVal();

    inline Operand(OperandType type):type(type){

    }

    inline Operand(OperandType type, char val):type(type){
        SetCharVal(val);
    }

    inline Operand(OperandType type, byte val):type(type){
        SetByteVal(val);
    }

    inline Operand(OperandType type, short val):type(type){
        SetShortVal(val);
    }
    inline Operand(OperandType type, int val):type(type){
        SetIntVal(val);
    }

    inline Operand(OperandType type, long val):type(type){
        SetLongVal(val);
    }

    inline Operand(OperandType type, float val):type(type){
        SetFloatVal(val);
    }

    inline Operand(OperandType type, double val):type(type){
        SetDoubleVal(val);
    }

    inline Operand(OperandType type, KObject* val):type(type){
        SetRefVal(val);
    }

    inline char GetCharVal(){return this->val.charVal;}
    inline byte GetByteVal(){return this->val.byteVal;}
    inline short GetShortVal(){return this->val.shortVal;}
    inline int GetIntVal(){return this->val.intVal;}
    inline long GetLongVal(){return this->val.longVal;}
    inline float GetFloatVal(){return this->val.floatVal;}
    inline double GetDoubleVal(){return this->val.doubleVal;}
    inline KObject* GetRefVal(){return this->val.refVal;}

    inline void SetCharVal(char val){this->val.charVal = val;}
    inline void SetByteVal(byte val){this->val.byteVal = val;}
    inline void SetShortVal(short val){this->val.shortVal = val;}
    inline void SetIntVal(int val){this->val.intVal = val;}
    inline void SetLongVal(long val){this->val.longVal = val;}
    inline void SetFloatVal(float val){this->val.floatVal = val;}
    inline void SetDoubleVal(double val){this->val.doubleVal = val;}
    inline void SetRefVal(KObject* val){this->val.refVal = val;}
};


void Operand::InitVal(){
    switch(type){
    case OP_CHAR:
    case OP_SHORT:
    case OP_INTEGER:
    case OP_LONG:
        val.longVal = 0L;
        break;
    case OP_FLOAT:
        val.floatVal = 0.0f;
        break;
    case OP_DOUBLE:
        val.doubleVal = 0.0;
        break;
    }
}

class OperandStack {
public:
    Operand Pop();
    void Push(Operand operand);
private:
    std::vector<Operand> operands_;
};

Operand OperandStack::Pop(){
    Operand ret = operands_.back();
    operands_.pop_back();
}

void OperandStack::Push(Operand operand){
    operands_.push_back(operand);
}

class LocalVariableSolt {
public:
    Operand GetVarVal(int index);
    void SetVarVal(int index, Operand val);

private:

};



class CPU{

public:
    void aaload(){ 
        ArrayObject* ar =  PopArray(); 
        int index = PopInt();

        OperandType type = ar->GetItemType();
         
        switch(type){
        case OP_CHAR:
            PushChar(ar->GetCharItem(index));
            break;
        case OP_SHORT: 
           PushShort(ar->GetShortItem(index));
            break;
        case OP_INTEGER:
            PushInt(ar->GetIntItem(index));
            break;
        case OP_LONG:
            PushLong(ar->GetLongItem(index));
            break;
        case OP_FLOAT:
            PushFloat(ar->GetFloatItem(index));
            break;
        case OP_DOUBLE:
            PushDouble(ar->GetDoubleItem(index));
            break;
        case OP_REF:
            PushRef(ar->GetRefItem(index));
            break;
        } 
    }

    void aastore(){
        ArrayObject* ar =  PopArray(); 
        int index = PopInt();
         
        ar->SetRefItem(index, PopRef());
    }

    void aconst_null(){ 
        PushRef(NULL); 
    }

    void aload(int index){
        Push(localVars_.GetVarVal(index));
    }

    inline void aload_0(){
        aload(0);
    }

    inline void aload_1(){
        aload(1);
    }

    inline void aload_2(){
        aload(2);
    }
    
    inline void aload_3(){
        aload(3);
    }

    void anewarray(){
        byte index1 = NextByte();
        byte index2 = NextByte();

        u2 index = index1 << 8 | index2;
        Klass* klass = ResolveKlassType(index);

        int count = PopInt();
        if(count < 0){
            throw "invalid count";
        }
          
        PushRef(new ArrayObject(new KObject*[count], count, OP_REF, klass));
    }

    void areturn(){
        Operand op = Pop();
         
        DestoryFrame(stackFrames_[framePos_--]);

        JavaStackFrame* frame = currentFrame();
        frame->GetOperandStack().Push(op);
    }

    void arraylength(){  
        PushInt(PopArray()->GetCount());
    }

    inline void astore(){
        astore(NextByte());
    }

    inline void astore(int index){
        SetLocalVar(index, Pop());
    }

    inline void astore0(int index){
        astore(0);
    }

    inline void astore1(int index){
        astore(1);
    }

    inline void astore2(int index){
        astore(2);
    }

    inline void astore3(int index){
        astore(3);
    }

    void athrow(){
        KObject* obj = PopRef(); 
        throw obj;
    }

    void baload(){ 
        ArrayObject* ar = PopArray(); 
        int index = PopInt();

        PushByte(ar->GetCharItem(index));
    }

    void bastore(){ 
        ArrayObject* ar = PopArray();
         
        int index = PopInt();
        char c = PopChar();

        ar->SetCharItem(index, c);
    }

    void bipush(){ 
        PushInt(SignedExtend(NextByte()));
    }

    // zero-extended                                                          
    void caload(){ 
        char c = PopArray()->GetCharItem(PopInt()); 
        PushInt(ZeroExtend(c));
    }

    void castore(){  
        PopArray()->SetCharItem(PopInt(), PopChar());
    }

    void cheeckcast(){
        byte byte1 = NextByte();
        byte byte2 = NextByte();

        u2 index = byte1 << 8 | byte2;

        CheckObjectType(Top().GetRefVal(), index);
    }

    void d2f(){
        PushFloat((float)PopDouble());
    }

    void d2i(){ 
        PushInt((int)PopDouble());
    }

    void d2l(){
        PushLong((long)PopDouble());
    }

    void dadd(){ 
        PushDouble(PopDouble() + PopDouble());
    }

    void daload(){

    }

private:
    inline void PushRef(KObject* val);
    inline void PushChar(char c);
    inline void PushByte(byte c);
    inline void PushShort(short val);
    inline void PushInt(int val);
    inline void PushLong(long val);
    inline void PushFloat(float val);
    inline void PushDouble(double val);

    inline ArrayObject* PopArray();
    inline KObject*     PopRef();
    inline char         PopChar();
    inline short        PopShort();
    inline int          PopInt();
    inline long         PopLong();
    inline float        PopFloat();
    inline double       PopDouble();


private:
    Operand Pop();
    Operand Top();
    void Push(Operand op);

    byte NextByte();

    void CheckObjectType(KObject* obj, u2 index);

    inline int ZeroExtend(byte c);
    inline int SignedExtend(byte c);

    Klass* ResolveKlassType(u2 index); 
    void SetLocalVar(int index, Operand val);  
    void PopFrame();
    void DestoryFrame(JavaStackFrame* frame);
    JavaStackFrame* currentFrame();

private:
    OperandStack operandStack_;
    JavaStack javaStack_; 
    LocalVariableSolt localVars_;

    int framePos_;
    JavaStackFrame* stackFrames_[MAX_STACK_FRAME]; 
};

class JavaStackFrame{
public:
    OperandStack& GetOperandStack();

private: 
    OperandStack operandStack_;
    LocalVariableSolt localVars_;
};


#endif