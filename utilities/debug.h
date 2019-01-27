#ifndef UTILITIES_DEBUG_HPP
#define UTILITIES_DEBUG_HPP



// error reporting helper functions
void report_vm_error(const char* file, int line, const char* error_msg,
                     const char* detail_msg = NULL);

void warning(const char* format, ...);


#define assert_msg(p, msg)														 \
do {                                                                         \
    if (!(p)) {                                                              \
      report_vm_error(__FILE__, __LINE__, "assert(" #p ") failed", msg);     \
    }                                                                        \
} while (0);


#define assert

#define THROW_UNSUPPORTED()\
do {                                                                          \
    throw "usupported";   \
} while (0);

#define THROW_ILLEGAL_OPERATE()\
do {                                                                          \
    throw "illegal operate";   \
} while (0);

#endif


