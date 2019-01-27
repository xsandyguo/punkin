#ifndef GC_MEMORY_H
#define GC_MEMORY_H

#include "utilities/top.h"

struct Block {
    u4   tag;
    addr address;
};

struct MemroyConfig {
    u4 capacitySpace;
    u4 usedSpace;
    u4 freeSpace;
};

class MemoryGC {
  public:
    addr Alloc(int length);
    void Recycle();

    static MemoryGC& Instance();

  private:
    void MarkLocalVar();
    void MarkStaticMember();
    void Clean();

  private:
    static MemoryGC* instance_;
    MemroyConfig youngGen_;
    MemroyConfig oldGen_;
    MemroyConfig persistGen_;
};

#endif