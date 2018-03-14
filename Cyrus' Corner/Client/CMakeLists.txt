CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)

# Set the client type
PROJECT(RobotSimulatorNativeClient)

# Remove stupid warnings. These are introduced by Microsoft to get people to use non-standard
# functions
IF(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES=1)
ENDIF(MSVC)

# Set the C / C++ versions to the 11 standard
IF(CMAKE_MAJOR_VERSION VERSION_GREATER 2 AND
  CMAKE_MINOR_VERSION VERSION_GREATER 0)
  SET(CMAKE_C_STANDARD 11)
  SET(CMAKE_CXX_STANDARD 11)
ELSE()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  IF("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
  ELSE("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
  ENDIF("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
ENDIF()

# Find the threads library. This is needed for the Cog emulation.
# Note that on windows, it tries to find pthreads.h first. This is because
# pthreads has also been ported to windows.
FIND_PACKAGE(Threads)

# Helper macro for setting up executables
MACRO(DECLARE_APP appName mainsrc)
  SET(srcs)
  LIST(APPEND srcs ${mainsrc} ${ARGN})
#  MESSAGE(srcs=${srcs})
  ADD_EXECUTABLE(${appName} ${srcs})
  TARGET_LINK_LIBRARIES(${appName} client ${CMAKE_THREAD_LIBS_INIT})
ENDMACRO(DECLARE_APP)

# This sets up the include directory so that it is painless for client applications
INCLUDE_DIRECTORIES(${RobotSimulatorNativeClient_SOURCE_DIR}/include)

# Include the source for the simulator client library
ADD_SUBDIRECTORY(src)

# Other examples and test scripts
ADD_SUBDIRECTORY(final)

# (Optional) student submissions as tests

IF (EXISTS "${RobotSimulatorNativeClient_SOURCE_DIR}/Student_Submissions" AND IS_DIRECTORY
    "${RobotSimulatorNativeClient_SOURCE_DIR}/Student_Submissions")
  ADD_SUBDIRECTORY(Student_Submissions)
ENDIF()
