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

const char MIN_CHAR = 'a';
const char MAX_CHAR = 'z';

}

std::size_t yatest::count_stone_jewellery(const std::string& jewellery,
    const std::string& stones)
{
  std::vector<int> jewelery_set(MAX_CHAR - MIN_CHAR + 1, 0);
  for (const auto j : jewellery)
  {
    if (j < MIN_CHAR || MAX_CHAR < j)
    {
      throw std::invalid_argument(std::string("Jewellery should consist of ")
          + MIN_CHAR + '-' + MAX_CHAR + " only");
    }
    jewelery_set[j - MIN_CHAR] = 1;
  }
  std::size_t count = 0;
  for (const auto s : stones)
  {
    if (s < MIN_CHAR || MAX_CHAR < s)
    {
      throw std::invalid_argument(std::string("Stones should consist of ")
          + MIN_CHAR + '-' + MAX_CHAR + " only");
    }
    count += jewelery_set[s - MIN_CHAR];
  }
  return count;
}
