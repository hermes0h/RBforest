cmake_minimum_required(VERSION 3.21.4)
project(SPMatrix_Perf_Test)

add_compile_options(-std=c++17 -O3 -Wno-unused-result)

include_directories(./include)
add_executable(static_perf_test ./test/static_perf_test.cpp ./src/rb_tree.cpp ./src/rbmatrix.cpp
    ./src/csrmatrix.cpp ./src/almatrix.cpp ./src/dokmatrix.cpp ./src/lhrbmatrix.cpp)

add_executable(temporal_perf_test ./test/temporal_perf_test.cpp ./src/rb_tree.cpp ./src/rbmatrix.cpp
    ./src/csrmatrix.cpp ./src/almatrix.cpp ./src/dokmatrix.cpp ./src/lhrbmatrix.cpp)

add_executable(memory_test ./test/memory_test.cpp ./src/rb_tree.cpp ./src/rbmatrix.cpp
    ./src/csrmatrix.cpp ./src/almatrix.cpp ./src/dokmatrix.cpp ./src/lhrbmatrix.cpp)
