namespace s21 {

template <typename K, typename T>
typename BRTree<K, T>::tnode *BRTree<K, T>::find(tnode *&check_,
                                                 value_type value) {
  tnode *check__ = check_;
  while (check__ != nullptr && check__->data_.first != value.first) {
    if (value.first > check__->data_.first) {
      check__ = check__->right_;
    } else if (value.first < check__->data_.first) {
      check__ = check__->left_;
    }
  }
  return check__;
}

template <typename K, typename T>
void BRTree<K, T>::clear(tnode *root) {
  if (root != nullptr) {
    clear(root->left_);
    clear(root->right_);
    delete root;
  }
  root_ = nullptr;
  size_ = 0;
};

template <typename K, typename T>
void BRTree<K, T>::insert(value_type value) {
  tnode *new_node_ = new tnode(value, nullptr, nullptr, nullptr, RED);

  if (root_ == nullptr) {
    root_ = new_node_;
    root_->color_ = BLACK;
  } else {
    tnode *copy_root_ = root_;
    tnode *y_ = nullptr;

    while (copy_root_ != nullptr || copy_root_ != nullptr) {
      y_ = copy_root_;
      if (copy_root_->data_.first < new_node_->data_.first) {
        copy_root_ = copy_root_->right_;
      } else if (copy_root_->data_.first > new_node_->data_.first) {
        copy_root_ = copy_root_->left_;
      }
    }
    new_node_->parent_ = y_;

    if (new_node_->parent_->data_.first <= new_node_->data_.first) {
      y_->right_ = new_node_;
    } else if (new_node_->parent_->data_.first > new_node_->data_.first) {
      y_->left_ = new_node_;
    }
    if (new_node_->parent_->parent_ !=
        nullptr) {  //  we should balance the tree if grandpa or previous ones
                    //  exist (below)
      balance_tree(new_node_);
    }
  }
  size_++;
}

template <typename K, typename T>
void BRTree<K, T>::balance_tree(tnode *n_) {
  while (n_->parent_->color_ == RED) {
    tnode *g_ = n_->parent_->parent_;

    if (n_->parent_ == g_->left_) {  // Branch of the tree is left.
      tnode *u_ = g_->right_;
      if (u_ != nullptr && u_->color_ == RED) {  // case 3
        u_->color_ = BLACK;
        n_->parent_->color_ = BLACK;
        g_->color_ = RED;
      } else {
        if (n_ == n_->parent_->right_) {
          rotate_left(n_->parent_);
        }
        g_->color_ = RED;
        n_->parent_->color_ = BLACK;
        rotate_right(g_);
      }
    } else if (n_->parent_ == g_->right_) {  // Branch of the tree is right.
      // all the same but in the opposite direction
      tnode *u_ = g_->left_;
      if (u_ != nullptr && u_->color_ == RED) {
        u_->color_ = BLACK;
        n_->parent_->color_ = BLACK;
        g_->color_ = RED;
      } else {
        if (n_ == n_->parent_->left_) {
          rotate_right(n_->parent_);
        }
        g_->color_ = RED;
        n_->parent_->color_ = BLACK;
        rotate_left(g_);
      }
    }
  }
  root_->color_ = BLACK;  // case 1
}

template <typename K, typename T>
void BRTree<K, T>::rotate_left(
    tnode *p_) {  // name of varibles match the comments
  tnode *n_ = p_->right_;
  p_->right_ = n_->left_;
  if (n_->left_ != nullptr) {
    n_->left_->parent_ = p_;
  }
  n_->parent_ = p_->parent_;
  if (n_->parent_ == nullptr) {
    root_ = n_;
  } else if (n_ == n_->parent_->left_) {
    p_->parent_->left_ = n_;
  } else {
    p_->parent_->right_ = n_;
  }
  n_->left_ = p_;
  p_->parent_ = n_;
}

template <typename K, typename T>
void BRTree<K, T>::rotate_right(
    tnode *p_) {  // name of varibles match the comments
  tnode *n_ = p_->left_;
  p_->left_ = n_->right_;
  if (n_->right_ != nullptr) {
    n_->right_->parent_ = p_;
  }
  n_->parent_ = p_->parent_;
  if (n_->parent_ == nullptr) {
    root_ = n_;
  } else if (n_ == n_->parent_->right_) {
    p_->parent_->right_ = n_;
  } else {
    p_->parent_->left_ = n_;
  }
  n_->right_ = p_;
  p_->parent_ = n_;
}

template <typename K, typename T>
void BRTree<K, T>::remove(value_type value) {
  tnode *node_ = find(root_, value);
  if (node_ == nullptr) return;
  /*
   * The case when the node has no children
   */
  if (node_->left_ == nullptr && node_->right_ == nullptr) {
    if (node_->parent_ == nullptr) {
      root_ = nullptr;
    } else if (node_ == node_->parent_->right_) {
      node_->parent_->right_ = nullptr;
    } else if (node_ == node_->parent_->left_) {
      node_->parent_->left_ = nullptr;
    }
    /*
     * The case when the node has one child
     */
  } else if ((node_->left_ != nullptr || node_->right_ != nullptr) &&
             (node_->left_ == nullptr || node_->right_ == nullptr)) {
    (node_->left_ != nullptr)
        ? correcting(node_, node_->left_)
        : correcting(node_, node_->right_);  // correcting use for override node
    /*
     * The case when the node has two children
     */
  } else {
    tnode *minimal_ =
        node_->right_;  // Find the smallest element in its right subtree
                        // and move its value to the node to be removed
    while (minimal_->left_ != nullptr) {
      minimal_ = minimal_->left_;
    }
    if (minimal_ != node_->right_) {
      correcting(minimal_, minimal_->right_);
      minimal_->right_ = node_->right_;
      minimal_->right_->parent_ = minimal_;
    }
    correcting(node_, minimal_);
    minimal_->left_ = node_->left_;
    minimal_->parent_ = node_->parent_;
  }
  delete node_;
  node_ = nullptr;
  size_--;
}

template <typename K, typename T>
void BRTree<K, T>::correcting(tnode *removed_,
                              tnode *replaced_) {  // for override node
  if (removed_->parent_ == nullptr) {
    root_ = replaced_;
  } else if (removed_ == removed_->parent_->left_) {
    removed_->parent_->left_ = replaced_;
  } else if (removed_ == removed_->parent_->right_) {
    removed_->parent_->right_ = replaced_;
  }
  replaced_->parent_ = removed_->parent_;
}
}  // namespace s21

