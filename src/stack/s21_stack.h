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

#ifndef CPP2_S21_CONTAINERS_STACK_S21_STACK_H
#define CPP2_S21_CONTAINERS_STACK_S21_STACK_H

#include "../list/s21_list.h"

namespace s21 {

template <typename T>
class stack {
 public:
  /*
   * Change names of types
   */
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  /*
   * Stack Member functions
   */
  stack(){};
  stack(const stack &l) : data_(l.data_){};
  stack(stack &&l) noexcept : data_(std::move(l.data_)){};
  stack<value_type> &operator=(stack<value_type> &&l);
  stack<value_type> &operator=(const stack<value_type> &l);
  explicit stack(std::initializer_list<value_type> const &items);
  ~stack();
  /*
   * Stack Element access
   */
  const_reference top();
  /*
   * Stack Capacity
   */
  bool empty();
  size_type size();
  /*
   * Stack Modifiers
   */
  void pop();
  void swap(stack &other);
  void push(const_reference value);

 private:
  list<value_type> data_;
};

}  // namespace s21

#include "s21_stack.tpp"

#endif  // CPP2_S21_CONTAINERS_STACK_S21_STACK_H
