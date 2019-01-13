
#ifndef CPU_X86_VM_BYTES_X86_HPP
#define CPU_X86_VM_BYTES_X86_HPP

#include "utilities/top.hpp"

class Bytes {
 private:
#ifndef AMD64
  // Helper function for swap_u8
  static inline u8   swap_u8_base(u4 x, u4 y);        // compiler-dependent implementation
#endif // AMD64

 public:
  // Returns true if the byte ordering used by Java is different from the native byte ordering
  // of the underlying machine. For example, this is true for Intel x86, but false for Solaris
  // on Sparc.
  static inline bool is_Java_byte_ordering_different(){ return true; }


  // Efficient reading and writing of unaligned unsigned data in platform-specific byte ordering
  // (no special code is needed since x86 CPUs can access unaligned data)
  static inline u2   get_native_u2(addr p)         { return *(u2*)p; }
  static inline u4   get_native_u4(addr p)         { return *(u4*)p; }
  static inline u8   get_native_u8(addr p)         { return *(u8*)p; }

  static inline void put_native_u2(addr p, u2 x)   { *(u2*)p = x; }
  static inline void put_native_u4(addr p, u4 x)   { *(u4*)p = x; }
  static inline void put_native_u8(addr p, u8 x)   { *(u8*)p = x; }


  // Efficient reading and writing of unaligned unsigned data in Java
  // byte ordering (i.e. big-endian ordering). Byte-order reversal is
  // needed since x86 CPUs use little-endian format.
  static inline u2   get_Java_u2(addr p)           { return swap_u2(get_native_u2(p)); }
  static inline u4   get_Java_u4(addr p)           { return swap_u4(get_native_u4(p)); }
  static inline u8   get_Java_u8(addr p)           { return swap_u8(get_native_u8(p)); }

  static inline void put_Java_u2(addr p, u2 x)     { put_native_u2(p, swap_u2(x)); }
  static inline void put_Java_u4(addr p, u4 x)     { put_native_u4(p, swap_u4(x)); }
  static inline void put_Java_u8(addr p, u8 x)     { put_native_u8(p, swap_u8(x)); }


  // Efficient swapping of byte ordering
  static inline u2   swap_u2(u2 x);                   // compiler-dependent implementation
  static inline u4   swap_u4(u4 x);                   // compiler-dependent implementation
  static inline u8   swap_u8(u8 x);
};

 

// Efficient swapping of data bytes from Java byte
// ordering to native byte ordering and vice versa.
inline u2 Bytes::swap_u2(u2 x) {
#ifdef AMD64
  addr p = (addr) &x;
  return  ( (u2(p[0]) << 8 ) | ( u2(p[1])) );
#else
  __asm {
    mov ax, x
    xchg al, ah
  }
  // no return statement needed, result is already in ax
  // compiler warning C4035 disabled via warning pragma
#endif // AMD64
}

inline u4 Bytes::swap_u4(u4 x) {
#ifdef AMD64
  addr p = (addr) &x;
  return ( (u4(p[0]) << 24) | (u4(p[1]) << 16) | (u4(p[2]) << 8) | u4(p[3])) ;
#else
  __asm {
    mov eax, x
    bswap eax
  }
  // no return statement needed, result is already in eax
  // compiler warning C4035 disabled via warning pragma
#endif // AMD64
}

#ifdef AMD64
inline u8 Bytes::swap_u8(u8 x) {
  addr p = (addr) &x;
  return ( (u8(p[0]) << 56) | (u8(p[1]) << 48) | (u8(p[2]) << 40) | (u8(p[3]) << 32) |
           (u8(p[4]) << 24) | (u8(p[5]) << 16) | (u8(p[6]) << 8)  | u8(p[7])) ;
}

#else
// Helper function for swap_u8
inline u8 Bytes::swap_u8_base(u4 x, u4 y) {
  __asm {
    mov eax, y
    mov edx, x
    bswap eax
    bswap edx
  }
  // no return statement needed, result is already in edx:eax
  // compiler warning C4035 disabled via warning pragma
}

inline u8 Bytes::swap_u8(u8 x) {
  return swap_u8_base(*(u4*)&x, *(((u4*)&x)+1));
}
#endif // AMD64

#pragma warning(default: 4035) // Enable warning 4035: no return value


#endif // CPU_X86_VM_BYTES_X86_HPP