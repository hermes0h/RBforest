#include <cstdlib>
#include <iostream>
#include <vector>
#include <initializer_list>

#include "rb_tree.h"
#include "spmatix.h"

using namespace std;

template <class T>
RBMatrix<T>::RBMatrix(uint32_t n_row, uint32_t n_col)
    : SPMatrix<T>(n_row, n_col, 0)
{
    this->data_rbtree = new RBTree<T>();
}

template <class T>
RBMatrix<T>::~RBMatrix()
{
    delete this->data_rbtree;
}

template <class T>
pair<bool, T> RBMatrix<T>::get_value(const uint32_t x, const uint32_t y)
{
    RBNode<T> *node = this->data_rbtree->search(x, y, this->data_rbtree->get_root());

    if (this->data_rbtree->is_external(node))
    {
        return make_pair(false, ELEM_NOT_FOUND);
    }
    else
    {
        return make_pair(true, node->value);
    }
}

template <class T>
void RBMatrix<T>::set_value(const uint32_t x, const uint32_t y, const T value)
{
    RBNode<T> *n = this->data_rbtree->search(x, y, this->data_rbtree->get_root());
    this->nnz += this->data_rbtree->set_value(n, x, y, value);
}

template <class T>
void RBMatrix<T>::tocsr()
{
    this->csr_equivalent = new CSRMatrix<T>(this->n_row, this->n_col, this->nnz);

    RBNode<T> *tree_root = this->data_rbtree->get_root();
    this->inorder_csr_insert(tree_root);

    this->csr_equivalent->indptr_cumsum();
}

template <class T>
void RBMatrix<T>::free_csr()
{
    delete this->csr_equivalent;
}

template <class T>
void RBMatrix<T>::inorder_csr_insert(RBNode<T> *n)
{
    if (!this->data_rbtree->is_external(n))
    {
        inorder_csr_insert(n->leftChild);

        this->csr_equivalent->set_value(n->x_key, n->y_key, n->value);

        inorder_csr_insert(n->rightChild);
    }
}

// Misc : Only used for static_perf_test. Just for testing purpose.
template <class T>
void RBMatrix<T>::_insert(const uint32_t x, const uint32_t y, const T value)
{
    RBNode<T> *n = this->data_rbtree->search(x, y, this->data_rbtree->get_root());
    this->nnz += this->data_rbtree->set_value(n, x, y, value);
}

template <class T>
void RBMatrix<T>::_update(const uint32_t x, const uint32_t y, const T value)
{
    RBNode<T> *n = this->data_rbtree->search(x, y, this->data_rbtree->get_root());
    this->nnz += this->data_rbtree->set_value(n, x, y, value);
}

template <class T>
void RBMatrix<T>::_delete(const uint32_t x, const uint32_t y, const T value)
{
    RBNode<T> *n = this->data_rbtree->search(x, y, this->data_rbtree->get_root());
    this->nnz += this->data_rbtree->set_value(n, x, y, value);
}

template class RBMatrix<double>;