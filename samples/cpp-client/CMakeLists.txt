cmake_minimum_required(VERSION 3.16)

project(tcpi-cpp-client
        VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)

set(EXE_TARGET_NAME tcpi-cpp-client)

# YARP
find_package(YARP REQUIRED COMPONENTS
                           os
                           sig
)

# Find package containing the service
find_package(ThriftCppPythonInterop REQUIRED)

# Executable
add_executable(${EXE_TARGET_NAME} src/main.cpp)

target_link_libraries(${EXE_TARGET_NAME} PRIVATE
                                         YARP::YARP_init
                                         YARP::YARP_os
                                         YARP::YARP_sig
                                         ThriftCppPythonInterop::ThriftCppPythonInterop
)

install(TARGETS ${EXE_TARGET_NAME} DESTINATION bin)
