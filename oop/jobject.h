#ifndef OOP_JOBJECT_H
#define OOP_JOBJECT_H

#include "oop/oop.h"

class JObject{
public:
	JObject(Klass* klass);
	bool IsPrimativeType(); 

	JObject* GetRefFieldVal(u2 symIdx);
	void SetRefFieldVal(u2 symIndx, JObject* val);

	char GetCharFieldVal(u2 symIdx);
	void SetCharFieldVal(u2 symIdx, char val);

	byte GetByteFieldVal(u2 symIdx);
	void SetByteFieldVal(u2 symIdx, byte val);

	int GetIntFieldVal(u2 symIdx);
	void SetIntFieldVal(u2 symIdx, int);

	long GetLongFieldVal(u2 symIdx); 
	void SetLongFieldVal(u2 symIdx, long val);

	float GetFloatFieldVal(u2 symIdx);
	void SetFloatFieldVal(u2 symIdx, float val);

	double GetDoubleFieldVal(u2 symIdx); 
	void SetDoubleFieldVal(u2 symIdx, double val);

	addr GetObjectData();

private:
	Klass* klass_;
	addr data_;
};

#endif

