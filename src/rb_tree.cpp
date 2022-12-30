/*
 * Skeleton code for project 3 in EE205 2018 Fall KAIST
 * Created by Wan Ju Kang.
 */

#include "rb_tree.h"
#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <cassert>
#include <algorithm>

using namespace std;

template <class T>
void RBTree<T>::inorder_print(RBNode<T> *n)
{
    if (!is_external(n))
    {
        inorder_print(n->leftChild);
    }
    cout << "(" << n->x_key << ", " << n->y_key << ", " << n->color << "), ";
    if (!is_external(n))
    {
        inorder_print(n->rightChild);
    }

    cout << " -- ";
}

/*
 * Print keys along preorder traversal.
 * The rule is the same as inorder_print(), except the order.
 */
template <class T>
void RBTree<T>::preorder_print(RBNode<T> *n)
{
    cout << "(" << n->x_key << ", " << n->y_key << "), ";
    preorder_print(n->leftChild);
    preorder_print(n->rightChild);
}

template <class T>
void RBTree<T>::post_insertion_balance(RBNode<T> *n)
{
    RBNode<T> *x = n;
    RBNode<T> *sibling;
    int direction; // 1 if n->parent is leftChild of n->parent->parent, 2 otherwise
    while (x != this->root)
    {
        if (is_double_red(x))
        {
            if (x->parent->parent->leftChild == x->parent)
            {
                sibling = x->parent->parent->rightChild;
                direction = 1;
            }
            else
            {
                sibling = x->parent->parent->leftChild;
                direction = 2;
            }
            if (sibling->color == BLACK) // Restructuring
            {
                x = restructure(x, direction);
                x->color = BLACK;
                x->leftChild->color = RED;
                x->rightChild->color = RED;
                break;
            }
            else // Recoloring
            {
                x->parent->color = BLACK;
                sibling->color = BLACK;
                if (!is_root(x->parent->parent))
                    x->parent->parent->color = RED;
                x = x->parent->parent;
            }
        }
        else
            break;
    }
}

template <class T>
void RBTree<T>::post_removal_balance(RBNode<T> *n)
{
    RBNode<T> *x = n;
    RBNode<T> *sibling;
    int direction;
    while (x != root && is_double_black(x))
    {
        if (x->parent->leftChild == x)
        {
            sibling = x->parent->rightChild;
            direction = 2;
        }
        else
        {
            sibling = x->parent->leftChild;
            direction = 1;
        }
        if (sibling->color == BLACK)
        {
            if (sibling->leftChild->color == RED)
            {
                x->color = BLACK;
                if (direction == 1)
                {
                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->leftChild->color = BLACK;
                    x = restructure(sibling->leftChild, direction);
                }
                else if (direction == 2)
                {
                    sibling->leftChild->color = BLACK;
                    sibling->color = RED;
                    sibling = rotate_right(sibling);

                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->rightChild->color = BLACK;
                    x = restructure(sibling->rightChild, direction);
                }
                break;
            }

            else if (sibling->rightChild->color == RED)
            {
                x->color = BLACK;
                if (direction == 1)
                {
                    sibling->rightChild->color = BLACK;
                    sibling->color = RED;
                    sibling = rotate_left(sibling);

                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->leftChild->color = BLACK;
                    x = restructure(sibling->leftChild, direction);
                }
                else if (direction == 2)
                {
                    sibling->color = sibling->parent->color;
                    sibling->parent->color = BLACK;
                    sibling->rightChild->color = BLACK;
                    x = restructure(sibling->rightChild, direction);
                }
                break;
            }

            else // Both children are black.
            {
                x->color = BLACK;
                sibling->color = RED;
                x->parent->color += 1;
                x = x->parent;

                if (x == this->root)
                {
                    x->color = BLACK;
                    break;
                }
            }
        }
        else
        {
            sibling->color = BLACK;
            x->parent->color = RED;
            if (direction == 1)
            {
                restructure(sibling->leftChild, direction);
            }
            else
            {
                restructure(sibling->rightChild, direction);
            }
        }
    }
}

template <class T>
RBNode<T> *RBTree<T>::rotate_right(RBNode<T> *n)
{
    RBNode<T> *x = n->leftChild;

    n->leftChild = x->rightChild;
    n->leftChild->parent = n;

    x->rightChild = n;
    x->parent = n->parent;

    if (!is_root(n))
    {
        if (n->parent->leftChild == n)
            n->parent->leftChild = x;
        else
            n->parent->rightChild = x;
    }
    else
        root = x;
    n->parent = x;

    return x;
}

