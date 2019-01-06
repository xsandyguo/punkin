#pragma once

#include <Windows.h>
#include "base/debug.h"

inline HRESULT HRESULTFromLastError() {
    DWORD error_code = ::GetLastError();
    ASSERT1(error_code != NO_ERROR);
    HRESULT hr = error_code != NO_ERROR ? HRESULT_FROM_WIN32(error_code) : E_FAIL;
    return hr;
}