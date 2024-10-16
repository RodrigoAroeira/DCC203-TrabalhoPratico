#include "utils.hpp"
#include "pokemon.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<Pokemon> getPokemonInfo(std::ifstream &arq, size_t size) {

  std::vector<Pokemon> vec;
  vec.reserve(size);

  for (size_t i = 0; i < size; i++) {
    std::string nome, tipo;
    float ataque, defesa, vida;

    arq >> nome >> ataque >> defesa >> vida >> tipo;

    vec.emplace_back(nome, ataque, defesa, vida, tipo);
  }
  return vec;
}

std::array<Treinador, 2> lerTreinadores(const std::string nomeArq) {
  std::ifstream arquivo(nomeArq);

  if (!arquivo.is_open()) {
    std::cerr << "Falha ao abrir o arquivo " << nomeArq << ", tente novamente."
              << std::endl;
    exit(1);
  }

  int totalPokemons1, totalPokemons2;

  arquivo >> totalPokemons1 >> totalPokemons2;

  std::vector<Pokemon> pokemons1 = getPokemonInfo(arquivo, totalPokemons1);
  std::vector<Pokemon> pokemons2 = getPokemonInfo(arquivo, totalPokemons2);

  Treinador t1(pokemons1);
  Treinador t2(pokemons2);

  return {t1, t2};
}
