include(FetchContent)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.93.0
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(imgui)

# Dear ImGui ships without a CMakeLists.txt, so the target is created here.
# Only the renderer core and the two backends this project uses are compiled.
if (NOT TARGET imgui)
    set(SRC_IMGUI
        "${imgui_SOURCE_DIR}/imgui.cpp"
        "${imgui_SOURCE_DIR}/imgui_draw.cpp"
        "${imgui_SOURCE_DIR}/imgui_tables.cpp"
        "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
        "${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp"
        "${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp"
    )

    add_library(imgui STATIC ${SRC_IMGUI})

    target_include_directories(imgui PUBLIC
        "${imgui_SOURCE_DIR}"
        "${imgui_SOURCE_DIR}/backends"
    )

    target_compile_definitions(imgui PRIVATE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
        _CRT_SECURE_NO_WARNINGS
    )

    set_target_properties(imgui PROPERTIES FOLDER "deps")
    source_group(TREE "${imgui_SOURCE_DIR}" PREFIX "imgui" FILES ${SRC_IMGUI})
endif()
