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

#ifndef CPP2_S21_CONTAINERS_QUEUE_S21_QUEUE_H
#define CPP2_S21_CONTAINERS_QUEUE_S21_QUEUE_H

#include "../list/s21_list.h"

namespace s21 {

template <typename T>
class queue {
 public:
  /*
   * Change names of types
   */
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  /*
   * Queue Member functions
   */
  queue(){};
  queue(const queue &l) : data_(l.data_){};
  queue(queue &&l) noexcept : data_(std::move(l.data_)){};
  queue<value_type> &operator=(queue<value_type> &&l);
  queue<value_type> &operator=(const queue<value_type> &l);
  explicit queue(std::initializer_list<value_type> const &items);
  ~queue();
  /*
   * Queue Element access
   */
  const_reference front();
  const_reference back();
  /*
   * Queue Capacity
   */
  bool empty();
  size_type size();
  /*
   * Queue Modifiers
   */
  void pop();
  void swap(queue &other);
  void push(const_reference value);

 private:
  list<value_type> data_;
};

}  // namespace s21

#include "s21_queue.tpp"

#endif  // CPP2_S21_CONTAINERS_QUEUE_S21_QUEUE_H
