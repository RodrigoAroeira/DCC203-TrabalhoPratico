// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "treinador.hpp"
#include "utils.hpp"

static std::array<Treinador, 2> treinadores = lerTreinadores("exemplo.txt");

TEST_CASE("Treinador empty") {
  Treinador t({});
  CHECK(t.pokemons.empty());
  CHECK_FALSE(t.isVencedor());
  CHECK(t.pokemonsVivos == 0);
  CHECK(t.pokemonsTotal == 0);
}

TEST_CASE("Treinador with pokemons") {
  int pokemonsTotal =
      treinadores[0].pokemonsTotal + treinadores[1].pokemonsTotal;

  CHECK(pokemonsTotal == 5);
}
