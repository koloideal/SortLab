cmake_minimum_required(VERSION 3.16)
project(SortLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.x
    GIT_SHALLOW    ON     
    EXCLUDE_FROM_ALL       
    SYSTEM               
)
FetchContent_MakeAvailable(SFML)

add_executable(SortLab
    src/main.cpp
    src/App.cpp
    src/App_audio.cpp
    src/Array.cpp
    src/Sorter.cpp
    src/UI.cpp
    src/sorters/BubbleSorter.cpp
    src/sorters/SelectionSorter.cpp
    src/sorters/InsertionSorter.cpp
    src/sorters/MergeSorter.cpp
    src/sorters/QuickSorter.cpp
)

target_include_directories(SortLab PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(SortLab PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)


if(WIN32)
    add_custom_command(TARGET SortLab POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:SortLab>
        $<TARGET_FILE_DIR:SortLab>
        COMMAND_EXPAND_LISTS
    )
endif()
