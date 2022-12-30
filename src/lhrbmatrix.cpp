#include <cstdlib>
#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <unordered_map>
#include <algorithm>

#include "rb_tree.h"
#include "spmatix.h"

using namespace std;

template <class T>
LHRBMatrix<T>::LHRBMatrix(uint32_t n_row, uint32_t n_col)
    : SPMatrix<T>(n_row, n_col, 0),
      rbtree_vector(n_row)
{
   // this->hash_connector.reserve(50000000);
}

template <class T>
auto LHRBMatrix<T>::search(const uint32_t x, const uint32_t y)
{
    return this->hash_connector.find({x, y});
}

template <class T>
pair<bool, T> LHRBMatrix<T>::get_value(const uint32_t x, const uint32_t y)
{
    auto search_result = this->search(x, y);

    // Found
    if (search_result != this->hash_connector.end())
        return make_pair(true, search_result->second->value);

    // Not Found
    return make_pair(false, -100000); // Temp : Not Found
}

template <class T>
void LHRBMatrix<T>::set_value(const uint32_t x, const uint32_t y, const T value)
{
    auto search_result = this->search(x, y);

    // Insertion
    if (search_result == this->hash_connector.end())
    {
        if (value != 0.0)
        {
            RBNode<T> *inserted_node = (this->rbtree_vector[x]).set_value(y, value);
            this->hash_connector.insert({{x, y}, inserted_node});
            this->nnz++;
        }
    }

    else
    {
        // Update
        if (value != 0.0)
        {
            search_result->second->value = value;
        }

        // Deletion
        else
        {
            bool modified =
                (this->rbtree_vector[x]).remove(y, search_result->second);
            if (modified)
            {
                RBNode<T> *modified_node = search_result->second;
                this->hash_connector.insert_or_assign(
                    {x, modified_node->y_key}, modified_node);
            }

            this->hash_connector.erase(search_result);
            this->nnz--;
        }
    }
}

template <class T>
void LHRBMatrix<T>::tocsr()
{
    this->csr_equivalent = new CSRMatrix<T>(this->n_row, this->n_col, this->nnz);

    for (uint32_t x = 0; x < this->n_row; x++)
    {
        RBNode<T> *tree_root = (this->rbtree_vector[x]).get_root();
        this->inorder_csr_insert(x, tree_root);
    }

    this->csr_equivalent->indptr_cumsum();
}

template <class T>
void LHRBMatrix<T>::free_csr()
{
    delete this->csr_equivalent;
}

template <class T>
void LHRBMatrix<T>::inorder_csr_insert(uint32_t x_coord, RBNode<T> *n)
{
    if (!(this->rbtree_vector[x_coord]).is_external(n))
    {
        inorder_csr_insert(x_coord, n->leftChild);

        this->csr_equivalent->set_value(x_coord, n->y_key, n->value);

        inorder_csr_insert(x_coord, n->rightChild);
    }
}

// Misc : Only used for static_perf_test. Just for testing purpose.
template <class T>
void LHRBMatrix<T>::_insert(const uint32_t x, const uint32_t y, const T value)
{
    auto search_result = this->search(x, y);

    // Insertion
    if (search_result == this->hash_connector.end())
    {
        if (value != 0.0)
        {
            RBNode<T> *inserted_node = (this->rbtree_vector[x]).set_value(y, value);
            this->hash_connector.insert({{x, y}, inserted_node});
            this->nnz++;
        }
    }

    else
    {
        // Update
        if (value != 0.0)
        {
            search_result->second->value = value;
        }

        // Deletion
        else
        {
            bool modified =
                (this->rbtree_vector[x]).remove(y, search_result->second);
            if (modified)
            {
                RBNode<T> *modified_node = search_result->second;
                this->hash_connector.insert_or_assign(
                    {x, modified_node->y_key}, modified_node);
            }

            this->hash_connector.erase(search_result);
            this->nnz--;
        }
    }
}

template <class T>
void LHRBMatrix<T>::_update(const uint32_t x, const uint32_t y, const T value)
{
    auto search_result = this->search(x, y);

    // Insertion
    if (search_result == this->hash_connector.end())
    {
        if (value != 0.0)
        {
            RBNode<T> *inserted_node = (this->rbtree_vector[x]).set_value(y, value);
            this->hash_connector.insert({{x, y}, inserted_node});
            this->nnz++;
        }
    }

    else
    {
        // Update
        if (value != 0.0)
        {
            search_result->second->value = value;
        }

        // Deletion
        else
        {
            bool modified =
                (this->rbtree_vector[x]).remove(y, search_result->second);
            if (modified)
            {
                RBNode<T> *modified_node = search_result->second;
                this->hash_connector.insert_or_assign(
                    {x, modified_node->y_key}, modified_node);
            }

            this->hash_connector.erase(search_result);
            this->nnz--;
        }
    }
}

template <class T>
void LHRBMatrix<T>::_delete(const uint32_t x, const uint32_t y, const T value)
{
    auto search_result = this->search(x, y);

    // Insertion
    if (search_result == this->hash_connector.end())
    {
        if (value != 0.0)
        {
            RBNode<T> *inserted_node = (this->rbtree_vector[x]).set_value(y, value);
            this->hash_connector.insert({{x, y}, inserted_node});
            this->nnz++;
        }
    }

    else
    {
        // Update
        if (value != 0.0)
        {
            search_result->second->value = value;
        }

        // Deletion
        else
        {
            bool modified =
                (this->rbtree_vector[x]).remove(y, search_result->second);
            if (modified)
            {
                RBNode<T> *modified_node = search_result->second;
                this->hash_connector.insert_or_assign(
                    {x, modified_node->y_key}, modified_node);
            }

            this->hash_connector.erase(search_result);
            this->nnz--;
        }
    }
}

template class LHRBMatrix<double>;
