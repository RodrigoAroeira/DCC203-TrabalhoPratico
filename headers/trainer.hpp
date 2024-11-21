#pragma once

#include <array>
#include <cstddef>
#include <vector>

#include "pokemon.hpp"

class Trainer {
public:
  Trainer(const std::vector<Pokemon> &pokemons)
      : pokemons(std::move(pokemons)), alivePokemon(pokemons.size()),
        totalPokemon(pokemons.size()), m_winner(false) {}

  void makeWinner(void) { m_winner = true; }
  bool isWinner(void) { return m_winner; }

public:
  std::vector<Pokemon> pokemons;
  size_t alivePokemon;
  size_t totalPokemon;

private:
  bool m_winner;
};

void Battle(std::array<Trainer, 2> &trainers);
