/* Copyright 21.05.2023 Dmitry S

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <gtest/gtest.h>

#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "s21_containers.h"

using namespace s21;
/*
 * LIST
 */
TEST(s21_list_constructor1, default_constructor) {
  s21::list<int> s21list;
  std::list<int> stdlist;
  ASSERT_EQ(s21list.empty(), stdlist.empty());
  ASSERT_EQ(s21list.size(), stdlist.size());
}

TEST(s21_list_constructor1, copy) { // проверка на утечки
  s21::list<int> s21list(10);
  s21::list<int> stdlist(9);
  s21list = stdlist;
  ASSERT_EQ(s21list.empty(), stdlist.empty());
  ASSERT_EQ(s21list.size(), stdlist.size());
}

TEST(s21_list_constructor1, move_1) { // проверка на утечки
  s21::list<int> s21list(10);
  s21::list<int> stdlist(9);
  s21list = std::move(stdlist);
}

TEST(s21_list_constructor1, move) { // проверка на утечки
  s21::list<int> s21list(10);
  s21::list<int> stdlist = std::move(s21list);
}

TEST(s21_list_constructor2, size_constructor) {
  s21::list<int> s21list(100);
  std::list<int> stdlist(100);
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_constructor2, size_constructor_harder) {
  s21::list<int> s21list(10);
  std::list<int> stdlist(10);
  s21list.push_back(1);
  stdlist.push_back(1);

  s21list.push_front(1);
  stdlist.push_front(1);

  s21list.push_back(1);
  stdlist.push_back(1);

  s21list.pop_front();
  stdlist.pop_front();
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_constructor3, init_constructor) {
  s21::list<int> s21list{734, 5235, 11, 837};
  std::list<int> stdlist{734, 5235, 11, 837};
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_constructor4, init_char_constructor) {
  s21::list<char> s21list{'b', 'c', 'c'};
  std::list<char> stdlist{'b', 'c', 'c'};
  s21::list<char>::iterator s21it = s21list.begin();
  std::list<char>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_constructor5, init_string_constructor) {
  s21::list<std::string> s21list{"hello", "school", "twentyone"};
  std::list<std::string> stdlist{"hello", "school", "twentyone"};
  s21::list<std::string>::iterator s21it = s21list.begin();
  std::list<std::string>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_constructor5, init_string_constructor_with_pop) {
  s21::list<std::string> s21list{"hello", "school", "twentyone"};
  std::list<std::string> stdlist{"hello", "school", "twentyone"};
  s21list.pop_back();
  stdlist.pop_back();
  s21::list<std::string>::iterator s21it = s21list.begin();
  std::list<std::string>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_constructor6, copy_constructor) {
  s21::list<int> s21list{734, 5235, 11, 837};
  std::list<int> stdlist{734, 5235, 11, 837};
  s21::list<int> s21list2(s21list);
  std::list<int> stdlist2(stdlist);
  s21::list<int>::iterator s21it = s21list2.begin();
  std::list<int>::iterator stdit = stdlist2.begin();
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_constructor7, move_constructor) {
  s21::list<int> s21list{734, 5235, 11, 837};
  std::list<int> stdlist{734, 5235, 11, 837};
  s21::list<int> s21list2(std::move(s21list));
  std::list<int> stdlist2(std::move(stdlist));
  s21::list<int>::iterator s21it = s21list2.begin();
  std::list<int>::iterator stdit = stdlist2.begin();
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_constructor8, move_operator_constructor) {
  s21::list<int> s21list{734, 5235, 11, 837};
  std::list<int> stdlist{734, 5235, 11, 837};
  s21::list<int> s21list2 = std::move(s21list);
  std::list<int> stdlist2 = std::move(stdlist);
  s21::list<int>::iterator s21it = s21list2.begin();
  std::list<int>::iterator stdit = stdlist2.begin();
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_front_back, front_back) {
  s21::list<int> s21list;
  std::list<int> stdlist;
  s21list.push_front(100);
  s21list.push_back(616);
  s21list.push_back(3231);
  stdlist.push_front(100);
  stdlist.push_back(616);
  stdlist.push_back(3231);
  ASSERT_EQ(s21list.front(), stdlist.front());
  ASSERT_EQ(s21list.back(), stdlist.back());
}

TEST(s21_list_empty_clear, clear) {
  s21::list<int> s21list;
  std::list<int> stdlist;
  s21list.push_front(100);
  s21list.push_back(616);
  s21list.push_back(3231);
  stdlist.push_front(100);
  stdlist.push_back(616);
  stdlist.push_back(3231);
  s21list.clear();
  stdlist.clear();
  ASSERT_EQ(s21list.size(), stdlist.size());
  ASSERT_EQ(s21list.empty(), stdlist.empty());
}

TEST(s21_list_push_pop, push) {
  s21::list<int> s21list;
  std::list<int> stdlist;
  s21list.push_front(100);
  s21list.push_back(616);
  s21list.push_back(3231);
  stdlist.push_front(100);
  stdlist.push_back(616);
  stdlist.push_back(3231);
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_push_pop, pop) {
  s21::list<int> s21list{727, 515, 230, 817};
  std::list<int> stdlist{727, 515, 230, 817};
  s21list.pop_back();
  stdlist.pop_back();
  ASSERT_EQ(s21list.front(), stdlist.front());
  ASSERT_EQ(s21list.back(), stdlist.back());
  s21list.pop_front();
  stdlist.pop_front();
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
  s21list.clear();
  stdlist.clear();
  ASSERT_EQ(s21list.empty(), stdlist.empty());
}

