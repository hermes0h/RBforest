#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <random>
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <unistd.h>

#include "rb_tree.h"
#include "spmatix.h"

using namespace std;

void memory_test(char *matrix_type)
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

    // Insertion Test
    random_shuffle(edge_vector.begin(), edge_vector.end());

    // Check Memory Occupation
    cout << "Memory footprint before matrix allocation" << endl;
    pid_t cur_pid = getpid();
    string command = "cat /proc/" + to_string(cur_pid) + "/status | grep VmData";
    system(command.c_str());

    // SPMatrix<double> *spmatrix;
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

    for (auto iter = edge_vector.begin();
         iter != edge_vector.end();
         iter++)
    {
        tuple<uint32_t, uint32_t> elem = *iter;
        spmatrix->set_value(get<0>(elem), get<1>(elem), unif(re));
    }

    // Check Memory Occupation
    cout << "Memory footprint after matrix allocation & insertions" << endl;
    system(command.c_str());
}

int main(int argc, char **argv)
{
    memory_test(argv[1]);

    return 0;
}