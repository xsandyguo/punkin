#ifndef OOP_URL_CLASS_LOADER_H
#define OOP_URL_CLASS_LOADER_H

#include "oop/class_loader.h"


class UrlClassLoader : public ClassLoader {
  public:
    UrlClassLoader(const std::string& jar);
    ~UrlClassLoader();

    virtual Klass* FindClass(const std::string& name);

  private:
    const std::string jar_;
};

#endif