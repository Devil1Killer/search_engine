
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


set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

set(CMAKE_CXX_STANDARD 23)

add_executable(${CMAKE_PROJECT_NAME}
        sourceFiles/main.cpp
        sourceFiles/inverted_index.cpp
        sourceFiles/converter_JSON.cpp
        sourceFiles/search_server.cpp
        headerFiles/inverted_index.h
        headerFiles/converter_JSON.h
        headerFiles/search_server.h)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

#
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})
#
