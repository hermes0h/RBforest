# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/dnjsgus/study/cmake-3.21.4/bin/cmake

# The command to remove a file.
RM = /home/dnjsgus/study/cmake-3.21.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dnjsgus/rbforest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dnjsgus/rbforest

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/dnjsgus/study/cmake-3.21.4/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/home/dnjsgus/study/cmake-3.21.4/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dnjsgus/rbforest/CMakeFiles /home/dnjsgus/rbforest//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/dnjsgus/rbforest/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named memory_test

# Build rule for target.
memory_test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 memory_test
.PHONY : memory_test

# fast build rule for target.
memory_test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/build
.PHONY : memory_test/fast

#=============================================================================
# Target rules for targets named temporal_perf_test

# Build rule for target.
temporal_perf_test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 temporal_perf_test
.PHONY : temporal_perf_test

# fast build rule for target.
temporal_perf_test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/build
.PHONY : temporal_perf_test/fast

#=============================================================================
# Target rules for targets named static_perf_test

# Build rule for target.
static_perf_test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 static_perf_test
.PHONY : static_perf_test

# fast build rule for target.
static_perf_test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/build
.PHONY : static_perf_test/fast

src/almatrix.o: src/almatrix.cpp.o
.PHONY : src/almatrix.o

# target to build an object file
src/almatrix.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/almatrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/almatrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/almatrix.cpp.o
.PHONY : src/almatrix.cpp.o

src/almatrix.i: src/almatrix.cpp.i
.PHONY : src/almatrix.i

# target to preprocess a source file
src/almatrix.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/almatrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/almatrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/almatrix.cpp.i
.PHONY : src/almatrix.cpp.i

src/almatrix.s: src/almatrix.cpp.s
.PHONY : src/almatrix.s

# target to generate assembly for a file
src/almatrix.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/almatrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/almatrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/almatrix.cpp.s
.PHONY : src/almatrix.cpp.s

src/csrmatrix.o: src/csrmatrix.cpp.o
.PHONY : src/csrmatrix.o

# target to build an object file
src/csrmatrix.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/csrmatrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/csrmatrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/csrmatrix.cpp.o
.PHONY : src/csrmatrix.cpp.o

src/csrmatrix.i: src/csrmatrix.cpp.i
.PHONY : src/csrmatrix.i

# target to preprocess a source file
src/csrmatrix.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/csrmatrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/csrmatrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/csrmatrix.cpp.i
.PHONY : src/csrmatrix.cpp.i

src/csrmatrix.s: src/csrmatrix.cpp.s
.PHONY : src/csrmatrix.s

# target to generate assembly for a file
src/csrmatrix.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/csrmatrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/csrmatrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/csrmatrix.cpp.s
.PHONY : src/csrmatrix.cpp.s

src/dokmatrix.o: src/dokmatrix.cpp.o
.PHONY : src/dokmatrix.o

# target to build an object file
src/dokmatrix.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/dokmatrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/dokmatrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/dokmatrix.cpp.o
.PHONY : src/dokmatrix.cpp.o

src/dokmatrix.i: src/dokmatrix.cpp.i
.PHONY : src/dokmatrix.i

# target to preprocess a source file
src/dokmatrix.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/dokmatrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/dokmatrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/dokmatrix.cpp.i
.PHONY : src/dokmatrix.cpp.i

src/dokmatrix.s: src/dokmatrix.cpp.s
.PHONY : src/dokmatrix.s

# target to generate assembly for a file
src/dokmatrix.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/dokmatrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/dokmatrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/dokmatrix.cpp.s
.PHONY : src/dokmatrix.cpp.s

src/lhrbmatrix.o: src/lhrbmatrix.cpp.o
.PHONY : src/lhrbmatrix.o

# target to build an object file
src/lhrbmatrix.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/lhrbmatrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/lhrbmatrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/lhrbmatrix.cpp.o
.PHONY : src/lhrbmatrix.cpp.o

src/lhrbmatrix.i: src/lhrbmatrix.cpp.i
.PHONY : src/lhrbmatrix.i

# target to preprocess a source file
src/lhrbmatrix.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/lhrbmatrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/lhrbmatrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/lhrbmatrix.cpp.i
.PHONY : src/lhrbmatrix.cpp.i

src/lhrbmatrix.s: src/lhrbmatrix.cpp.s
.PHONY : src/lhrbmatrix.s

# target to generate assembly for a file
src/lhrbmatrix.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/lhrbmatrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/lhrbmatrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/lhrbmatrix.cpp.s
.PHONY : src/lhrbmatrix.cpp.s

src/rb_tree.o: src/rb_tree.cpp.o
.PHONY : src/rb_tree.o

# target to build an object file
src/rb_tree.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/rb_tree.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/rb_tree.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/rb_tree.cpp.o
.PHONY : src/rb_tree.cpp.o

src/rb_tree.i: src/rb_tree.cpp.i
.PHONY : src/rb_tree.i

# target to preprocess a source file
src/rb_tree.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/rb_tree.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/rb_tree.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/rb_tree.cpp.i
.PHONY : src/rb_tree.cpp.i

