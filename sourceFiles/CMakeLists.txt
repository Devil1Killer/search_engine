cmake_minimum_required(VERSION 3.27)

set(Src
        inverted_index.cpp
        converter_JSON.cpp
        search_server.cpp
        main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${Src})

target_link_libraries(${CMAKE_PROJECT_NAME} nlohmann_json::nlohmann_json)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${MY_HEADERFILES_DIR})