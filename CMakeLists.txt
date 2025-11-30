cmake_minimum_required(VERSION 3.10.0)
project(lab7 VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS filesystem program_options)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/headers
)

file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/cpp/*.cpp
)

add_executable(lab7
    main.cpp
    ${SOURCES}
)

target_link_libraries(lab7
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
)