# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /snap/clion/137/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/137/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cyberogg/hpc_course/hpc-20-21/openmp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cyberogg/hpc_course/hpc-20-21/openmp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/single.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/single.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/single.dir/flags.make

CMakeFiles/single.dir/single.cpp.o: CMakeFiles/single.dir/flags.make
CMakeFiles/single.dir/single.cpp.o: ../single.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyberogg/hpc_course/hpc-20-21/openmp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/single.dir/single.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/single.dir/single.cpp.o -c /home/cyberogg/hpc_course/hpc-20-21/openmp/single.cpp

CMakeFiles/single.dir/single.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/single.dir/single.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyberogg/hpc_course/hpc-20-21/openmp/single.cpp > CMakeFiles/single.dir/single.cpp.i

CMakeFiles/single.dir/single.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/single.dir/single.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyberogg/hpc_course/hpc-20-21/openmp/single.cpp -o CMakeFiles/single.dir/single.cpp.s

# Object files for target single
single_OBJECTS = \
"CMakeFiles/single.dir/single.cpp.o"

# External object files for target single
single_EXTERNAL_OBJECTS =

single: CMakeFiles/single.dir/single.cpp.o
single: CMakeFiles/single.dir/build.make
single: CMakeFiles/single.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cyberogg/hpc_course/hpc-20-21/openmp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable single"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/single.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/single.dir/build: single

.PHONY : CMakeFiles/single.dir/build

CMakeFiles/single.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/single.dir/cmake_clean.cmake
.PHONY : CMakeFiles/single.dir/clean

CMakeFiles/single.dir/depend:
	cd /home/cyberogg/hpc_course/hpc-20-21/openmp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cyberogg/hpc_course/hpc-20-21/openmp /home/cyberogg/hpc_course/hpc-20-21/openmp /home/cyberogg/hpc_course/hpc-20-21/openmp/cmake-build-debug /home/cyberogg/hpc_course/hpc-20-21/openmp/cmake-build-debug /home/cyberogg/hpc_course/hpc-20-21/openmp/cmake-build-debug/CMakeFiles/single.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/single.dir/depend

