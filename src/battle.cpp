#include <array>
#include <iostream>

#include "trainer.hpp"

static void setWinner(std::array<Trainer, 2> &trainers) {
  /*Facilitates checks by the end*/
  for (auto &trainer : trainers) {
    if (trainer.alivePokemon != 0)
      trainer.makeWinner();
  }
}

static void printWinner(const Trainer &trainer, int idx) {
  std::cout << "Player " << idx + 1 << " won\n";
  std::cout << "Surviving pokemon:\n";
  for (const auto &pokemon : trainer.pokemons) {
    if (pokemon.getHP() > 0) {
      std::cout << pokemon.getName() << '\n';
    }
  }
}

static void printDefeatedPokemon(const std::array<Trainer, 2> &trainers) {
  std::cout << "Defeated pokemon:\n";
  for (const auto &trainer : trainers)
    for (const auto &pokemon : trainer.pokemons)

      if (pokemon.getHP() <= 0)
        std::cout << pokemon.getName() << std::endl;
}

static void printOverview(std::array<Trainer, 2> &trainers) {
  for (int i = 0; i < trainers.size(); i++) {
    Trainer &treinador = trainers[i];
    if (treinador.isWinner()) {
      printWinner(treinador, i);
    }
  }
  printDefeatedPokemon(trainers);
}

static void processAttack(Pokemon *attacker, Pokemon *defender,
                          int &defenderIdx, Trainer &defenderTrainer) {

  attacker->Attack(*defender);

  if (defender->getHP() <= 0) {
    std::cout << attacker->getName() << " won " << defender->getName()
              << std::endl;
    defenderTrainer.alivePokemon--;
    defenderIdx++;
    if (defenderIdx < defenderTrainer.totalPokemon)
      defender = &(defenderTrainer.pokemons[defenderIdx]);
  }
}

void Battle(std::array<Trainer, 2> &trainers) {
  Trainer &trainer1 = trainers[0];
  Trainer &trainer2 = trainers[1];

  int i = 0, j = 0;

  while (true) {
    Pokemon *pokemon1 = &trainer1.pokemons[i];
    Pokemon *pokemon2 = &trainer2.pokemons[j];

    processAttack(pokemon1, pokemon2, j, trainer2);

    if (j >= trainer2.totalPokemon)
      break; // Exit if no more Pokémon are left for treinador2

    processAttack(pokemon2, pokemon1, i, trainer1);
    if (i >= trainer1.totalPokemon)
      break; // Exit if no more Pokémon are left for treinador1
  }
  setWinner(trainers);
  printOverview(trainers);
}
