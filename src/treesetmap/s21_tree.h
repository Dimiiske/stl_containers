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

#ifndef CPP2_S21_CONTAINERS_TREESETMAP_S21_TREE_H
#define CPP2_S21_CONTAINERS_TREESETMAP_S21_TREE_H

#include <initializer_list>
#include <iterator>
#include <limits>

namespace s21 {
enum node_color { RED, BLACK };

template <typename K, typename T>
class node {
 public:
  using value_type = std::pair<const K, T>;
  /*
   * Constructor and Destructor
   */
  node() : node(K(), T()) {}
  explicit node(value_type value = value_type(), node *parent = nullptr,
                node *left = nullptr, node *right = nullptr, int color = int())
      : data_(value),
        parent_(parent),
        left_(left),
        right_(right),
        color_(color) {}
  ~node() {}

 public:
  value_type data_;
  node *parent_;
  node *left_;
  node *right_;
  int color_;
};

template <typename K, typename T>
class BRTree {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using tnode = node<key_type, mapped_type>;
  using size_type = size_t;
  /*
   * Constructor and Destructor
   */
  BRTree() {}
  ~BRTree() {}
  /*
   * Base methods
   */
  void clear(tnode *root);
  void insert(value_type value);
  void remove(value_type value);
  tnode *find(tnode *&check_, value_type value);

 public:
  tnode *root_{};
  size_type size_{};

 private:
  /*
   * Extra methods for balance tree
   */
  void correcting(tnode *removed_, tnode *replaced_);
  void balance_tree(tnode *root_);
  void rotate_left(tnode *p_);
  void rotate_right(tnode *p_);
};

}  // namespace s21

#include "s21_tree.tpp"

#endif  // CPP2_S21_CONTAINERS_TREESETMAP_S21_TREE_H