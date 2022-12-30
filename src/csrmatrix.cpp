#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

#include "rb_tree.h"
#include "spmatix.h"

using namespace std;

template <class T>
CSRMatrix<T>::CSRMatrix(uint32_t n_row, uint32_t n_col, size_t capacity)
    : n_row{n_row},
      n_col{n_col},
      nnz{0},
      indptr(n_row + 1, 0),
      indices(capacity),
      data(capacity)
{
}

template <class T>
T CSRMatrix<T>::get_value(const uint32_t x, const uint32_t y)
{
    uint32_t start = this->indptr[x];
    uint32_t finish = this->indptr[x + 1];

    for (uint32_t i = start; i < finish; i++)
    {
        if (this->indices[i] == y)
            return this->data[i];
    }

    return -100000; // Temp : Not Found
}

template <class T>
void CSRMatrix<T>::set_value(const uint32_t x, const uint32_t y, const T value)
{
    this->indptr[x + 1]++;
    this->indices[this->nnz] = y;
    this->data[this->nnz] = value;

    this->nnz++;
}

// Same as scipy's dok -> csr algorithm with sorted indices.
template <class T>
void CSRMatrix<T>::load_from_coo(const vector<pair<tuple<uint32_t, uint32_t>, T>> &coo_vector)
{
    // Compute nnz for each row
    for (auto const &[coord, v] : coo_vector)
    {
        this->indptr[get<0>(coord) + 1]++;
    }

    this->indptr_cumsum();

    // Write Data
    for (auto const &[coord, v] : coo_vector)
    {
        this->indices[this->indptr[get<0>(coord)]] = get<1>(coord);
        this->data[this->indptr[get<0>(coord)]] = v;

        this->indptr[get<0>(coord)]++;
    }

    // Roll back the indptr in original form
    for (uint32_t i = 0; i < this->n_row; i++)
    {
        this->indptr[this->n_row - i] = this->indptr[this->n_row - i - 1];
    }
    this->indptr[0] = 0;

    // Sort each row's column indicies.
    vector<pair<uint32_t, T>> temp;

    for (uint32_t i = 0; i < this->n_row; i++)
    {
        uint32_t row_start = this->indptr[i];
        uint32_t row_end = this->indptr[i + 1];

        temp.resize(row_end - row_start);
        for (uint32_t j = 0; j < row_end - row_start; j++)
        {
            temp[j].first = this->indices[row_start + j];
            temp[j].second = this->data[row_start + j];
        }

        sort(temp.begin(), temp.end(),
             [](const auto &x, const auto &y)
             { return x.first < y.first; });

        for (uint32_t j = 0; j < row_end - row_start; j++)
        {
            this->indices[row_start + j] = temp[j].first;
            this->data[row_start + j] = temp[j].second;
        }
    }
}

// Cumsum over indptr
template <class T>
void CSRMatrix<T>::indptr_cumsum()
{
    for (uint32_t i = 0; i < this->n_row; i++)
    {
        this->indptr[i + 1] += this->indptr[i];
    }
}

template class CSRMatrix<double>;