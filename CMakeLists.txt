cmake_minimum_required(VERSION 3.14)
project(example)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1
)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif ()

FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)
set(TEST_NAME ${PROJECT_NAME}_tests)
add_subdirectory(life_backend)
add_executable(${TEST_NAME} life_tests/Life_tests.cpp
        life_backend/src/Life.cpp
        life_backend/include/Life.h
        life_tests/library_tests.cpp
        life_tests/library_tests.cpp
        life_frontend/life_frontend.cpp
        life_frontend/life_frontend.cpp
)
target_link_libraries(${TEST_NAME} gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
