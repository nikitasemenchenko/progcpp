cmake_minimum_required(VERSION 3.10)
project(lab2)

if(NOT DEFINED PROJECT_VERSION_MAJOR)
  set(PROJECT_VERSION_MAJOR 0)
endif()
if(NOT DEFINED PROJECT_VERSION_MINOR)
  set(PROJECT_VERSION_MINOR 0)
endif()
if(NOT DEFINED PATCH_VERSION)
  set(PATCH_VERSION 0)
endif()

set(CPACK_PACKAGE_NAME "Lab2")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/package")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PATCH_VERSION}")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_DEBIAN_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION}")

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