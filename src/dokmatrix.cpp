#include <cstdlib>
#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <unordered_map>
#include <algorithm>

#include "spmatix.h"

using namespace std;

template <class T>
DOKMatrix<T>::DOKMatrix(uint32_t n_row, uint32_t n_col)
    : SPMatrix<T>(n_row, n_col, 0)
{
}

template <class T>
auto DOKMatrix<T>::search(const uint32_t x, const uint32_t y)
{
    return this->hash_table.find({x, y});
}

template <class T>
pair<bool, T> DOKMatrix<T>::get_value(const uint32_t x, const uint32_t y)
{
    auto search_result = this->search(x, y);

    // Found
    if (search_result != this->hash_table.end())
        return make_pair(true, search_result->second);

    // Not Found
    return make_pair(false, -100000); // Not Found
}

template <class T>
void DOKMatrix<T>::set_value(const uint32_t x, const uint32_t y, const T value)
{
    auto search_result = this->search(x, y);

    // Insertion
    if (search_result == this->hash_table.end())
    {
        if (value != 0.0)
        {
            this->hash_table.insert_or_assign({x, y}, value);
            this->nnz++;
        }
    }

    else
    {
        // Update
        if (value != 0.0)
        {
            search_result->second = value;
        }

        // Deletion
        else
        {
            this->hash_table.erase(search_result);
            this->nnz--;
        }
    }
}

template <class T>
void DOKMatrix<T>::tocsr()
{
    vector<pair<tuple<uint32_t, uint32_t>, T>> elems(this->hash_table.begin(),
                                                     this->hash_table.end());

    this->csr_equivalent = new CSRMatrix<T>(this->n_row, this->n_col, this->nnz);

    sort(elems.begin(), elems.end(),
         [](const auto &x, const auto &y)
         {
             return ((get<0>(x.first) < get<0>(y.first)) ||
                     ((get<0>(x.first) == get<0>(y.first) &&
                       (get<1>(x.first) < get<1>(y.first)))));
         });

    for (auto const &[k, v] : elems)
    {
        this->csr_equivalent->set_value(get<0>(k), get<1>(k), v);
    }

    this->csr_equivalent->indptr_cumsum();
}

template <class T>
void DOKMatrix<T>::free_csr()
{
    delete this->csr_equivalent;
}

// Misc : Only used for static_perf_test. Just for testing purpose.
template <class T>
void DOKMatrix<T>::_insert(const uint32_t x, const uint32_t y, const T value)
{
    auto search_result = this->search(x, y);

    // Insertion
    if (search_result == this->hash_table.end())
    {
        if (value != 0.0)
        {
            this->hash_table.insert_or_assign({x, y}, value);
            this->nnz++;
        }
    }

    else
    {
        // Update
        if (value != 0.0)
        {
            search_result->second = value;
        }

        // Deletion
        else
        {
            this->hash_table.erase(search_result);
            this->nnz--;
        }
    }
}

template <class T>
void DOKMatrix<T>::_update(const uint32_t x, const uint32_t y, const T value)
{
    auto search_result = this->search(x, y);

    // Insertion
    if (search_result == this->hash_table.end())
    {
        if (value != 0.0)
        {
            this->hash_table.insert_or_assign({x, y}, value);
            this->nnz++;
        }
    }

    else
    {
        // Update
        if (value != 0.0)
        {
            search_result->second = value;
        }

        // Deletion
        else
        {
            this->hash_table.erase(search_result);
            this->nnz--;
        }
    }
}

template <class T>
void DOKMatrix<T>::_delete(const uint32_t x, const uint32_t y, const T value)
{
    auto search_result = this->search(x, y);

    // Insertion
    if (search_result == this->hash_table.end())
    {
        if (value != 0.0)
        {
            this->hash_table.insert_or_assign({x, y}, value);
            this->nnz++;
        }
    }

    else
    {
        // Update
        if (value != 0.0)
        {
            search_result->second = value;
        }

        // Deletion
        else
        {
            this->hash_table.erase(search_result);
            this->nnz--;
        }
    }
}

template class DOKMatrix<double>;
