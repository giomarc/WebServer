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
CMAKE_COMMAND = /home/giorgia/Scaricati/clion-2018.1.5/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/giorgia/Scaricati/clion-2018.1.5/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/giorgia/CLionProjects/WebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/giorgia/CLionProjects/WebServer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/WebServer7.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WebServer7.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WebServer7.dir/flags.make

CMakeFiles/WebServer7.dir/init_server.c.o: CMakeFiles/WebServer7.dir/flags.make
CMakeFiles/WebServer7.dir/init_server.c.o: ../init_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/giorgia/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/WebServer7.dir/init_server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/WebServer7.dir/init_server.c.o   -c /home/giorgia/CLionProjects/WebServer/init_server.c

CMakeFiles/WebServer7.dir/init_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WebServer7.dir/init_server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/giorgia/CLionProjects/WebServer/init_server.c > CMakeFiles/WebServer7.dir/init_server.c.i

CMakeFiles/WebServer7.dir/init_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WebServer7.dir/init_server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/giorgia/CLionProjects/WebServer/init_server.c -o CMakeFiles/WebServer7.dir/init_server.c.s

CMakeFiles/WebServer7.dir/init_server.c.o.requires:

.PHONY : CMakeFiles/WebServer7.dir/init_server.c.o.requires

CMakeFiles/WebServer7.dir/init_server.c.o.provides: CMakeFiles/WebServer7.dir/init_server.c.o.requires
	$(MAKE) -f CMakeFiles/WebServer7.dir/build.make CMakeFiles/WebServer7.dir/init_server.c.o.provides.build
.PHONY : CMakeFiles/WebServer7.dir/init_server.c.o.provides

CMakeFiles/WebServer7.dir/init_server.c.o.provides.build: CMakeFiles/WebServer7.dir/init_server.c.o


# Object files for target WebServer7
WebServer7_OBJECTS = \
"CMakeFiles/WebServer7.dir/init_server.c.o"

# External object files for target WebServer7
WebServer7_EXTERNAL_OBJECTS =

WebServer7: CMakeFiles/WebServer7.dir/init_server.c.o
WebServer7: CMakeFiles/WebServer7.dir/build.make
WebServer7: CMakeFiles/WebServer7.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/giorgia/CLionProjects/WebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable WebServer7"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WebServer7.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WebServer7.dir/build: WebServer7

.PHONY : CMakeFiles/WebServer7.dir/build

CMakeFiles/WebServer7.dir/requires: CMakeFiles/WebServer7.dir/init_server.c.o.requires

.PHONY : CMakeFiles/WebServer7.dir/requires

CMakeFiles/WebServer7.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WebServer7.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WebServer7.dir/clean

CMakeFiles/WebServer7.dir/depend:
	cd /home/giorgia/CLionProjects/WebServer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/giorgia/CLionProjects/WebServer /home/giorgia/CLionProjects/WebServer /home/giorgia/CLionProjects/WebServer/cmake-build-debug /home/giorgia/CLionProjects/WebServer/cmake-build-debug /home/giorgia/CLionProjects/WebServer/cmake-build-debug/CMakeFiles/WebServer7.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WebServer7.dir/depend

