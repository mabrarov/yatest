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

#include <string>
#include <vector>
#include <brackets_solver.hpp>

namespace {

bool is_open_bracket(char c)
{
  return '(' == c
      || '[' == c
      || '{' == c;
}

bool are_pair_brackets(char open_bracket, char close_bracket)
{
  return ('(' == open_bracket && ')' == close_bracket)
      || ('[' == open_bracket && ']' == close_bracket)
      || ('{' == open_bracket && '}' == close_bracket);
}

} // anonymous namespace

bool yatest::is_valid_sequence_of_brackets(const std::string& sequence_of_brackets)
{
  const auto total_brackets = sequence_of_brackets.length();
  // Number of brackets should be even because each bracket should have a pair
  if (total_brackets % 2)
  {
    return false;
  }
  std::vector<char> stack;
  stack.reserve(total_brackets / 2);
  auto remaining_brackets = total_brackets;
  for (const auto current_bracket: sequence_of_brackets)
  {
    --remaining_brackets;
    if (is_open_bracket(current_bracket))
    {
      if (stack.size() >= remaining_brackets)
      {
        // Too many opening brackets - we won't be able to find closing brackets
        // for all of them
        return false;
      }
      // Remember this opening bracket and go to the next one
      stack.push_back(current_bracket);
      continue;
    }
    // Assuming this is a closing bracket
    if (stack.empty())
    {
      // No opening brackets for this closing bracket
      return false;
    }
    const auto last_open_bracket = stack.back();
    if (!are_pair_brackets(last_open_bracket, current_bracket))
    {
      // Last opening bracket has different kind comparing to
      // current closing bracket
      return false;
    }
    // We found a pair for the last opening bracket - let's forget about it now
    stack.pop_back();
  }
  // All brackets should have a pair - there shouldn't be
  // any opening (pending) bracket on the stack
  return stack.empty();
}
