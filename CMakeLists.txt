cmake_minimum_required(VERSION 3.21)

# Set project name (this will be the SKSE .dll name)
project(EnxyAbilities VERSION 1.0.0 LANGUAGES CXX)

# VCPKG triplet for CommonLibSSE
set(VCPKG_TARGET_TRIPLET "x64-windows-static-md")

# ==============================
# COMMONLIBSSE SETUP
# ==============================
find_package(CommonLibSSE CONFIG REQUIRED)

# List all C++ source files
set(SOURCES
    src/plugin.cpp
    src/hud.cpp
    src/setting.cpp
    src/config.cpp
)

# Create SKSE plugin
add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${SOURCES})

# Set C++23 standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Set precompiled headers (PCH.h must exist in src/)
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h)

# Add include directory for src/
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)