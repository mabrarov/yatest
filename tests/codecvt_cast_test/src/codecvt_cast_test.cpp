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

typedef std::codecvt<wchar_t, char, std::mbstate_t> wide_codecvt_type;
typedef std::codecvt<char, char, std::mbstate_t> noconv_codecvt_type;

TEST(codecvt_cast_out, empty)
{
  const auto& wide_codecvt =
      std::use_facet<wide_codecvt_type>(std::locale::classic());
  ASSERT_EQ("", out(std::wstring(), wide_codecvt));
}

TEST(codecvt_cast_out, latin)
{
  const auto& wide_codecvt =
      std::use_facet<wide_codecvt_type>(std::locale::classic());
  ASSERT_EQ("ABc01+)", out(std::wstring(L"ABc01+)"), wide_codecvt));
}

TEST(codecvt_cast_out, noconv)
{
  const auto& noconv_codecvt =
      std::use_facet<noconv_codecvt_type>(std::locale::classic());
  ASSERT_EQ("test", out(std::string("test"), noconv_codecvt));
}

TEST(codecvt_cast_out, bad_cast)
{
  const auto& wide_codecvt =
      std::use_facet<wide_codecvt_type>(std::locale::classic());
  ASSERT_THROW(out(std::wstring(L"\u20B5"), wide_codecvt), codecvt_cast::bad_conversion);
}

TEST(codecvt_cast_in, empty)
{
  const auto& wide_codecvt =
      std::use_facet<wide_codecvt_type>(std::locale::classic());
  ASSERT_EQ(L"", in(std::string(), wide_codecvt));
}

TEST(codecvt_cast_in, latin)
{
  const auto& wide_codecvt =
      std::use_facet<wide_codecvt_type>(std::locale::classic());
  ASSERT_EQ(L"ABc01+)", in(std::string("ABc01+)"), wide_codecvt));
}

TEST(codecvt_cast_in, noconv)
{
  const auto& noconv_codecvt =
      std::use_facet<noconv_codecvt_type>(std::locale::classic());
  ASSERT_EQ("test", in(std::string("test"), noconv_codecvt));
}

} // namespace codecvt_cast
