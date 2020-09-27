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

#include <cstdlib>
#include <stdexcept>
#include <utility>
#include <rle_lib.hpp>

std::string yatest::rle(const std::string& str)
{
  if (str.empty())
  {
    return std::string();
  }
  const auto length = str.length();
  // Result is at most as long as input str
  std::string result;
  result.reserve(length);
  char prev_char = 0;
  std::size_t prev_char_count = 0;
  for (std::string::size_type i = 0; i < length; ++i)
  {
    const auto current_char = str[i];
    // Validate: str should consist of A-Z symbols only
    if (current_char < 'A' || 'Z' < current_char)
    {
      throw std::invalid_argument(
          std::string("Invalid char \"") + current_char + "\" at "
              + std::to_string(i));
    }
    // First char should be handled separately
    if (result.empty())
    {
      result += current_char;
      prev_char = current_char;
      prev_char_count = 1;
      continue;
    }
    // Handling of subsequent char when there is previous char
    if (current_char == prev_char)
    {
      // Found duplicate
      ++prev_char_count;
      continue;
    }
    // Found new char. First complete handling of previous char
    if (prev_char_count > 1)
    {
      // Store number of chars only if it's greater than one
      result += std::to_string(prev_char_count);
    }
    // Handle new char
    result += current_char;
    prev_char = current_char;
    prev_char_count = 1;
  }
  // Complete handling of last char
  if (prev_char_count > 1)
  {
    result += std::to_string(prev_char_count);
  }
  return std::move(result);
}
