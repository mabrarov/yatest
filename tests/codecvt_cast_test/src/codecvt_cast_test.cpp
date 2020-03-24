//
// Copyright (c) 2020 Marat Abrarov (abrarov@gmail.com)
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

#include <stdexcept>
#include <locale>
#include <gtest/gtest.h>
#include <codecvt_cast.hpp>

namespace codecvt_cast {

typedef std::codecvt<wchar_t, char, mbstate_t> wide_codecvt_type;

TEST(codecvt_cast_out, empty)
{
  const std::locale sys_locale("C");
  const auto& wide_codecvt = std::use_facet<wide_codecvt_type>(sys_locale);
  ASSERT_EQ("", out(std::wstring(), wide_codecvt));
}

TEST(codecvt_cast_out, latin)
{
  const std::locale sys_locale("C");
  const auto& wide_codecvt = std::use_facet<wide_codecvt_type>(sys_locale);
  ASSERT_EQ("ABc01+)", out(std::wstring(L"ABc01+)"), wide_codecvt));
}

TEST(codecvt_cast_out, bad_cast)
{
  const std::locale sys_locale("C");
  const auto& wide_codecvt = std::use_facet<wide_codecvt_type>(sys_locale);
  ASSERT_THROW(out(std::wstring(L"\u20B5"), wide_codecvt), codecvt_cast::bad_conversion);
}

TEST(codecvt_cast_in, empty)
{
  const std::locale sys_locale("C");
  const auto& wide_codecvt = std::use_facet<wide_codecvt_type>(sys_locale);
  ASSERT_EQ(L"", in(std::string(), wide_codecvt));
}

TEST(codecvt_cast_in, latin)
{
  const std::locale sys_locale("C");
  const auto& wide_codecvt = std::use_facet<wide_codecvt_type>(sys_locale);
  ASSERT_EQ(L"ABc01+)", in(std::string("ABc01+)"), wide_codecvt));
}

} // namespace codecvt_cast
