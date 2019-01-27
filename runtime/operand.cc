
#include "runtime/operand.h"


Operand::Operand() :
	type_(BASIC_TYPE_ILLEGAL) {
}

Operand::Operand(const Operand& operand) {
	this->val_ = operand.val_;
	this->type_ = operand.type_;
}