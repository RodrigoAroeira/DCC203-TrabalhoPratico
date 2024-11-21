#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>

#include "doctest.h"
#include "trainer.hpp"
#include "utils.hpp"

TEST_CASE("Battle") {
  auto old_buffer = std::cout.rdbuf(nullptr);
  auto trainers = readTrainers("example.txt");
  Battle(trainers);
  CHECK(trainers[0].isWinner());
  std::cout.rdbuf(old_buffer);

  for (auto &trainer : trainers) {
    if (trainer.isWinner()) {
      CHECK(std::all_of(
          trainer.pokemons.begin(), trainer.pokemons.end(),
          [](const Pokemon &pokemon) { return pokemon.getHP() >= 0; }));
      CHECK(trainer.alivePokemon > 0);
    } else {
      CHECK(trainer.alivePokemon == 0);
      CHECK(std::all_of(
          trainer.pokemons.begin(), trainer.pokemons.end(),
          [](const Pokemon &pokemon) { return pokemon.getHP() == 0; }));
    }
  }
}
