 
#include "interpreter/byte_code_stream.h"
#include "interpreter/byte_codes.h"

Bytecodes::Code RawBytecodeStream::raw_next_special(Bytecodes::Code code) {
    assert(!is_last_bytecode(), "should have been checked");
    // set next bytecode position
    address bcp = RawBytecodeStream::bcp();
    address end = method()->code_base() + end_bci();
    int l = Bytecodes::raw_special_length_at(bcp, end);
    if (l <= 0 || (_bci + l) > _end_bci) {
        code = Bytecodes::_illegal;
    } else {
        _next_bci += l;
        assert(_bci < _next_bci, "length must be > 0");
        // set attributes
        _is_wide = false;
        // check for special (uncommon) cases
        if (code == Bytecodes::_wide) {
            if (bcp + 1 >= end) {
                code = Bytecodes::_illegal;
            } else {
                code = (Bytecodes::Code)bcp[1];
                _is_wide = true;
            }
        }
    }
    _raw_code = code;
    return code;
}