TEST(s21_list_function, insert) {
  s21::list<int> s21list{727, 515, 230, 817, 411};
  std::list<int> stdlist{727, 515, 230, 817, 411};
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  s21list.insert(s21it, 717);
  stdlist.insert(stdit, 717);
  s21it = s21list.end();
  stdit = stdlist.end();
  s21list.insert(s21it, 636);
  stdlist.insert(stdit, 636);
  ASSERT_EQ(s21list.front(), stdlist.front());
  ++s21it;
  ++stdit;
  s21list.insert(s21it, 23);
  stdlist.insert(stdit, 23);
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_function, erase) {
  s21::list<int> s21list{717, 5335, 123, 187};
  std::list<int> stdlist{717, 5335, 123, 187};
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  s21list.erase(s21it);
  stdlist.erase(stdit);
  ASSERT_EQ(s21list.front(), stdlist.front());
  s21it = s21list.begin();
  stdit = stdlist.begin();
  ++s21it;
  ++stdit;
  s21list.erase(s21it);
  stdlist.erase(stdit);
  s21it = s21list.begin();
  stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_function, erase_one_more) {
  s21::list<int> s21list{717, 5335, 123, 187};
  std::list<int> stdlist{717, 5335, 123, 187};
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  s21list.erase(s21it);
  stdlist.erase(stdit);
  ASSERT_EQ(s21list.front(), stdlist.front());
  s21it = s21list.begin();
  stdit = stdlist.begin();
  ++s21it;
  ++stdit;
  ++s21it;
  ++stdit;
  s21list.erase(s21it);
  stdlist.erase(stdit);
  s21it = s21list.begin();
  stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_function, swap) {
  s21::list<int> s21list{13377, 5335, 0, 83237, 11111};
  s21::list<int> s21list2{15, 31, 3};
  std::list<int> stdlist{13377, 5335, 0, 83237, 11111};
  std::list<int> stdlist2{15, 31, 3};
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  s21list.swap(s21list2);
  stdlist.swap(stdlist2);
  ASSERT_EQ(s21list.size(), stdlist.size());
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_function, merge) {
  s21::list<int> s21list{737, 535, 16, 837, 111321};
  s21::list<int> s21list2{53, 33, 4};
  std::list<int> stdlist{737, 535, 16, 837, 111321};
  std::list<int> stdlist2{53, 33, 4};
  s21list.merge(s21list2);
  stdlist.merge(stdlist2);
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
  ASSERT_EQ(s21list2.empty(), stdlist2.empty());
}

TEST(s21_list_function, merge_2) {
  s21::list<int> s21list{10, 20, 30};
  s21::list<int> s21list2{40, 50, 60};
  std::list<int> stdlist{10, 20, 30};
  std::list<int> stdlist2{40, 50, 60};
  s21list.merge(s21list2);
  stdlist.merge(stdlist2);
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
  ASSERT_EQ(s21list2.empty(), stdlist2.empty());
}

TEST(s21_list_function, splice) {
  s21::list<int> s21list{717, 535, 10, 837, 11131};
  s21::list<int> s21list2{15, 16};
  std::list<int> stdlist{717, 535, 10, 837, 11131};
  std::list<int> stdlist2{15, 16};
  s21::list<int>::const_iterator s21it = s21list.cbegin();
  std::list<int>::const_iterator stdit = stdlist.cbegin();
  s21list.splice(s21it, s21list2);
  stdlist.splice(stdit, stdlist2);
  ASSERT_EQ(s21list.size(), stdlist.size());
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
  ASSERT_EQ(s21list2.empty(), stdlist2.empty());
}

TEST(s21_list_function, splice_plus_plus) {
  s21::list<int> s21list{717, 535, 10, 837, 11131};
  s21::list<int> s21list2{15, 16};
  std::list<int> stdlist{717, 535, 10, 837, 11131};
  std::list<int> stdlist2{15, 16};
  s21::list<int>::const_iterator s21it = s21list.cbegin();
  std::list<int>::const_iterator stdit = stdlist.cbegin();
  ++s21it;
  ++stdit;
  s21list.splice(s21it, s21list2);
  stdlist.splice(stdit, stdlist2);
  ASSERT_EQ(s21list.size(), stdlist.size());
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
  ASSERT_EQ(s21list2.empty(), stdlist2.empty());
}

