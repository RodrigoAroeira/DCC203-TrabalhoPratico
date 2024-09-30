#pragma once

#include "pokemon.hpp"

#include <array>
#include <iostream>
#include <vector>

class Treinador {
public:
  Treinador(std::vector<Pokemon> pokemons)
      : pokemons(pokemons), pokemonsVivos(pokemons.size()),
        pokemonsTotal(pokemons.size()), m_vencedor(false) {}

  void makeVencedor(void);
  bool isVencedor(void);

public:
  std::vector<Pokemon> pokemons;
  int pokemonsVivos;
  int pokemonsTotal;

private:
  bool m_vencedor;
};

void Batalha(std::array<Treinador, 2> &treinadores);
