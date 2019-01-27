#ifndef RUNTIME_OPERAND_H
#define RUNTIME_OPERAND_H

#include "oop/oop.h"

class Operand {
  public:
	Operand();
	Operand(const Operand& operand);

    inline Operand(BasicDataType type):
        type_(type) {
    }

    inline Operand(BasicDataType type, jchar val):
        type_(type) {
        SetCharVal(val);
    }

    inline Operand(BasicDataType type, jbyte val):
        type_(type) {
        SetByteVal(val);
    }

	inline Operand(BasicDataType type, jbool val) :
		type_(type) {
		SetBoolVal(val);
	}

    inline Operand(BasicDataType type, jshort val):
        type_(type) {
        SetShortVal(val);
    }

    inline Operand(BasicDataType type, jint val):
        type_(type) {
        SetIntVal(val);
    }

    inline Operand(BasicDataType type, jlong val):
        type_(type) {
        SetLongVal(val);
    }

    inline Operand(BasicDataType type, jfloat val):
        type_(type) {
        SetFloatVal(val);
    }

    inline Operand(BasicDataType type, jdouble val):
        type_(type) {
        SetDoubleVal(val);
    }

    inline Operand(BasicDataType type, JObject* val):
        type_(type) {
        SetRefVal(val);
    }

    inline bool IsCategoryOneType() {
        return type_ != BASIC_TYPE_DOUBLE && type_ != BASIC_TYPE_FLOAT;
    }

    inline bool IsCategoryTwoType() {
        return type_ == BASIC_TYPE_DOUBLE || type_ == BASIC_TYPE_FLOAT;
    }

    inline jchar GetCharVal() {
        return this->val_.c;
    }

    inline jbyte GetByteVal() {
        return this->val_.b;
    }

	inline jbool GetBoolVal() {
		return this->val_.z;
	}

    inline jshort GetShortVal() {
        return this->val_.s;
    }

    inline jint GetIntVal() {
        return this->val_.i;
    }

    inline jlong GetLongVal() {
        return this->val_.j;
    }

    inline jfloat GetFloatVal() {
        return this->val_.f;
    }

    inline jdouble GetDoubleVal() {
        return this->val_.d;
    }

    inline jobject GetRefVal() {
        return this->val_.l;
    }

    inline void SetCharVal(jchar val) {
        this->val_.c = val;
    }

	inline void SetBoolVal(jbool val) {
		this->val_.z = val;
	}

    inline void SetByteVal(jbyte val) {
        this->val_.b = val;
    }

    inline void SetShortVal(jshort val) {
        this->val_.s = val;
    }

    inline void SetIntVal(jint val) {
        this->val_.i = val;
    }

    inline void SetLongVal(jlong val) {
        this->val_.j = val;
    }

    inline void SetFloatVal(jfloat val) {
        this->val_.f = val;
    }

    inline void SetDoubleVal(jdouble val) {
        this->val_.d = val;
    }

    inline void SetRefVal(jobject val) {
        this->val_.l = val;
    }

  private:
    jvalue val_;
    BasicDataType type_;
};

#endif