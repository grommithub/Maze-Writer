project(Maze-Writer)

target_sources(
    Maze-Writer
    PRIVATE
        Coords.cpp
        Game.cpp
        main.cpp
)

target_compile_definitions(Maze-Writer PUBLIC CMAKE_BUILD)

find_package(SDL2 REQUIRED)

target_link_libraries(
    Maze-Writer
    PRIVATE
        SDL2::SDL2
)
