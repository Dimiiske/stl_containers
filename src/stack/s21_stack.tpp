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
 * Stack Member functions
 */
template <typename value_type>
stack<value_type>::stack(std::initializer_list<value_type> const &items) {
  for (auto &iter_ : items) {
    data_.push_back(iter_);
  }
}

template <typename value_type>
stack<value_type> &stack<value_type>::operator=(stack<value_type> &&l) {
  data_ = std::move(l.data_);
  return *this;
}

template <typename value_type>
stack<value_type> &stack<value_type>::operator=(const stack<value_type> &l) {
  data_ = l.data_;
  return *this;
}

template <typename value_type>
stack<value_type>::~stack() {}
/*
 * Stack Element access
 */
template <typename value_type>
typename stack<value_type>::const_reference stack<value_type>::top() {
  return data_.front();
}
/*
 * Stack Capacity
 */
template <typename value_type>
typename stack<value_type>::size_type stack<value_type>::size() {
  return data_.size();
}

template <typename value_type>
bool stack<value_type>::empty() {
  return data_.empty();
}
/*
 * Stack Modifiers
 */
template <typename value_type>
void stack<value_type>::pop() {
  data_.pop_front();
}

template <typename value_type>
void stack<value_type>::swap(stack &other) {
  data_.swap(other.data_);
}

template <typename value_type>
void stack<value_type>::push(const_reference value) {
  data_.push_front(value);
}

}  // namespace s21