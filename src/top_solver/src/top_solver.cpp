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
#include <set>
#include <top_solver.hpp>

class yatest::top::impl
{
public:
  class greater
  {
  public:
    bool operator()(const item_type& left, const item_type& right) const
    {
      return left.second > right.second;
    }
  };

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
  if (0 == n)
  {
    return result_type();
  }
  const impl::greater greater;
  std::multiset<item_type, impl::greater> sorted;
  for (const auto& item : impl_->dict)
  {
    const auto size = sorted.size();
    if (size == n && !greater(item, *sorted.rbegin()))
    {
      continue;
    }
    sorted.emplace(item.first, item.second);
    if (size == n)
    {
      sorted.erase(std::prev(sorted.end()));
    }
  }
  return result_type(sorted.begin(), sorted.end());
}
