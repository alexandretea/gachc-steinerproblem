cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "gachc-steinerproblem")

project(${PROJECT_NAME})

include(ExternalProject)
include(CheckIncludeFileCXX)

include_directories(
    .
    srcs/
    srcs/ga
    srcs/gsp
    srcs/exceptions
)

set(LIBS
)

file(GLOB sources
	srcs/*.cpp
	srcs/ga/*.cpp
	srcs/gsp/*.cpp
	srcs/utils/*.cpp
	srcs/exceptions/*.cpp
)
set(SOURCES ${sources})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES
                      COMPILE_FLAGS "${CMAKE_CXX_FLAGS} \
-D PRODUCTION -std=c++14 -W -Wall -Wextra")
target_link_libraries(${PROJECT_NAME} ${LIBS})
