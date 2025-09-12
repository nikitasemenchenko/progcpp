cmake_minimum_required(VERSION 3.10)
project(lab2)

add_library(functions STATIC functions.cpp)
target_include_directories(functions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(lab2 main.cpp)
target_link_libraries(lab2 PRIVATE functions)

add_subdirectory(gtest_tests)

set(CPACK_PACKAGE_NAME "Lab2")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/package")

if(WIN32)
  set(CPACK_GENERATOR "ZIP")
elseif(UNIX)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "nas97 <nas97@tpu.ru>")
endif()

install(TARGETS lab2 DESTINATION bin)

include(CPack)