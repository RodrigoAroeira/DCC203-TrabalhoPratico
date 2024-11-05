cmake_minimum_required(VERSION 3.10)

project("Pokemon")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

file(GLOB SRC_FILES "src/*.cpp")
list(REMOVE_ITEM SRC_FILES "${CMAKE_SOURCE_DIR}/src/main.cpp")

include_directories(headers includes/usr/include)

# Create a static library from the common source files
add_library(PokemonLib STATIC ${SRC_FILES})

# Add executable for the main application
add_executable(Pokemon src/main.cpp)
target_link_libraries(Pokemon PokemonLib)

file(GLOB FILES_TO_LINK
    ${CMAKE_SOURCE_DIR}/treinadores.txt
    ${CMAKE_SOURCE_DIR}/exemplo.txt
    ${CMAKE_SOURCE_DIR}/instrucoes.txt
)

foreach(FILE ${FILES_TO_LINK})
  get_filename_component(FILENAME ${FILE} NAME)
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${FILE} ${CMAKE_BINARY_DIR}/${FILENAME})
endforeach()

add_custom_target(run
  COMMAND Pokemon
  DEPENDS Pokemon
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

file(GLOB TEST_FILES "tests/*.cpp")
add_executable(TestPokemon ${TEST_FILES})
include_directories("tests")
target_link_libraries(TestPokemon PokemonLib)

add_custom_target(tests
  DEPENDS TestPokemon
  COMMAND TestPokemon
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

set_target_properties(TestPokemon PROPERTIES EXCLUDE_FROM_ALL TRUE)
