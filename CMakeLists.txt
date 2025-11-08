cmake_minimum_required(VERSION 3.10.0)
project(lab6 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(lab6 main.cpp model/Document.cpp model/Circle.cpp model/Square.cpp controller/Controller.cpp view/View.cpp)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/controller
    ${CMAKE_CURRENT_SOURCE_DIR}/view
)
