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
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <rle_lib.hpp>

namespace yatest {

TEST(rle, empty)
{
  ASSERT_TRUE(rle("").empty());
}

TEST(rle, single)
{
  ASSERT_EQ("T", rle("T"));
}

TEST(rle, smaller_char_start_throw)
{
  ASSERT_THROW(rle("0ABC"), std::exception);
}

TEST(rle, smaller_char_mid_throw)
{
  ASSERT_THROW(rle("AB0C"), std::exception);
}

TEST(rle, smaller_char_end_throw)
{
  ASSERT_THROW(rle("ABC0"), std::exception);
}

TEST(rle, greater_char_start_throw)
{
  ASSERT_THROW(rle("aABC"), std::exception);
}

TEST(rle, greater_char_mid_throw)
{
  ASSERT_THROW(rle("ABaC"), std::exception);
}

TEST(rle, greater_char_end_throw)
{
  ASSERT_THROW(rle("ABCa"), std::exception);
}

TEST(rle, starts_from_same_single)
{
  ASSERT_THAT(rle("XYYYBXBTTRR"), testing::StartsWith("XY3"));
}

TEST(rle, ends_with_same_single)
{
  ASSERT_THAT(rle("AAAXYRYYBBTTR"), testing::EndsWith("T2R"));
}

TEST(rle, contains_single)
{
  ASSERT_THAT(rle("AABAXYYYBTTRR"), testing::HasSubstr("Y3BT2"));
}

TEST(rle, repeated)
{
  ASSERT_EQ("A2BAXY3BTPTR2U3AP4NMNMNL3E3A3", rle("AABAXYYYBTPTRRUUUAPPPPNMNMNLLLEEEAAA"));
}

} // namespace yatest
