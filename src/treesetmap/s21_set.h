#ifndef CPP2_S21_CONTAINERS_TREESETMAP_S21_SET_H
#define CPP2_S21_CONTAINERS_TREESETMAP_S21_SET_H

#include "s21_tree.h"

namespace s21 {

template <typename Key>
class set : BRTree<Key, bool> {
 public:
  class Iterator;

  using value_type = Key;
  using iterator = typename set<value_type>::Iterator;
  using Binary = BRTree<value_type, bool>;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator() : node_(nullptr) {}
    explicit Iterator(typename Binary::tnode *other) : node_(other) {}
    ~Iterator() {}

    value_type operator*() const;
    value_type *operator->();
    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();

    bool operator==(const Iterator &other) const noexcept;
    bool operator!=(const Iterator &other) const noexcept;

    typename Binary::tnode *node_;
  };
  /*
   * Set Member functions
   */
  set(){};
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s) noexcept;
  ~set();
  set<value_type> &operator=(set &&s);
  set<value_type> &operator=(const set &s);
  /*
   * Set Iterators
   */
  iterator cbegin() const;
  iterator begin();
  iterator cend() const;
  iterator end();
  /*
   * Set Capacity
   */
  bool empty();
  size_type size();
  size_type max_size();
  /*
   * Set Modifiers
   */
  void clear();
  std::pair<iterator, bool> insert(const Key &key);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);
  /*
   * Set Lookup
   */
  iterator find(const Key &key);
  bool contains(const Key &key);
};

}  // namespace s21

#include "s21_set.tpp"

#endif  // CPP2_S21_CONTAINERS_TREESETMAP_S21_SET_H