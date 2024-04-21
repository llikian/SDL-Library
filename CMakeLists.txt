cmake_minimum_required(VERSION 3.25)
project(SDL-Library)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME}
        main.cpp

        src/mainLib.cpp
        src/SDL.cpp
        src/complex_functions.cpp
        src/color_functions.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${SDL2_LIBRARIES}
        SDL2_image
        SDL2_mixer
        SDL2_ttf
)

# Sets executable folder to bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)