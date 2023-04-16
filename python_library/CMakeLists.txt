cmake_minimum_required(VERSION 3.16)

project(ThriftCppPythonInterop
        VERSION 0.0.1)

set(LIBRARY_TARGET_NAME tcpi)

# Default build type to Release
if(NOT CMAKE_CONFIGURATION_TYPES)
    if(NOT CMAKE_BUILD_TYPE)
        message(STATUS "Setting build type to 'Release' as none was specified.")
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Release")
    endif()
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

# Find package containing the service
find_package(ThriftCppPythonInterop REQUIRED)

# Python
find_package(Python3 REQUIRED COMPONENTS Interpreter Development REQUIRED)

# YARP
find_package(YARP REQUIRED)
foreach(_component conf sig)
  get_property(YARP_${_component}_INCLUDE_DIRS TARGET YARP::YARP_${_component} PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
  include_directories(${YARP_${_component}_INCLUDE_DIRS})
endforeach()
include_directories(${YARP_BINDINGS})

# SWIG
find_package(SWIG 4.0 REQUIRED)
include(${SWIG_USE_FILE})

# Configure SWIG
set(SWIG_BINDINGS_SOURCE_FILE ${LIBRARY_TARGET_NAME}-python-types.i)
set_source_files_properties(${SWIG_BINDINGS_SOURCE_FILE} PROPERTIES CPLUSPLUS ON)
set(CMAKE_SWIG_OUTDIR "${CMAKE_BINARY_DIR}/lib/python3")
set(CMAKE_SWIG_FLAGS "-py3;-O;-threads")

# Create SWIG library
swig_add_library(${LIBRARY_TARGET_NAME}
                 LANGUAGE python
                 SOURCES ${SWIG_BINDINGS_SOURCE_FILE})

# Link libraries
swig_link_libraries(${LIBRARY_TARGET_NAME} ThriftCppPythonInterop::ThriftCppPythonInterop Python3::Python YARP::YARP_os YARP::YARP_sig)

# Include directories
target_include_directories(${SWIG_MODULE_${LIBRARY_TARGET_NAME}_REAL_NAME} BEFORE PRIVATE ${Python3_INCLUDE_DIRS})

# Target properties
set_target_properties(${SWIG_MODULE_${LIBRARY_TARGET_NAME}_REAL_NAME}
                      PROPERTIES OUTPUT_NAME "${LIBRARY_TARGET_NAME}_cpp"
                      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/python3"
                      # treat Python3_INCLUDE_DIRS as non-system so that it can be overriden
                      NO_SYSTEM_FROM_IMPORTED TRUE)

# Installation
execute_process(
  COMMAND ${Python3_EXECUTABLE} -c "from distutils import sysconfig; print(sysconfig.get_python_lib())"
  OUTPUT_VARIABLE Python3_INSTDIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(_CMAKE_INSTALL_PYTHON3DIR "${Python3_INSTDIR}")
set(CMAKE_INSTALL_PYTHON3DIR ${_CMAKE_INSTALL_PYTHON3DIR} CACHE PATH "python3 bindings (${_CMAKE_INSTALL_PYTHON3DIR})")
mark_as_advanced(CMAKE_INSTALL_PYTHON3DIR)
if(NOT IS_ABSOLUTE ${CMAKE_INSTALL_PYTHON3DIR})
  set(CMAKE_INSTALL_FULL_PYTHON3DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_PYTHON3DIR}")
else()
  set(CMAKE_INSTALL_FULL_PYTHON3DIR "${CMAKE_INSTALL_PYTHON3DIR}")
endif()

install(FILES ${CMAKE_BINARY_DIR}/lib/python3/${LIBRARY_TARGET_NAME}.py
        DESTINATION ${CMAKE_INSTALL_PYTHON3DIR})

if(NOT CMAKE_SKIP_RPATH AND NOT CMAKE_SKIP_INSTALL_RPATH)
  file(RELATIVE_PATH _rel_path "${CMAKE_INSTALL_FULL_PYTHON3DIR}" "${CMAKE_INSTALL_FULL_LIBDIR}")
  get_target_property(_current_rpath ${SWIG_MODULE_${LIBRARY_TARGET_NAME}_REAL_NAME} INSTALL_RPATH)
  if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    list(APPEND _current_rpath "@loader_path/${_rel_path}")
  else()
    list(APPEND _current_rpath "\$ORIGIN/${_rel_path}")
  endif()
  set_target_properties(${SWIG_MODULE_${LIBRARY_TARGET_NAME}_REAL_NAME} PROPERTIES INSTALL_RPATH "${_current_rpath}")
endif()

install(
  TARGETS ${SWIG_MODULE_${LIBRARY_TARGET_NAME}_REAL_NAME}
  DESTINATION ${CMAKE_INSTALL_PYTHON3DIR}
)

option(${LIBRARY_TARGET_NAME}_PYTHON_PIP_METADATA_INSTALL "Use CMake to install Python pip metadata. Set to false if some other tool installs it." TRUE)
mark_as_advanced(${LIBRARY_TARGET_NAME}_PYTHON_PIP_METADATA_INSTALL)
set(${LIBRARY_TARGET_NAME}_PYTHON_PIP_METADATA_INSTALLER "cmake" CACHE STRING "Specify the string to identify the pip Installer. Default: cmake, change this if you are using another tool.")
mark_as_advanced(${LIBRARY_TARGET_NAME}_PYTHON_PIP_METADATA_INSTALLER)
if(${LIBRARY_TARGET_NAME}_PYTHON_PIP_METADATA_INSTALL)
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/METADATA "")
  file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/METADATA "Metadata-Version: 2.1\n")
  file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/METADATA "Name: ${LIBRARY_TARGET_NAME}\n")
  file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/METADATA "Version: 0.0.100\n")
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/INSTALLER "${${LIBRARY_TARGET_NAME}_PYTHON_PIP_METADATA_INSTALLER}\n")
  install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/METADATA" "${CMAKE_CURRENT_BINARY_DIR}/INSTALLER"
    DESTINATION ${CMAKE_INSTALL_PYTHON3DIR}/${LIBRARY_TARGET_NAME}.dist-info)
endif()

# Add standard uninstall target
include(AddUninstallTarget)
