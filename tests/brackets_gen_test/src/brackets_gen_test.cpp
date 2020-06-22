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

#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <brackets_gen_lib.hpp>

namespace yatest {

typedef std::vector<std::string> string_vector;

std::function<void(const std::string&)> output_saver(string_vector& output)
{
  return [&output](const std::string& str)
  {
    output.push_back(str);
  };
}

TEST(gen_brackets, zero_pairs)
{
  string_vector output;
  gen_brackets(0, output_saver(output));
  ASSERT_TRUE(output.empty());
}

TEST(gen_brackets, one_pair)
{
  string_vector output;
  gen_brackets(1, output_saver(output));
  ASSERT_THAT(output, testing::ElementsAre("()"));
}

TEST(gen_brackets, two_pairs)
{
  string_vector output;
  gen_brackets(2, output_saver(output));
  ASSERT_THAT(output, testing::ElementsAre("(())", "()()"));
}

TEST(gen_brackets, three_pairs)
{
  string_vector output;
  gen_brackets(3, output_saver(output));
  ASSERT_THAT(output,
      testing::ElementsAre("((()))", "(()())", "(())()", "()(())", "()()()"));
}

TEST(gen_brackets, four_pairs)
{
  string_vector output;
  gen_brackets(4, output_saver(output));
  ASSERT_THAT(output, testing::ElementsAre(
      "(((())))",
      "((()()))",
      "((())())",
      "((()))()",
      "(()(()))",
      "(()()())",
      "(()())()",
      "(())(())",
      "(())()()",
      "()((()))",
      "()(()())",
      "()(())()",
      "()()(())",
      "()()()()"));
}

} // namespace yatest
