cmake_minimum_required(VERSION 3.26)
project ( excel )

set (CMAKE_CXX_STANDARD 20)
link_directories (${CMAKE_SOURCE_DIR}/arm64-darwin23-clang/)

add_executable ( excel
        result.cpp
        expression.h)

target_link_libraries ( excel PRIVATE libexpression_parser.a)
target_include_directories ( excel PRIVATE ${CMAKE_SOURCE_DIR})