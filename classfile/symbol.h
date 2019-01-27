#ifndef CLASS_FILE_SYMBOLE_H
#define CLASS_FILE_SYMBOLE_H

#include "oop/oop.h"
#include <string.h>

class Symbol {
  public:
    Symbol(char* buf, int length);
    ~Symbol();

    enum {
        // max_symbollength_ is constrained by type of length_
        max_symbollength_ = (1 << 16) - 1
    };
  public:
    // Low-level access (used with care, since not GC-safe)
    const jbyte* GetBase() const {
        return &_body[0];
    }

    // Returns the largest size symbol we can safely hold.
    static int GetMaxLength() {
        return max_symbollength_;
    }

    int GetByte(int index) const {
        assert(index >= 0 && index < length_, "symbol index overflow");
        return GetBase()[index];
    }

    const jbyte* GetBytes() const {
        return GetBase();
    }

    int GetUtf8Length() const {
        return length_;
    }

    // Compares the symbol with a string.
    bool Equals(const char* str, int len) const;
    bool Equals(const char* str) const {
        return Equals(str, (int)strlen(str));
    }

    // Tests if the symbol starts with the given prefix.
    bool StartWith(const char* prefix, int len) const;
    bool StartWith(const char* prefix) const {
        return StartWith(prefix, (int)strlen(prefix));
    }

    // Tests if the symbol starts with the given prefix.
    int IndexOf(int i, const char* str, int len) const;
    int IndexOf(int i, const char* str) const {
        return IndexOf(i, str, (int)strlen(str));
    }

    // Three-way compare for sorting; returns -1/0/1 if receiver is </==/> than arg
    // note that the ordering is not alfabetical
    inline int FastCompare(Symbol* other) const;

    // Returns receiver converted to null-terminated UTF-8 string; string is
    // allocated in resource area, or in the char buffer provided by caller.
    char* AsCString() const;
    char* AsCString(char* buf, int size) const;
    // Use buf if needed buffer length is <= size.

    // Returns an escaped form of a Java string.
    char* AsQuotedAscii() const;

    // Returns a null terminated utf8 string in a resource array
    char* AsUtf8() const {
        return AsCString();
    }

    jchar* AsUnicode(int& length) const;

    // Treating this symbol as a class name, returns the Java name for the class.
    // String is allocated in resource area if buffer is not provided.
    // See Klass::external_name()
    const char* AsKlassExternalName() const;
    const char* AsKlassExternalName(char* buf, int size) const;

  private:
    int length_;

    jbyte _body[1];
};


// Note: this comparison is used for vtable sorting only; it doesn't matter
// what order it defines, as long as it is a total, time-invariant order
// Since Symbol*s are in C_HEAP, their relative order in memory never changes,
// so use address comparison for speed
int Symbol::FastCompare(Symbol* other) const {
    return (((uintptr_t)this < (uintptr_t)other) ? -1
            : ((uintptr_t)this == (uintptr_t)other) ? 0 : 1);
}

#endif