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

#ifndef YATEST_BRACKETS_LIB_HPP
#define YATEST_BRACKETS_LIB_HPP

#include <string>

namespace yatest {

bool is_valid_sequence_of_brackets(const std::string& sequence_of_brackets);

}

#endif // YATEST_BRACKETS_LIB_HPP