/* Refer to the supplementary PPT file. And right above ↑↑↑ */
template <class T>
RBNode<T> *RBTree<T>::rotate_left(RBNode<T> *n)
{
    RBNode<T> *x = n->rightChild;

    n->rightChild = x->leftChild;
    n->rightChild->parent = n;

    x->leftChild = n;
    x->parent = n->parent;

    if (!is_root(n))
    {
        if (n->parent->leftChild == n)
            n->parent->leftChild = x;
        else
            n->parent->rightChild = x;
    }
    else
    {
        root = x;
    }
    n->parent = x;

    return x;
}

template <class T>
bool RBTree<T>::is_double_red(RBNode<T> *n)
{
    return (n->color == RED && n->parent->color == RED);
}

template <class T>
bool RBTree<T>::is_double_black(RBNode<T> *n)
{
    return (n->color == DOUBLE_BLACK);
}

template <class T>
RBNode<T> *RBTree<T>::restructure(RBNode<T> *n, int direction)
{
    RBNode<T> *x = n;
    if (x->parent->leftChild == x)
    {
        if (direction == 1)
        {
            x = rotate_right(x->parent->parent);
        }
        else
        {
            x = rotate_right(x->parent);
            x = rotate_left(x->parent);
        }
    }
    else
    {
        if (direction == 1)
        {
            x = rotate_left(x->parent);
            x = rotate_right(x->parent);
        }
        else
        {
            x = rotate_left(x->parent->parent);
        }
    }
    return x;
}

template <class T>
RBNode<T> *RBTree<T>::search(uint32_t x, uint32_t y, RBNode<T> *n)
{
    if (is_external(n))
        return n;

    if (x < n->x_key || (x == n->x_key && y < n->y_key))
        return search(x, y, n->leftChild);
    else if (x > n->x_key || (x == n->x_key && y > n->y_key))
        return search(x, y, n->rightChild);
    else
        return n;
}
template <class T>
RBNode<T> *RBTree<T>::search(uint32_t y, RBNode<T> *n)
{
    RBNode<T> *inserted_node = n;
    while (!is_external(inserted_node))
    {
        if (y < inserted_node->y_key)
            inserted_node = inserted_node->leftChild;
        else
            inserted_node = inserted_node->rightChild;
    }

    return inserted_node;
}

template <class T>
int RBTree<T>::set_value(RBNode<T> *n, uint32_t x, uint32_t y, T value)
{
    if (is_external(n)) // Insert
    {
        if (value != 0.0)
        {
            n->x_key = x;
            n->y_key = y;
            n->leftChild = new RBNode<T>(0, 0, n);
            n->rightChild = new RBNode<T>(0, 0, n);
            n->value = value;

            if (!is_root(n))
            {
                n->color = RED;
                post_insertion_balance(n);
            }
            return 1;
        }
        else
            return 0;
    }
    else
    {
        if (value != 0) // Update
        {
            n->value = value;
            return 0;
        }
        else // Delete
        {
            this->remove(x, y, n);
            return -1;
        }
    }
}

template <class T>
RBNode<T> *RBTree<T>::set_value(uint32_t y, T value)
{
    RBNode<T> *n = search(y, this->root);

    n->y_key = y;
    n->leftChild = new RBNode<T>(0, n);
    n->rightChild = new RBNode<T>(0, n);
    n->value = value;
    if (!is_root(n))
    {
        n->color = RED;
        post_insertion_balance(n);
    }
    return n;
}

