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
include bin/CMakeFiles/perf_server.dir/depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/perf_server.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/perf_server.dir/flags.make

bin/CMakeFiles/perf_server.dir/perf_server.c.o: bin/CMakeFiles/perf_server.dir/flags.make
bin/CMakeFiles/perf_server.dir/perf_server.c.o: bin/perf_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrea/experiments/QUIC/lsquic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object bin/CMakeFiles/perf_server.dir/perf_server.c.o"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/perf_server.dir/perf_server.c.o   -c /home/andrea/experiments/QUIC/lsquic/bin/perf_server.c

bin/CMakeFiles/perf_server.dir/perf_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/perf_server.dir/perf_server.c.i"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrea/experiments/QUIC/lsquic/bin/perf_server.c > CMakeFiles/perf_server.dir/perf_server.c.i

bin/CMakeFiles/perf_server.dir/perf_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/perf_server.dir/perf_server.c.s"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrea/experiments/QUIC/lsquic/bin/perf_server.c -o CMakeFiles/perf_server.dir/perf_server.c.s

bin/CMakeFiles/perf_server.dir/prog.c.o: bin/CMakeFiles/perf_server.dir/flags.make
bin/CMakeFiles/perf_server.dir/prog.c.o: bin/prog.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrea/experiments/QUIC/lsquic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object bin/CMakeFiles/perf_server.dir/prog.c.o"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/perf_server.dir/prog.c.o   -c /home/andrea/experiments/QUIC/lsquic/bin/prog.c

bin/CMakeFiles/perf_server.dir/prog.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/perf_server.dir/prog.c.i"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrea/experiments/QUIC/lsquic/bin/prog.c > CMakeFiles/perf_server.dir/prog.c.i

bin/CMakeFiles/perf_server.dir/prog.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/perf_server.dir/prog.c.s"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrea/experiments/QUIC/lsquic/bin/prog.c -o CMakeFiles/perf_server.dir/prog.c.s

bin/CMakeFiles/perf_server.dir/test_common.c.o: bin/CMakeFiles/perf_server.dir/flags.make
bin/CMakeFiles/perf_server.dir/test_common.c.o: bin/test_common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrea/experiments/QUIC/lsquic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object bin/CMakeFiles/perf_server.dir/test_common.c.o"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/perf_server.dir/test_common.c.o   -c /home/andrea/experiments/QUIC/lsquic/bin/test_common.c

bin/CMakeFiles/perf_server.dir/test_common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/perf_server.dir/test_common.c.i"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrea/experiments/QUIC/lsquic/bin/test_common.c > CMakeFiles/perf_server.dir/test_common.c.i

bin/CMakeFiles/perf_server.dir/test_common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/perf_server.dir/test_common.c.s"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrea/experiments/QUIC/lsquic/bin/test_common.c -o CMakeFiles/perf_server.dir/test_common.c.s

bin/CMakeFiles/perf_server.dir/test_cert.c.o: bin/CMakeFiles/perf_server.dir/flags.make
bin/CMakeFiles/perf_server.dir/test_cert.c.o: bin/test_cert.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrea/experiments/QUIC/lsquic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object bin/CMakeFiles/perf_server.dir/test_cert.c.o"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/perf_server.dir/test_cert.c.o   -c /home/andrea/experiments/QUIC/lsquic/bin/test_cert.c

bin/CMakeFiles/perf_server.dir/test_cert.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/perf_server.dir/test_cert.c.i"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrea/experiments/QUIC/lsquic/bin/test_cert.c > CMakeFiles/perf_server.dir/test_cert.c.i

bin/CMakeFiles/perf_server.dir/test_cert.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/perf_server.dir/test_cert.c.s"
	cd /home/andrea/experiments/QUIC/lsquic/bin && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrea/experiments/QUIC/lsquic/bin/test_cert.c -o CMakeFiles/perf_server.dir/test_cert.c.s

# Object files for target perf_server
perf_server_OBJECTS = \
"CMakeFiles/perf_server.dir/perf_server.c.o" \
"CMakeFiles/perf_server.dir/prog.c.o" \
"CMakeFiles/perf_server.dir/test_common.c.o" \
"CMakeFiles/perf_server.dir/test_cert.c.o"

# External object files for target perf_server
perf_server_EXTERNAL_OBJECTS =

bin/perf_server: bin/CMakeFiles/perf_server.dir/perf_server.c.o
bin/perf_server: bin/CMakeFiles/perf_server.dir/prog.c.o
bin/perf_server: bin/CMakeFiles/perf_server.dir/test_common.c.o
bin/perf_server: bin/CMakeFiles/perf_server.dir/test_cert.c.o
bin/perf_server: bin/CMakeFiles/perf_server.dir/build.make
bin/perf_server: src/liblsquic/liblsquic.a
bin/perf_server: /home/andrea/boringssl/ssl/libssl.a
bin/perf_server: /home/andrea/boringssl/crypto/libcrypto.a
bin/perf_server: /usr/lib/x86_64-linux-gnu/libz.a
bin/perf_server: /usr/local/lib/libevent.a
bin/perf_server: bin/CMakeFiles/perf_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrea/experiments/QUIC/lsquic/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable perf_server"
	cd /home/andrea/experiments/QUIC/lsquic/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/perf_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/perf_server.dir/build: bin/perf_server

.PHONY : bin/CMakeFiles/perf_server.dir/build

bin/CMakeFiles/perf_server.dir/clean:
	cd /home/andrea/experiments/QUIC/lsquic/bin && $(CMAKE_COMMAND) -P CMakeFiles/perf_server.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/perf_server.dir/clean

bin/CMakeFiles/perf_server.dir/depend:
	cd /home/andrea/experiments/QUIC/lsquic && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrea/experiments/QUIC/lsquic /home/andrea/experiments/QUIC/lsquic/bin /home/andrea/experiments/QUIC/lsquic /home/andrea/experiments/QUIC/lsquic/bin /home/andrea/experiments/QUIC/lsquic/bin/CMakeFiles/perf_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/perf_server.dir/depend

