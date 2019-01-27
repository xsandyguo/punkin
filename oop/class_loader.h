#ifndef OOP_CLASS_LOADER_H
#define OOP_CLASS_LOADER_H

#include "utilities/top.h"
#include <list>
#include <map>
#include <string>

class Klass;

class ClassLoader {
  public:
    ClassLoader();
    ClassLoader(ClassLoader* parent);
    ~ClassLoader();
  public:
    Klass* LoadClass(const std::string& name);

    static std::list<ClassLoader*>& GetAllInstance();

    std::map<std::string, Klass*>& GetLoadedKlasses();

  protected:
    virtual Klass* FindClass(const std::string& name) = 0;
    Klass* DefineClass(const std::string& name, byte* codes, int length);

    void ResolveKlass(Klass* klass);

  private:
    Klass* FindLoadedKlass(const std::string& name);


  private:
    ClassLoader* parent_;
    std::map<std::string, Klass*> loadedKlass_;
    static std::list<ClassLoader*> instances_;
};

#endif