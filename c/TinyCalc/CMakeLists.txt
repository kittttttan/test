cmake_minimum_required(VERSION 2.4)

project(TinyCalc)

add_library(TinyCalc parser.cc lexer.cc)

include_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_BINARY_DIR})

add_executable(TinyCalcDemo main.cc)

target_link_libraries(TinyCalcDemo TinyCalc)
