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

#ifndef YATEST_BRACKETS_GEN_LIB_HPP
#define YATEST_BRACKETS_GEN_LIB_HPP

#include <cstdlib>
#include <string>
#include <functional>

namespace yatest {

void gen_brackets(std::size_t pair_number,
    std::function<void(const std::string&)> consumer);

}

#endif // YATEST_BRACKETS_GEN_LIB_HPP
