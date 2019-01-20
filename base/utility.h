#pragma once

#include <atlstr.h>
#include <string>

CString AnsiToWideString(const char *from, int length) ;
std::string WideToAnsiDirect(const std::wstring & in) ;
std::string WideToAnsi(const std::wstring& w);
std::wstring AnsiToWideChar(const std::string& ansi, UINT num_bytes) ;