TEST(s21_list_function, reverse) {
  s21::list<int> s21list{737, 515, 5, 187, 31111};
  std::list<int> stdlist{737, 515, 5, 187, 31111};
  s21list.reverse();
  stdlist.reverse();
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_function, reverse_reverse) {
  s21::list<int> s21list{737, 515, 5, 187, 31111};
  std::list<int> stdlist{737, 515, 5, 187, 31111};

  s21list.reverse();
  stdlist.reverse();

  s21list.reverse();
  stdlist.reverse();

  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_function, unique) {
  s21::list<int> s21list{11, 1, 1, 1, 2322, 222, 23, 313, 3, 3};
  std::list<int> stdlist{11, 1, 1, 1, 2322, 222, 23, 313, 3, 3};
  s21list.unique();
  stdlist.unique();
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_function, unique_one_more) {
  s21::list<int> s21list{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  std::list<int> stdlist{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  s21list.unique();
  stdlist.unique();
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_sort, sort_pos) {
  s21::list<int> s21list{737, 515, 30, 817, 13111};
  std::list<int> stdlist{737, 515, 30, 817, 13111};
  s21list.sort();
  stdlist.sort();
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_sort, sort_neg) {
  s21::list<int> s21list{-737, -515, -30, -817, -13111};
  std::list<int> stdlist{-737, -515, -30, -817, -13111};
  s21list.sort();
  stdlist.sort();
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i < s21list.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_list_iterator, iterator_begin) {
  s21::list<int> s21list{737, 535, 10, 837, 11111};
  s21::list<int>::iterator begin = s21list.begin();
  s21::list<int>::iterator begin_1 = begin;
  ASSERT_TRUE(begin == begin_1);
  ASSERT_FALSE(begin != begin_1);
}

TEST(s21_list_iterator, iterator_end) {
  s21::list<int> s21list{737, 535, 10, 837, 11111};
  s21::list<int>::iterator end = s21list.end();
  s21::list<int>::iterator end_1 = end;
  ASSERT_TRUE(end == end_1);
  ASSERT_FALSE(end != end_1);
}
/*
 * QUEUE
 */
TEST(s21_queue, default_constructor) {
  s21::queue<int> s21queue;
  std::queue<int> stdqueue;
  ASSERT_EQ(s21queue.empty(), stdqueue.empty());
  ASSERT_EQ(s21queue.size(), stdqueue.size());
}

TEST(s21_queue, copy) {
  s21::queue<int> s21queue{1, 2, 3};
  s21::queue<int> stdqueue{2, 3, 4};
  s21queue = stdqueue;
  ASSERT_EQ(s21queue.empty(), stdqueue.empty());
  ASSERT_EQ(s21queue.size(), stdqueue.size());
}

TEST(s21_queue, move_1) {
  s21::queue<int> s21queue{1, 2, 3};
  s21::queue<int> stdqueue{2, 3, 4};
  s21queue = std::move(stdqueue);
}

TEST(s21_queue, move) {
  s21::queue<int> s21queue{1, 2, 3};
  s21::queue<int> stdqueue = std::move(s21queue);
}

TEST(s21_queue, push_pop_front_back_int) {
  s21::queue<int> s21queue;
  std::queue<int> stdqueue;
  s21queue.push(1);
  stdqueue.push(1);
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  s21queue.push(2);
  stdqueue.push(2);
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  s21queue.push(3);
  stdqueue.push(3);
  ASSERT_EQ(s21queue.back(), stdqueue.back());
  s21queue.pop();
  stdqueue.pop();
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  ASSERT_EQ(s21queue.size(), stdqueue.size());
}

TEST(s21_queue_constructor4, push_pop_front_back_char) {
  s21::queue<char> s21queue;
  std::queue<char> stdqueue;
  s21queue.push('a');
  stdqueue.push('a');
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  s21queue.push('b');
  stdqueue.push('b');
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  s21queue.push('c');
  stdqueue.push('c');
  ASSERT_EQ(s21queue.back(), stdqueue.back());
  s21queue.pop();
  stdqueue.pop();
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  ASSERT_EQ(s21queue.size(), stdqueue.size());
}

TEST(s21_queue_constructor5, push_pop_front_back_string) {
  s21::queue<std::string> s21queue;
  std::queue<std::string> stdqueue;
  s21queue.push("hi");
  stdqueue.push("hi");
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  s21queue.push("hello");
  stdqueue.push("hello");
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  s21queue.push("bye");
  stdqueue.push("bye");
  ASSERT_EQ(s21queue.back(), stdqueue.back());
  s21queue.pop();
  stdqueue.pop();
  ASSERT_EQ(s21queue.front(), stdqueue.front());
  ASSERT_EQ(s21queue.size(), stdqueue.size());
}

TEST(s21_queue_constructor6, copy_constructor) {
  s21::queue<int> s21queue({734, 5235, 11, 837});
  std::queue<int> stdqueue({734, 5235, 11, 837});
  s21::queue<int> s21queue2(s21queue);
  std::queue<int> stdqueue2(stdqueue);
  ASSERT_EQ(s21queue2.size(), stdqueue2.size());
  while (!s21queue.empty()) {
    ASSERT_EQ(s21queue.front(), stdqueue.front());
    s21queue.pop();
    stdqueue.pop();
  }
}

TEST(s21_queue_constructor7, move_constructor) {
  s21::queue<int> s21queue({734, 5235, 11, 837});
  std::queue<int> stdqueue({734, 5235, 11, 837});
  s21::queue<int> s21queue2(std::move(s21queue));
  std::queue<int> stdqueue2(std::move(stdqueue));
  ASSERT_EQ(s21queue2.size(), stdqueue2.size());
  while (!s21queue.empty()) {
    ASSERT_EQ(s21queue.front(), stdqueue.front());
    s21queue.pop();
    stdqueue.pop();
  }
}

TEST(s21_queue_constructor8, move_operator_constructor) {
  s21::queue<int> s21queue({734, 5235, 11, 837});
  std::queue<int> stdqueue({734, 5235, 11, 837});
  s21::queue<int> s21queue2 = std::move(s21queue);
  std::queue<int> stdqueue2 = std::move(stdqueue);
  ASSERT_EQ(s21queue2.size(), stdqueue2.size());
  while (!s21queue.empty()) {
    ASSERT_EQ(s21queue.front(), stdqueue.front());
    s21queue.pop();
    stdqueue.pop();
  }
}

TEST(s21_queue_function, swap) {
  s21::queue<int> s21queue({13377, 5335, 0, 83237, 11111});
  s21::queue<int> s21queue2({15, 31, 3});
  std::queue<int> stdqueue({13377, 5335, 0, 83237, 11111});
  std::queue<int> stdqueue2({15, 31, 3});
  s21queue.swap(s21queue2);
  stdqueue.swap(stdqueue2);
  ASSERT_EQ(s21queue.size(), stdqueue.size());
  ASSERT_EQ(s21queue2.size(), stdqueue2.size());
  while (!s21queue.empty()) {
    ASSERT_EQ(s21queue.front(), stdqueue.front());
    s21queue.pop();
    stdqueue.pop();
  }
}
/*
 * STACK
 */
TEST(s21_stack, default_constructor) {
  s21::stack<int> s21stack;
  std::stack<int> stdstack;
  ASSERT_EQ(s21stack.empty(), stdstack.empty());
  ASSERT_EQ(s21stack.size(), stdstack.size());
}

TEST(s21_stack, copy) {
  s21::stack<int> s21stack{1, 2, 3};
  s21::stack<int> stdstack{2, 3, 4};
  s21stack = stdstack;
  ASSERT_EQ(s21stack.empty(), stdstack.empty());
  ASSERT_EQ(s21stack.size(), stdstack.size());
}

TEST(s21_stack, move) {
  s21::stack<int> s21stack{1, 2, 3};
  s21::stack<int> stdstack = std::move(s21stack);
}

TEST(s21_stack, move_1) {
  s21::stack<int> s21stack{1, 2, 3};
  s21::stack<int> stdstack{2, 3, 4};
  stdstack = std::move(s21stack);
}

TEST(s21_stack, push_pop_top_int) {
  s21::stack<int> s21stack;
  std::stack<int> stdstack;
  s21stack.push(1);
  stdstack.push(1);
  ASSERT_EQ(s21stack.top(), stdstack.top());
  s21stack.push(2);
  stdstack.push(2);
  ASSERT_EQ(s21stack.top(), stdstack.top());
  s21stack.push(3);
  stdstack.push(3);
  s21stack.pop();
  stdstack.pop();
  ASSERT_EQ(s21stack.top(), stdstack.top());
  ASSERT_EQ(s21stack.size(), stdstack.size());
}

TEST(s21_stack_constructor4, push_pop_top_char) {
  s21::stack<char> s21stack;
  std::stack<char> stdstack;
  s21stack.push('a');
  stdstack.push('a');
  ASSERT_EQ(s21stack.top(), stdstack.top());
  s21stack.push('b');
  stdstack.push('b');
  ASSERT_EQ(s21stack.top(), stdstack.top());
  s21stack.push('c');
  stdstack.push('c');
  s21stack.pop();
  stdstack.pop();
  ASSERT_EQ(s21stack.top(), stdstack.top());
  ASSERT_EQ(s21stack.size(), stdstack.size());
}

TEST(s21_stack_function, swap) {
  s21::stack<int> s21stack({13377, 5335, 0, 83237, 11111});
  s21::stack<int> s21stack2({15, 31, 3});
  std::stack<int> stdstack({13377, 5335, 0, 83237, 11111});
  std::stack<int> stdstack2({15, 31, 3});
  s21stack.swap(s21stack2);
  stdstack.swap(stdstack2);
  ASSERT_EQ(s21stack.size(), stdstack.size());
  ASSERT_EQ(s21stack2.size(), stdstack2.size());
  while (!s21stack.empty()) {
    ASSERT_EQ(s21stack.top(), stdstack.top());
    s21stack.pop();
    stdstack.pop();
  }
}

TEST(s21_stack_constructor5, push_pop_top_string) {
  s21::stack<std::string> s21stack;
  std::stack<std::string> stdstack;
  s21stack.push("hi");
  stdstack.push("hi");
  ASSERT_EQ(s21stack.top(), stdstack.top());
  s21stack.push("hello");
  stdstack.push("hello");
  ASSERT_EQ(s21stack.top(), stdstack.top());
  s21stack.push("bye");
  stdstack.push("bye");
  s21stack.pop();
  stdstack.pop();
  ASSERT_EQ(s21stack.top(), stdstack.top());
  ASSERT_EQ(s21stack.size(), stdstack.size());
}

TEST(s21_stack_constructor6, copy_constructor) {
  s21::stack<int> s21stack({734, 5235, 11, 837});
  std::stack<int> stdstack({734, 5235, 11, 837});
  s21::stack<int> s21stack2(s21stack);
  std::stack<int> stdstack2(stdstack);
  ASSERT_EQ(s21stack2.size(), stdstack2.size());
  while (!s21stack.empty()) {
    ASSERT_EQ(s21stack.top(), stdstack.top());
    s21stack.pop();
    stdstack.pop();
  }
}

TEST(s21_stack_constructor7, move_constructor) {
  s21::stack<int> s21stack({734, 5235, 11, 837});
  std::stack<int> stdstack({734, 5235, 11, 837});
  s21::stack<int> s21stack2(std::move(s21stack));
  std::stack<int> stdstack2(std::move(stdstack));
  ASSERT_EQ(s21stack2.size(), stdstack2.size());
  while (!s21stack.empty()) {
    ASSERT_EQ(s21stack.top(), stdstack.top());
    s21stack.pop();
    stdstack.pop();
  }
}

TEST(s21_stack_constructor8, move_operator_constructor) {
  s21::stack<int> s21stack({734, 5235, 11, 837});
  std::stack<int> stdstack({734, 5235, 11, 837});
  s21::stack<int> s21stack2 = std::move(s21stack);
  std::stack<int> stdstack2 = std::move(stdstack);
  ASSERT_EQ(s21stack2.size(), stdstack2.size());
  while (!s21stack.empty()) {
    ASSERT_EQ(s21stack.top(), stdstack.top());
    s21stack.pop();
    stdstack.pop();
  }
}
/*
 * VECTOR
 */
TEST(s21_vector, default_constructor) {
  s21::vector<int> s21vector;
  std::vector<int> stdvector;
  ASSERT_EQ(s21vector.empty(), stdvector.empty());
  ASSERT_EQ(s21vector.size(), stdvector.size());
}

TEST(s21_vector, move) {
  s21::vector<int> s21vector{1, 2, 3};
  s21::vector<int> stdvector = std::move(s21vector);
}

TEST(s21_vector, move2) {
  s21::vector<int> s21vector{1, 2, 3};
  s21::vector<int> stdvector{3, 2, 1};
  stdvector = std::move(s21vector);
}

TEST(s21_vector, copy) {
  s21::vector<int> s21vector{1, 2, 3};
  s21::vector<int> stdvector{2, 3, 4};
  s21vector = stdvector;
  ASSERT_EQ(s21vector.empty(), stdvector.empty());
  ASSERT_EQ(s21vector.size(), stdvector.size());
}

TEST(s21_vector, push_pop_int) {
  s21::vector<int> s21vector;
  std::vector<int> stdvector;
  s21vector.push_back(1);
  stdvector.push_back(1);
  ASSERT_EQ(s21vector[0], stdvector[0]);
  s21vector.push_back(2);
  stdvector.push_back(2);
  ASSERT_EQ(s21vector[1], stdvector[1]);
  s21vector.push_back(3);
  stdvector.push_back(3);
  s21vector.pop_back();
  stdvector.pop_back();
  ASSERT_EQ(s21vector[1], stdvector[1]);
  ASSERT_EQ(s21vector.size(), stdvector.size());
}

TEST(s21_vector_constructor4, push_pop_char) {
  s21::vector<char> s21vector;
  std::vector<char> stdvector;
  s21vector.push_back('a');
  stdvector.push_back('a');
  ASSERT_EQ(s21vector[0], stdvector[0]);
  s21vector.push_back('b');
  stdvector.push_back('b');
  ASSERT_EQ(s21vector[1], stdvector[1]);
  s21vector.push_back('c');
  stdvector.push_back('c');
  s21vector.pop_back();
  stdvector.pop_back();
  ASSERT_EQ(s21vector[1], stdvector[1]);
  ASSERT_EQ(s21vector.size(), stdvector.size());
}

TEST(s21_vector_function, swap) {
  s21::vector<int> s21vector({13377, 5335, 0, 83237, 11111});
  s21::vector<int> s21vector2({15, 31, 3});
  std::vector<int> stdvector({13377, 5335, 0, 83237, 11111});
  std::vector<int> stdvector2({15, 31, 3});
  s21vector.swap(s21vector2);
  stdvector.swap(stdvector2);
  ASSERT_EQ(s21vector.size(), stdvector.size());
  ASSERT_EQ(s21vector2.size(), stdvector2.size());
  for (std::size_t i = 0; i < s21vector2.size(); i++) {
    ASSERT_EQ(s21vector2[i], stdvector2[i]);
  }
}

TEST(s21_vector_constructor6, copy_constructor) {
  s21::vector<int> vector1{51, 12, 43};
  std::vector<int> vector2{51, 12, 43};
  s21::vector<int> vector3(vector1);
  std::vector<int> vector4(vector2);
  ASSERT_EQ(vector3.size(), vector4.size());
  for (std::size_t i = 0; i < vector1.size(); i++) {
    ASSERT_EQ(vector3[i], vector4[i]);
  }
}

TEST(s21_vector_constructor7, move_constructor) {
  s21::vector<int> s21vector({734, 5235, 11, 837});
  std::vector<int> stdvector({734, 5235, 11, 837});
  s21::vector<int> s21vector2(std::move(s21vector));
  std::vector<int> stdvector2(std::move(stdvector));
  ASSERT_EQ(s21vector2.size(), stdvector2.size());
  for (std::size_t i = 0; i < s21vector2.size(); i++) {
    ASSERT_EQ(s21vector2[i], stdvector2[i]);
  }
}

TEST(s21_vector_empty_clear, clear) {
  s21::vector<int> s21vector;
  std::vector<int> stdvector;
  s21vector.push_back(616);
  s21vector.push_back(3231);
  stdvector.push_back(616);
  stdvector.push_back(3231);
  s21vector.clear();
  stdvector.clear();
  ASSERT_EQ(s21vector.size(), stdvector.size());
  ASSERT_EQ(s21vector.empty(), stdvector.empty());
}

TEST(s21_vector_function, insert) {
  s21::vector<int> s21vector{727, 515, 230, 817, 411};
  std::vector<int> stdvector{727, 515, 230, 817, 411};
  s21::vector<int>::iterator s21a = s21vector.begin();
  std::vector<int>::iterator stda = stdvector.begin();
  s21vector.insert(s21a, 717);
  stdvector.insert(stda, 717);
  s21::vector<int>::iterator s21it = s21vector.end();
  std::vector<int>::iterator stdit = stdvector.end();
  s21vector.insert(s21it, 636);
  stdvector.insert(stdit, 636);
  ASSERT_EQ(s21vector.size(), stdvector.size());
  s21::vector<int>::iterator s21i = s21vector.begin();
  std::vector<int>::iterator stdi = stdvector.begin();
  for (; s21i != s21vector.end(); s21i++, stdi++) {
    ASSERT_EQ(*s21i, *stdi);
  }
}

TEST(s21_vector_function, erase) {
  s21::vector<int> s21vector{717, 5335, 123, 187};
  std::vector<int> stdvector{717, 5335, 123, 187};
  s21::vector<int>::iterator s21it = s21vector.begin();
  std::vector<int>::iterator stdit = stdvector.begin();
  s21vector.erase(s21it);
  stdvector.erase(stdit);
  ASSERT_EQ(s21vector.front(), stdvector.front());
  s21it = s21vector.begin();
  stdit = stdvector.begin();
  ++s21it;
  ++stdit;
  s21vector.erase(s21it);
  stdvector.erase(stdit);
  s21it = s21vector.begin();
  stdit = stdvector.begin();
  ASSERT_EQ(s21vector.size(), stdvector.size());
  for (size_t i = 0; i < s21vector.size(); i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(s21_vector_function, at_reverse) {
  s21::vector<int> vector1{41, 12, 53};
  std::vector<int> vector2{41, 12, 53};
  s21::vector<int> vector3(vector1);
  std::vector<int> vector4(vector2);
  vector3.reserve(5);
  vector4.reserve(5);
  ASSERT_EQ(vector3.size(), vector4.size());
  for (std::size_t i = 0; i < vector1.size(); i++) {
    ASSERT_EQ(vector3.at(i), vector4.at(i));
  }
}

TEST(s21_vector_function, back_begin) {
  s21::vector<int> vector1{112, 122, 31};
  std::vector<int> vector2{112, 122, 31};
  s21::vector<int> vector3(vector1);
  std::vector<int> vector4(vector2);
  vector3.reserve(5);
  vector4.reserve(5);
  ASSERT_EQ(vector3.size(), vector4.size());
  ASSERT_EQ(vector3.back(), vector4.back());
  ASSERT_EQ(vector3.front(), vector4.front());
}

TEST(s21_vector_function, data) {
  s21::vector<int> vector1{14, 2000, 33};
  std::vector<int> vector2{14, 2000, 33};
  ASSERT_EQ(vector1.size(), vector2.size());
  ASSERT_EQ(vector1.max_size(), vector2.max_size());
  auto *s21it_ = vector1.data();
  auto *stdit_ = vector2.data();
  for (; s21it_ != vector1.end(); s21it_++, stdit_++) {
    ASSERT_EQ(*s21it_, *stdit_);
  }
}
/*
 * SET
 */
TEST(s21_set, default_constructor) {
  s21::set<int> s21set;
  std::set<int> stdset;
  ASSERT_EQ(s21set.empty(), stdset.empty());
  ASSERT_EQ(s21set.size(), stdset.size());
}

TEST(s21_set, move) {
  s21::set<int> s21set{1, 2, 3};
  s21::set<int> stdset = std::move(s21set);
  ASSERT_EQ(stdset.size(), 3);
}

TEST(s21_set, copy) {
  s21::set<int> s21set{1, 2, 3};
  s21::set<int> stdset{2, 3, 4};
  s21set = stdset;
  ASSERT_EQ(stdset.size(), 3);
}

TEST(s21_set, move_1) {
  s21::set<int> s21set{1, 2, 3};
  s21::set<int> stdset{2, 3, 4};
  s21set = std::move(stdset);
}

TEST(s21_set_function, swap) {
  std::initializer_list<int> items{22, 21};
  std::initializer_list<int> items2{23, 24};
  s21::set<int> s21set(items);
  std::set<int> stdset(items);
  s21::set<int> s21set2(items2);
  std::set<int> stdset2(items2);

  s21set.swap(s21set2);
  stdset.swap(stdset2);

  ASSERT_EQ(s21set.size(), stdset.size());
  ASSERT_EQ(s21set2.size(), stdset2.size());

  auto my_iter2 = s21set2.begin();
  auto std_iter2 = stdset2.begin();

  while (my_iter2 != s21set2.end() && std_iter2 != stdset2.end()) {
    ASSERT_EQ(*my_iter2, *std_iter2);
    my_iter2++;
    std_iter2++;
  }
}

TEST(s21_set_function, insert) {
  s21::set<int> s21set({13377, 5335, 0, 83237, 11111});
  std::set<int> stdset({13377, 5335, 0, 83237, 11111});
  s21set.insert(5);
  stdset.insert(5);
  ASSERT_EQ(s21set.size(), stdset.size());
  auto my_iter = s21set.begin();
  auto std_iter = stdset.begin();

  while (my_iter != s21set.end() && std_iter != stdset.end()) {
    ASSERT_EQ(*my_iter, *std_iter);
    my_iter++;
    std_iter++;
  }
}

TEST(s21_set_function, clear) {
  s21::set<int> s21set({13377, 5335, 0, 83237, 11111});
  std::set<int> stdset({13377, 5335, 0, 83237, 11111});
  s21set.clear();
  stdset.clear();
  ASSERT_EQ(s21set.size(), stdset.size());
  ASSERT_EQ(s21set.empty(), stdset.empty());
}

TEST(s21_set_function, clear_second) {
  s21::set<int> s21set({2, 3, 0, 1, 5});
  std::set<int> stdset({2, 3, 0, 1, 5});
  s21set.clear();
  stdset.clear();
  ASSERT_EQ(s21set.size(), stdset.size());
  ASSERT_EQ(s21set.empty(), stdset.empty());
}

TEST(s21_set_function, find_contains) {
  s21::set<int> s21set({13377, 5335, 0, 83237, 11111});
  std::set<int> stdset({13377, 5335, 0, 83237, 11111});
  auto s21a = s21set.find(0);
  auto stda = stdset.find(0);
  ASSERT_EQ(*s21a, *stda);
  s21set.clear();
  stdset.clear();
  bool s21b = s21set.contains(2);
  ASSERT_EQ(s21b, 0);
}

TEST(s21_set_function, merge) {
  std::initializer_list<int> items{1, 2, 3};
  std::initializer_list<int> items2{4, 5, 6};
  s21::set<int> s21set(items);
  std::set<int> stdset(items);
  s21::set<int> s21set2(items2);
  std::set<int> stdset2(items2);
  s21set.merge(s21set2);
  stdset.merge(stdset2);
  auto my_iter = s21set.begin();
  auto std_iter = stdset.begin();
  while (std_iter != stdset.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
}

TEST(s21_set_function, erase) {
  s21::set<int> s21set({13377, 5335, 0});
  std::set<int> stdset({13377, 5335, 0});

  auto my_iter = s21set.begin();
  auto std_iter = stdset.begin();

  s21set.erase(my_iter);
  stdset.erase(std_iter);

  my_iter = s21set.begin();
  std_iter = stdset.begin();

  while (my_iter != s21set.end() && std_iter != stdset.end()) {
    ASSERT_EQ(*my_iter, *std_iter);
    my_iter++;
    std_iter++;
  }
}
/*
 * MAP
 */
TEST(s21_map, default_constructor) {
  s21::map<int, int> s21map;
  std::map<int, int> stdmap;
  ASSERT_EQ(s21map.empty(), stdmap.empty());
  ASSERT_EQ(s21map.size(), stdmap.size());
}

TEST(s21_map, move) {
  s21::map<int, int> s21map = {{1, 22}, {2, 21}};
  s21::map<int, int> stdmap = std::move(s21map);
}

TEST(s21_map, copy) {
  s21::map<int, int> s21map = {{1, 22}, {2, 21}};
  s21::map<int, int> stdmap = {{1, 52}, {2, 51}};
  s21map = stdmap;
  ASSERT_EQ(s21map.empty(), stdmap.empty());
  ASSERT_EQ(s21map.size(), stdmap.size());
}

TEST(s21_map, move_1) {
  s21::map<int, int> s21map = {{1, 22}, {2, 21}};
  s21::map<int, int> stdmap = {{1, 52}, {2, 51}};
  s21map = std::move(stdmap);
}

TEST(s21_map, move2) {
  s21::map<int, int> s21map = {{1, 22}, {2, 21}};
  s21::map<int, int> stdmap = std::move(s21map);
  ASSERT_EQ(stdmap.empty(), false);
  ASSERT_EQ(stdmap.size(), 2);
}

TEST(s21_map_function, swap) {
  s21::map<int, int> s21map = {{1, 22}, {2, 21}};
  std::map<int, int> stdmap = {{1, 22}, {2, 21}};
  s21::map<int, int> s21map2 = {{3, 23}, {4, 24}};
  std::map<int, int> stdmap2 = {{3, 23}, {4, 24}};

  s21map.swap(s21map2);
  stdmap.swap(stdmap2);

  ASSERT_EQ(s21map.size(), stdmap.size());
  ASSERT_EQ(s21map2.size(), stdmap2.size());

  auto my_iter2 = s21map2.begin();
  auto std_iter2 = stdmap2.begin();

  while (my_iter2 != s21map2.end() && std_iter2 != stdmap2.end()) {
    ASSERT_EQ(*my_iter2, *std_iter2);
    my_iter2++;
    std_iter2++;
  }
}

TEST(s21_map_function, insert) {
  s21::map<int, int> s21map;
  std::map<int, int> stdmap;
  // для инсерта без создания пары в оригинальной stl испозьзуется emplace
  s21map.insert(1, 5);
  stdmap.emplace(1, 5);
  s21map.insert(2, 5);
  stdmap.emplace(2, 5);
  s21map.insert(3, 5);
  stdmap.emplace(3, 5);
  ASSERT_EQ(s21map.size(), stdmap.size());
  auto my_iter = s21map.begin();
  auto std_iter = stdmap.begin();

  while (my_iter != s21map.end() || std_iter != stdmap.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    my_iter++;
    std_iter++;
  }
}

TEST(s21_map_function, clear) {
  s21::map<std::string, std::string> s21map{
      {"Hi", "Привет"}, {"Student", "Студент"}, {"!", "!"}};
  std::map<std::string, std::string> stdmap{
      {"Hi", "Привет"}, {"Student", "Студент"}, {"!", "!"}};
  s21map.clear();
  stdmap.clear();
  ASSERT_EQ(s21map.size(), stdmap.size());
  ASSERT_EQ(s21map.empty(), stdmap.empty());
}

TEST(s21_map_function, contains) {
  s21::map<std::string, std::string> s21map{
      {"Hi", "Привет"}, {"Student", "Студент"}, {"!", "!"}};
  bool s21b = s21map.contains("2");
  ASSERT_EQ(s21b, 0);
}

TEST(s21_map_function, merge) {
  s21::map<int, int> s21map = {{1, 2}, {2, 3}};
  std::map<int, int> stdmap = {{1, 2}, {2, 3}};
  s21::map<int, int> s21map2 = {{3, 3}, {4, 4}};
  std::map<int, int> stdmap2 = {{3, 3}, {4, 4}};
  s21map.merge(s21map2);
  stdmap.merge(stdmap2);
  auto my_iter = s21map.begin();
  auto std_iter = stdmap.begin();
  ASSERT_EQ(s21map.size(), stdmap.size());
  while (my_iter != s21map.end() || std_iter != stdmap.end()) {
    ASSERT_EQ((*my_iter).first, (*std_iter).first);
    my_iter++;
    std_iter++;
  }
}

TEST(s21_map_function, erase) {
  s21::map<int, int> s21map = {{1, 2}, {2, 3}};
  std::map<int, int> stdmap = {{1, 2}, {2, 3}};

  auto my_iter = s21map.begin();
  auto std_iter = stdmap.begin();

  s21map.erase(my_iter);
  stdmap.erase(std_iter);

  my_iter = s21map.begin();
  std_iter = stdmap.begin();

  while (my_iter != s21map.end() && std_iter != stdmap.end()) {
    ASSERT_EQ(*my_iter, *std_iter);
    my_iter++;
    std_iter++;
  }
}

TEST(s21_map_function, erase_one_more) {
  s21::map<int, int> s21map = {{1, 2}, {2, 3}, {3, 4}};
  std::map<int, int> stdmap = {{1, 2}, {2, 3}, {3, 4}};

  auto my_iter = s21map.begin();
  auto std_iter = stdmap.begin();

  // my_iter++;
  // std_iter++;

  s21map.erase(my_iter);
  stdmap.erase(std_iter);

  my_iter = s21map.begin();
  std_iter = stdmap.begin();

  while (my_iter != s21map.end() && std_iter != stdmap.end()) {
    ASSERT_EQ(s21map.size(), stdmap.size());
    my_iter++;
    std_iter++;
  }
}

TEST(s21_map_function, erase_two_more) {
  s21::map<int, int> s21map = {{10, 20}};
  std::map<int, int> stdmap = {{10, 20}};

  auto my_iter = s21map.begin();
  auto std_iter = stdmap.begin();

  s21map.erase(my_iter);
  stdmap.erase(std_iter);

  my_iter = s21map.begin();
  std_iter = stdmap.begin();

  while (my_iter != s21map.end() && std_iter != stdmap.end()) {
    ASSERT_EQ(s21map.size(), stdmap.size());
    my_iter++;
    std_iter++;
  }
}

TEST(s21_map_function, erase_two_more_) {
  s21::map<int, int> s21map = {{10, 20}, {11, 30}, {5, 2}, {6, 2}};
  std::map<int, int> stdmap = {{10, 20}, {11, 30}, {5, 2}, {6, 2}};

  auto my_iter = s21map.begin();
  auto std_iter = stdmap.begin();

  s21map.erase(my_iter);
  stdmap.erase(std_iter);

  my_iter = s21map.begin();
  std_iter = stdmap.begin();

  while (my_iter != s21map.end() && std_iter != stdmap.end()) {
    ASSERT_EQ(s21map.size(), stdmap.size());
    my_iter++;
    std_iter++;
  }
}

TEST(s21_map_function, erase_third_more) {
  s21::map<int, int> s21map = {{10, 20}, {11, 21}, {9, 22}, {1, 2}, {0, 3}};
  std::map<int, int> stdmap = {{10, 20}, {11, 21}, {9, 22}, {1, 2}, {0, 3}};

  auto my_iter = s21map.begin();
  auto std_iter = stdmap.begin();

  s21map.erase(my_iter);
  stdmap.erase(std_iter);

  my_iter = s21map.begin();
  std_iter = stdmap.begin();

  while (my_iter != s21map.end() && std_iter != stdmap.end()) {
    ASSERT_EQ(s21map.size(), stdmap.size());
    my_iter++;
    std_iter++;
  }
}

TEST(s21_map_function, at) {
  s21::map<int, int> s21map = {{1, 2}, {2, 3}};
  std::map<int, int> stdmap = {{1, 2}, {2, 3}};

  ASSERT_EQ(s21map.at(1), stdmap.at(1));
}

TEST(s21_map_function, branches) {
  s21::map<int, int> s21map = {{1, 2}, {2, 3}};
  std::map<int, int> stdmap = {{1, 2}, {2, 3}};

  s21map[1] = 5;
  stdmap[1] = 5;
  ASSERT_EQ(s21map.at(1), stdmap.at(1));
}

TEST(s21_map_function, insert_or_assign) {
  s21::map<int, int> s21map = {{1, 2}, {2, 3}};
  std::map<int, int> stdmap = {{1, 2}, {2, 3}};

  s21map.insert_or_assign(1, 5);
  stdmap.insert_or_assign(1, 5);

  ASSERT_EQ(s21map.at(1), stdmap.at(1));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}