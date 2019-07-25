project (Minesweeper)

cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 14)

file (GLOB SOURCES "src/*.cpp" "src/*.c")
add_executable (${PROJECT_NAME} ${SOURCES})

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

find_package (SDL2 REQUIRED)
find_package (SDL2_image REQUIRED)
find_package (SDL2TTF REQUIRED)

include_directories (include)
include_directories (${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})
include_directories (${PROJECT_NAME} ${SDL2_IMAGE_DIRS})
include_directories (${PROJECT_NAME} ${SDL2TTF_DIRS})

configure_file(tiles.png tiles.png COPYONLY)
configure_file(early_gameboy.ttf early_gameboy.ttf COPYONLY)

target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})
