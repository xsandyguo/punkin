#ifndef CLASSFILE_METHOD_H
#define CLASSFILE_METHOD_H

#include <vector>
#include "oop/oop.h"

class Klass;

class Executable{
public:
	Executable();
	~Executable();
public:
	const char* GetName();
	void        SetName(const char* name);

	int GetModifier();
	void SetModifier(int modifier);

	Klass*      GetDeclareClass();
	void        SetDeclareClass(Klass* klass);

	std::vector<Klass*>& GetParamerterTypes(); 
	void        SetParameterTypes(std::vector<Klass*>& parameterTypes);
	int         GetParameterCount();

	Klass*      GetReturnType();
	void        SetReturnType(Klass* returnType); 

	Klass*      GetType();
	void		SetType(Klass* klass);

	jobject Invoke(jobject obj, std::vector<jobject>& parameters);
private:
	int midifers_;
	Klass* returnType_;
	Klass* klass_;
	const char* name_; 
	std::vector<Klass*> parameterTypes_;
};


class Method : public Executable{

};


class Constructor : public Executable{
public:
	jobject New();
};

#endif