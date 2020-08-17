cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(SolidBackground)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O3")


#---Set ROOT parameter
list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# RooFit RooFitCore
find_package(ROOT REQUIRED COMPONENTS Core RooStats Tree RIO Matrix MathCore)
#find_package(ROOT REQUIRED COMPONENTS RooFit RooFitCore Core RooStats Tree RIO Matrix MathCore)

#--- Include ROOT
include(${ROOT_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})

#--- Include project files
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB scripts ${PROJECT_SOURCE_DIR}/scripts/*.cc)

add_executable(${PROJECT_NAME} main.cpp ${sources}  ${headers} ${scripts})
target_link_libraries(${PROJECT_NAME} ${ROOT_LIBRARIES})
