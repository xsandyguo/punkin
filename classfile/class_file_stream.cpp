#include "classfile/class_file_stream.hpp"
#include "jvm/vm_symbols.hpp"

void ClassFileStream::truncated_file_error() {
  //THROW_MSG(vmSymbols::java_lang_ClassFormatError(), "Truncated class file");
	throw "Truncated class file";
}

ClassFileStream::ClassFileStream(u1* buffer, int length, char* source) {
  _buffer_start = buffer;
  _buffer_end   = buffer + length;
  _current      = buffer;
  _source       = source;
  _need_verify  = false;
}

u1 ClassFileStream::get_u1() {
  if (_need_verify) {
    guarantee_more(1);
  } else {
    assert(1 <= _buffer_end - _current, "buffer overflow");
  }
  return *_current++;
}

u2 ClassFileStream::get_u2() {
  if (_need_verify) {
    guarantee_more(2);
  } else {
    assert(2 <= _buffer_end - _current, "buffer overflow");
  }
  u1* tmp = _current;
  _current += 2;
  return Bytes::get_Java_u2(tmp);
}

u4 ClassFileStream::get_u4() {
  if (_need_verify) {
    guarantee_more(4);
  } else {
    assert(4 <= _buffer_end - _current, "buffer overflow");
  }
  u1* tmp = _current;
  _current += 4;
  return Bytes::get_Java_u4(tmp);
}

u8 ClassFileStream::get_u8() {
  if (_need_verify) {
    guarantee_more(8);
  } else {
    assert(8 <= _buffer_end - _current, "buffer overflow");
  }
  u1* tmp = _current;
  _current += 8;
  return Bytes::get_Java_u8(tmp);
}

void ClassFileStream::skip_u1(int length ) {
  if (_need_verify) {
    guarantee_more(length);
  }
  _current += length;
}

void ClassFileStream::skip_u2(int length) {
  if (_need_verify) {
    guarantee_more(length * 2);
  }
  _current += length * 2;
}

void ClassFileStream::skip_u4(int length) {
  if (_need_verify) {
    guarantee_more(length * 4);
  }
  _current += length * 4;
}
