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
include tests/CMakeFiles/test_engine_ctor.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_engine_ctor.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_engine_ctor.dir/flags.make

tests/CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.o: tests/CMakeFiles/test_engine_ctor.dir/flags.make
tests/CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.o: tests/test_engine_ctor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrea/experiments/QUIC/lsquic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.o"
	cd /home/andrea/experiments/QUIC/lsquic/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.o   -c /home/andrea/experiments/QUIC/lsquic/tests/test_engine_ctor.c

tests/CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.i"
	cd /home/andrea/experiments/QUIC/lsquic/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrea/experiments/QUIC/lsquic/tests/test_engine_ctor.c > CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.i

tests/CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.s"
	cd /home/andrea/experiments/QUIC/lsquic/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrea/experiments/QUIC/lsquic/tests/test_engine_ctor.c -o CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.s

# Object files for target test_engine_ctor
test_engine_ctor_OBJECTS = \
"CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.o"

# External object files for target test_engine_ctor
test_engine_ctor_EXTERNAL_OBJECTS =

tests/test_engine_ctor: tests/CMakeFiles/test_engine_ctor.dir/test_engine_ctor.c.o
tests/test_engine_ctor: tests/CMakeFiles/test_engine_ctor.dir/build.make
tests/test_engine_ctor: src/liblsquic/liblsquic.a
tests/test_engine_ctor: /home/andrea/boringssl/ssl/libssl.a
tests/test_engine_ctor: /home/andrea/boringssl/crypto/libcrypto.a
tests/test_engine_ctor: /usr/lib/x86_64-linux-gnu/libz.a
tests/test_engine_ctor: tests/CMakeFiles/test_engine_ctor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrea/experiments/QUIC/lsquic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_engine_ctor"
	cd /home/andrea/experiments/QUIC/lsquic/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_engine_ctor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_engine_ctor.dir/build: tests/test_engine_ctor

.PHONY : tests/CMakeFiles/test_engine_ctor.dir/build

tests/CMakeFiles/test_engine_ctor.dir/clean:
	cd /home/andrea/experiments/QUIC/lsquic/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_engine_ctor.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_engine_ctor.dir/clean

tests/CMakeFiles/test_engine_ctor.dir/depend:
	cd /home/andrea/experiments/QUIC/lsquic && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrea/experiments/QUIC/lsquic /home/andrea/experiments/QUIC/lsquic/tests /home/andrea/experiments/QUIC/lsquic /home/andrea/experiments/QUIC/lsquic/tests /home/andrea/experiments/QUIC/lsquic/tests/CMakeFiles/test_engine_ctor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_engine_ctor.dir/depend

