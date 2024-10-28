cmake_minimum_required(VERSION 3.10)

project("Pokemon")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

file(GLOB SRC_FILES "src/*.cpp")

include_directories(headers includes/usr/include)

add_executable(Pokemon ${SRC_FILES})

file(GLOB FILES_TO_COPY
    ${CMAKE_SOURCE_DIR}/treinadores.txt
    ${CMAKE_SOURCE_DIR}/exemplo.txt
)

foreach(FILE ${FILES_TO_COPY})
  file(COPY ${FILE} DESTINATION ${CMAKE_BINARY_DIR})
endforeach()

add_custom_target(run
COMMAND Pokemon
DEPENDS Pokemon
WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
