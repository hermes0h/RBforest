#ifndef __SP_MATRIX_H__
#define __SP_MATRIX_H__

#include <cstdlib>
#include <vector>
#include <forward_list>
#include <unordered_map>
#include <map>
#include <chrono>

#include "rb_tree.h"

using namespace std;

template <class T>
class CSRMatrix
{
public:
    T get_value(const uint32_t x, const uint32_t y);
    void set_value(const uint32_t x, const uint32_t y, const T value);
    void load_from_coo(const vector<pair<tuple<uint32_t, uint32_t>, T>> &coo_vector);
    void indptr_cumsum();

    CSRMatrix(uint32_t n_row, uint32_t n_col, size_t capacity);

    uint32_t size();

private:
    uint32_t n_row;
    uint32_t n_col;
    size_t nnz;
    vector<uint32_t> indptr;
    vector<uint32_t> indices;
    vector<T> data;

    template <class U>
    friend class LHRBMatrix;
    template <class U>
    friend class RBMatrix;
};

template <class T>
uint32_t CSRMatrix<T>::size()
{
    return this->nnz;
}

template <class T>
class SPMatrix
{
public:
    virtual pair<bool, T> get_value(const uint32_t x, const uint32_t y) = 0;
    virtual void set_value(const uint32_t x, const uint32_t y, T const value) = 0;
    virtual void tocsr() = 0;
    virtual void free_csr() = 0;

    // Used only for static_perf_test
    virtual void _insert(const uint32_t x, const uint32_t y, T const value) = 0;
    virtual void _update(const uint32_t x, const uint32_t y, T const value) = 0;
    virtual void _delete(const uint32_t x, const uint32_t y, T const value) = 0;

    uint32_t size();

    SPMatrix(uint32_t n_row, uint32_t n_col, size_t nnz);
    virtual ~SPMatrix();

protected:
    uint32_t n_row;
    uint32_t n_col;
    size_t nnz;
    CSRMatrix<T> *csr_equivalent;
};

template <class T>
SPMatrix<T>::SPMatrix(uint32_t n_row, uint32_t n_col, size_t nnz)
    : n_row{n_row},
      n_col{n_col},
      nnz{nnz}
{
}

template <class T>
SPMatrix<T>::~SPMatrix()
{
}

template <class T>
uint32_t SPMatrix<T>::size()
{
    return this->nnz;
}

using hash_key_type = tuple<uint32_t, uint32_t>;

struct hash_key_hash
{
    // Cantor's Pairing Function
    uint32_t operator()(const hash_key_type &key) const
    {
        uint32_t x = get<0>(key);
        uint32_t y = get<1>(key);
        return (((x + y) * (x + y + 1)) >> 1) + x;
    }
};

template <class T>
class LHRBMatrix : public SPMatrix<T>
{
public:
    pair<bool, T> get_value(const uint32_t x, const uint32_t y) override;
    void set_value(const uint32_t x, const uint32_t y, const T value) override;
    void tocsr() override;
    void free_csr() override;

    void _insert(const uint32_t x, const uint32_t y, T const value);
    void _update(const uint32_t x, const uint32_t y, T const value);
    void _delete(const uint32_t x, const uint32_t y, T const value);

    LHRBMatrix(uint32_t n_row, uint32_t n_col);

    auto search(const uint32_t x, const uint32_t y);

private:
    vector<RBTree<T>> rbtree_vector;
    unordered_map<tuple<uint32_t, uint32_t>, RBNode<T> *, hash_key_hash> hash_connector;

    void inorder_csr_insert(uint32_t x_coord, RBNode<T> *n);
};

template <class T>
class DOKMatrix : public SPMatrix<T>
{
public:
    pair<bool, T> get_value(const uint32_t x, const uint32_t y) override;
    void set_value(const uint32_t x, const uint32_t y, const T value) override;
    void tocsr() override;
    void free_csr() override;

    void _insert(const uint32_t x, const uint32_t y, T const value);
    void _update(const uint32_t x, const uint32_t y, T const value);
    void _delete(const uint32_t x, const uint32_t y, T const value);

    DOKMatrix(uint32_t n_row, uint32_t n_col);

    auto search(const uint32_t x, const uint32_t y);

private:
    unordered_map<tuple<uint32_t, uint32_t>, T, hash_key_hash> hash_table;
};

template <class T>
class ALMatrix : public SPMatrix<T>
{
public:
    pair<bool, T> get_value(const uint32_t x, const uint32_t y) override;
    void set_value(const uint32_t x, const uint32_t y, const T value) override;
    void tocsr() override;
    void free_csr() override;

    void _insert(const uint32_t x, const uint32_t y, T const value);
    void _update(const uint32_t x, const uint32_t y, T const value);
    void _delete(const uint32_t x, const uint32_t y, T const value);

    ALMatrix(uint32_t n_row, uint32_t n_col);

private:
    vector<forward_list<tuple<uint32_t, T>>> bucket;

    auto search(const uint32_t x, const uint32_t y, forward_list<tuple<uint32_t, T>> &edge_list);
};

// rbmatrix used rbtree of mine
template <class T>
class RBMatrix : public SPMatrix<T>
{
public:
    pair<bool, T> get_value(const uint32_t x, const uint32_t y) override;
    void set_value(const uint32_t x, const uint32_t y, const T value) override;
    void tocsr() override;
    void free_csr() override;

    void _insert(const uint32_t x, const uint32_t y, T const value);
    void _update(const uint32_t x, const uint32_t y, T const value);
    void _delete(const uint32_t x, const uint32_t y, T const value);

    RBMatrix(uint32_t n_row, uint32_t n_col);
    ~RBMatrix();

private:
    RBTree<T> *data_rbtree;

    void inorder_csr_insert(RBNode<T> *n);
};

#define ELEM_NOT_FOUND -1000000

#endif