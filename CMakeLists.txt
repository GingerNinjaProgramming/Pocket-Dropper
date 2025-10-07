cmake_minimum_required(VERSION 3.16)
project(Pocket-Dropper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_executable(PocketDropper
        main.cpp
        player.cpp
        obstacle.cpp
        projectile.cpp
        sprite.cpp
)


target_include_directories(PocketDropper PRIVATE .)
target_link_libraries(PocketDropper PRIVATE raylib)

if (WIN32)
    target_link_libraries(PocketDropper PRIVATE winmm)
endif()