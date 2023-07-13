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
 * List Member functions
 */
template <typename value_type>
list<value_type>::list() {
  init();
}

template <typename value_type>
list<value_type>::list(size_type n) {
  init();
  for (size_type i = 0; i < n; i++) {
    push_front(0);
  }
}

template <typename value_type>
list<value_type>::list(const list &l) {
  init();
  copy(l.head_, l.count_node_);
}

template <typename value_type>
list<value_type>::list(list &&l) noexcept {
  init();
  swap_list(std::move(l));
}

template <typename value_type>
list<value_type> &list<value_type>::operator=(list<value_type> &&l) {
  clear();
  swap_list(std::move(l));
  return *this;
}

template <typename value_type>
list<value_type> &list<value_type>::operator=(const list<value_type> &l) {
  clear();
  copy(l.head_, l.count_node_);

  return *this;
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const &items) {
  init();
  for (auto &iter : items) {
    push_back(iter);
  }
}

template <typename value_type>
list<value_type>::~list() {
  clear();
  delete end_;
}
/*
 * List Element access
 */
template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  if (count_node_ == 0) throw std::out_of_range("list is empty");
  return head_->data_;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  if (count_node_ == 0) throw std::out_of_range("list is empty");
  return tail_->data_;
}
/*
 * List Capacity
 */
template <typename value_type>
bool list<value_type>::empty() {
  int flag = 1;
  if (head_ == nullptr && end_ == nullptr) flag = 0;
  return flag;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() {
  return count_node_;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(node) / 2;
}
/*
 * List Iterators
 */
template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return iterator(head_);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(end_);
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::cbegin() const {
  return const_iterator(head_);
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::cend() const {
  return const_iterator(end_);
}
/*
 * List Modifiers
 */
template <typename value_type>
void list<value_type>::sort() {
  if (count_node_ > 1) {
    // explanation - line 417
    for (auto i = begin(); i != end(); ++i) {
      for (auto j = begin(), j1 = ++begin(); j != --end(); ++j, ++j1) {
        if (j.ptr_->data_ > j1.ptr_->data_) {
          std::swap(j1.ptr_->data_, j.ptr_->data_);
        }
      }
    }
  }
}

template <typename value_type>
void list<value_type>::clear() {
  while (count_node_) {
    pop_front();
  }
}

template <typename value_type>
void list<value_type>::unique() {
  list<int>::iterator it_ = begin();
  for (; it_ != end(); ++it_) {
    if (it_.ptr_->data_ == it_.ptr_->p_prev_->data_) {
      erase(it_.ptr_->p_prev_);
    }
  }
}

template <typename value_type>
void list<value_type>::reverse() {
  int count_ = size() / 2;
  node *head_ = this->head_;
  node *tail_ = this->tail_;
  while (count_--) {
    std::swap(tail_->data_, head_->data_);
    head_ = head_->p_next_;
    tail_ = tail_->p_prev_;
  }
}

template <typename value_type>
void list<value_type>::pop_back() {
  if (tail_ == nullptr) throw std::out_of_range("list is empty");

  node *current_ = this->tail_;
  if (count_node_ == 1) {
    tail_ = head_ = nullptr;
  } else {
    tail_ = current_->p_prev_;
    tail_->p_next_ = nullptr;
  }
  delete current_;
  count_node_--;
  relate_end();
}

template <typename value_type>
void list<value_type>::pop_front() {
  if (head_ == nullptr) throw std::out_of_range("list is empty");
  node *current_ = this->head_;

  if (count_node_ == 1) {
    head_ = tail_ = nullptr;
  } else {
    head_ = current_->p_next_;
    head_->p_prev_ = nullptr;
  }
  delete current_;
  count_node_--;
  relate_end();
}

template <typename value_type>
void list<value_type>::swap(list &other) {
  node *head_this_ = this->head_;
  node *tail_this_ = this->tail_;
  node *end_this_ = this->end_;
  int count_this_ = this->count_node_;

  this->head_ = other.head_;
  this->tail_ = other.tail_;
  this->end_ = other.end_;
  this->count_node_ = other.count_node_;

  other.head_ = head_this_;
  other.tail_ = tail_this_;
  other.end_ = end_this_;
  other.count_node_ = count_this_;
}

template <typename value_type>
void list<value_type>::merge(list &other) {
  if (this != &other) {
    auto pos_this_ = begin();
    auto pos_other_ = other.begin();
    while (pos_this_ != end() && pos_other_ != other.end()) {
      if (*pos_this_ > *pos_other_) {
        insert(pos_this_, *pos_other_);
        ++pos_other_;
      } else if (*pos_this_ <= *pos_other_) {
        ++pos_this_;
      }
    }
    while (pos_other_ != other.end()) {
      insert(pos_this_, *pos_other_);
      ++pos_other_;
    }
    other.clear();
  }
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  if (pos.ptr_ == head_) {
    pop_front();
  } else if (pos.ptr_ == tail_) {
    pop_back();
  } else {
    pos.ptr_->p_next_->p_prev_ = pos.ptr_->p_prev_;
    pos.ptr_->p_prev_->p_next_ = pos.ptr_->p_next_;
    delete pos.ptr_;
    count_node_--;
  }
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  node *new_object = new node(value);
  if (tail_) {
    new_object->p_prev_ = tail_;
    tail_->p_next_ = new_object;
    tail_ = new_object;
  } else {
    head_ = new_object;
    tail_ = new_object;
  }
  count_node_++;
  relate_end();
}

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  node *new_object = new node(value);
  if (head_ != nullptr) {
    new_object->p_next_ = head_;
    head_->p_prev_ = new_object;
    head_ = new_object;
  } else {
    tail_ = new_object;
    head_ = new_object;
  }
  count_node_++;
  relate_end();
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  for (auto it_ = other.begin(); it_ != other.end(); ++it_) {
    insert(pos, *it_);
  }
  other.clear();
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos == begin()) {
    push_front(value);
  } else if (pos == end()) {
    push_back(value);
  } else {
    node *current_ = pos.ptr_;
    node *new_node_ = new node(value);
    new_node_->p_next_ = current_;
    new_node_->p_prev_ = current_->p_prev_;
    current_->p_prev_->p_next_ = new_node_;
    current_->p_prev_ = new_node_;
    count_node_++;
    relate_end();
  }
  return pos;
}
/*
 * Extra
 */
