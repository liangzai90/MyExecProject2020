# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/henry/cppProject/JsonCppDemo-master/src/lib_json

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/henry/cppProject/JsonCppDemo-master/src/lib_json

# Include any dependencies generated for this target.
include CMakeFiles/jsoncpp_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jsoncpp_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jsoncpp_lib.dir/flags.make

CMakeFiles/jsoncpp_lib.dir/json_reader.o: CMakeFiles/jsoncpp_lib.dir/flags.make
CMakeFiles/jsoncpp_lib.dir/json_reader.o: json_reader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/henry/cppProject/JsonCppDemo-master/src/lib_json/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jsoncpp_lib.dir/json_reader.o"
	/usr/local/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jsoncpp_lib.dir/json_reader.o -c /home/henry/cppProject/JsonCppDemo-master/src/lib_json/json_reader.cpp

CMakeFiles/jsoncpp_lib.dir/json_reader.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib.dir/json_reader.i"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/henry/cppProject/JsonCppDemo-master/src/lib_json/json_reader.cpp > CMakeFiles/jsoncpp_lib.dir/json_reader.i

CMakeFiles/jsoncpp_lib.dir/json_reader.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib.dir/json_reader.s"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/henry/cppProject/JsonCppDemo-master/src/lib_json/json_reader.cpp -o CMakeFiles/jsoncpp_lib.dir/json_reader.s

CMakeFiles/jsoncpp_lib.dir/json_value.o: CMakeFiles/jsoncpp_lib.dir/flags.make
CMakeFiles/jsoncpp_lib.dir/json_value.o: json_value.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/henry/cppProject/JsonCppDemo-master/src/lib_json/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/jsoncpp_lib.dir/json_value.o"
	/usr/local/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jsoncpp_lib.dir/json_value.o -c /home/henry/cppProject/JsonCppDemo-master/src/lib_json/json_value.cpp

CMakeFiles/jsoncpp_lib.dir/json_value.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib.dir/json_value.i"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/henry/cppProject/JsonCppDemo-master/src/lib_json/json_value.cpp > CMakeFiles/jsoncpp_lib.dir/json_value.i

CMakeFiles/jsoncpp_lib.dir/json_value.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib.dir/json_value.s"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/henry/cppProject/JsonCppDemo-master/src/lib_json/json_value.cpp -o CMakeFiles/jsoncpp_lib.dir/json_value.s

CMakeFiles/jsoncpp_lib.dir/json_writer.o: CMakeFiles/jsoncpp_lib.dir/flags.make
CMakeFiles/jsoncpp_lib.dir/json_writer.o: json_writer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/henry/cppProject/JsonCppDemo-master/src/lib_json/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/jsoncpp_lib.dir/json_writer.o"
	/usr/local/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jsoncpp_lib.dir/json_writer.o -c /home/henry/cppProject/JsonCppDemo-master/src/lib_json/json_writer.cpp

CMakeFiles/jsoncpp_lib.dir/json_writer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_lib.dir/json_writer.i"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/henry/cppProject/JsonCppDemo-master/src/lib_json/json_writer.cpp > CMakeFiles/jsoncpp_lib.dir/json_writer.i

CMakeFiles/jsoncpp_lib.dir/json_writer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_lib.dir/json_writer.s"
	/usr/local/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/henry/cppProject/JsonCppDemo-master/src/lib_json/json_writer.cpp -o CMakeFiles/jsoncpp_lib.dir/json_writer.s

# Object files for target jsoncpp_lib
jsoncpp_lib_OBJECTS = \
"CMakeFiles/jsoncpp_lib.dir/json_reader.o" \
"CMakeFiles/jsoncpp_lib.dir/json_value.o" \
"CMakeFiles/jsoncpp_lib.dir/json_writer.o"

# External object files for target jsoncpp_lib
jsoncpp_lib_EXTERNAL_OBJECTS =

libjsoncpp.a: CMakeFiles/jsoncpp_lib.dir/json_reader.o
libjsoncpp.a: CMakeFiles/jsoncpp_lib.dir/json_value.o
libjsoncpp.a: CMakeFiles/jsoncpp_lib.dir/json_writer.o
libjsoncpp.a: CMakeFiles/jsoncpp_lib.dir/build.make
libjsoncpp.a: CMakeFiles/jsoncpp_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/henry/cppProject/JsonCppDemo-master/src/lib_json/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libjsoncpp.a"
	$(CMAKE_COMMAND) -P CMakeFiles/jsoncpp_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jsoncpp_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jsoncpp_lib.dir/build: libjsoncpp.a

.PHONY : CMakeFiles/jsoncpp_lib.dir/build

CMakeFiles/jsoncpp_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jsoncpp_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jsoncpp_lib.dir/clean

CMakeFiles/jsoncpp_lib.dir/depend:
	cd /home/henry/cppProject/JsonCppDemo-master/src/lib_json && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/henry/cppProject/JsonCppDemo-master/src/lib_json /home/henry/cppProject/JsonCppDemo-master/src/lib_json /home/henry/cppProject/JsonCppDemo-master/src/lib_json /home/henry/cppProject/JsonCppDemo-master/src/lib_json /home/henry/cppProject/JsonCppDemo-master/src/lib_json/CMakeFiles/jsoncpp_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jsoncpp_lib.dir/depend

