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

#ifndef YATEST_TOP_SOLVER_HPP
#define YATEST_TOP_SOLVER_HPP

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <cstdlib>

namespace yatest {

class top
{
public:
  typedef std::pair<std::string, std::size_t> item_type;
  typedef std::vector<item_type> result_type;

  top();

  ~top();

  void apply(const std::string& s);

  result_type count(std::size_t n) const;

private:
  class impl;

  std::unique_ptr<impl> impl_;
};

}

#endif // YATEST_TOP_SOLVER_HPP
