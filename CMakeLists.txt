cmake_minimum_required(VERSION 3.10)
project(coursework LANGUAGES CXX)

include_directories("C:/msys64/mingw64/include"
                ${CMAKE_SOURCE_DIR}/headers)

file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/cpp/*.cpp
)

link_directories("C:/msys64/mingw64/lib")

add_executable(coursework main.cpp ${SOURCES})

target_link_libraries(coursework PRIVATE wt wthttp)

add_custom_target(copy_ui ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/ui
            ${CMAKE_BINARY_DIR}/ui
)

add_dependencies(coursework copy_ui)