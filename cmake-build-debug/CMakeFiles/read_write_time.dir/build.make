# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/knig/Program/clion-2017.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/knig/Program/clion-2017.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/knig/programmering/clion/io_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/knig/programmering/clion/io_test/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/read_write_time.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/read_write_time.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/read_write_time.dir/flags.make

CMakeFiles/read_write_time.dir/io_test.c.o: CMakeFiles/read_write_time.dir/flags.make
CMakeFiles/read_write_time.dir/io_test.c.o: ../io_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/knig/programmering/clion/io_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/read_write_time.dir/io_test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/read_write_time.dir/io_test.c.o   -c /home/knig/programmering/clion/io_test/io_test.c

CMakeFiles/read_write_time.dir/io_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/read_write_time.dir/io_test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/knig/programmering/clion/io_test/io_test.c > CMakeFiles/read_write_time.dir/io_test.c.i

CMakeFiles/read_write_time.dir/io_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/read_write_time.dir/io_test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/knig/programmering/clion/io_test/io_test.c -o CMakeFiles/read_write_time.dir/io_test.c.s

CMakeFiles/read_write_time.dir/io_test.c.o.requires:

.PHONY : CMakeFiles/read_write_time.dir/io_test.c.o.requires

CMakeFiles/read_write_time.dir/io_test.c.o.provides: CMakeFiles/read_write_time.dir/io_test.c.o.requires
	$(MAKE) -f CMakeFiles/read_write_time.dir/build.make CMakeFiles/read_write_time.dir/io_test.c.o.provides.build
.PHONY : CMakeFiles/read_write_time.dir/io_test.c.o.provides

CMakeFiles/read_write_time.dir/io_test.c.o.provides.build: CMakeFiles/read_write_time.dir/io_test.c.o


# Object files for target read_write_time
read_write_time_OBJECTS = \
"CMakeFiles/read_write_time.dir/io_test.c.o"

# External object files for target read_write_time
read_write_time_EXTERNAL_OBJECTS =

read_write_time: CMakeFiles/read_write_time.dir/io_test.c.o
read_write_time: CMakeFiles/read_write_time.dir/build.make
read_write_time: CMakeFiles/read_write_time.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/knig/programmering/clion/io_test/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable read_write_time"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/read_write_time.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/read_write_time.dir/build: read_write_time

.PHONY : CMakeFiles/read_write_time.dir/build

CMakeFiles/read_write_time.dir/requires: CMakeFiles/read_write_time.dir/io_test.c.o.requires

.PHONY : CMakeFiles/read_write_time.dir/requires

CMakeFiles/read_write_time.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/read_write_time.dir/cmake_clean.cmake
.PHONY : CMakeFiles/read_write_time.dir/clean

CMakeFiles/read_write_time.dir/depend:
	cd /home/knig/programmering/clion/io_test/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/knig/programmering/clion/io_test /home/knig/programmering/clion/io_test /home/knig/programmering/clion/io_test/cmake-build-debug /home/knig/programmering/clion/io_test/cmake-build-debug /home/knig/programmering/clion/io_test/cmake-build-debug/CMakeFiles/read_write_time.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/read_write_time.dir/depend
