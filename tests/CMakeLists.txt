cmake_minimum_required(VERSION 3.27)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SrcFiles
        ${MY_SOURCEFILES_DIR}/inverted_index.cpp
        ${MY_SOURCEFILES_DIR}/converter_JSON.cpp
        ${MY_SOURCEFILES_DIR}/search_server.cpp
)

set(TestsFiles
        Test.cpp
)

add_executable(GtestTests ${TestsFiles} ${SrcFiles})
target_link_libraries(GtestTests nlohmann_json::nlohmann_json gtest_main)
include(GoogleTest)
target_include_directories(GtestTests PUBLIC ${MY_HEADERFILES_DIR})
gtest_discover_tests(GtestTests)