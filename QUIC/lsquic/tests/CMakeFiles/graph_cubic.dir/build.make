# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/andrea/experiments/QUIC/lsquic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrea/experiments/QUIC/lsquic

# Include any dependencies generated for this target.
include tests/CMakeFiles/graph_cubic.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/graph_cubic.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/graph_cubic.dir/flags.make

tests/CMakeFiles/graph_cubic.dir/graph_cubic.c.o: tests/CMakeFiles/graph_cubic.dir/flags.make
tests/CMakeFiles/graph_cubic.dir/graph_cubic.c.o: tests/graph_cubic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrea/experiments/QUIC/lsquic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/graph_cubic.dir/graph_cubic.c.o"
	cd /home/andrea/experiments/QUIC/lsquic/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/graph_cubic.dir/graph_cubic.c.o   -c /home/andrea/experiments/QUIC/lsquic/tests/graph_cubic.c

tests/CMakeFiles/graph_cubic.dir/graph_cubic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graph_cubic.dir/graph_cubic.c.i"
	cd /home/andrea/experiments/QUIC/lsquic/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrea/experiments/QUIC/lsquic/tests/graph_cubic.c > CMakeFiles/graph_cubic.dir/graph_cubic.c.i

tests/CMakeFiles/graph_cubic.dir/graph_cubic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graph_cubic.dir/graph_cubic.c.s"
	cd /home/andrea/experiments/QUIC/lsquic/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrea/experiments/QUIC/lsquic/tests/graph_cubic.c -o CMakeFiles/graph_cubic.dir/graph_cubic.c.s

# Object files for target graph_cubic
graph_cubic_OBJECTS = \
"CMakeFiles/graph_cubic.dir/graph_cubic.c.o"

# External object files for target graph_cubic
graph_cubic_EXTERNAL_OBJECTS =

tests/graph_cubic: tests/CMakeFiles/graph_cubic.dir/graph_cubic.c.o
tests/graph_cubic: tests/CMakeFiles/graph_cubic.dir/build.make
tests/graph_cubic: src/liblsquic/liblsquic.a
tests/graph_cubic: /home/andrea/boringssl/ssl/libssl.a
tests/graph_cubic: /home/andrea/boringssl/crypto/libcrypto.a
tests/graph_cubic: /usr/lib/x86_64-linux-gnu/libz.a
tests/graph_cubic: tests/CMakeFiles/graph_cubic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrea/experiments/QUIC/lsquic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable graph_cubic"
	cd /home/andrea/experiments/QUIC/lsquic/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graph_cubic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/graph_cubic.dir/build: tests/graph_cubic

.PHONY : tests/CMakeFiles/graph_cubic.dir/build

tests/CMakeFiles/graph_cubic.dir/clean:
	cd /home/andrea/experiments/QUIC/lsquic/tests && $(CMAKE_COMMAND) -P CMakeFiles/graph_cubic.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/graph_cubic.dir/clean

tests/CMakeFiles/graph_cubic.dir/depend:
	cd /home/andrea/experiments/QUIC/lsquic && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrea/experiments/QUIC/lsquic /home/andrea/experiments/QUIC/lsquic/tests /home/andrea/experiments/QUIC/lsquic /home/andrea/experiments/QUIC/lsquic/tests /home/andrea/experiments/QUIC/lsquic/tests/CMakeFiles/graph_cubic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/graph_cubic.dir/depend
