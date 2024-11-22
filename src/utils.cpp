#include "utils.hpp"

#include <array>
#include <fstream>
#include <iostream>
#include <vector>

#include "pokemon.hpp"

static std::vector<Pokemon> getPokemonInfo(std::ifstream &file, size_t size) {

  std::vector<Pokemon> vec;
  vec.reserve(size);

  for (size_t i = 0; i < size; i++) {
    std::string name, type;
    float attack, defense, hp;

    file >> name >> attack >> defense >> hp >> type;

    vec.emplace_back(name, attack, defense, hp, type);
  }
  return vec;
}

std::array<Trainer, 2> readTrainers(const std::string &filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Failed to open the file " << filename << ", please try again."
              << std::endl;
    exit(1);
  }

  int totalPokemons1, totalPokemons2;

  file >> totalPokemons1 >> totalPokemons2;

  std::vector<Pokemon> pokemons1 = getPokemonInfo(file, totalPokemons1);
  std::vector<Pokemon> pokemons2 = getPokemonInfo(file, totalPokemons2);

  Trainer t1(pokemons1);
  Trainer t2(pokemons2);

  return {t1, t2};
}
