#ifndef CPP2_S21_CONTAINERS_LIST_S21_LIST_H
#define CPP2_S21_CONTAINERS_LIST_S21_LIST_H

#include <initializer_list>
#include <iterator>
#include <limits>
#include <stdexcept>

namespace s21 {

template <typename T>
class list {
  class node;

 public:
  /*
   * Change names of types
   */
  class ListIterator;
  class ListConstIterator;
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 public:
  class ListIterator {
   public:
    node *ptr_;

   public:
    ListIterator();
    ListIterator(node *ptr);
    reference operator*();
    ListIterator &operator++();
    ListIterator &operator--();
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    ~ListIterator() {}
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator(){};
    ListConstIterator(node *ptr);
    const_reference operator*() const;
    ListConstIterator &operator++();
    ~ListConstIterator() {}
  };

 public:
  /*
   * List Member functions
   */
  list();
  explicit list(size_type n);
  list(const list &l);
  list(list &&l) noexcept;
  list<value_type> &operator=(list<value_type> &&l);
  list<value_type> &operator=(const list<value_type> &l);
  explicit list(std::initializer_list<value_type> const &items);
  ~list();
  /*
   * List Element access
   */
  const_reference front();
  const_reference back();
  /*
   * List Capacity
   */
  bool empty();
  size_type size();
  size_type max_size();
  /*
   * List Iterators
   */
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  /*
   * List Modifiers
   */
  void sort();
  void clear();
  void unique();
  void reverse();
  void pop_back();
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void erase(iterator pos);
  void push_back(const_reference value);
  void push_front(const_reference value);
  void splice(const_iterator pos, list &other);
  iterator insert(iterator pos, const_reference value);

 private:
  class node {
   public:
    node *p_prev_;
    node *p_next_;
    value_type data_;
    explicit node(value_type data_ = value_type(), node *p_next_ = nullptr,
                  node *p_prev_ = nullptr) {
      this->data_ = data_;
      this->p_next_ = p_next_;
      this->p_prev_ = p_prev_;
    }
  };

 private:
  node *head_;
  node *tail_;
  node *end_;
  int count_node_;

 private:
  void init();
  void copy(node *tmp, int count);
  void relate_end();
  void swap_list(list &&l);
};

}  // namespace s21

#include "s21_list.tpp"

#endif  // CPP2_S21_CONTAINERS_LIST_S21_LIST_H
