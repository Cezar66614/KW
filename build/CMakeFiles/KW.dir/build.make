# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/k32ar/Projects/KW

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/k32ar/Projects/KW/build

# Include any dependencies generated for this target.
include CMakeFiles/KW.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/KW.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/KW.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KW.dir/flags.make

CMakeFiles/KW.dir/codegen:
.PHONY : CMakeFiles/KW.dir/codegen

CMakeFiles/KW.dir/src/main.c.o: CMakeFiles/KW.dir/flags.make
CMakeFiles/KW.dir/src/main.c.o: /home/k32ar/Projects/KW/src/main.c
CMakeFiles/KW.dir/src/main.c.o: CMakeFiles/KW.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/k32ar/Projects/KW/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/KW.dir/src/main.c.o"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/KW.dir/src/main.c.o -MF CMakeFiles/KW.dir/src/main.c.o.d -o CMakeFiles/KW.dir/src/main.c.o -c /home/k32ar/Projects/KW/src/main.c

CMakeFiles/KW.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/KW.dir/src/main.c.i"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/k32ar/Projects/KW/src/main.c > CMakeFiles/KW.dir/src/main.c.i

CMakeFiles/KW.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/KW.dir/src/main.c.s"
	/usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/k32ar/Projects/KW/src/main.c -o CMakeFiles/KW.dir/src/main.c.s

# Object files for target KW
KW_OBJECTS = \
"CMakeFiles/KW.dir/src/main.c.o"

# External object files for target KW
KW_EXTERNAL_OBJECTS =

KW: CMakeFiles/KW.dir/src/main.c.o
KW: CMakeFiles/KW.dir/build.make
KW: CMakeFiles/KW.dir/compiler_depend.ts
KW: CMakeFiles/KW.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/k32ar/Projects/KW/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable KW"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KW.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KW.dir/build: KW
.PHONY : CMakeFiles/KW.dir/build

CMakeFiles/KW.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/KW.dir/cmake_clean.cmake
.PHONY : CMakeFiles/KW.dir/clean

CMakeFiles/KW.dir/depend:
	cd /home/k32ar/Projects/KW/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/k32ar/Projects/KW /home/k32ar/Projects/KW /home/k32ar/Projects/KW/build /home/k32ar/Projects/KW/build /home/k32ar/Projects/KW/build/CMakeFiles/KW.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/KW.dir/depend
