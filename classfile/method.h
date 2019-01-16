#ifndef CLASSFILE_METHOD_H
#define CLASSFILE_METHOD_H


class Method{
public:
	Method(const char* name, int modifier, Klass* returnType,
		Klass* klass_, std::vector<Klass*> parameterTypes);
	~Method();
public:
	const char* GetName();
	void        SetName(const char* name);

	Klass*      GetDeclareClass();
	void        SetDeclareClass(Klass* klass);

	std::vector<Klass*> GetParamerterTypes(); 
	void        SetParameterTypes(std::vector<Klass*> parameterTypes);

	Klass*      GetReturnType();
	void        SetReturnType(Klass* returnType); 
	int         GetParameterCount();

	jobject Invoke(jobject obj, std::vector<jobject>& parameters);
private:
	int midifers_;
	Klass* returnType_;
	Klass* klass_;
	const char* name_; 
	std::vector<Klass*> parameterTypes_;
};



class Constructor : public Method{

};

#endif