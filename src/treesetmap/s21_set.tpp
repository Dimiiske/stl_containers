namespace s21 {
/*
 * Set Member functions
 */
template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items) {
  for (auto &it_ : items) {
    insert(it_);
  }
}

template <typename Key>
set<Key>::set(const set &s) {
  clear();
  for (auto &it_ : s) {
    insert(it_.first);
  }
}

template <typename Key>
set<Key>::set(set &&s) noexcept {
  std::swap(this->root_, s.root_);
  std::swap(this->size_, s.size_);
}

template <typename Key>
set<Key>::~set() {
  clear();
}

template <typename Key>
set<Key> &set<Key>::operator=(set &&s) {
  std::swap(this->root_, s.root_);
  std::swap(this->size_, s.size_);
  return *this;
}

template <typename Key>
set<Key> &set<Key>::operator=(const set &s) {
  auto it_ = cbegin();
  for (; it_ != s.cend(); ++it_) {
    insert(*it_);
  }
  return *this;
}

/*
 * Set Iterators
 */
template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  typename Binary::tnode *node_ = this->root_;
  while (node_ != nullptr && node_->left_ != nullptr) {
    node_ = node_->left_;
  }
  return iterator(node_);
}

template <typename Key>
typename set<Key>::iterator set<Key>::cbegin() const {
  typename Binary::tnode *node_ = this->root_;
  while (node_ != nullptr && node_->left_ != nullptr) {
    node_ = node_->left_;
  }
  return iterator(node_);
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return iterator(nullptr);
}

template <typename Key>
typename set<Key>::iterator set<Key>::cend() const {
  return iterator(nullptr);
}
/*
 * Set Capacity
 */
template <typename Key>
bool set<Key>::empty() {
  return (this->root_ == nullptr);
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() {
  return Binary::size_;
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}
/*
 * Set Modifiers
 */
template <typename Key>
void set<Key>::clear() {
  if (this->root_ == nullptr) return;
  Binary::clear(this->root_);
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(const Key &key) {
  std::pair<value_type, bool> val_ = std::make_pair(key, 0);
  typename Binary::tnode *check_ = Binary::find(this->root_, val_);
  bool exp = false;
  if (check_ == nullptr) {
    Binary::insert(val_);
    exp = true;
  }
  return std::make_pair(iterator(Binary::find(this->root_, val_)), exp);
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  std::pair<value_type, bool> val_ = std::make_pair(*pos, 0);
  Binary::remove(val_);
}

template <typename Key>
void set<Key>::swap(set &other) {
  std::swap(this->root_, other.root_);
  std::swap(this->size_, other.size_);
}

template <typename Key>
void set<Key>::merge(set &other) {
  for (auto it_ : other) {
    if (it_ != this->root_->data_.first) {
      insert(std::move(it_));
    }
  }
  other.clear();
}
/*
 * Set Lookup
 */
template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key &key) {
  std::pair<value_type, bool> val_ = std::make_pair(key, 0);
  typename Binary::tnode *node_ = Binary::find(this->root_, val_);
  if (node_ != nullptr) {
    return iterator(node_);
  }
  return end();
}

template <typename Key>
bool set<Key>::contains(const Key &key) {
  std::pair<value_type, bool> val_ = std::make_pair(key, 0);
  typename Binary::tnode *check_ = Binary::find(this->root_, val_);
  return (check_ != nullptr);
}
/*
 * Iterator methods
 */
template <typename Key>
typename set<Key>::value_type set<Key>::Iterator::operator*() const {
  return this->node_->data_.first;
}

template <typename Key>
typename set<Key>::value_type *set<Key>::Iterator::operator->() {
  return this->node_->data_;
}

template <typename Key>
typename set<Key>::Iterator &set<Key>::Iterator::operator++() {
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

template <typename Key>
typename set<Key>::Iterator set<Key>::Iterator::operator++(int) {
  Iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <class Key>
typename set<Key>::Iterator &set<Key>::Iterator::operator--() {
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

template <typename Key>
bool set<Key>::Iterator::operator==(const Iterator &other) const noexcept {
  return node_ == other.node_;
}

template <typename Key>
bool set<Key>::Iterator::operator!=(const Iterator &other) const noexcept {
  return node_ != other.node_;
}
}  // namespace s21
