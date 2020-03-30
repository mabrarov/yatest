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

#include <gtest/gtest.h>
#include <anagram_lib.hpp>

namespace yatest {

char_provider str_char_provider(const char* str1, const char* str2)
{
  const char* c = str1;
  const char* str = str1;
  return [c, str, str1, str2]() mutable -> char
  {
    if (c && *c)
    {
      return *c++;
    }
    if (str == str1)
    {
      c = str2;
      str = str2;
    }
    return '\n';
  };
}

TEST(is_anagram, empty)
{
  ASSERT_TRUE(is_anagram(str_char_provider("", "")));
}

TEST(is_anagram, equal)
{
  ASSERT_TRUE(is_anagram(str_char_provider("abcd", "abcd")));
}

TEST(is_anagram, not_equal_anagram)
{
  ASSERT_TRUE(is_anagram(str_char_provider("abcdc", "cdcab")));
}

TEST(is_anagram, not_anagram_same_length)
{
  ASSERT_FALSE(is_anagram(str_char_provider("abcdm", "cdcab")));
}

TEST(is_anagram, shorter)
{
  ASSERT_FALSE(is_anagram(str_char_provider("abcd", "cdcab")));
}

TEST(is_anagram, longer)
{
  ASSERT_FALSE(is_anagram(str_char_provider("abcdca", "cdcab")));
}

} // namespace yatest
