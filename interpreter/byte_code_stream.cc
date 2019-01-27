 
#include "interpreter/byte_code_stream.h"
#include "interpreter/byte_codes.h"
 

void BytecodeStream::truncated_file_error() {
	//THROW_MSG(vmSymbols::java_lang_ClassFormatError(), "Truncated class file");
	throw "Truncated class file";
}

BytecodeStream::BytecodeStream(u1* buffer, int length) {
	_buffer_start = buffer;
	_buffer_end = buffer + length;
	_current = buffer; 
	_need_verify = false;
}

u1 BytecodeStream::get_u1() {
	if (_need_verify) {
		guarantee_more(1);
	}
	else {
		assert(1 <= _buffer_end - _current, "buffer overflow");
	}
	return *_current++;
}

u2 BytecodeStream::get_u2() {
	if (_need_verify) {
		guarantee_more(2);
	}
	else {
		assert(2 <= _buffer_end - _current, "buffer overflow");
	}
	u1* tmp = _current;
	_current += 2;
	return Bytes::get_Java_u2(tmp);
}


int BytecodeStream::get_u1(u1* buffer, int size) {
	if (_need_verify) {
		guarantee_more(size);
	}
	else {
		assert(size <= _buffer_end - _current, "buffer overflow");
	}
	u1* tmp = _current;
	_current += size;

	for (int i = 0; i < size; ++i) {
		buffer[i] = *tmp++;
	}

	return size;
}


u4 BytecodeStream::get_u4() {
	if (_need_verify) {
		guarantee_more(4);
	}
	else {
		assert(4 <= _buffer_end - _current, "buffer overflow");
	}
	u1* tmp = _current;
	_current += 4;
	return Bytes::get_Java_u4(tmp);
}

u8 BytecodeStream::get_u8() {
	if (_need_verify) {
		guarantee_more(8);
	}
	else {
		assert(8 <= _buffer_end - _current, "buffer overflow");
	}
	u1* tmp = _current;
	_current += 8;
	return Bytes::get_Java_u8(tmp);
}

void BytecodeStream::skip_u1(int length) {
	if (_need_verify) {
		guarantee_more(length);
	}
	_current += length;
}

void BytecodeStream::skip_u2(int length) {
	if (_need_verify) {
		guarantee_more(length * 2);
	}
	_current += length * 2;
}

void BytecodeStream::skip_u4(int length) {
	if (_need_verify) {
		guarantee_more(length * 4);
	}
	_current += length * 4;
}
