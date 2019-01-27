#ifndef GC_ALLOCATOR_H
#define GC_ALLOCATOR_h


#include <new>        // for placement new
#include <cstddef>    // for ptrdiff_t, size_t
#include <cstdlib>    // for exit()
#include <climits>    // for UINT_MAX
#include <iostream>    // for cerr

namespace gc {

template <class T>
inline T* _allocate(ptrdiff_t n, T*) {
    set_new_handler(0);
    T* tmp = (T*)(::operator new((size_t)(n * sizeof(T))));
    if (tmp == 0) {
        cerr << "alloc memory error!" << endl;
        exit(1);
    }
    return tmp;
}

template <class T>
inline void _deallocate(T* p) {
    ::operator delete(p);
}

template <class T1, class T2>
inline void _construct(T1* p, const T2& value) {
    new(p) T1(value);
}

template <class T>
inline void _destroy(T* p) {
    p->~T();
}

template <class T>
class allocator {
  public:
    typedef T            value_type;
    typedef T*            pointer;
    typedef const T*    const_pointer;
    typedef T&            reference;
    typedef const T&    const_reference;
    typedef size_t        size_type;
    typedef ptrdiff_t    difference_type;

    template <class U>
    struct rebind {
        typedef allocator<U> other;
    };

    pointer address(reference x) {
        return (pointer)&x;
    }

    const_pointer address(const_reference x) const {
        return (const_pointer)&x;
    }

    pointer allocate(size_type n, const void *hint = 0) {
        return _allocate((difference_type)n, (pointer)0); // mark
    }

    void deallocate(pointer p, size_type n) {
        _deallocate(p);
    }

    size_type max_size() const {
        return size_type(UINT_MAX / sizeof(T));
    }

    void construct(pointer p, const T& x) {
        _construct(p, x);
    }

    void destroy(pointer p) {
        _destroy(p);
    }
};
}
#endif
