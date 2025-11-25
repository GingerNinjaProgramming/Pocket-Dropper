cmake_minimum_required(VERSION 3.16)
project(Pocket-Dropper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

find_package(raylib 5.0 QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

include(FetchContent)
FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

file(GLOB SOURCES "*.cpp" "Include/*.cpp" "Resources/*.png")

add_executable(
        PocketDropper ${SOURCES}
)

add_custom_command(TARGET PocketDropper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:PocketDropper>/Resources
)

target_include_directories(PocketDropper PRIVATE . Include)
target_link_libraries(PocketDropper PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(PocketDropper PRIVATE raylib)

if (WIN32)
    target_link_libraries(PocketDropper PRIVATE winmm)
endif()
