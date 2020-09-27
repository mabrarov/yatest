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

#include <utility>
#include <brackets_gen_lib.hpp>

namespace {

const char open_bracket = '(';
const char close_bracket = ')';

void gen_pairs(std::string& brackets, std::size_t offset,
    std::size_t open_pairs, std::size_t pair_budget,
    std::function<void(const std::string&)> consumer)
{
  if (pair_budget == 0 && open_pairs == 0 && brackets.length() > 0)
  {
    consumer(brackets);
    return;
  }
  if (pair_budget > 0)
  {
    // ...(...
    brackets[offset] = open_bracket;
    gen_pairs(brackets, offset + 1, open_pairs + 1, pair_budget - 1,
        consumer);
  }
  if (open_pairs > 0)
  {
    // ...)...
    brackets[offset] = close_bracket;
    gen_pairs(brackets, offset + 1, open_pairs - 1, pair_budget,
        std::move(consumer));
  }
}

} // anonymous namespace

void yatest::gen_brackets(std::size_t pair_number,
    std::function<void(const std::string&)> consumer)
{
  std::string brackets(pair_number * 2, ' ');
  gen_pairs(brackets, 0, 0, pair_number, std::move(consumer));
}
