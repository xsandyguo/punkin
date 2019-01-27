#include "classfile/symbol.h"
#include "utilities/utf8.h"

Symbol::Symbol(char* buf, int length)
    :  length_(length) {
    jbyte* base =(jbyte*) GetBytes();
    for (int i = 0; i < length; i++) {
        base[i] = (jbyte)buf[i];
    }
}

Symbol::~Symbol() {

}

// ------------------------------------------------------------------
// Symbol::equals
//
// Compares the symbol with a string of the given length.
bool Symbol::Equals(const char* str, int len) const {
    int l = GetUtf8Length();
    if (l != len) return false;
    while (l-- > 0) {
        if (str[l] != (char)GetByte(l))
            return false;
    }
    assert(l == -1, "we should be at the beginning");
    return true;
}


// ------------------------------------------------------------------
// Symbol::starts_with
//
// Tests if the symbol starts with the specified prefix of the given
// length.
bool Symbol::StartWith(const char* prefix, int len) const {
    if (len > GetUtf8Length()) return false;
    while (len-- > 0) {
        if (prefix[len] != (char)GetByte(len))
            return false;
    }
    assert(len == -1, "we should be at the beginning");
    return true;
}


// ------------------------------------------------------------------
// Symbol::index_of
//
// Finds if the given string is a substring of this symbol's utf8 bytes.
// Return -1 on failure.  Otherwise return the first index where str occurs.
int Symbol::IndexOf(int i, const char* str, int len) const {
    assert(i >= 0 && i <= GetUtf8Length(), "oob");
    if (len <= 0)  return 0;
    char first_char = str[0];
    jbyte* bytes = (jbyte*)((Symbol*)this)->GetBase();
    jbyte* limit = bytes + GetUtf8Length() - len;  // inclusive limit
    jbyte* scan = bytes + i;
    if (scan > limit)
        return -1;
    for (; scan <= limit; scan++) {
        scan = (jbyte*)memchr(scan, first_char, (limit + 1 - scan));
        if (scan == NULL)
            return -1;  // not found
        assert(scan >= bytes + i && scan <= limit, "scan oob");
        if (memcmp(scan, str, len) == 0)
            return (int)(scan - bytes);
    }
    return -1;
}

char* Symbol::AsCString(char* buf, int size) const {
    if (size > 0) {
        int len =  size - 1> GetUtf8Length() ? size - 1 : GetUtf8Length();
        for (int i = 0; i < len; i++) {
            buf[i] = GetByte(i);
        }
        buf[len] = '\0';
    }
    return buf;
}

char* Symbol::AsCString() const {
    int len = GetUtf8Length();
    char* str = new char[len + 1];
    return AsCString(str, len + 1);
}

char* Symbol::AsQuotedAscii() const {
    const char *ptr = (const char *)&_body[0];
    int quoted_length = UTF8::GetQuotedAsciiLength(ptr, GetUtf8Length());
    char* result = new char[quoted_length + 1];
    UTF8::AsQuotedAscii(ptr, GetUtf8Length(), result, quoted_length + 1);
    return result;
}

jchar* Symbol::AsUnicode(int& length) const {
    Symbol* this_ptr = (Symbol*)this;
    length = UTF8::GetUnicodeLength((char*)this_ptr->GetBytes(), GetUtf8Length());
    jchar* result = new jchar[length];
    if (length > 0) {
        UTF8::ConvertToUnicode((char*)this_ptr->GetBytes(), result, length);
    }
    return result;
}

const char* Symbol::AsKlassExternalName(char* buf, int size) const {
    if (size > 0) {
        char* str = AsCString(buf, size);
        int   length = (int)strlen(str);
        // Turn all '/'s into '.'s (also for array klasses)
        for (int index = 0; index < length; index++) {
            if (str[index] == '/') {
                str[index] = '.';
            }
        }
        return str;
    } else {
        return buf;
    }
}

const char* Symbol::AsKlassExternalName() const {
    char* str = AsCString();
    int   length = (int)strlen(str);

    // Turn all '/'s into '.'s (also for array klasses)
    for (int index = 0; index < length; index++) {
        if (str[index] == '/') {
            str[index] = '.';
        }
    }
    return str;
}
