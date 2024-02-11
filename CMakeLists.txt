cmake_minimum_required(VERSION 3.27)
project(project)


include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
FetchContent_MakeAvailable(googletest)
enable_testing()

set(CMAKE_CXX_STANDARD 23)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set(MY_HEADERFILES_DIR ${CMAKE_SOURCE_DIR}/headerFiles)
set(MY_SOURCEFILES_DIR ${CMAKE_SOURCE_DIR}/sourceFiles)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_subdirectory(nlohmann_json)

add_subdirectory(sourceFiles)
add_subdirectory(tests)