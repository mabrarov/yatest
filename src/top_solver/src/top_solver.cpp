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

#include <utility>
#include <unordered_map>
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
  const auto greater =
      [](const dict_item_type& left, const dict_item_type& right) -> bool
      {
        return left.second > right.second;
      };
  result.reserve((std::min)(n, impl_->dict.size()));
  for (const auto& item : impl_->dict)
  {
    const auto size = result.size();
    if (size == n && !greater(item, *result.rbegin()))
    {
      continue;
    }
    const auto begin = result.begin();
    const auto end = result.end();
    const auto lesser_pos = std::upper_bound(begin, end, item, greater);
    if (size < n)
    {
      result.insert(lesser_pos, item);
      continue;
    }
    std::move_backward(lesser_pos, std::prev(end), end);
    *lesser_pos = item;
  }
  return result;
}
