# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dontssh/Documents/GitHub/PngProject/disassembler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dontssh/Documents/GitHub/PngProject/build

# Include any dependencies generated for this target.
include CMakeFiles/disassembler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/disassembler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/disassembler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/disassembler.dir/flags.make

CMakeFiles/disassembler.dir/main.cpp.o: CMakeFiles/disassembler.dir/flags.make
CMakeFiles/disassembler.dir/main.cpp.o: /Users/dontssh/Documents/GitHub/PngProject/disassembler/main.cpp
CMakeFiles/disassembler.dir/main.cpp.o: CMakeFiles/disassembler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dontssh/Documents/GitHub/PngProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/disassembler.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/disassembler.dir/main.cpp.o -MF CMakeFiles/disassembler.dir/main.cpp.o.d -o CMakeFiles/disassembler.dir/main.cpp.o -c /Users/dontssh/Documents/GitHub/PngProject/disassembler/main.cpp

CMakeFiles/disassembler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/disassembler.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dontssh/Documents/GitHub/PngProject/disassembler/main.cpp > CMakeFiles/disassembler.dir/main.cpp.i

CMakeFiles/disassembler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/disassembler.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dontssh/Documents/GitHub/PngProject/disassembler/main.cpp -o CMakeFiles/disassembler.dir/main.cpp.s

# Object files for target disassembler
disassembler_OBJECTS = \
"CMakeFiles/disassembler.dir/main.cpp.o"

# External object files for target disassembler
disassembler_EXTERNAL_OBJECTS =

disassembler: CMakeFiles/disassembler.dir/main.cpp.o
disassembler: CMakeFiles/disassembler.dir/build.make
disassembler: CMakeFiles/disassembler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dontssh/Documents/GitHub/PngProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable disassembler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/disassembler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/disassembler.dir/build: disassembler
.PHONY : CMakeFiles/disassembler.dir/build

CMakeFiles/disassembler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/disassembler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/disassembler.dir/clean

CMakeFiles/disassembler.dir/depend:
	cd /Users/dontssh/Documents/GitHub/PngProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dontssh/Documents/GitHub/PngProject/disassembler /Users/dontssh/Documents/GitHub/PngProject/disassembler /Users/dontssh/Documents/GitHub/PngProject/build /Users/dontssh/Documents/GitHub/PngProject/build /Users/dontssh/Documents/GitHub/PngProject/build/CMakeFiles/disassembler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/disassembler.dir/depend

