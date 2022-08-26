#pragma once

#include <iostream>

//#define USE_WCHAR

#ifdef USE_WCHAR

using char_t = wchar_t;
using string_t = std::wstring;
// std::wostream &console_print = std::wcout;
#else

using char_t = char;
using string_t = std::string;
//std::ostream &console_print = std::cout;

#endif