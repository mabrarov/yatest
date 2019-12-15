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
#include <memory>
#include <functional>
#include <iterator>
#include <unordered_map>
#include <algorithm>
#include <top_solver.hpp>

class yatest::top::impl
{
public:
  typedef std::shared_ptr<const std::string> string_shared_ptr;
  typedef const std::string* string_ptr;

  class key
  {
  public:
    key(string_shared_ptr shared_ptr, string_ptr ptr)
      : shared_ptr_(std::move(shared_ptr))
      , ptr_(ptr)
    {
    }

    static key own(const std::string& s)
    {
      return key(std::make_shared<std::string>(s), nullptr);
    }

    static key reference(const std::string& s)
    {
      return key(string_shared_ptr(), &s);
    }

    const std::string& value() const
    {
      if (shared_ptr_)
      {
        return *shared_ptr_;
      }
      return *ptr_;
    }

  private:
    string_shared_ptr shared_ptr_;
    string_ptr ptr_;
  };

  class hash
  {
  public:
    std::size_t operator()(const key& v) const
    {
      return std::hash<std::string>()(v.value());
    }
  };

  class equals_to
  {
  public:
    bool operator()(const key& left, const key& right) const
    {
      return left.value() == right.value();
    }
  };

  typedef std::pair<key, std::size_t> dict_item_type;

  std::unordered_map<key, std::size_t, hash, equals_to> dict;
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
  const auto existing_pos = impl_->dict.find(impl::key::reference(s));
  if (existing_pos == impl_->dict.end())
  {
    impl_->dict.emplace(impl::key::own(s), 1);
  }
  else
  {
    ++existing_pos->second;
  }
}

yatest::top::result_type yatest::top::count(std::size_t n) const
{
  if (0 == n)
  {
    return result_type();
  }
  const auto greater =
      [](const impl::dict_item_type& left, const impl::dict_item_type& right) -> bool
      {
        return left.second > right.second;
      };
  std::vector<impl::dict_item_type> sorted;
  sorted.reserve((std::min)(n, impl_->dict.size()));
  for (const auto& item : impl_->dict)
  {
    const auto size = sorted.size();
    if (size == n && !greater(item, *sorted.rbegin()))
    {
      continue;
    }
    const auto begin = sorted.begin();
    const auto end = sorted.end();
    const auto lesser_pos = std::upper_bound(begin, end, item, greater);
    if (size < n)
    {
      sorted.insert(lesser_pos, item);
      continue;
    }
    std::move_backward(lesser_pos, std::prev(end), end);
    *lesser_pos = item;
  }
  result_type result;
  result.reserve(sorted.size());
  std::transform(sorted.begin(), sorted.end(), std::back_inserter(result),
      [](const impl::dict_item_type& v) -> item_type
      {
        return item_type(v.first.value(), v.second);
      });
  return result;
}