src/rb_tree.s: src/rb_tree.cpp.s
.PHONY : src/rb_tree.s

# target to generate assembly for a file
src/rb_tree.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/rb_tree.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/rb_tree.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/rb_tree.cpp.s
.PHONY : src/rb_tree.cpp.s

src/rbmatrix.o: src/rbmatrix.cpp.o
.PHONY : src/rbmatrix.o

# target to build an object file
src/rbmatrix.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/rbmatrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/rbmatrix.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/rbmatrix.cpp.o
.PHONY : src/rbmatrix.cpp.o

src/rbmatrix.i: src/rbmatrix.cpp.i
.PHONY : src/rbmatrix.i

# target to preprocess a source file
src/rbmatrix.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/rbmatrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/rbmatrix.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/rbmatrix.cpp.i
.PHONY : src/rbmatrix.cpp.i

src/rbmatrix.s: src/rbmatrix.cpp.s
.PHONY : src/rbmatrix.s

# target to generate assembly for a file
src/rbmatrix.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/src/rbmatrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/src/rbmatrix.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/src/rbmatrix.cpp.s
.PHONY : src/rbmatrix.cpp.s

test/memory_test.o: test/memory_test.cpp.o
.PHONY : test/memory_test.o

# target to build an object file
test/memory_test.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/test/memory_test.cpp.o
.PHONY : test/memory_test.cpp.o

test/memory_test.i: test/memory_test.cpp.i
.PHONY : test/memory_test.i

# target to preprocess a source file
test/memory_test.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/test/memory_test.cpp.i
.PHONY : test/memory_test.cpp.i

test/memory_test.s: test/memory_test.cpp.s
.PHONY : test/memory_test.s

# target to generate assembly for a file
test/memory_test.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/memory_test.dir/build.make CMakeFiles/memory_test.dir/test/memory_test.cpp.s
.PHONY : test/memory_test.cpp.s

test/static_perf_test.o: test/static_perf_test.cpp.o
.PHONY : test/static_perf_test.o

# target to build an object file
test/static_perf_test.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/test/static_perf_test.cpp.o
.PHONY : test/static_perf_test.cpp.o

test/static_perf_test.i: test/static_perf_test.cpp.i
.PHONY : test/static_perf_test.i

# target to preprocess a source file
test/static_perf_test.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/test/static_perf_test.cpp.i
.PHONY : test/static_perf_test.cpp.i

test/static_perf_test.s: test/static_perf_test.cpp.s
.PHONY : test/static_perf_test.s

# target to generate assembly for a file
test/static_perf_test.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/static_perf_test.dir/build.make CMakeFiles/static_perf_test.dir/test/static_perf_test.cpp.s
.PHONY : test/static_perf_test.cpp.s

test/temporal_perf_test.o: test/temporal_perf_test.cpp.o
.PHONY : test/temporal_perf_test.o

# target to build an object file
test/temporal_perf_test.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/test/temporal_perf_test.cpp.o
.PHONY : test/temporal_perf_test.cpp.o

test/temporal_perf_test.i: test/temporal_perf_test.cpp.i
.PHONY : test/temporal_perf_test.i

# target to preprocess a source file
test/temporal_perf_test.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/test/temporal_perf_test.cpp.i
.PHONY : test/temporal_perf_test.cpp.i

test/temporal_perf_test.s: test/temporal_perf_test.cpp.s
.PHONY : test/temporal_perf_test.s

# target to generate assembly for a file
test/temporal_perf_test.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/temporal_perf_test.dir/build.make CMakeFiles/temporal_perf_test.dir/test/temporal_perf_test.cpp.s
.PHONY : test/temporal_perf_test.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... memory_test"
	@echo "... static_perf_test"
	@echo "... temporal_perf_test"
	@echo "... src/almatrix.o"
	@echo "... src/almatrix.i"
	@echo "... src/almatrix.s"
	@echo "... src/csrmatrix.o"
	@echo "... src/csrmatrix.i"
	@echo "... src/csrmatrix.s"
	@echo "... src/dokmatrix.o"
	@echo "... src/dokmatrix.i"
	@echo "... src/dokmatrix.s"
	@echo "... src/lhrbmatrix.o"
	@echo "... src/lhrbmatrix.i"
	@echo "... src/lhrbmatrix.s"
	@echo "... src/rb_tree.o"
	@echo "... src/rb_tree.i"
	@echo "... src/rb_tree.s"
	@echo "... src/rbmatrix.o"
	@echo "... src/rbmatrix.i"
	@echo "... src/rbmatrix.s"
	@echo "... test/memory_test.o"
	@echo "... test/memory_test.i"
	@echo "... test/memory_test.s"
	@echo "... test/static_perf_test.o"
	@echo "... test/static_perf_test.i"
	@echo "... test/static_perf_test.s"
	@echo "... test/temporal_perf_test.o"
	@echo "... test/temporal_perf_test.i"
	@echo "... test/temporal_perf_test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

