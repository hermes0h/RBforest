#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <random>
#include <cassert>
#include <vector>
#include <tuple>
#include <chrono>
#include <algorithm>
#include <set>

#include "rb_tree.h"
#include "spmatix.h"

using namespace std;

void test_with_real_dataset(char *matrix_type)
{
    char buffer[100];
    uint32_t num_row, num_col;
    uint32_t src, dest;
    double value; // Generated at random
    char *src_str, *dest_str;
    vector<tuple<uint32_t, uint32_t>> edge_vector;

    uniform_real_distribution<double> unif(1, 10000);
    random_device rd{};
    default_random_engine re{rd()};

    // Ignore Matrix Description Part.
    cin.getline(buffer, 1000);
    while (buffer[0] == '%')
    {
        cin.getline(buffer, 1000);
    }

    // Extract Matrix Dimension
    num_row = (uint32_t)atoi(strtok(buffer, " \t"));
    num_col = (uint32_t)atoi(strtok(NULL, " \t"));

    // MTX format's indeices start with 1. So we need to adjust it to start with 0
    cin.getline(buffer, 100);
    while (!cin.eof())
    {
        src_str = strtok(buffer, " \t");
        dest_str = strtok(NULL, " \t");
        src = (uint32_t)atoi(src_str) - 1;
        dest = (uint32_t)atoi(dest_str) - 1;

        edge_vector.push_back({src, dest});

        cin.getline(buffer, 100);
    }

    // Remove possible duplicates
    set<tuple<uint32_t, uint32_t>> edge_set(edge_vector.begin(), edge_vector.end());
    edge_vector.assign(edge_set.begin(), edge_set.end());

    // Matrix Construction depending on user-specified type
    SPMatrix<double> *spmatrix;
    if (strcmp(matrix_type, "almatrix") == 0)
    {
        spmatrix = new ALMatrix<double>(num_row, num_col);
    }
    else if (strcmp(matrix_type, "dokmatrix") == 0)
    {
        spmatrix = new DOKMatrix<double>(num_row, num_col);
    }
    else if (strcmp(matrix_type, "rbmatrix") == 0)
    {
        spmatrix = new RBMatrix<double>(num_row, num_col);
    }
    else if (strcmp(matrix_type, "lhrbmatrix") == 0)
    {
        spmatrix = new LHRBMatrix<double>(num_row, num_col);
    }

    int64_t search_time, mutation_time;

    // Insertion Test
    random_shuffle(edge_vector.begin(), edge_vector.end());
    cout << "Insertion test started" << endl;

    auto insert_start = chrono::steady_clock::now();
    for (auto iter = edge_vector.begin();
         iter != edge_vector.end();
         iter++)
    {
        tuple<uint32_t, uint32_t> elem = *iter;
        spmatrix->_insert(get<0>(elem), get<1>(elem), unif(re));
    }
    auto insert_end = chrono::steady_clock::now();

    cout << "\tTotal Insertion Time : "
         << chrono::duration_cast<chrono::milliseconds>(insert_end - insert_start).count()
         << " [ms]" << endl;

    cout << "\tNNZ after insertion : " << spmatrix->size() << endl; // Confirmation

    // Update Test
    random_shuffle(edge_vector.begin(), edge_vector.end());
    cout << "Update test started" << endl;

    auto update_start = chrono::steady_clock::now();
    for (auto iter = edge_vector.begin();
         iter != edge_vector.end();
         iter++)
    {
        tuple<uint32_t, uint32_t> elem = *iter;
        spmatrix->_update(get<0>(elem), get<1>(elem), unif(re));
    }
    auto update_end = chrono::steady_clock::now();

    cout << "\tTotal Update Time : "
         << chrono::duration_cast<chrono::milliseconds>(update_end - update_start).count()
         << " [ms]" << endl;

    cout << "\tNNZ after update : " << spmatrix->size() << endl; // Confirmation

    // CSR Conversion Test
    cout << "CSR Conversion test started" << endl;
    auto conversion_start = chrono::steady_clock::now();

    spmatrix->tocsr();

    auto conversion_end = chrono::steady_clock::now();
    cout << "\tTotal CSR Conversion Time : "
         << chrono::duration_cast<chrono::milliseconds>(conversion_end - conversion_start).count()
         << " [ms]" << endl;

    cout << "\tNNZ after CSR Conversion : " << spmatrix->size() << endl; // Confirmation

    spmatrix->free_csr();

    // Delete Test
    random_shuffle(edge_vector.begin(), edge_vector.end());
    cout << "Delete test started" << endl;

    auto delete_start = chrono::steady_clock::now();
    for (auto iter = edge_vector.begin();
         iter != edge_vector.end();
         iter++)
    {
        tuple<uint32_t, uint32_t> elem = *iter;
        spmatrix->_delete(get<0>(elem), get<1>(elem), 0.0);
    }
    auto delete_end = chrono::steady_clock::now();

    cout << "\tTotal Deletion Time : "
         << chrono::duration_cast<chrono::milliseconds>(delete_end - delete_start).count()
         << " [ms]" << endl;

    cout << "\tNNZ after deletion : " << spmatrix->size() << endl; // Confirmation

    delete spmatrix;
}

int main(int argc, char **argv)
{
    test_with_real_dataset(argv[1]);

    return 0;
}