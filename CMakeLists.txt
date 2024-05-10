cmake_minimum_required(VERSION 3.28.0)
project(TP VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

include_directories(..)

add_executable(TP 
main.c
func.c
Pokemon.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
