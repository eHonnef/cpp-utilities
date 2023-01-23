cmake_minimum_required(VERSION 3.2)
set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_STANDARD 20)

project(
  ByteUtilities
  LANGUAGES CXX
)

add_library(unittest OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/../unittest/catch2/catch_amalgamated.cpp ${CMAKE_CURRENT_SOURCE_DIR}/../unittest/catch2/catch_amalgamated.hpp)

add_executable(${PROJECT_NAME} Tests.cpp ByteUtilities.hpp)
include_directories(${PROJECT_NAME} PUBLIC ./ ${CMAKE_CURRENT_SOURCE_DIR}/../unittest/catch2/)
add_dependencies(${PROJECT_NAME} unittest)
target_link_libraries(${PROJECT_NAME} PUBLIC unittest)
