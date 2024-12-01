cmake_minimum_required(VERSION 3.29)

project(Visualizer)

include(FetchContent)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.9
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)

FetchContent_Declare(nfd
    GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended
    GIT_TAG v1.2.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(nfd)


add_executable(main main.cpp)
target_link_libraries(main PRIVATE 
    sfml-graphics sfml-window sfml-system sfml-audio
    ImGui-SFML::ImGui-SFML
    nfd
)

if(WIN32)
    set(CMAKE_GENERATOR_PLATFORM x64)
    target_link_libraries(main PRIVATE ole32 uuid shell32)
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/_deps/sfml-src/extlibs/bin/x64/openal32.dll"
        $<TARGET_FILE_DIR:main>   
    )
endif()

target_compile_features(main PRIVATE cxx_std_17)

target_sources(main PRIVATE
    AudioPlayer.cpp
    UIManager.cpp
    WaveformVisualizer.cpp    
    FileDialog.cpp
)

