#ifndef UTILITIES_UTF8_H
#define UTILITIES_UTF8_H

#include "oop/oop.h"

// Low-level interface for UTF8 strings

class UTF8  {
  public:
    // returns the unicode length of a 0-terminated utf8 string
    static int GetUnicodeLength(const char* utf8_str);

    // returns the unicode length of a non-0-terminated utf8 string
    static int GetUnicodeLength(const char* utf8_str, int len);

    // converts a utf8 string to a unicode string
    static void ConvertToUnicode(const char* utf8_str, jchar* unicode_buffer, int unicode_length);

    // returns the quoted ascii length of a utf8 string
    static int GetQuotedAsciiLength(const char* utf8_str, int utf8_length);

    // converts a utf8 string to quoted ascii
    static void AsQuotedAscii(const char* utf8_str, int utf8_length, char* buf, int buflen);

    // converts a quoted ascii string to utf8 string.  returns the original
    // string unchanged if nothing needs to be done.
    static const char* FromQuotedAscii(const char* quoted_ascii_string);

    // decodes the current utf8 character, stores the result in value,
    // and returns the end of the current utf8 chararacter.
    static char* Next(const char* str, jchar* value);

    // decodes the current utf8 character, gets the supplementary character instead of
    // the surrogate pair when seeing a supplementary character in string,
    // stores the result in value, and returns the end of the current utf8 chararacter.
    static char* NextCharacter(const char* str, jint* value);

    // Utility methods
    static const jbyte* Strrchr(const jbyte* base, int length, jbyte c);
    static bool   Equal(const jbyte* base1, int length1, const jbyte* base2, int length2);
    static bool   IsSupplementaryCharacter(const unsigned char* str);
    static jint   GetSupplementaryCharacter(const unsigned char* str);
};


// Low-level interface for UNICODE strings

// A unicode string represents a string in the UTF-16 format in which supplementary
// characters are represented by surrogate pairs. Index values refer to char code
// units, so a supplementary character uses two positions in a unicode string.

class Unicode  {
  public:
    // returns the utf8 size of a unicode character
    static int GetUtf8Size(jchar c);

    // returns the utf8 length of a unicode string
    static int GetUtf8Length(jchar* base, int length);

    // converts a unicode string to utf8 string
    static void ConvertToUtf8(const jchar* base, int length, char* utf8_buffer);

    // converts a unicode string to a utf8 string; result is allocated
    // in resource area unless a buffer is provided.
    static char* AsUtf8(jchar* base, int length);
    static char* AsUtf8(jchar* base, int length, char* buf, int buflen);

    // returns the quoted ascii length of a unicode string
    static int GetQuotedAsciiLength(jchar* base, int length);

    // converts a utf8 string to quoted ascii
    static void AsQuotedAscii(const jchar* base, int length, char* buf, int buflen);
};
#endif
