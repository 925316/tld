cmake_minimum_required(VERSION 3.20)

# Allow dependencies that still declare an old cmake_minimum_required.
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(tld CXX)

if (NOT MSVC)
  message(FATAL_ERROR "tld targets The Long Dark (x64 Windows) and is built with MSVC.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Dependencies are fetched into the CMake binary dir (sln/_deps) and are
# intentionally not committed to the repository.
include(cmake/imgui.cmake)
include(cmake/minhook.cmake)

# CONFIGURE_DEPENDS re-runs the glob at build time, so a newly added feature
# file is picked up without touching any project file.
file(GLOB_RECURSE SRC_MAIN CONFIGURE_DEPENDS
    "${SRC_DIR}/*.h"
    "${SRC_DIR}/*.hpp"
    "${SRC_DIR}/*.cpp"
)

list(LENGTH SRC_MAIN SRC_COUNT)
message(STATUS "tld sources: ${SRC_COUNT}")

add_library(tld MODULE ${SRC_MAIN})

target_include_directories(tld PRIVATE
    "${SRC_DIR}"
    "${imgui_SOURCE_DIR}"
)

target_precompile_headers(tld PRIVATE "${SRC_DIR}/pch.h")

target_compile_definitions(tld PRIVATE
    _WINDOWS
    _USRDLL
    TLD_EXPORTS
    NOMINMAX
    _CRT_SECURE_NO_WARNINGS
)

target_compile_options(tld PRIVATE
    $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive-;/utf-8;/MP;/bigobj;/W3;/WX>
)

# winmm/psapi/d3d11/d3dcompiler/dxgi are already pulled in by
# '#pragma comment(lib, ...)' in pch.h for MSVC; declaring them here keeps the
# link line explicit and toolchain independent.
target_link_libraries(tld PRIVATE
    imgui
    minhook
    winmm
    psapi
    d3d11
    d3dcompiler
    dxgi
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
source_group(TREE "${SRC_DIR}" PREFIX "src" FILES ${SRC_MAIN})
