#include "Pokemon.h"
#include <string.h>
#include <stdio.h>

float ataqueMultiplier(Pokemon *ataque, Pokemon *defesa)
{
  float multiplier = 1;

  if (strcmp(ataque->SuperEfetivo, defesa->Tipo) == 0)
  {
    multiplier = 1.2;
  }
  if (strcmp(defesa->SuperEfetivo, ataque->Tipo) == 0)
  {
    multiplier = 0.8;
  }
  return multiplier;
}

void Atacar(Pokemon *ataque, Pokemon *defesa)
{
  float multiplier = ataqueMultiplier(ataque, defesa);
  float dano = ataque->Ataque * multiplier - defesa->Defesa;
  if (dano <= 0)
  {
    dano = 1;
  }
  defesa->Vida -= dano;
}

void setVencedor(Treinador treinadores[2])
{
  for (int i = 0; i < 2; i++)
  {
    if (treinadores[i].PokemonsVivos == 0)
    {
      treinadores[i].vencedor = false;
    }
    else
      treinadores[i].vencedor = true;
  }
}

void printOverview(Treinador treinadores[2])
{
  Treinador *treinadorPtr;
  Pokemon *pokemonPtr;
  for (int i = 0; i < 2; i++)
  {
    treinadorPtr = &treinadores[i];
    if (treinadorPtr->vencedor)
    {
      printf("Jogador %d venceu\n", i + 1);
      printf("Pokemons sobreviventes:\n");
      for (int j = 0; j < treinadorPtr->PokemonsTotal; j++)
      {
        pokemonPtr = &treinadorPtr->Pokemons[j];
        if (pokemonPtr->Vida > 0)
        {
          printf("%s\n", pokemonPtr->Nome);
        }
      }
    }
  }

  printf("Pokemons derrotados:\n");
  for (int i = 0; i < 2; i++)
  {
    treinadorPtr = &treinadores[i];
    for (int j = 0; j < treinadorPtr->PokemonsTotal; j++)
    {
      pokemonPtr = &treinadorPtr->Pokemons[j];
      if (pokemonPtr->Vida <= 0)
      {
        printf("%s\n", pokemonPtr->Nome);
      }
    }
  }
}

void Batalha(Treinador treinadores[2])
{
  Treinador *treinador1 = &treinadores[0];
  Treinador *treinador2 = &treinadores[1];

  Pokemon *pokemonPtr1, *pokemonPtr2;

  int i = 0, j = 0;

  while (i < treinador1->PokemonsTotal && j < treinador2->PokemonsTotal)
  {
    pokemonPtr1 = &treinador1->Pokemons[i];
    pokemonPtr2 = &treinador2->Pokemons[j];

    Atacar(pokemonPtr1, pokemonPtr2);

    if (pokemonPtr2->Vida <= 0)
    {
      printf("%s venceu %s\n", pokemonPtr1->Nome, pokemonPtr2->Nome);
      j++;
      treinador2->PokemonsVivos--;
      continue;
    }

    Atacar(pokemonPtr2, pokemonPtr1);
    if (pokemonPtr1->Vida <= 0)
    {
      printf("%s venceu %s\n", pokemonPtr2->Nome, pokemonPtr1->Nome);
      i++;
      treinador1->PokemonsVivos--;
    }
  }
  setVencedor(treinadores);
  printOverview(treinadores);
}