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
#include <stone_jewellery_lib.hpp>

namespace yatest {

TEST(count_stone_jewellery, empty_jewellery)
{
  ASSERT_EQ(0, count_stone_jewellery("", "a"));
}

TEST(count_stone_jewellery, empty_stones)
{
  ASSERT_EQ(0, count_stone_jewellery("a", ""));
}

TEST(count_stone_jewellery, empty_jewellery_stones)
{
  ASSERT_EQ(0, count_stone_jewellery("", ""));
}

TEST(count_stone_jewellery, wrong_jewellery)
{
  ASSERT_THROW(count_stone_jewellery("1", "a"), std::exception);
}

TEST(count_stone_jewellery, wrong_stone)
{
  ASSERT_THROW(count_stone_jewellery("a", "Z"), std::exception);
}

TEST(count_stone_jewellery, single_jewellery_and_different_stones)
{
  ASSERT_EQ(0, count_stone_jewellery("a", "bcd"));
}

TEST(count_stone_jewellery, single_stone_and_different_jewellery)
{
  ASSERT_EQ(0, count_stone_jewellery("bcd", "a"));
}

TEST(count_stone_jewellery, jewellery_intersect_one_stone)
{
  ASSERT_EQ(1, count_stone_jewellery("abcdefg", "zwway"));
}

TEST(count_stone_jewellery, duplicate_jewellery_intersect_duplicate_stones)
{
  ASSERT_EQ(4, count_stone_jewellery("aabcadefagbn", "zwwaaybb"));
}

} // namespace yatest