/*
    we should balance the tree if grandpa or previous ones exist

                        root(grandpa)
                parent              parent
        child                               child
--------------------------------------------------------------------
                        TO FIX AFTER INSERT

          If P is RED, U doesn't exist or its color is BLACK. And N is
      right child of P, but P is left child of G - case 4. Need to use Left
      Rotate.

                              G - root should be black
                        ______||_______
                      |               |
                      P == red        U == BLACK or doesn't exist
                      |_____
                            |
                            N == red

                             |
                             |
                             |
                            \ /

                      left rotate

                              G - root should be black
                        ______||_______
                      |               |
                      N == red        U == BLACK or doesn't exist
                _____ |
                |
                P == red
                             |
                             |
                             |
                            \ /

      if P is red and U is black. And P is left child of G and N is left
      child of P. Use rotate G.

                              P
                        ______||_______
                      |               |
                      N               G
                                      |______
                                              |
                                              U
----------------------------------------------------------------------------
          If U and P are RED than change their colors to black, G to red -
      case 3. G - should be black(it's root) - case 1, rechange color at the
      end of method;

                              G - root should be black
                        ______||_______
                      |               |
                      P == red        U == red
                _____||_____     _____||_____
                |            |   |            |
                N            N   X            X

  */

/*
      FOR DELETING

* well, there are 3 cases of nodes:
* 1) if the node has leaves on the left and right
* 2) if a node either has a node on the left or on the right
* 3) if a node has nodes on the right and on the left
* It is necessary to work out each of these options.
            For myself, visually imagine the removal:

                               G
                         ______||_______
                        |
                        P - an element for deleting
                  _____||_____
                 |            |
                 N            Х -  leaf
                 |
      Exist node

     What are we doing?

    If P has one node missing:
      When removing an element, it is necessary to knit a G knot to N.
      The parent of node P will point to the left node on N and node N will be
    point to node G as the parent.

   In case P is the root, N becomes the root of the tree.
*/
