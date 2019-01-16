#ifndef CLASSFILE_FIELD_H
#define CLASSFILE_FIELD_H



class Field{
public:
	Field();
	~Field();
public:
	const char* GetName();
	void        SetName(const char* name);

	Klass*      GetType();
	void        SetType(Klass* type);

	int         GetModifier();
	void        SetModifier(int modifier);

	int		    GetDataOffset();
	void	    SetDataOffset(int offset);

public:
	jobject     Get(jobject obj);
	jbool       GetBoolean(jobject obj);
	jbyte       GetByte(jobject obj);
	jchar       GetChar(jobject obj);
	jshort      GetShort(jobject obj);
	jint        GetInt(jobject obj);
	jlong       GetLong(jobject obj);
	jfloat      GetFloat(jobject obj);
	jdouble     GetDouble(jobject obj);

	void Set(jobject obj, jobject val);
	void SetBoolean(jobject obj, jbool val);
	void SetByte(jobject obj, jbyte val);
	void SetChar(jobject obj, jchar val);
	void SetShort(jobject obj, jshort val);
	void SetInt(jobject obj, jint val);
	void SetLong(jobject obj, jlong val);
	void SetFloat(jobject obj, jfloat val);
	void SetDouble(jobject obj, jdouble val); 
private:
	inline addr GetFieldData(jobject obj){
		return (char*)obj->GetObjectData()+offset_;
	}
private:
	int offset_;
	const char* name_;
	int modifier_;
	Klass* type_;
};


#endif