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

namespace s21 {
/*
 * Queue Member functions
 */
template <typename value_type>
queue<value_type> &queue<value_type>::operator=(queue<value_type> &&l) {
  data_ = std::move(l.data_);
  return *this;
}

template <typename value_type>
queue<value_type> &queue<value_type>::operator=(const queue<value_type> &l) {
  data_ = l.data_;
  return *this;
}

template <typename value_type>
queue<value_type>::queue(std::initializer_list<value_type> const &items) {
  for (auto &iter : items) {
    data_.push_back(iter);
  }
}

template <typename value_type>
queue<value_type>::~queue() {}
/*
 * Queue Element access
 */
template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::front() {
  return data_.front();
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::back() {
  return data_.back();
}
/*
 * Queue Capacity
 */
template <typename value_type>
bool queue<value_type>::empty() {
  return data_.empty();
}

template <typename value_type>
typename queue<value_type>::size_type queue<value_type>::size() {
  return data_.size();
}
/*
 * Queue Modifiers
 */
template <typename value_type>
void queue<value_type>::pop() {
  data_.pop_front();
}

template <typename value_type>
void queue<value_type>::swap(queue &other) {
  data_.swap(other.data_);
}

template <typename value_type>
void queue<value_type>::push(const_reference value) {
  data_.push_back(value);
}

}  // namespace s21
