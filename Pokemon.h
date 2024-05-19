#pragma once
#include <stdbool.h>


typedef struct
{
  char Nome[100];
  float Ataque;
  float Defesa;
  float Vida;
  char Tipo[20]; 
  char SuperEfetivo[20];
} Pokemon;

typedef struct
{
  Pokemon *Pokemons;
  int PokemonsTotal;
  int PokemonsVivos;
  bool vencedor;
} Treinador;

void Atacar(Pokemon *pokemon1, Pokemon *pokemon2);

void Batalha(Treinador treinadores[2]);
