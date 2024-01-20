#
include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
FetchContent_MakeAvailable(googletest)
enable_testing()
#

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)
cmake_minimum_required(VERSION 3.27)
project(project)

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
