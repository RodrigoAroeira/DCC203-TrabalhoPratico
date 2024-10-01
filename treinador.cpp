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

void processarAtaque(Pokemon *atacante, Pokemon *defesa, int &indiceDefesa,
                     Treinador &treinadorDefesa) {

  atacante->Atacar(*defesa);

  if (defesa->getVida() <= 0) {
    std::cout << atacante->getNome() << " venceu " << defesa->getNome()
              << std::endl;
    treinadorDefesa.pokemonsVivos--;
    indiceDefesa++;
    if (indiceDefesa < treinadorDefesa.pokemonsTotal)
      defesa = &(treinadorDefesa.pokemons[indiceDefesa]);
  }
}

void Batalha(std::array<Treinador, 2> &treinadores) {
  Treinador &treinador1 = treinadores[0];
  Treinador &treinador2 = treinadores[1];

  int i = 0, j = 0;

  while (true) {
    Pokemon *pokemon1 = &treinador1.pokemons[i];
    Pokemon *pokemon2 = &treinador2.pokemons[j];

    processarAtaque(pokemon1, pokemon2, j, treinador2);

    if (j >= treinador2.pokemonsTotal)
      break; // Exit if no more Pokémon are left for treinador2

    processarAtaque(pokemon2, pokemon1, i, treinador1);
    if (i >= treinador1.pokemonsTotal)
      break; // Exit if no more Pokémon are left for treinador1
  }
  setVencedor(treinadores);
  printOverview(treinadores);
}
