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
 * Map Member functions
 */
template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) {
  for (auto &it_ : items) {
    insert(it_);
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map &s) {
  clear();
  for (auto &it_ : s) {
    insert(it_.first);
  }
}

template <typename Key, typename T>
map<Key, T>::map(map &&s) noexcept {
  std::swap(this->root_, s.root_);
  std::swap(this->size_, s.size_);
}

template <typename Key, typename T>
map<Key, T>::~map() {
  clear();
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&s) {
  clear();
  std::swap(this->root_, s.root_);
  std::swap(this->size_, s.size_);
  return *this;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &s) {
  clear();
  auto it_ = s.cbegin();
  for (; it_ != s.cend(); ++it_) {
    insert(*it_);
  }

  return *this;
}
/*
 * Map Element access
 */
template <typename Key, typename T>
T &map<Key, T>::at(const Key &key) {
  std::pair<key_type, mapped_type> val_ = std::make_pair(key, mapped_type());
  typename Binary::tnode *check_ = Binary::find(this->root_, val_);
  if (check_ == nullptr) {
    throw std::out_of_range("Out of range!");
  }
  return check_->data_.second;
}

template <typename Key, typename T>
T &map<Key, T>::operator[](const Key &key) {
  std::pair<key_type, mapped_type> val_ = std::make_pair(key, mapped_type());
  typename Binary::tnode *check_ = Binary::find(this->root_, val_);
  return check_->data_.second;
}
/*
 * Map Iterators
 */
template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  typename Binary::tnode *node_ = this->root_;
  while (node_ != nullptr && node_->left_ != nullptr) {
    node_ = node_->left_;
  }
  return iterator(node_);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::cbegin() const {
  typename Binary::tnode *node_ = this->root_;
  while (node_ != nullptr && node_->left_ != nullptr) {
    node_ = node_->left_;
  }
  return iterator(node_);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::cend() const {
  return iterator(nullptr);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  return iterator(nullptr);
}
/*
 * Map Capacity
 */
template <typename Key, typename T>
bool map<Key, T>::empty() {
  return (this->root_ == nullptr);
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() {
  return Binary::size_;
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}
/*
 * Map Modifiers
 */
template <typename Key, typename T>
void map<Key, T>::clear() {
  if (this->root_ == nullptr) return;
  Binary::clear(this->root_);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  std::pair<key_type, mapped_type> val_ = std::make_pair(key, obj);
  typename Binary::tnode *check_ = Binary::find(this->root_, val_);
  bool exp = false;
  if (check_ == nullptr) {
    Binary::insert(val_);
    exp = true;
  }
  return std::make_pair(iterator(Binary::find(this->root_, val_)), exp);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type &value) {
  typename Binary::tnode *check_ = Binary::find(this->root_, value);
  bool exp = false;
  if (check_ == nullptr) {
    Binary::insert(value);
    exp = true;
  }
  return std::make_pair(iterator(Binary::find(this->root_, value)), exp);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  std::pair<key_type, mapped_type> val_ = std::make_pair(key, obj);
  typename Binary::tnode *check_ = Binary::find(this->root_, val_);
  if (check_ == nullptr) {
    Binary::insert(val_);
  } else {
    check_->data_.second = obj;
  }
  return std::make_pair(iterator(Binary::find(this->root_, val_)), true);
}

template <typename Key, typename T>
void map<Key, T>::erase(typename map<Key, T>::iterator pos) {
  std::pair<key_type, mapped_type> val_ =
      std::make_pair((*pos).first, mapped_type());
  Binary::remove(val_);
}

template <typename Key, typename T>
void map<Key, T>::swap(map &other) {
  std::swap(this->root_, other.root_);
  std::swap(this->size_, other.size_);
}

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  for (auto it_ : other) {
    if (it_.first != this->root_->data_.first) {
      insert(std::move(it_));
    }
  }
  other.clear();
}
/*
 * Map Lookup
 */
template <typename Key, typename T>
bool map<Key, T>::contains(const Key &key) {
  std::pair<key_type, mapped_type> val_ = std::make_pair(key, mapped_type());
  typename Binary::tnode *check_ = Binary::find(this->root_, val_);
  return (check_ != nullptr);
}
/*
 * Iterator methods
 */
template <typename Key, typename T>
typename map<Key, T>::value_type map<Key, T>::Iterator::operator*() const {
  return this->node_->data_;
}

template <typename Key, typename T>
typename map<Key, T>::value_type *map<Key, T>::Iterator::operator->() {
  return this->node_->data_;
}

template <typename Key, typename T>
typename map<Key, T>::Iterator &map<Key, T>::Iterator::operator++() {
  if (node_->right_) {
    node_ = node_->right_;
    while (node_->left_) {
      node_ = node_->left_;
    }
  } else {
    typename Binary::tnode *parent_ = node_->parent_;
    while (parent_ && node_ == parent_->right_) {
      node_ = parent_;
      parent_ = parent_->parent_;
    }
    node_ = parent_;
  }
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::Iterator map<Key, T>::Iterator::operator++(int) {
  Iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename Key, typename T>
typename map<Key, T>::Iterator &map<Key, T>::Iterator::operator--() {
  if (node_->left_) {
    node_ = node_->left_;
    while (node_->right_) {
      node_ = node_->right_;
    }
  } else {
    typename Binary::tnode *parent_ = node_->parent_;
    while (parent_ && node_ == parent_->left_) {
      node_ = parent_;
      parent_ = parent_->parent_;
    }
    node_ = parent_;
  }
  return *this;
}

template <typename Key, typename T>
bool map<Key, T>::Iterator::operator==(const Iterator &other) const noexcept {
  return node_ == other.node_;
}

template <typename Key, typename T>
bool map<Key, T>::Iterator::operator!=(const Iterator &other) const noexcept {
  return node_ != other.node_;
}
}  // namespace s21
