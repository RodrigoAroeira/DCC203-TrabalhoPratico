#include "treinador.hpp"
#include <array>
#include <iostream>

void Treinador::makeVencedor(void) { m_vencedor = true; }
bool Treinador::isVencedor(void) { return m_vencedor; }

void setVencedor(std::array<Treinador, 2> &treinadores) {
  /*Função para facilitar a checagem de pokemons vivos ao final*/
  for (auto &treinador : treinadores) {
    if (treinador.pokemonsVivos != 0)
      treinador.makeVencedor();
  }
}

void printOverview(std::array<Treinador, 2> &treinadores) {

  for (int i = 0; i < treinadores.size(); i++) {
    Treinador &treinador = treinadores[i];

    if (!treinador.isVencedor())
      continue;

    std::cout << "Jogador " << i + 1 << " venceu\n";
    std::cout << "Pokemons sobreviventes:\n";
    for (auto &pokemon : treinador.pokemons) {
      if (pokemon.getVida() > 0) {
        std::cout << pokemon.getNome() + '\n';
      }
    }
  }

  std::cout << "Pokemons derrotados:\n";
  for (auto &treinador : treinadores) {
    for (auto &pokemon : treinador.pokemons) {
      if (pokemon.getVida() <= 0)
        std::cout << pokemon.getNome() << std::endl;
    }
  }
}

void printAll(const std::array<Treinador, 2> &t) {
  for (auto &trein : t) {
    for (auto &pok : trein.pokemons) {
      std::cout << pok << "hp" << std::endl;
    }
  }
}

void Batalha(std::array<Treinador, 2> &treinadores) {
  Treinador &treinador1 = treinadores[0];
  Treinador &treinador2 = treinadores[1];

  int i = 0, j = 0;

  std::cout << "Before: " << std::endl;
  printAll(treinadores);

  while (i < treinador1.pokemonsTotal && j < treinador2.pokemonsTotal) {
    Pokemon &pokemon1 = treinador1.pokemons[i];
    Pokemon &pokemon2 = treinador2.pokemons[j];

    pokemon1.Atacar(pokemon2);
    if (pokemon2.getVida() <= 0) {
      std::cout << pokemon1.getNome() << " venceu " << pokemon2.getNome()
                << std::endl;
      treinador2.pokemonsVivos--;
      j++;
      if (j < treinador2.pokemonsTotal) {
        pokemon2 = treinador2.pokemons[j];
      } else
        break; // Exit if no more Pokémon are left for treinador2
    }

    pokemon2.Atacar(pokemon1);
    if (pokemon1.getVida() <= 0) {
      std::cout << pokemon2.getNome() << " venceu " << pokemon1.getNome()
                << std::endl;
      treinador1.pokemonsVivos--;
      i++;
      if (i < treinador1.pokemonsTotal) {
        pokemon1 = treinador1.pokemons[i];
      } else
        break; // Exit if no more Pokémon are left for treinador1
    }
  }

  // setVencedor(treinadores);
  // printOverview(treinadores);
  std::cout << "After: " << std::endl;
  printAll(treinadores);
}
