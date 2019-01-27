#include "jvm/vm_exception.h"

#include "runtime/virtual_machine.h"
#include "runtime/jthread.h"

namespace vmExceptions {

void java_lang_ClassFormatError() {

}

void java_lang_NullPointerException() {
    JThread* thread = JThread::Current();

    ClassLoader* loader = thread->GetClassLoader();

    Klass* klass = loader->LoadClass("java.lang.NullPointerException");
    jobject obj = NULL;
    thread->GetVM().throw_java_exception(obj);
}

void java_lang_ClassNotFoundException() {

}

void java_lang_NoSuchFieldException() {

}

void java_lang_NoSuchMethodException() {

}

void java_lang_InternalError() {

}

void java_lang_ClassCastException() {

}

}
