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

#ifndef CPP2_S21_CONTAINERS_TREESETMAP_S21_MAP_H
#define CPP2_S21_CONTAINERS_TREESETMAP_S21_MAP_H

#include "s21_tree.h"

namespace s21 {

template <typename Key, typename T>
class map : BRTree<Key, T> {
 public:
  class Iterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using iterator = map<key_type, mapped_type>::Iterator;
  using Binary = BRTree<key_type, mapped_type>;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator() {}
    explicit Iterator(typename Binary::tnode *other) : node_(other) {}
    ~Iterator() {}

    value_type operator*() const;
    value_type *operator->();
    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();

    bool operator==(const Iterator &other) const noexcept;
    bool operator!=(const Iterator &other) const noexcept;

    typename Binary::tnode *node_{};
  };
  /*
   * Map Member functions
   */
  map() {}
  map(std::initializer_list<value_type> const &items);
  map(const map &s);
  map(map &&s) noexcept;
  ~map();
  map<key_type, mapped_type> &operator=(map &&s);
  map<key_type, mapped_type> &operator=(const map &s);
  /*
   * Map Element access
   */
  T &at(const Key &key);
  T &operator[](const Key &key);
  /*
   * Map Iterators
   */
  iterator begin();
  iterator end();
  iterator cbegin() const;
  iterator cend() const;
  /*
   * Map Capacity
   */
  bool empty();
  size_type size();
  size_type max_size();
  /*
   * Map Modifiers
   */
  void clear();
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  void erase(typename map<Key, T>::iterator pos);
  void swap(map &other);
  void merge(map &other);
  /*
   * Map Lookup
   */
  bool contains(const Key &key);
};

}  // namespace s21

#include "s21_map.tpp"

#endif  // CPP2_S21_CONTAINERS_TREESETMAP_S21_MAP_H