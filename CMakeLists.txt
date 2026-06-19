cmake_minimum_required(VERSION 3.21)

project(EnxyAbilities VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ENABLE_HARNESS ON CACHE BOOL "" FORCE)

find_package(CommonLibSSE CONFIG REQUIRED)

# List semua file .cpp
set(SOURCES
    src/plugin.cpp
    src/hud.cpp
    src/setting.cpp
    src/config.cpp
)

add_skse_plugin(${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE CommonLibSSE::CommonLibSSE)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)