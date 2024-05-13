#include "Pokemon.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void setupTreinador(Treinador *treinadorPtr, int qtdPokemons)
{
  treinadorPtr->PokemonsTotal = qtdPokemons;
  treinadorPtr->PokemonsVivos = qtdPokemons;
  treinadorPtr->Pokemons = (Pokemon *)malloc(qtdPokemons * sizeof(Pokemon));
  treinadorPtr->vencedor = false;
}

void getSuperEfetividade(Pokemon *pokemon)
{
  char *tipo = pokemon->Tipo;
  
  char *tipos[5] = {"elétrico", "água", "fogo", "gelo", "pedra"};
  char *contraTipos[5] = {"água", "fogo", "gelo", "pedra", "elétrico"};
  char super[20];
  for (int i = 0; i < 5; i++)
  {
    if (strcmp(tipo, tipos[i]) == 0)
    {
      strcpy(super, contraTipos[i]);
    }
  }
  memcpy(pokemon->SuperEfetivo, super, sizeof(super));
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

int main1(int argc, char *argv[])
{
  Treinador *treinadores;
  treinadores = lerTreinadores("treinadores.txt");
  if (treinadores == NULL)
  {
    printf("Falha ao ler treinadores.\n");
    exit(1);
  }

  for (int i = 0; i < 2; i++)
  {
    printf("Treinador %d\n", i + 1);
    Treinador *treinador = &treinadores[i];
    for (size_t i = 0; i < treinador->PokemonsTotal; i++)
    {
      Pokemon *pokemon = &treinador->Pokemons[i];
      puts("-----------------");
      printf("Nome: %s\n", pokemon->Nome);
      printf("Ataque: %f\n", pokemon->Ataque);
      printf("Defesa: %f\n", pokemon->Defesa);
      printf("Vida: %f\n", pokemon->Vida);
      printf("Tipo: %s\n", pokemon->Tipo);
      printf("Super Efetivo contra: %s\n", pokemon->SuperEfetivo);
      puts("-----------------");
    }
  }

  limparTreinadores(treinadores);
  return EXIT_SUCCESS;
}