template <class T>
bool RBTree<T>::remove(uint32_t x, uint32_t y, RBNode<T> *n)
{
    if (!is_external(n->leftChild) && !is_external(n->rightChild))
    {
        RBNode<T> *inorder_successor = n; // will be replaced with this after removal
        inorder_successor = inorder_successor->rightChild;
        while (!is_external(inorder_successor->leftChild))
        {
            inorder_successor = inorder_successor->leftChild;
        }
        n->x_key = inorder_successor->x_key;
        n->y_key = inorder_successor->y_key;
        n->value = inorder_successor->value;

        if (inorder_successor->parent->rightChild == inorder_successor)
        {
            inorder_successor->parent->rightChild = inorder_successor->rightChild;
            inorder_successor->rightChild->parent = inorder_successor->parent;
        }
        else
        {
            inorder_successor->parent->leftChild = inorder_successor->rightChild;
            inorder_successor->rightChild->parent = inorder_successor->parent;
        }

        if (inorder_successor->color == BLACK &&
            inorder_successor->rightChild->color == BLACK) // Right child must be leaf in this case
        {
            inorder_successor->rightChild->color = DOUBLE_BLACK;
            post_removal_balance(inorder_successor->rightChild);
        }
        else
            inorder_successor->rightChild->color = BLACK;

        delete inorder_successor->leftChild; // Leaf
        delete inorder_successor;

        return true;
    }
    else
    {
        if (!is_external(n->leftChild))
        {
            RBNode<T> *replace = n->leftChild;
            replace->parent = n->parent;
            if (!is_root(n))
            {
                if (n->parent->leftChild == n)
                    n->parent->leftChild = replace;
                else
                    n->parent->rightChild = replace;
            }
            else
                this->root = replace;

            // This cannot happen !
            if (n->color == BLACK && replace->color == BLACK)
            {
                // replace (left child) must be leaf node in this case
                replace->color = DOUBLE_BLACK;
                post_removal_balance(replace);
            }
            else
                replace->color = BLACK;

            delete n->rightChild;
            delete n;

            return true;
        }
        else
        {
            RBNode<T> *replace = n->rightChild;
            replace->parent = n->parent;
            if (!is_root(n))
            {
                if (n->parent->leftChild == n)
                    n->parent->leftChild = replace;
                else
                    n->parent->rightChild = replace;
            }
            else
                this->root = replace;

            if (n->color == BLACK && replace->color == BLACK)
            {
                // replace (right child) must be leaf node in this case
                replace->color = DOUBLE_BLACK;
                post_removal_balance(replace);
            }
            else
                replace->color = BLACK;

            delete n->leftChild;
            delete n;

            return true;
        }
    }
}
template <class T>
bool RBTree<T>::remove(uint32_t y, RBNode<T> *n)
{
    if (!is_external(n->leftChild) && !is_external(n->rightChild))
    {
        RBNode<T> *inorder_successor = n; // will be replaced with this after removal
        inorder_successor = inorder_successor->rightChild;
        while (!is_external(inorder_successor->leftChild))
        {
            inorder_successor = inorder_successor->leftChild;
        }
        n->y_key = inorder_successor->y_key;
        n->value = inorder_successor->value;

        if (inorder_successor->parent->rightChild == inorder_successor)
        {
            inorder_successor->parent->rightChild = inorder_successor->rightChild;
            inorder_successor->rightChild->parent = inorder_successor->parent;
        }
        else
        {
            inorder_successor->parent->leftChild = inorder_successor->rightChild;
            inorder_successor->rightChild->parent = inorder_successor->parent;
        }

        if (inorder_successor->color == BLACK &&
            inorder_successor->rightChild->color == BLACK) // Right child must be leaf in this case
        {
            inorder_successor->rightChild->color = DOUBLE_BLACK;
            post_removal_balance(inorder_successor->rightChild);
        }
        else
            inorder_successor->rightChild->color = BLACK;

        delete inorder_successor->leftChild;
        delete inorder_successor;
        return true;
    }
    else
    {
        if (!is_external(n->leftChild))
        {
            RBNode<T> *replace = n->leftChild;
            replace->parent = n->parent;
            if (!is_root(n))
            {
                if (n->parent->leftChild == n)
                    n->parent->leftChild = replace;
                else
                    n->parent->rightChild = replace;
            }
            else
                this->root = replace;

            // This cannot happen !
            if (n->color == BLACK && replace->color == BLACK)
            {
                // replace (left child) must be leaf node in this case
                replace->color = DOUBLE_BLACK;
                post_removal_balance(replace);
            }
            else
                replace->color = BLACK;

            delete n->rightChild;
            delete n;

            return false;
        }
        else
        {
            RBNode<T> *replace = n->rightChild;
            replace->parent = n->parent;
            if (!is_root(n))
            {
                if (n->parent->leftChild == n)
                    n->parent->leftChild = replace;
                else
                    n->parent->rightChild = replace;
            }
            else
                this->root = replace;

            if (n->color == BLACK && replace->color == BLACK)
            {
                // replace (right child) must be leaf node in this case
                replace->color = DOUBLE_BLACK;
                post_removal_balance(replace);
            }
            else
                replace->color = BLACK;

            delete n->leftChild;
            delete n;

            return false;
        }
    }
}

template <class T>
void RBTree<T>::clean(RBNode<T> *n)
{
    if (is_external(n))
    {
        delete n;
    }
    else
    {
        RBNode<T> *n_left = n->leftChild;
        RBNode<T> *n_right = n->rightChild;
        delete n;
        clean(n_left);
        clean(n_right);
    }
}

template class RBNode<double>;
template class RBTree<double>;