# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/ccfree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/ccfree/build

# Include any dependencies generated for this target.
include CMakeFiles/test_module.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_module.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_module.dir/flags.make

CMakeFiles/test_module.dir/tests/test_module.cc.o: CMakeFiles/test_module.dir/flags.make
CMakeFiles/test_module.dir/tests/test_module.cc.o: ../tests/test_module.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ccfree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_module.dir/tests/test_module.cc.o"
	/opt/rh/devtoolset-8/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_module.dir/tests/test_module.cc.o -c /root/ccfree/tests/test_module.cc

CMakeFiles/test_module.dir/tests/test_module.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_module.dir/tests/test_module.cc.i"
	/opt/rh/devtoolset-8/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/ccfree/tests/test_module.cc > CMakeFiles/test_module.dir/tests/test_module.cc.i

CMakeFiles/test_module.dir/tests/test_module.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_module.dir/tests/test_module.cc.s"
	/opt/rh/devtoolset-8/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/ccfree/tests/test_module.cc -o CMakeFiles/test_module.dir/tests/test_module.cc.s

# Object files for target test_module
test_module_OBJECTS = \
"CMakeFiles/test_module.dir/tests/test_module.cc.o"

# External object files for target test_module
test_module_EXTERNAL_OBJECTS =

../lib/libtest_module.so: CMakeFiles/test_module.dir/tests/test_module.cc.o
../lib/libtest_module.so: CMakeFiles/test_module.dir/build.make
../lib/libtest_module.so: CMakeFiles/test_module.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/ccfree/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../lib/libtest_module.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_module.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_module.dir/build: ../lib/libtest_module.so

.PHONY : CMakeFiles/test_module.dir/build

CMakeFiles/test_module.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_module.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_module.dir/clean

CMakeFiles/test_module.dir/depend:
	cd /root/ccfree/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ccfree /root/ccfree /root/ccfree/build /root/ccfree/build /root/ccfree/build/CMakeFiles/test_module.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_module.dir/depend

