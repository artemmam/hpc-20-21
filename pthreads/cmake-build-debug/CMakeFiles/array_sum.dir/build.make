# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/ARTEM/CLionProjects/pthreads

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/ARTEM/CLionProjects/pthreads/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/array_sum.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/array_sum.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/array_sum.dir/flags.make

CMakeFiles/array_sum.dir/array_sum.cpp.o: CMakeFiles/array_sum.dir/flags.make
CMakeFiles/array_sum.dir/array_sum.cpp.o: ../array_sum.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/ARTEM/CLionProjects/pthreads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/array_sum.dir/array_sum.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/array_sum.dir/array_sum.cpp.o -c /mnt/c/Users/ARTEM/CLionProjects/pthreads/array_sum.cpp

CMakeFiles/array_sum.dir/array_sum.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/array_sum.dir/array_sum.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/ARTEM/CLionProjects/pthreads/array_sum.cpp > CMakeFiles/array_sum.dir/array_sum.cpp.i

CMakeFiles/array_sum.dir/array_sum.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/array_sum.dir/array_sum.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/ARTEM/CLionProjects/pthreads/array_sum.cpp -o CMakeFiles/array_sum.dir/array_sum.cpp.s

CMakeFiles/array_sum.dir/array_sum.cpp.o.requires:

.PHONY : CMakeFiles/array_sum.dir/array_sum.cpp.o.requires

CMakeFiles/array_sum.dir/array_sum.cpp.o.provides: CMakeFiles/array_sum.dir/array_sum.cpp.o.requires
	$(MAKE) -f CMakeFiles/array_sum.dir/build.make CMakeFiles/array_sum.dir/array_sum.cpp.o.provides.build
.PHONY : CMakeFiles/array_sum.dir/array_sum.cpp.o.provides

CMakeFiles/array_sum.dir/array_sum.cpp.o.provides.build: CMakeFiles/array_sum.dir/array_sum.cpp.o


# Object files for target array_sum
array_sum_OBJECTS = \
"CMakeFiles/array_sum.dir/array_sum.cpp.o"

# External object files for target array_sum
array_sum_EXTERNAL_OBJECTS =

array_sum: CMakeFiles/array_sum.dir/array_sum.cpp.o
array_sum: CMakeFiles/array_sum.dir/build.make
array_sum: CMakeFiles/array_sum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/ARTEM/CLionProjects/pthreads/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable array_sum"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/array_sum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/array_sum.dir/build: array_sum

.PHONY : CMakeFiles/array_sum.dir/build

CMakeFiles/array_sum.dir/requires: CMakeFiles/array_sum.dir/array_sum.cpp.o.requires

.PHONY : CMakeFiles/array_sum.dir/requires

CMakeFiles/array_sum.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/array_sum.dir/cmake_clean.cmake
.PHONY : CMakeFiles/array_sum.dir/clean

CMakeFiles/array_sum.dir/depend:
	cd /mnt/c/Users/ARTEM/CLionProjects/pthreads/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/ARTEM/CLionProjects/pthreads /mnt/c/Users/ARTEM/CLionProjects/pthreads /mnt/c/Users/ARTEM/CLionProjects/pthreads/cmake-build-debug /mnt/c/Users/ARTEM/CLionProjects/pthreads/cmake-build-debug /mnt/c/Users/ARTEM/CLionProjects/pthreads/cmake-build-debug/CMakeFiles/array_sum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/array_sum.dir/depend

