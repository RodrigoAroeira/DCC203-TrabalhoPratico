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

# Function to create a link (hardlink on Windows, symlink on other platforms)
function(create_link source target)
  if(WIN32)
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E create_hardlink ${target} ${source}
      RESULT_VARIABLE result
    )
  else()
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${target}
      RESULT_VARIABLE result
    )
  endif()

  if(NOT result EQUAL 0)
    message(FATAL_ERROR "Failed to create link from ${source} to ${target}")
  endif()
endfunction()

# Iterate over files and create links
foreach(FILE ${FILES_TO_LINK})
  get_filename_component(FILENAME ${FILE} NAME)
  create_link(${FILE} ${CMAKE_BINARY_DIR}/${FILENAME})
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
