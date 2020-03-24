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

#ifndef CODECVT_CAST_HPP
#define CODECVT_CAST_HPP

#include <memory>
#include <cstring>
#include <locale>
#include <string>
#include <stdexcept>

namespace codecvt_cast {

class bad_conversion : public std::runtime_error
{
public:
  bad_conversion()
    : std::runtime_error(std::string())
  {
  }
};

template <typename CharType, typename Byte>
std::basic_string<CharType> in(
    const std::basic_string<Byte>& external_str,
    const std::codecvt<CharType, Byte, mbstate_t>& codecvt)
{
  typedef std::basic_string<CharType> wstring;
  typedef std::basic_string<Byte>     string;
  typedef std::codecvt<CharType, Byte, mbstate_t> codecvt_type;

  typename string::size_type external_str_size = external_str.length();
  const Byte* first_external = external_str.data();
  const Byte* last_external  = first_external + external_str_size;
  const Byte* next_external  = last_external;

  wstring internal_str;

  // Zero initialized
  typename codecvt_type::state_type state;
  std::memset(&state, 0, sizeof(state));

  typename wstring::size_type out_buf_size =
      static_cast<typename wstring::size_type>(
          codecvt.length(state, first_external, last_external,
              internal_str.max_size()));

  std::unique_ptr<CharType[]> out_buf(new CharType[out_buf_size]);

  CharType* first_internal = out_buf.get();
  CharType* last_internal  = first_internal + out_buf_size;
  CharType* next_internal  = first_internal;

  typename codecvt_type::result r = codecvt.in(state,
      first_external, last_external, next_external,
      first_internal, last_internal, next_internal);

  if (codecvt_type::ok == r)
  {
    internal_str.assign(first_internal, last_internal);
  }
  else if (codecvt_type::noconv == r)
  {
    internal_str.assign(reinterpret_cast<const CharType*>(first_external),
        reinterpret_cast<const CharType*>(last_external));
  }
  else
  {
    throw bad_conversion();
  }

  return internal_str;
}

template <typename CharType, typename Byte>
std::basic_string<Byte> out(
    const std::basic_string<CharType>& internal_str,
    const std::codecvt<CharType, Byte, mbstate_t>& codecvt)
{
  typedef std::basic_string<CharType> wstring;
  typedef std::basic_string<Byte>     string;
  typedef std::codecvt<CharType, Byte, mbstate_t> codecvt_type;

  string external_str;

  typename wstring::size_type internal_str_size = internal_str.length();
  typename wstring::size_type out_buf_size =
      static_cast<typename wstring::size_type>(codecvt.max_length()) *
          internal_str_size;
  std::unique_ptr<Byte[]> out_buf(new Byte[out_buf_size]);

  const CharType* first_internal = internal_str.data();
  const CharType* last_internal  = first_internal + internal_str_size;
  const CharType* next_internal  = first_internal;

  Byte* first_external = out_buf.get();
  Byte* last_external  = first_external + out_buf_size;
  Byte* next_external  = first_external;

  // Zero initialized
  typename codecvt_type::state_type state;
  std::memset(&state, 0, sizeof(state));

  typename codecvt_type::result r = codecvt.out(state,
      first_internal, last_internal, next_internal,
      first_external, last_external, next_external);

  if (codecvt_type::ok == r)
  {
    external_str.assign(first_external, next_external);
  }
  else if (codecvt_type::noconv == r)
  {
    external_str.assign(reinterpret_cast<const Byte*>(first_internal),
        reinterpret_cast<const Byte*>(last_internal));
  }
  else
  {
    throw bad_conversion();
  }

  return external_str;
}

} // namespace codecvt_cast

#endif // CODECVT_CAST_HPP
