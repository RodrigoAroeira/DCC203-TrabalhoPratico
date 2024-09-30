#include "utils.hpp"
#include "pokemon.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

void getPokemonInfo(std::ifstream &arq, int maxRange,
                    std::vector<Pokemon> &targetVec) {

  for (int i = 0; i < maxRange; i++) {
    std::string nome, tipo;
    float ataque, defesa, vida;

    arq >> nome >> ataque >> defesa >> vida >> tipo;

    Pokemon pokemon(nome, ataque, defesa, vida, tipo);
    targetVec.push_back(pokemon);
  }
}

std::array<Treinador, 2> lerTreinadores(const std::string nomeArq) {
  std::ifstream arquivo(nomeArq);

  if (!arquivo.is_open()) {
    std::cerr << "Falha ao abrir o arqivo " << nomeArq << ", tente novamente."
              << std::endl;
    exit(1);
  }

  int totalPokemons1, totalPokemons2;

  arquivo >> totalPokemons1 >> totalPokemons2;
  std::vector<Pokemon> pokemons1, pokemons2;

  getPokemonInfo(arquivo, totalPokemons1, pokemons1);
  getPokemonInfo(arquivo, totalPokemons2, pokemons2);

  Treinador t1(pokemons1);
  Treinador t2(pokemons2);

  return {t1, t2};
}
