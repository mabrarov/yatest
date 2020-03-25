//
// Copyright (c) 2019 Marat Abrarov (abrarov@gmail.com)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#if defined(WIN32)
#include <tchar.h>
#endif

#if defined(WIN32) && (defined(_UNICODE) || defined(UNICODE))
#define TCHAR_WIDE_CHAR
#else
#undef  TCHAR_WIDE_CHAR
#endif

#include <cstdlib>
#include <exception>
#include <string>
#include <iostream>

#ifdef TCHAR_WIDE_CHAR
#include <locale>
#include <codecvt_cast.hpp>
#endif

#include <rle_lib.hpp>

#if defined(WIN32)
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
  try
  {
#ifdef TCHAR_WIDE_CHAR
    typedef std::codecvt<wchar_t, char, std::mbstate_t> wide_codecvt_type;
    const std::locale sys_locale("");
    const auto& wide_codecvt = std::use_facet<wide_codecvt_type>(sys_locale);
#endif
    if (argc < 2)
    {
#ifdef TCHAR_WIDE_CHAR
      const auto app_name = codecvt_cast::out(std::wstring(argv[0]), wide_codecvt);
#else
      const std::string app_name(argv[0]);
#endif
      std::cerr << "Usage: " << app_name << " <text_to_transform>" << std::endl;
      return EXIT_FAILURE;
    }
#ifdef TCHAR_WIDE_CHAR
    const auto text = codecvt_cast::out(std::wstring(argv[1]), wide_codecvt);
#else
    const std::string text(argv[1]);
#endif
    std::cout << text << '\n' << yatest::rle(text);
    return EXIT_SUCCESS;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Unknown error" << std::endl;
  }
  return EXIT_FAILURE;
} // main
