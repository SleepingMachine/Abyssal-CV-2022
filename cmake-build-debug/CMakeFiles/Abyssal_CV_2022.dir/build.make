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
CMAKE_COMMAND = /snap/clion/193/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/193/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Abyssal_CV_2022.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Abyssal_CV_2022.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Abyssal_CV_2022.dir/flags.make

CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/main.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/main.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/main.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.o: ../src/camera/camera-stream.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/camera/camera-stream.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/camera/camera-stream.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/camera/camera-stream.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.o: ../src/armor/armor-identify.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/armor/armor-identify.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/armor/armor-identify.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/armor/armor-identify.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.o: ../src/armor/KCF/armor-KCF.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/armor/KCF/armor-KCF.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/armor/KCF/armor-KCF.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/armor/KCF/armor-KCF.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.o: ../src/video/video-save.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/video/video-save.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/video/video-save.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/video/video-save.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.o: ../src/serial/serial-port.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-port.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-port.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-port.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.o: ../src/energy/energy-buff.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/energy/energy-buff.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/energy/energy-buff.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/energy/energy-buff.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.o: ../src/control/control-switch.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/control/control-switch.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/control/control-switch.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/control/control-switch.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.o: ../src/serial/serial-TUP/serial-port-TUP.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-TUP/serial-port-TUP.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-TUP/serial-port-TUP.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-TUP/serial-port-TUP.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.o: ../src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.o: ../src/serial/serial-TUP/serial-synchronize-TUP.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-TUP/serial-synchronize-TUP.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-TUP/serial-synchronize-TUP.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-TUP/serial-synchronize-TUP.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.o: ../src/serial/serial-2nd/serial-port-2nd.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-2nd/serial-port-2nd.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-2nd/serial-port-2nd.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-2nd/serial-port-2nd.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.o: ../src/serial/serial-2nd/serial-synchronize-2nd.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-2nd/serial-synchronize-2nd.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-2nd/serial-synchronize-2nd.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/serial/serial-2nd/serial-synchronize-2nd.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.s

CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/flags.make
CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.o: ../src/decision/decision-making.cpp
CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.o: CMakeFiles/Abyssal_CV_2022.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.o -MF CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.o.d -o CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.o -c /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/decision/decision-making.cpp

CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/decision/decision-making.cpp > CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.i

CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/src/decision/decision-making.cpp -o CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.s

# Object files for target Abyssal_CV_2022
Abyssal_CV_2022_OBJECTS = \
"CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.o" \
"CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.o"

# External object files for target Abyssal_CV_2022
Abyssal_CV_2022_EXTERNAL_OBJECTS =

Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/main.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/camera/camera-stream.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/armor/armor-identify.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/armor/KCF/armor-KCF.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/video/video-save.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-port.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/energy/energy-buff.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/control/control-switch.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-port-TUP.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/CRC/serial-CRC-TUP.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-TUP/serial-synchronize-TUP.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-port-2nd.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/serial/serial-2nd/serial-synchronize-2nd.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/src/decision/decision-making.cpp.o
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/build.make
Abyssal_CV_2022: /usr/local/lib/libopencv_gapi.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_stitching.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_alphamat.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_aruco.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_barcode.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_bgsegm.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_bioinspired.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_ccalib.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_dnn_objdetect.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_dnn_superres.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_dpm.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_face.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_freetype.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_fuzzy.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_hfs.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_img_hash.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_intensity_transform.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_line_descriptor.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_mcc.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_quality.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_rapid.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_reg.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_rgbd.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_saliency.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_stereo.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_structured_light.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_superres.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_surface_matching.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_tracking.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_videostab.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_wechat_qrcode.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_xfeatures2d.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_xobjdetect.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_xphoto.so.4.5.5
Abyssal_CV_2022: ../lib/libMVSDK.so
Abyssal_CV_2022: /usr/local/lib/libopencv_shape.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_highgui.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_datasets.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_plot.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_text.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_ml.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_phase_unwrapping.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_optflow.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_ximgproc.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_video.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_videoio.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_imgcodecs.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_objdetect.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_calib3d.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_dnn.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_features2d.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_flann.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_photo.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_imgproc.so.4.5.5
Abyssal_CV_2022: /usr/local/lib/libopencv_core.so.4.5.5
Abyssal_CV_2022: CMakeFiles/Abyssal_CV_2022.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable Abyssal_CV_2022"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Abyssal_CV_2022.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Abyssal_CV_2022.dir/build: Abyssal_CV_2022
.PHONY : CMakeFiles/Abyssal_CV_2022.dir/build

CMakeFiles/Abyssal_CV_2022.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Abyssal_CV_2022.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Abyssal_CV_2022.dir/clean

CMakeFiles/Abyssal_CV_2022.dir/depend:
	cd /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022 /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022 /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug /home/sleepingmachine/RoboMaster-Code/Abyssal-CV-2022/cmake-build-debug/CMakeFiles/Abyssal_CV_2022.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Abyssal_CV_2022.dir/depend

