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

#include <unordered_map>
#include <utility>
#include <algorithm>
#include <top_solver.hpp>

class yatest::top::impl
{
public:
  std::unordered_map<std::string, std::size_t> dict;
};

yatest::top::top()
  : impl_(new impl)
{
}

yatest::top::~top()
{
}

void yatest::top::apply(const std::string& s)
{
  ++(impl_->dict[s]);
}

yatest::top::result_type yatest::top::count(std::size_t n) const
{
  typedef std::pair<std::string, std::size_t> dict_item_type;

  result_type result;
  if (0 == n)
  {
    return result;
  }

  auto result_size = (std::min)(n, impl_->dict.size());
  result.reserve(result_size);

  for (const auto& item : impl_->dict)
  {
    const auto begin = result.begin();
    const auto end = result.end();
    const auto lesser = std::upper_bound(begin, end, item,
        [](const dict_item_type& left, const dict_item_type& right)
        {
          return left.second > right.second;
        });
    if (result.size() < n)
    {
      result.insert(lesser, item);
      continue;
    }
    if (lesser == end)
    {
      continue;
    }
    const auto next_lesser = std::next(lesser);
    std::move_backward(lesser, std::prev(end), end);
    *lesser = item;
  }
  return result;
}
