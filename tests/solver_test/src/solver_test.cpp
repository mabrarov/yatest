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
#include <solver.hpp>

namespace yatest {

TEST(is_valid_sequence_of_brackets, empty)
{
  ASSERT_TRUE(is_valid_sequence_of_brackets(""));
}

TEST(is_valid_sequence_of_brackets, invalid_char)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets("X"));
}

TEST(is_valid_sequence_of_brackets, invalid_char_with_brackets)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets("(X)"));
}

TEST(is_valid_sequence_of_brackets, single_open_bracket)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets("("));
}

TEST(is_valid_sequence_of_brackets, single_close_bracket)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets(")"));
}

TEST(is_valid_sequence_of_brackets, couple_of_round_brackets)
{
  ASSERT_TRUE(is_valid_sequence_of_brackets("()"));
}

TEST(is_valid_sequence_of_brackets, couple_of_curly_brackets)
{
  ASSERT_TRUE(is_valid_sequence_of_brackets("()"));
}

TEST(is_valid_sequence_of_brackets, couple_of_square_brackets)
{
  ASSERT_TRUE(is_valid_sequence_of_brackets("[]"));
}

TEST(is_valid_sequence_of_brackets, complex)
{
  ASSERT_TRUE(is_valid_sequence_of_brackets("[()[[{}]]({})]"));
}

TEST(is_valid_sequence_of_brackets, missing_right_bracket_in_the_middle)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets("[()[[{]]({})]"));
}

TEST(is_valid_sequence_of_brackets, missing_right_bracket_at_the_beginning)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets("[()[[{}]]({})"));
}

TEST(is_valid_sequence_of_brackets, missing_right_bracket_at_the_end)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets("[]()[[{}]]({}){"));
}

TEST(is_valid_sequence_of_brackets, missing_left_bracket_in_the_middle)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets("[()[]{}}]]({})]"));
}

TEST(is_valid_sequence_of_brackets, missing_left_bracket_at_the_beginning)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets("[]}()[[{}]]({})"));
}

TEST(is_valid_sequence_of_brackets, missing_left_bracket_at_the_end)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets("[]()[[{}]]({}){}]"));
}

TEST(is_valid_sequence_of_brackets, wrong_order_couple)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets(")("));
}

TEST(is_valid_sequence_of_brackets, wrong_order)
{
  ASSERT_FALSE(is_valid_sequence_of_brackets("[]()[[{]}]({}){}"));
}

} // namespace yatest
