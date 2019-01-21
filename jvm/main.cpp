// punkin.cpp : Defines the entry point for the console application.
//

#include <utility>
#include <stdio.h>
#include <stdlib.h>

#include "utilities/top.hpp"
#include "oop/method.h"
#include "oop/klass.h"
#include "runtime/jthread.h"
#include "oop/bootstrap_class_loader.h"

int _tmain(int argc, char** argv[]) {
    BootstrapClassLoader* classLoader =
        new BootstrapClassLoader("D:\\workspace\\java\\target\\classes\\");
    JThread * thread = new JThread(classLoader, "com.petstore.Main");
    thread->Start();

    return 0;
}

