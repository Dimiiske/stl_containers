#ifndef CPP2_S21_CONTAINERS_VECTOR_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_VECTOR_S21_VECTOR_H

#include <initializer_list>
#include <iterator>
#include <limits>
#include <stdexcept>

namespace s21 {

template <typename T>
class vector {
 public:
  /*
   * Change names of types
   */
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  /*
   * Vector Member functions
   */
  vector() : data_(nullptr), size_(0), capacity_(0){};
  vector(size_type n);
  explicit vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector();
  vector<value_type> &operator=(vector<value_type> &&v);
  vector<value_type> &operator=(const vector<value_type> &v);
  /*
   * Vector Element access
   */
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  value_type *data();
  /*
   * Vector Iterators
   */
  iterator begin();
  iterator end();
  iterator cbegin() const;
  iterator cend() const;
  /*
   * Vector Capacity
   */
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();
  /*
   * Vector Modifiers
   */
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

 private:
  value_type *data_;
  size_type size_;
  size_type capacity_;
  void copy(value_type *array, size_type size, size_type capacity);
  void push_front(const_reference value);
  void push_between(const_reference value, iterator pos);
};
}  // namespace s21

#include "s21_vector.tpp"

#endif  // CPP2_S21_CONTAINERS_VECTOR_S21_VECTOR_H
