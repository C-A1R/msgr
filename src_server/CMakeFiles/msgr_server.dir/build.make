# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/runner/work/otus_project/otus_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/runner/work/otus_project/otus_project

# Include any dependencies generated for this target.
include src_server/CMakeFiles/msgr_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src_server/CMakeFiles/msgr_server.dir/compiler_depend.make

# Include the progress variables for this target.
include src_server/CMakeFiles/msgr_server.dir/progress.make

# Include the compile flags for this target's objects.
include src_server/CMakeFiles/msgr_server.dir/flags.make

src_server/CMakeFiles/msgr_server.dir/main.cpp.o: src_server/CMakeFiles/msgr_server.dir/flags.make
src_server/CMakeFiles/msgr_server.dir/main.cpp.o: src_server/main.cpp
src_server/CMakeFiles/msgr_server.dir/main.cpp.o: src_server/CMakeFiles/msgr_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/runner/work/otus_project/otus_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src_server/CMakeFiles/msgr_server.dir/main.cpp.o"
	cd /home/runner/work/otus_project/otus_project/src_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src_server/CMakeFiles/msgr_server.dir/main.cpp.o -MF CMakeFiles/msgr_server.dir/main.cpp.o.d -o CMakeFiles/msgr_server.dir/main.cpp.o -c /home/runner/work/otus_project/otus_project/src_server/main.cpp

src_server/CMakeFiles/msgr_server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/msgr_server.dir/main.cpp.i"
	cd /home/runner/work/otus_project/otus_project/src_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/otus_project/otus_project/src_server/main.cpp > CMakeFiles/msgr_server.dir/main.cpp.i

src_server/CMakeFiles/msgr_server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/msgr_server.dir/main.cpp.s"
	cd /home/runner/work/otus_project/otus_project/src_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/otus_project/otus_project/src_server/main.cpp -o CMakeFiles/msgr_server.dir/main.cpp.s

src_server/CMakeFiles/msgr_server.dir/server.cpp.o: src_server/CMakeFiles/msgr_server.dir/flags.make
src_server/CMakeFiles/msgr_server.dir/server.cpp.o: src_server/server.cpp
src_server/CMakeFiles/msgr_server.dir/server.cpp.o: src_server/CMakeFiles/msgr_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/runner/work/otus_project/otus_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src_server/CMakeFiles/msgr_server.dir/server.cpp.o"
	cd /home/runner/work/otus_project/otus_project/src_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src_server/CMakeFiles/msgr_server.dir/server.cpp.o -MF CMakeFiles/msgr_server.dir/server.cpp.o.d -o CMakeFiles/msgr_server.dir/server.cpp.o -c /home/runner/work/otus_project/otus_project/src_server/server.cpp

src_server/CMakeFiles/msgr_server.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/msgr_server.dir/server.cpp.i"
	cd /home/runner/work/otus_project/otus_project/src_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/otus_project/otus_project/src_server/server.cpp > CMakeFiles/msgr_server.dir/server.cpp.i

src_server/CMakeFiles/msgr_server.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/msgr_server.dir/server.cpp.s"
	cd /home/runner/work/otus_project/otus_project/src_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/otus_project/otus_project/src_server/server.cpp -o CMakeFiles/msgr_server.dir/server.cpp.s

src_server/CMakeFiles/msgr_server.dir/session.cpp.o: src_server/CMakeFiles/msgr_server.dir/flags.make
src_server/CMakeFiles/msgr_server.dir/session.cpp.o: src_server/session.cpp
src_server/CMakeFiles/msgr_server.dir/session.cpp.o: src_server/CMakeFiles/msgr_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/runner/work/otus_project/otus_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src_server/CMakeFiles/msgr_server.dir/session.cpp.o"
	cd /home/runner/work/otus_project/otus_project/src_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src_server/CMakeFiles/msgr_server.dir/session.cpp.o -MF CMakeFiles/msgr_server.dir/session.cpp.o.d -o CMakeFiles/msgr_server.dir/session.cpp.o -c /home/runner/work/otus_project/otus_project/src_server/session.cpp

src_server/CMakeFiles/msgr_server.dir/session.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/msgr_server.dir/session.cpp.i"
	cd /home/runner/work/otus_project/otus_project/src_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/otus_project/otus_project/src_server/session.cpp > CMakeFiles/msgr_server.dir/session.cpp.i

src_server/CMakeFiles/msgr_server.dir/session.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/msgr_server.dir/session.cpp.s"
	cd /home/runner/work/otus_project/otus_project/src_server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/otus_project/otus_project/src_server/session.cpp -o CMakeFiles/msgr_server.dir/session.cpp.s

# Object files for target msgr_server
msgr_server_OBJECTS = \
"CMakeFiles/msgr_server.dir/main.cpp.o" \
"CMakeFiles/msgr_server.dir/server.cpp.o" \
"CMakeFiles/msgr_server.dir/session.cpp.o"

# External object files for target msgr_server
msgr_server_EXTERNAL_OBJECTS =

src_server/msgr_server: src_server/CMakeFiles/msgr_server.dir/main.cpp.o
src_server/msgr_server: src_server/CMakeFiles/msgr_server.dir/server.cpp.o
src_server/msgr_server: src_server/CMakeFiles/msgr_server.dir/session.cpp.o
src_server/msgr_server: src_server/CMakeFiles/msgr_server.dir/build.make
src_server/msgr_server: src_server/CMakeFiles/msgr_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/runner/work/otus_project/otus_project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable msgr_server"
	cd /home/runner/work/otus_project/otus_project/src_server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/msgr_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src_server/CMakeFiles/msgr_server.dir/build: src_server/msgr_server
.PHONY : src_server/CMakeFiles/msgr_server.dir/build

src_server/CMakeFiles/msgr_server.dir/clean:
	cd /home/runner/work/otus_project/otus_project/src_server && $(CMAKE_COMMAND) -P CMakeFiles/msgr_server.dir/cmake_clean.cmake
.PHONY : src_server/CMakeFiles/msgr_server.dir/clean

src_server/CMakeFiles/msgr_server.dir/depend:
	cd /home/runner/work/otus_project/otus_project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runner/work/otus_project/otus_project /home/runner/work/otus_project/otus_project/src_server /home/runner/work/otus_project/otus_project /home/runner/work/otus_project/otus_project/src_server /home/runner/work/otus_project/otus_project/src_server/CMakeFiles/msgr_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src_server/CMakeFiles/msgr_server.dir/depend

