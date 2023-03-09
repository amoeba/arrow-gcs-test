cmake_minimum_required(VERSION 3.10)

project(arrow_gcs_test VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

# Set up find_package to find Arrow in $ARROW_HOME
SET(ARROW_HOME $ENV{ARROW_HOME})

if (ARROW_HOME STREQUAL "")
    message(STATUS "ARROW_HOME not set. YMMV!")
else()
    message(STATUS "Using $ARROW_HOME of ${ARROW_HOME}")
    set(CMAKE_PREFIX_PATH ${ARROW_HOME})
endif()

find_package(Arrow REQUIRED)

add_executable(gcs-test gcs-test.cc)
set_property(TARGET gcs-test PROPERTY CXX_STANDARD 17)
target_link_libraries(gcs-test PRIVATE Arrow::arrow_shared)
