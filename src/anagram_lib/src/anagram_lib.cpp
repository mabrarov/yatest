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

#include <stdexcept>
#include <vector>
#include <string>
#include <anagram_lib.hpp>

namespace {

const char min_char = 'a';
const char max_char = 'z';
const char end_char = '\n';

}

bool yatest::is_anagram(char_provider str, frequency_type max_frequency,
    length_type max_length)
{
  std::vector<frequency_type> dict(max_char - min_char + 1, 0);
  length_type length = 0;
  while (true)
  {
    const char c = str();
    if (end_char == c)
    {
      break;
    }
    if (c < min_char || max_char < c)
    {
      throw std::invalid_argument(
          std::string("Only ") + min_char + '-' + max_char
              + " allowed, but got: " + c);
    }
    if (max_length == length)
    {
      throw std::overflow_error(
          std::string("Length of inputs string is greater than max supported: ")
              + std::to_string(max_length));
    }
    ++length;
    frequency_type& frequency = dict[c - min_char];
    if (max_frequency == frequency)
    {
      throw std::overflow_error(
          std::string("Frequency of ") + c + " is greater than max supported: "
              + std::to_string(max_frequency));
    }
    ++frequency;
  }
  while (true)
  {
    const char c = str();
    if (end_char == c)
    {
      break;
    }
    if (c < min_char || max_char < c)
    {
      throw std::invalid_argument(
          std::string("Only ") + min_char + '-' + max_char
              + " allowed, but got: " + c);
    }
    if (0 == length)
    {
      return false;
    }
    --length;
    frequency_type& frequency = dict[c - min_char];
    if (0 == frequency)
    {
      return false;
    }
    --frequency;
  }
  return 0 == length;
}