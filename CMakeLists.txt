cmake_minimum_required(VERSION 3.10)

project(CppCourseKids VERSION 1.0
        DESCRIPTION "C/C++-Kurs für Kinder ab der 5. Klasse"
        LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_definitions(-Wall)
add_subdirectory(book)
add_subdirectory(src)