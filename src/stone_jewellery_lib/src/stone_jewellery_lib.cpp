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
#include <algorithm>
#include <vector>
#include <stone_jewellery_lib.hpp>

namespace {

const char MIN_CHAR = 'a';
const char MAX_CHAR = 'z';

void validate_lower_case_latin_only(const std::string& text)
{
  for (const auto c : text)
  {
    if (c < MIN_CHAR || MAX_CHAR < c)
    {
      throw std::invalid_argument("Input text should consist of a-z only");
    }
  }
}

}

std::size_t yatest::count_stone_jewellery(const std::string& jewellery,
    const std::string& stones)
{
  validate_lower_case_latin_only(jewellery);
  validate_lower_case_latin_only(stones);
  std::vector<int> jewelery_set(MAX_CHAR - MIN_CHAR + 1, 0);
  for (const auto c : jewellery)
  {
    jewelery_set[c - MIN_CHAR] = 1;
  }
  return std::count_if(stones.begin(), stones.end(),
      [&jewelery_set](char c)
  {
    return 0 != jewelery_set[c - MIN_CHAR];
  });
}
