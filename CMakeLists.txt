cmake_minimum_required(VERSION 3.21)

set(PROJECT_NAME Abyssal_CV_2022)
project(${PROJECT_NAME})

#set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20  -pthread" )

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/cmake-build-debug)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
#find_package(ngraph REQUIRED)

include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/src)


add_executable(Abyssal_CV_2022
        include/camera/CameraApi.h
        include/camera/CameraDefine.h
        include/camera/CameraStatus.h

        src/main.cpp

        src/camera/camera-stream.cpp
        src/camera/camera-stream.hpp

        src/armor/armor-identify.cpp
        src/armor/armor-identify.hpp
        asset/RoboMasterConfig.hpp
        src/armor/armor-tool.hpp

        src/video/video-save.hpp
        src/video/video-save.cpp

        src/serial/serial-port.hpp
        src/serial/serial-port.cpp src/armor/KCF/armor-KCF.hpp src/armor/KCF/armor-KCF.cpp src/energy/energy-buff.hpp src/energy/energy-buff.cpp src/control/control-switch.cpp src/control/control-switch.hpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/lib/libMVSDK.so")
#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} detector)
#target_link_libraries(Abyssal_CV_2022 Threads::Threads)