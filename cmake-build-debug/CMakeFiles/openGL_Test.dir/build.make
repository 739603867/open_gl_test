# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liuxiaobei/CLionProjects/openGL_Test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liuxiaobei/CLionProjects/openGL_Test/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/openGL_Test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/openGL_Test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/openGL_Test.dir/flags.make

CMakeFiles/openGL_Test.dir/main.cpp.o: CMakeFiles/openGL_Test.dir/flags.make
CMakeFiles/openGL_Test.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuxiaobei/CLionProjects/openGL_Test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/openGL_Test.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/openGL_Test.dir/main.cpp.o -c /Users/liuxiaobei/CLionProjects/openGL_Test/main.cpp

CMakeFiles/openGL_Test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/openGL_Test.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuxiaobei/CLionProjects/openGL_Test/main.cpp > CMakeFiles/openGL_Test.dir/main.cpp.i

CMakeFiles/openGL_Test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/openGL_Test.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuxiaobei/CLionProjects/openGL_Test/main.cpp -o CMakeFiles/openGL_Test.dir/main.cpp.s

# Object files for target openGL_Test
openGL_Test_OBJECTS = \
"CMakeFiles/openGL_Test.dir/main.cpp.o"

# External object files for target openGL_Test
openGL_Test_EXTERNAL_OBJECTS =

openGL_Test: CMakeFiles/openGL_Test.dir/main.cpp.o
openGL_Test: CMakeFiles/openGL_Test.dir/build.make
openGL_Test: CMakeFiles/openGL_Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/liuxiaobei/CLionProjects/openGL_Test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable openGL_Test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/openGL_Test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/openGL_Test.dir/build: openGL_Test

.PHONY : CMakeFiles/openGL_Test.dir/build

CMakeFiles/openGL_Test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/openGL_Test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/openGL_Test.dir/clean

CMakeFiles/openGL_Test.dir/depend:
	cd /Users/liuxiaobei/CLionProjects/openGL_Test/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liuxiaobei/CLionProjects/openGL_Test /Users/liuxiaobei/CLionProjects/openGL_Test /Users/liuxiaobei/CLionProjects/openGL_Test/cmake-build-debug /Users/liuxiaobei/CLionProjects/openGL_Test/cmake-build-debug /Users/liuxiaobei/CLionProjects/openGL_Test/cmake-build-debug/CMakeFiles/openGL_Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/openGL_Test.dir/depend

