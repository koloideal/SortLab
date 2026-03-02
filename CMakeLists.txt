cmake_minimum_required(VERSION 3.16)
project(SortLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

add_executable(SortLab
    src/main.cpp
)

target_link_libraries(SortLab PRIVATE sfml-graphics sfml-window sfml-system)
