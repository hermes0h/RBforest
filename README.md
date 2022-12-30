# RBForest

## Introduction
- [`RBForest`] is an efficient in-memory format for sparse matrices on dynamic workloads.
- It acheives better performance than previously proposed formats such as DOK, LIL and RBT.


## How to Use
### Prerequisite
- cmake 3.21.4 or higher
- C++17
- g++ 7.5.0 or higher

### Build
- 'cmake CMakeLists.txt'
- 'make'

### Test
- 'static_perf_test' : Test with static matrices. Measure performances of individual operations seperately.
- 'temporal_perf_test' : Test with temporal matrices. Measure performances on dynamic workloads.
- 'memory_test' : Measure memory occupation

### Sample Dataset
- Two temporal matrices. 'temporal_perf_test' should be used to test with these data. 'static_perf_test' and 'memory_test' will produce undefined behavior.
- 'hs_2013' is a contact and friendship network between students in a high school in Marseilles, France in December 2013. 
- 'ps_2014' s a contact network between the children and teachers in a primary school in January 2014. 

## Directory Overview
```
RBForest
├── CMakeLists.txt                                      // for cmake
├── Makefile                                            // Meaningless. You should make it your own using cmake.
├── README.md                                       
└── include
    ├── rb_tree.h                                       // API declarations for red-black tree implementation.
    ├── spmatrix.h                                      // Sparse matrix abstract class definition.
└── src
    ├── rb_tree.cpp                                     // Red-black tree implementation.
    ├── csrmatrix.cpp                                   // CSR matrix class implementation.
    ├── almatrix.cpp                                    // LIL matrix class implementation.
    ├── dokmatrix.cpp                                   // DOK matrix class implementation.
    ├── rbmatrix.cpp                                    // RBT matrix class implementation.
    ├── lhrbmatrix.cpp                                  // RBF matrix class implementation. (RBForest)
└── test
    ├── static_perf_test.cpp
    ├── temporal_perf_test.cpp                          
    ├── memory_test.cpp
└── dataset
    ├── hs_2013
    │   └── hs.in                                       // Preprocessed data file that. Input of the temporal_perf_test
    │   └── High-School_data_2013.csv                   // Raw data file downloaded online.
    │   └── metadata_2013.txt                           // Metadata of the raw data file.
    ├── ps_2014
    │   └── ps.in                                       // Preprocessed data file that. Input of the temporal_perf_test
    │   └── primaryschool.csv                           // Raw data file downloaded online.
    │   └── metadata_primaryschool.txt                  // Metadata of the raw data file.

``` 

## Contact
For all inqueries about the project, please email : devhermes0h@gmail.com