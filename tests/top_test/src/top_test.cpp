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

#include <algorithm>
#include <gtest/gtest.h>
#include <top_lib.hpp>

namespace yatest {

TEST(top_n, empty_top_0)
{
  ASSERT_TRUE(top().count(0).empty());
}

TEST(top_n, single_top_0)
{
  top solver;
  solver.apply("x");
  ASSERT_TRUE(solver.count(0).empty());
}

TEST(top_n, empty_top_10)
{
  ASSERT_TRUE(top().count(10).empty());
}

TEST(top_n, single_top_10)
{
  const std::string s = "x";

  top solver;
  solver.apply(s);
  const auto top_10 = solver.count(10);

  ASSERT_EQ(1, top_10.size());
  ASSERT_EQ(s, top_10.front().first);
  ASSERT_EQ(1, top_10.front().second);
}

TEST(top_n, single_empty_top_1)
{
  const std::string s;

  top solver;
  solver.apply(s);
  const auto top_1 = solver.count(1);

  ASSERT_EQ(1, top_1.size());
  ASSERT_EQ(s, top_1.front().first);
  ASSERT_EQ(1, top_1.front().second);
}

TEST(top_n, single_non_empty_top_1)
{
  const std::string s = "x";

  top solver;
  solver.apply(s);
  const auto top_1 = solver.count(1);

  ASSERT_EQ(1, top_1.size());
  ASSERT_EQ(s, top_1.front().first);
  ASSERT_EQ(1, top_1.front().second);
}

TEST(top_n, all_equal_top_10)
{
  const std::size_t n = 10;
  const std::string s = "x";

  top solver;
  for (std::size_t i = 0; i < n; ++i)
  {
    solver.apply(s);
  }
  const auto top_10 = solver.count(n);

  ASSERT_EQ(1, top_10.size());
  ASSERT_EQ(s, top_10.front().first);
  ASSERT_EQ(n, top_10.front().second);
}

TEST(top_n, all_equal_top_more_than_items)
{
  const std::size_t n = 10;
  const std::string s = "x";

  top solver;
  for (std::size_t i = 0; i < n; ++i)
  {
    solver.apply(s);
  }
  const auto top_20 = solver.count(n * 2);

  ASSERT_EQ(1, top_20.size());
  ASSERT_EQ(s, top_20.front().first);
  ASSERT_EQ(n, top_20.front().second);
}

TEST(top_n, once)
{
  const std::string s1 = "a";
  const std::string s2 = "b";
  const std::string s3 = "c";

  top solver;
  solver.apply(s1);
  solver.apply(s2);
  solver.apply(s3);
  const auto top_3 = solver.count(3);

  ASSERT_EQ(3, top_3.size());
  ASSERT_NE(top_3.end(), std::find(top_3.begin(), top_3.end(), top::item_type(s1, 1)));
  ASSERT_NE(top_3.end(), std::find(top_3.begin(), top_3.end(), top::item_type(s2, 1)));
  ASSERT_NE(top_3.end(), std::find(top_3.begin(), top_3.end(), top::item_type(s3, 1)));
}

TEST(top_n, different_frequency_desc_order)
{
  const std::string s1 = "a";
  const std::string s2 = "b";
  const std::string s3 = "c";
  const std::string s4 = "d";
  const std::string s5 = "e";

  top solver;
  solver.apply(s5);
  solver.apply(s5);
  solver.apply(s5);
  solver.apply(s5);
  solver.apply(s5);
  solver.apply(s4);
  solver.apply(s4);
  solver.apply(s4);
  solver.apply(s4);
  solver.apply(s3);
  solver.apply(s3);
  solver.apply(s3);
  solver.apply(s2);
  solver.apply(s2);
  solver.apply(s1);
  const auto top_3 = solver.count(3);

  ASSERT_EQ(3, top_3.size());
  ASSERT_EQ(top_3[0], top::item_type(s5, 5));
  ASSERT_EQ(top_3[1], top::item_type(s4, 4));
  ASSERT_EQ(top_3[2], top::item_type(s3, 3));
}

TEST(top_n, different_frequency_asc_order)
{
  const std::string s1 = "a";
  const std::string s2 = "b";
  const std::string s3 = "c";
  const std::string s4 = "d";
  const std::string s5 = "e";

  top solver;
  solver.apply(s1);
  solver.apply(s2);
  solver.apply(s2);
  solver.apply(s3);
  solver.apply(s3);
  solver.apply(s3);
  solver.apply(s4);
  solver.apply(s4);
  solver.apply(s4);
  solver.apply(s4);
  solver.apply(s5);
  solver.apply(s5);
  solver.apply(s5);
  solver.apply(s5);
  solver.apply(s5);
  const auto top_3 = solver.count(3);

  ASSERT_EQ(3, top_3.size());
  ASSERT_EQ(top_3[0], top::item_type(s5, 5));
  ASSERT_EQ(top_3[1], top::item_type(s4, 4));
  ASSERT_EQ(top_3[2], top::item_type(s3, 3));
}

TEST(top_n, different_frequency_mixed_order)
{
  const std::string s1 = "a";
  const std::string s2 = "b";
  const std::string s3 = "c";
  const std::string s4 = "d";
  const std::string s5 = "e";

  top solver;
  solver.apply(s5);
  solver.apply(s5);
  solver.apply(s5);
  solver.apply(s2);
  solver.apply(s2);
  solver.apply(s3);
  solver.apply(s3);
  solver.apply(s1);
  solver.apply(s3);
  solver.apply(s4);
  solver.apply(s4);
  solver.apply(s4);
  solver.apply(s4);
  solver.apply(s5);
  solver.apply(s5);
  const auto top_3 = solver.count(3);

  ASSERT_EQ(3, top_3.size());
  ASSERT_EQ(top_3[0], top::item_type(s5, 5));
  ASSERT_EQ(top_3[1], top::item_type(s4, 4));
  ASSERT_EQ(top_3[2], top::item_type(s3, 3));
}

TEST(top_n, same_frequency)
{
  const std::string s1 = "a";
  const std::string s2 = "b";
  const std::string s3 = "c";

  top solver;
  solver.apply(s1);
  solver.apply(s2);
  solver.apply(s2);
  solver.apply(s2);
  solver.apply(s3);
  solver.apply(s3);
  solver.apply(s3);
  const auto top_2 = solver.count(2);

  ASSERT_EQ(2, top_2.size());
  ASSERT_NE(top_2.end(), std::find(top_2.begin(), top_2.end(), top::item_type(s2, 3)));
  ASSERT_NE(top_2.end(), std::find(top_2.begin(), top_2.end(), top::item_type(s3, 3)));
}

} // namespace yatest
