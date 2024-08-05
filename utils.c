#include "Pokemon.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void setupTreinador(Treinador *treinadorPtr, int qtdPokemons)
{
  if (qtdPokemons <= 0 || qtdPokemons > 100)
  {
    printf("Quantidade de Pokemons '%d' inválida, tente novamente.\n", qtdPokemons);
    exit(1);
  }

  treinadorPtr->PokemonsTotal = qtdPokemons;
  treinadorPtr->PokemonsVivos = qtdPokemons;
  treinadorPtr->Pokemons = (Pokemon *)malloc(qtdPokemons * sizeof(Pokemon));
  treinadorPtr->vencedor = false;
}

void getSuperEfetividade(Pokemon *pokemon)
{
  char *tipo = pokemon->Tipo;

  char *tipos[5] = {"eletrico", "agua", "fogo", "gelo", "pedra"};
  char *contraTipos[5] = {"agua", "fogo", "gelo", "pedra", "eletrico"};
  for (int i = 0; i < 5; i++)
  {
    if (strcmp(tipo, tipos[i]) == 0)
    {
      strcpy(pokemon->SuperEfetivo, contraTipos[i]);
      return;
    }
  }
  printf("Tipo '%s' não encontrado, saindo do programa.\n", tipo); // No caso do tipo não ser encontrado.
  exit(1);
}

Treinador *lerTreinadores(const char nomeArq[])
{
  Treinador *treinadores = (Treinador *)malloc(2 * sizeof(Treinador));
  Treinador *treinador1 = &treinadores[0];
  Treinador *treinador2 = &treinadores[1];
  Pokemon *pokemonPtr;

  FILE *arquivoP = fopen(nomeArq, "r");

  if (arquivoP == NULL)
  {
    printf("Falha ao abrir o arquivo '%s', tente novamente.\n", nomeArq);
    exit(1);
  }

  fscanf(arquivoP, "%d %d", &treinador1->PokemonsTotal, &treinador2->PokemonsTotal);

  setupTreinador(treinador1, treinador1->PokemonsTotal);
  setupTreinador(treinador2, treinador2->PokemonsTotal);

  for (int i = 0; i < treinador1->PokemonsTotal; i++)
  {
    pokemonPtr = &treinador1->Pokemons[i];
    fscanf(arquivoP, "%s %f %f %f %s", pokemonPtr->Nome, &pokemonPtr->Ataque, &pokemonPtr->Defesa, &pokemonPtr->Vida, pokemonPtr->Tipo);
    getSuperEfetividade(pokemonPtr);
  }

  for (int i = 0; i < treinador2->PokemonsTotal; i++)
  {
    pokemonPtr = &treinador2->Pokemons[i];
    fscanf(arquivoP, "%s %f %f %f %s", pokemonPtr->Nome, &pokemonPtr->Ataque, &pokemonPtr->Defesa, &pokemonPtr->Vida, pokemonPtr->Tipo);
    getSuperEfetividade(pokemonPtr);
  }

  fclose(arquivoP);

  return treinadores;
}

void limparTreinadores(Treinador treinadores[2])
{
  for (int i = 0; i < 2; i++)
  {
    free(treinadores[i].Pokemons);
  }
  free(treinadores);
}

