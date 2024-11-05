// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "treinador.hpp"
#include "utils.hpp"

static std::array<Treinador, 2> treinadores = lerTreinadores("exemplo.txt");

TEST_CASE("Treinador empty") {
  Treinador t({});
  CHECK(t.pokemons.empty());
  CHECK(t.pokemonsVivos == 0);
  CHECK(t.pokemonsTotal == 0);
}

TEST_CASE("Treinador with pokemons") {
  size_t pokemonsTotal =
      treinadores[0].pokemonsTotal + treinadores[1].pokemonsTotal;

  CHECK(pokemonsTotal == 5);
}

TEST_CASE("Treinador winner") {
  Treinador t({});
  CHECK_FALSE(t.isVencedor());
  t.makeVencedor();
  CHECK(t.isVencedor());
}
