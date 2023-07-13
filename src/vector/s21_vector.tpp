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
 * Vector Member functions
 */
template <typename value_type>
vector<value_type>::vector(size_type n) {
  size_ = n;
  capacity_ =
      size_ *
      2;  // capacity_ depends of complier (it can be size_* 1.5 or size_ * 2)
  data_ = new value_type[capacity_];
  for (auto it_ = begin(); it_ != end(); it_++) {
    *it_ = 0;
  }
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const& items) {
  size_ = items.size();
  capacity_ = items.size();
  data_ = new value_type[capacity_];
  std::copy(items.begin(), items.end(), data_);
}

template <typename value_type>
vector<value_type>::vector(const vector& v) {
  copy(v.data_, v.size_, v.capacity_);
}

template <typename value_type>
vector<value_type>::vector(vector&& v) noexcept {
  data_ = nullptr;
  std::swap(data_, v.data_);
  std::swap(capacity_, v.capacity_);
  std::swap(size_, v.size_);
}

template <typename value_type>
vector<value_type>::~vector() {
  clear();
  capacity_ = 0;
}

template <typename value_type>
vector<value_type>& vector<value_type>::operator=(vector<value_type>&& v) {
  clear();
  capacity_ = 0;
  std::swap(data_, v.data_);
  std::swap(capacity_, v.capacity_);
  std::swap(size_, v.size_);

  return *this;
}

template <typename value_type>
vector<value_type>& vector<value_type>::operator=(const vector<value_type>& v) {
  clear();
  copy(v.data_, v.size_, v.capacity_);

  return *this;
}
/*
 * Vector Element access
 */
template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos > size_ || static_cast<int>(pos) < 0) {
    throw std::out_of_range("Out of range");
  }
  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type pos) {
  if (pos > size_ || static_cast<int>(pos) < 0) {
    throw std::out_of_range("out of range");
  }
  return data_[pos];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() {
  return data_[0];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() {
  return data_[size_ - 1];
}

template <typename value_type>
typename vector<value_type>::value_type* vector<value_type>::data() {
  return data_;
}
/*
 * Vector Iterators
 */
template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return data_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return data_ + size_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::cbegin() const {
  return data_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::cend() const {
  return data_ + size_;
}
/*
 * Vector Capacity
 */
template <typename value_type>
bool vector<value_type>::empty() {
  return size_ == 0;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() {
  return size_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <typename value_type>
void vector<value_type>::reserve(size_type size) {
  capacity_ = size + size_;
  value_type* new_ = new value_type[capacity_];
  for (auto it_ = begin(), i_ = 0; it_ != end(); it_++) {
    new_[i_++] = *it_;
  }
  delete[] data_;
  data_ = new_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() {
  return (capacity_ - size_);
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  size_type count_ = this->size_;
  while (count_--) {
    this->capacity_--;
  }
}
/*
 * Vector Modifiers
 */
template <typename value_type>
void vector<value_type>::clear() {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos == begin()) {
    push_front(value);
  } else if (pos == end()) {
    push_back(value);
  } else {
    push_between(value, pos);
  }
  return pos;
}

template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
  if (size_ == 0) {
    capacity_ = 2;
  } else {
    capacity_ = (size_ + 1) * 2;
  }
  value_type* tmp_ = data_;
  data_ = new value_type[capacity_];
  for (size_type i_ = 0; i_ < size_; i_++) {
    data_[i_] = tmp_[i_];
  }
  data_[size_++] = value;
  delete[] tmp_;
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
  capacity_ = (size_ - 1) * 2;
  value_type* new_ = new value_type[capacity_];
  for (auto it_ = begin(), i_ = 0; it_ != end(); it_++) {
    if (it_ != pos) {
      new_[i_++] = *it_;
    }
  }
  delete[] data_;
  size_ -= 1;
  data_ = new_;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  if (size_ > 0) {
    size_--;
  }
}

template <typename value_type>
void vector<value_type>::swap(vector& other) {
  std::swap(this->data_, other.data_);
  std::swap(this->size_, other.size_);
  std::swap(this->capacity_, other.capacity_);
}
/*
 * Extra
 */
template <typename value_type>
void vector<value_type>::copy(value_type* array, size_type size,
                              size_type capacity) {
  this->capacity_ = capacity;
  this->size_ = size;
  value_type* new_ = new value_type[capacity_];
  for (size_type i_ = 0; i_ < size_; i_++) {
    new_[i_] = array[i_];
  }
  this->data_ = new_;
}

template <typename value_type>
void vector<value_type>::push_front(const_reference value) {
  capacity_ = (size_ + 1) * 2;  // increase size
  value_type* new_ = new value_type[capacity_];
  size_type new_size_ = 0;
  new_[new_size_++] = value;
  for (iterator it_ = begin(); it_ != end(); it_++) {
    new_[new_size_++] = *it_;
  }
  delete[] data_;
  this->data_ = new_;
  this->size_ = new_size_;
}

template <typename value_type>
void vector<value_type>::push_between(const_reference value, iterator pos) {
  capacity_ = (size_ + 1) * 2;
  value_type* new_ = new value_type[capacity_];
  size_type new_size_ = 0;
  for (auto it_ = begin(); it_ != end(); it_++) {
    if (it_ == pos) {
      new_[new_size_++] = value;
      new_[new_size_++] = *it_;
    } else {
      new_[new_size_++] = *it_;
    }
  }
  delete[] data_;
  data_ = new_;
  size_ = new_size_;
}

}  // namespace s21
