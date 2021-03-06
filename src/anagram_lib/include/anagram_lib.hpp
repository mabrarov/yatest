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

#ifndef YATEST_ANAGRAM_LIB_HPP
#define YATEST_ANAGRAM_LIB_HPP

#include <limits>
#include <functional>

namespace yatest {

typedef std::size_t frequency_type;
typedef std::size_t length_type;
typedef std::function<char()> char_provider;

bool is_anagram(char_provider str,
    frequency_type max_frequency = (std::numeric_limits<frequency_type>::max)(),
    length_type max_length = (std::numeric_limits<length_type>::max)());

}

#endif // YATEST_ANAGRAM_LIB_HPP
