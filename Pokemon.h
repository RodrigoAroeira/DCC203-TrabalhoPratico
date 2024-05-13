#include <stdbool.h>

#ifndef POKEMON_H
#define POKEMON_H

typedef struct {
  char Nome[100];
  float Ataque;
  float Defesa;
  float Vida;
  char Tipo[7]; // Maior palavra deveria ser Elétrico
  char SuperEfetivo[7];
} Pokemon;


typedef struct {
  Pokemon* Pokemons;
  int PokemonsTotal;
  int PokemonsVivos;
  bool vencedor;
} Treinador;

void Atacar(Pokemon *pokemon1, Pokemon *pokemon2);

void Batalha(Treinador treinadores[2]);

#endif // POKEMON_H