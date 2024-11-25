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