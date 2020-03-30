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
#include <vector>
#include <stone_jewellery_lib.hpp>

namespace {

const char min_char = 'a';
const char max_char = 'z';

}

std::size_t yatest::count_stone_jewellery(const std::string& jewellery,
    const std::string& stones)
{
  std::vector<int> jewelery_set(max_char - min_char + 1, 0);
  for (const auto j : jewellery)
  {
    if (j < min_char || max_char < j)
    {
      throw std::invalid_argument(std::string("Jewellery should consist of ")
          + min_char + '-' + max_char + " only");
    }
    jewelery_set[j - min_char] = 1;
  }
  std::size_t count = 0;
  for (const auto s : stones)
  {
    if (s < min_char || max_char < s)
    {
      throw std::invalid_argument(std::string("Stones should consist of ")
          + min_char + '-' + max_char + " only");
    }
    count += jewelery_set[s - min_char];
  }
  return count;
}
