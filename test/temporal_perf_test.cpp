#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <random>
#include <vector>
#include <tuple>
#include <chrono>
#include <algorithm>

#include "rb_tree.h"
#include "spmatix.h"

using namespace std;

void temporal_workload_test(char *matrix_type, char *time_slice)
{
    char buffer[200];
    uint32_t num_row, num_col;
    uint32_t src, dest;
    double weight;
    char *src_str, *dest_str, *weight_str;
    string date, cur_date = "1900-01-01 00:00:00";
    vector<vector<tuple<uint32_t, uint32_t, double>>> edge_vector_all;

    // Extract Matrix Dimension
    cin.getline(buffer, 200);
    num_row = (uint32_t)atoi(strtok(buffer, " \t"));
    num_col = (uint32_t)atoi(strtok(NULL, " \t"));

    // Generate vector of tuples for each day.
    cin.getline(buffer, 200);
    while (!cin.eof())
    {
        src_str = strtok(buffer, " \t");
        dest_str = strtok(NULL, " \t");
        weight_str = strtok(NULL, " \t");
        date = strtok(NULL, "");
        src = (uint32_t)atoi(src_str) - 1;
        dest = (uint32_t)atoi(dest_str) - 1;
        weight = (double)atof(weight_str);

        // New hour found
        if (strcmp(time_slice, "hour") == 0 &&
            cur_date.compare(0, 13, date, 0, 13) != 0)
        {
            vector<tuple<uint32_t, uint32_t, double>> edge_vector_partition;
            edge_vector_all.push_back(edge_vector_partition);
            cur_date = date;
        }
        // New day found
        else if (strcmp(time_slice, "day") == 0 &&
                 cur_date.compare(0, 10, date, 0, 10) != 0)
        {
            vector<tuple<uint32_t, uint32_t, double>> edge_vector_partition;
            edge_vector_all.push_back(edge_vector_partition);
            cur_date = date;
        }
        // New month found
        else if (strcmp(time_slice, "month") == 0 &&
                 cur_date.compare(0, 7, date, 0, 7) != 0)
        {
            vector<tuple<uint32_t, uint32_t, double>> edge_vector_partition;
            edge_vector_all.push_back(edge_vector_partition);
            cur_date = date;
        }
        // New year found
        else if (strcmp(time_slice, "year") == 0 &&
                 cur_date.compare(0, 4, date, 0, 4) != 0)
        {
            vector<tuple<uint32_t, uint32_t, double>> edge_vector_partition;
            edge_vector_all.push_back(edge_vector_partition);
            cur_date = date;
        }

        edge_vector_all[edge_vector_all.size() - 1].push_back({src, dest, weight});

        cin.getline(buffer, 200);
    }

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

    cout << "Number of different partitions : " << edge_vector_all.size() << endl;
    cout << "Temporal Performance Test Started" << endl;
    auto test_start = chrono::steady_clock::now();
    auto total_conversion_time = 0;

    for (auto const &day : edge_vector_all)
    {
        for (auto const &edge : day)
        {
            spmatrix->set_value(get<0>(edge), get<1>(edge), get<2>(edge));
        }

        spmatrix->tocsr();

        spmatrix->free_csr();
    }

    cout << "Number of Static Edges after all Temporal Edge Mutations : " << spmatrix->size() << endl;

    auto test_end = chrono::steady_clock::now();
    cout << "Total Elapsed Time : "
         << chrono::duration_cast<chrono::microseconds>(test_end - test_start).count()
         << "[us]" << endl;

    delete spmatrix;
}

void periodic_workload_test(char *matrix_type, int num_mutation_per_convert)
{
    char buffer[200];
    uint32_t num_row, num_col, num_edge, num_edge_per_partition;
    uint32_t src, dest;
    int weight;
    int cur_partition = 0;
    double value; // Generated at random
    char *src_str, *dest_str, *weight_str;

    // Extract Matrix Dimension
    cin.getline(buffer, 200);
    num_row = (uint32_t)atoi(strtok(buffer, " \t"));
    num_col = (uint32_t)atoi(strtok(NULL, " \t"));

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

    cout << "Dynamic Performance Test Started" << endl;
    int iter = 0;

    // Partition the matrix with the given size.
    auto test_start = chrono::steady_clock::now();
    cin.getline(buffer, 200);
    while (!cin.eof())
    {
        iter++;
        src_str = strtok(buffer, " \t");
        dest_str = strtok(NULL, " \t");
        weight_str = strtok(NULL, " \t");
        src = (uint32_t)atoi(src_str) - 1;
        dest = (uint32_t)atoi(dest_str) - 1;
        weight = (int)atoi(weight_str);

        spmatrix->set_value(src, dest, weight);

        if (iter % num_mutation_per_convert == 0)
        {
            spmatrix->tocsr();
            spmatrix->free_csr();
        }

        cin.getline(buffer, 200);
    }

    auto test_finish = chrono::steady_clock::now();
    cout << "Elapsed time : "
         << chrono::duration_cast<chrono::milliseconds>(test_finish - test_start).count()
         << "[ms]" << endl;

    cout << "Number of Static Edges after all Temporal Edge Insertions : " << spmatrix->size() << endl;

    delete spmatrix;
}

int main(int argc, char **argv)
{
    temporal_workload_test(argv[1], argv[2]);

    //periodic_workload_test(argv[1], atoi(argv[2]));

    return 0;
}