template <typename value_type>
void list<value_type>::copy(node *tmp, int count) {
  while (count--) {
    push_back(tmp->data_);
    tmp = tmp->p_next_;
  }
}

template <typename value_type>
list<value_type>::ListIterator::ListIterator() {
  ptr_ = nullptr;
}

template <typename value_type>
list<value_type>::ListIterator::ListIterator(node *ptr) {
  ptr_ = ptr;
}

template <typename value_type>
list<value_type>::ListConstIterator::ListConstIterator(node *ptr) {
  ListIterator::ptr_ = ptr;
}

template <typename value_type>
typename list<value_type>::iterator &
list<value_type>::ListIterator::operator--() {
  ptr_ = ptr_->p_prev_;
  return *this;
}

template <typename value_type>
typename list<value_type>::iterator &
list<value_type>::ListIterator::operator++() {
  ptr_ = ptr_->p_next_;
  return *this;
}

template <typename value_type>
typename list<value_type>::const_iterator &
list<value_type>::ListConstIterator::operator++() {
  ListIterator::ptr_ = ListIterator::ptr_->p_next_;
  return *this;
}

template <typename value_type>
typename list<value_type>::reference
list<value_type>::ListIterator::operator*() {
  return ptr_->data_;
}

template <typename value_type>
bool list<value_type>::ListIterator::operator==(const iterator &other) const {
  return ptr_ == other.ptr_;
}

template <typename value_type>
bool list<value_type>::ListIterator::operator!=(const iterator &other) const {
  return ptr_ != other.ptr_;
}

template <typename value_type>
typename list<value_type>::const_reference
list<value_type>::ListConstIterator::operator*() const {
  return ListIterator::ptr_->data_;
}

template <typename T>
void list<T>::relate_end() {
  if (end_) {
    end_->p_next_ = head_;
    end_->p_prev_ = tail_;
    end_->data_ = size();
  }
  if (head_) {
    head_->p_prev_ = end_;
  }
  if (tail_) {
    tail_->p_next_ = end_;
  }
}

template <typename value_type>
void list<value_type>::init() {
  count_node_ = 0;
  head_ = tail_ = nullptr;
  end_ = new node;
}

template <typename value_type>
void list<value_type>::swap_list(list &&l) {
  std::swap(this->head_, l.head_);
  std::swap(this->tail_, l.tail_);
  std::swap(this->count_node_, l.count_node_);
  std::swap(this->end_, l.end_);
}

}  // namespace s21

/*
  About sort

  1. i - iterate over i from the first iterator to the last, to include the
  last iterator in the loop using end() as (i < n)
  2. j - by j we take the first iterator and go to (end - 1) as (n - 1)
  3. In order to compare the first iterator with the next one, let's create
  another iterator j + 1, let's call it j1
  4. If j.data_ is greater than j1.data_ swap them == if (j > j + 1)
*/