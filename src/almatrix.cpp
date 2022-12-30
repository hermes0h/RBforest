#include <cstdlib>
#include <iostream>
#include <vector>
#include <tuple>
#include <forward_list>

#include "spmatix.h"

using namespace std;

template <class T>
ALMatrix<T>::ALMatrix(uint32_t n_row, uint32_t n_col)
    : SPMatrix<T>(n_row, n_col, 0),
      bucket(n_row)
{
}

template <class T>
auto ALMatrix<T>::search(const uint32_t x, const uint32_t y, forward_list<tuple<uint32_t, T>> &edge_list)
{
    auto iter = edge_list.begin();
    auto prev = edge_list.begin();

    for (;
         iter != edge_list.end();
         iter++)
    {
        if (get<0>(*iter) >= y)
        {
            break;
        }
        prev = iter;
    }

    if (iter == edge_list.begin())
    {
        return make_pair(iter, 0);
    }
    else
    {
        return make_pair(prev, 1);
    }
}

template <class T>
pair<bool, T> ALMatrix<T>::get_value(const uint32_t x, const uint32_t y)
{
    auto &edge_list = this->bucket[x];

    for (auto iter = edge_list.begin();
         iter != edge_list.end();
         iter++)
    {
        if (get<0>(*iter) == y)
        {
            return make_pair(true, get<1>(*iter));
        }
    }

    return make_pair(false, ELEM_NOT_FOUND); // Not Found
}

template <class T>
void ALMatrix<T>::set_value(const uint32_t x, const uint32_t y, const T value)
{
    auto &edge_list = this->bucket[x];
    auto search_result = search(x, y, edge_list);
    auto iter = search_result.first;
    int is_back = search_result.second;

    if (is_back == 0)
    {
        // Insertion
        if (iter == edge_list.end() ||
            get<0>(*iter) > y)
        {
            if (value != 0.0)
            {
                edge_list.push_front({y, value});
                this->nnz++;
            }
        }
        else if (get<0>(*iter) == y)
        {
            // Update
            if (value != 0.0)
            {
                get<1>(*iter) = value;
            }
            // Delete
            else
            {
                edge_list.pop_front();
                this->nnz--;
            }
        }
    }

    else
    {
        auto next = iter;
        next++;

        // Insertion
        if (next == edge_list.end() ||
            get<0>(*next) > y)
        {
            edge_list.insert_after(iter, {y, value});
            this->nnz++;
        }
        else if (get<0>(*next) == y)
        {
            // Update
            if (value != 0.0)
            {
                get<1>(*next) = value;
            }
            // Delete
            else
            {
                edge_list.erase_after(iter);
                this->nnz--;
            }
        }
    }
}

template <class T>
void ALMatrix<T>::tocsr()
{
    this->csr_equivalent = new CSRMatrix<T>(this->n_row, this->n_col, this->nnz);

    for (uint32_t i = 0; i < this->n_row; i++)
    {
        auto &edge_list = this->bucket[i];
        auto iter = edge_list.begin();

        for (;
             iter != edge_list.end();
             iter++)
        {
            this->csr_equivalent->set_value(i, get<0>(*iter), get<1>(*iter));
        }
    }

    this->csr_equivalent->indptr_cumsum();
}

template <class T>
void ALMatrix<T>::free_csr()
{
    delete this->csr_equivalent;
}

// Misc : Only used for static_perf_test. Just for testing purpose.
template <class T>
void ALMatrix<T>::_insert(const uint32_t x, const uint32_t y, const T value)
{
    auto &edge_list = this->bucket[x];
    auto search_result = search(x, y, edge_list);
    auto iter = search_result.first;
    int is_back = search_result.second;

    if (is_back == 0)
    {
        // Insertion
        if (iter == edge_list.end() ||
            get<0>(*iter) > y)
        {
            if (value != 0.0)
            {
                edge_list.push_front({y, value});
                this->nnz++;
            }
        }
        else if (get<0>(*iter) == y)
        {
            // Update
            if (value != 0.0)
            {
                get<1>(*iter) = value;
            }
            // Delete
            else
            {
                edge_list.pop_front();
                this->nnz--;
            }
        }
    }

    else
    {
        auto next = iter;
        next++;

        // Insertion
        if (next == edge_list.end() ||
            get<0>(*next) > y)
        {
            edge_list.insert_after(iter, {y, value});
            this->nnz++;
        }
        else if (get<0>(*next) == y)
        {
            // Update
            if (value != 0.0)
            {
                get<1>(*next) = value;
            }
            // Delete
            else
            {
                edge_list.erase_after(iter);
                this->nnz--;
            }
        }
    }
}

template <class T>
void ALMatrix<T>::_update(const uint32_t x, const uint32_t y, const T value)
{
    auto &edge_list = this->bucket[x];
    auto search_result = search(x, y, edge_list);
    auto iter = search_result.first;
    int is_back = search_result.second;

    if (is_back == 0)
    {
        // Insertion
        if (iter == edge_list.end() ||
            get<0>(*iter) > y)
        {
            if (value != 0.0)
            {
                edge_list.push_front({y, value});
                this->nnz++;
            }
        }
        else if (get<0>(*iter) == y)
        {
            // Update
            if (value != 0.0)
            {
                get<1>(*iter) = value;
            }
            // Delete
            else
            {
                edge_list.pop_front();
                this->nnz--;
            }
        }
    }

    else
    {
        auto next = iter;
        next++;

        // Insertion
        if (next == edge_list.end() ||
            get<0>(*next) > y)
        {
            edge_list.insert_after(iter, {y, value});
            this->nnz++;
        }
        else if (get<0>(*next) == y)
        {
            // Update
            if (value != 0.0)
            {
                get<1>(*next) = value;
            }
            // Delete
            else
            {
                edge_list.erase_after(iter);
                this->nnz--;
            }
        }
    }
}

template <class T>
void ALMatrix<T>::_delete(const uint32_t x, const uint32_t y, const T value)
{
    auto &edge_list = this->bucket[x];
    auto search_result = search(x, y, edge_list);
    auto iter = search_result.first;
    int is_back = search_result.second;

    if (is_back == 0)
    {
        // Insertion
        if (iter == edge_list.end() ||
            get<0>(*iter) > y)
        {
            if (value != 0.0)
            {
                edge_list.push_front({y, value});
                this->nnz++;
            }
        }
        else if (get<0>(*iter) == y)
        {
            // Update
            if (value != 0.0)
            {
                get<1>(*iter) = value;
            }
            // Delete
            else
            {
                edge_list.pop_front();
                this->nnz--;
            }
        }
    }

    else
    {
        auto next = iter;
        next++;

        // Insertion
        if (next == edge_list.end() ||
            get<0>(*next) > y)
        {
            edge_list.insert_after(iter, {y, value});
            this->nnz++;
        }
        else if (get<0>(*next) == y)
        {
            // Update
            if (value != 0.0)
            {
                get<1>(*next) = value;
            }
            // Delete
            else
            {
                edge_list.erase_after(iter);
                this->nnz--;
            }
        }
    }
}

template class ALMatrix<double>;
