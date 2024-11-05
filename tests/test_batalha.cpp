#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "treinador.hpp"
#include "utils.hpp"
#include <iostream>

TEST_CASE("Batalha") {
  auto old_buffer = std::cout.rdbuf(nullptr);
  auto treinadores = lerTreinadores("exemplo.txt");
  Batalha(treinadores);
  CHECK(treinadores[0].isVencedor());
  std::cout.rdbuf(old_buffer);

  for (auto &treinador : treinadores) {
    if (treinador.isVencedor()) {
      CHECK(std::all_of(
          treinador.pokemons.begin(), treinador.pokemons.end(),
          [](const Pokemon &pokemon) { return pokemon.getVida() >= 0; }));
      CHECK(treinador.pokemonsVivos > 0);
    } else {
      CHECK(treinador.pokemonsVivos == 0);
      CHECK(std::all_of(
          treinador.pokemons.begin(), treinador.pokemons.end(),
          [](const Pokemon &pokemon) { return pokemon.getVida() == 0; }));

      for (auto &pokemon : treinador.pokemons)
        CHECK(pokemon.getVida() <= 0);
    }
  }
}
