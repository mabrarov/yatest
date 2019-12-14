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
#include <queue>
#include <top_solver.hpp>

class yatest::top::impl
{
public:
  class greater_item
  {
  public:
    bool operator()(const item_type& left, const item_type& right)
    {
      return left.second > right.second;
    };
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
  std::priority_queue<item_type, std::vector<item_type>, impl::greater_item> top_n;
  for (const auto& item : impl_->dict)
  {
    top_n.emplace(item.first, item.second);
    if (top_n.size() > n)
    {
      top_n.pop();
    }
  }
  result_type result(top_n.size());
  for (auto i = result.rbegin(); !top_n.empty(); ++i)
  {
    (*i) = top_n.top();
    top_n.pop();
  }
  return result;
}
