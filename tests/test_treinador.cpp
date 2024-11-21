// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "trainer.hpp"
#include "utils.hpp"

static std::array<Trainer, 2> treinadores = readTrainers("example.txt");

TEST_CASE("Trainer empty") {
  Trainer t({});
  CHECK(t.pokemons.empty());
  CHECK(t.alivePokemon == 0);
  CHECK(t.totalPokemon == 0);
}

TEST_CASE("Trainer with pokemons") {
  size_t totalPokemon =
      treinadores[0].totalPokemon + treinadores[1].totalPokemon;

  CHECK(totalPokemon == 5);
}

TEST_CASE("Trainer winner") {
  Trainer t({});
  CHECK_FALSE(t.isWinner());
  t.makeWinner();
  CHECK(t.isWinner());
}
