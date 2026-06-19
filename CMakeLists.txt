cmake_minimum_required(VERSION 3.21)

project(EnxyAbilities VERSION 1.0.0 LANGUAGES CXX)

set(VCPKG_TARGET_TRIPLET "x64-windows-static-md")

find_package(CommonLibSSE CONFIG REQUIRED)

set(SOURCES
    src/plugin.cpp
    src/hud.cpp
    src/setting.cpp
    src/config.cpp
)

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# PCH.h di ROOT project (bukan src/)
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h)

# Include src/ dan root untuk headers
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)