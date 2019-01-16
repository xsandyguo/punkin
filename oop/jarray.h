#ifndef OOP_JARRAY_H
#define OOP_JARRAY_H

#include "oop/jobject.h"

class JArray :      public JObject {
public:
	JArray(addr list, int length, Klass* componentType);

public:
	int GetLength();
	Klass* GetComponentType();

	inline JObject* GetRefItem(int index) {
		CheckIndex(index);

		JObject** ar = (JObject**) dataList_;
		return ar[index];
	}

	inline jbyte     GetByteItem(int index){
		CheckIndex(index);

		jbyte* ar = (jbyte*)dataList_;
		return ar[index];
	}

	inline jchar     GetCharItem(int index){
		CheckIndex(index);

		jchar* ar = (jchar*)dataList_;
		return ar[index];
	}

	inline jshort    GetShortItem(int index){
		CheckIndex(index);
		jshort* ar = (jshort*)dataList_;
		return ar[index];
	}

	inline jint      GetIntItem(int index){
		CheckIndex(index);
		jint* ar = (jint*)dataList_;
		return ar[index];
	}

	inline jlong     GetLongItem(int index){
		CheckIndex(index);
		jlong* ar = (jlong*)dataList_;
		return ar[index];
	}

	inline jfloat    GetFloatItem(int index){
		CheckIndex(index);
		jfloat* ar = (jfloat*)dataList_;
		return ar[index];
	}

	inline jdouble   GetDoubleItem(int index){
		CheckIndex(index);
		jdouble* ar = (jdouble*)dataList_;
		return ar[index];
	}

	inline void SetRefItem(int index, JObject* val){
		CheckIndex(index);
		JObject** ar = (JObject**) dataList_;
		ar[index] = val;
	}

	inline void SetCharItem(int index, jchar val){ 
		CheckIndex(index);
		jchar* ar = (jchar*)dataList_;
		ar[index] = val;
	}

	inline void SetByteItem(int index, jbyte val){ 
		CheckIndex(index);
		jbyte* ar = (jbyte*)dataList_;
		ar[index] = val;
	}

	inline void SetShortItem(int index, jshort val){ 
		CheckIndex(index);
		jshort* ar = (jshort*)dataList_;
		ar[index] = val;
	}

	inline void SetIntItem(int index, jint val){
		CheckIndex(index);
		jint* ar = (jint*)dataList_;
		ar[index] = val;
	}

	inline void SetLongItem(int index, jlong val){ 
		CheckIndex(index);
		jlong* ar = (jlong*)dataList_;
		ar[index] = val;
	}

	inline void SetFloatItem(int index, jfloat val){
		CheckIndex(index);
		jfloat* ar = (jfloat*)dataList_;
		[index] = val;
	}

	inline void SetDoubleItem(int index, jdouble val){
		CheckIndex(index);
		jdouble* ar = (jdouble*)dataList_;
		ar[index] = val;
	}

private:
	void CheckIndex(int index);

private:
	addr dataList_;
	int length_;
	Klass* compoentType_;
};


class JThrowable :  public JObject{};
class JString :     public JObject{};
class BoolArray :   public JArray {};
class ByteArray :   public JArray {};
class CharArray :   public JArray {};
class ShortArray :  public JArray {};
class IntArray :    public JArray {};
class LongArray :   public JArray {};
class FloatArray :  public JArray {};
class DoubleArray : public JArray {};
class ObjectArray : public JArray {};

typedef Klass   *       jclass;
typedef JThrowable *    jthrowable;
typedef JString *       jstring;
typedef JArray *        jarray;
typedef BoolArray *     jbooleanArray;
typedef ByteArray *     jbyteArray;
typedef CharArray *     jcharArray;
typedef ShortArray *    jshortArray;
typedef IntArray *      jintArray;
typedef LongArray *     jlongArray;
typedef FloatArray *    jfloatArray;
typedef DoubleArray *   jdoubleArray;
typedef ObjectArray *   jobjectArray;

#endif