#include <stdlib.h>
#include "Pokemon.h"
#include <stdio.h>
#include <ctype.h>

Treinador *lerTreinadores(const char nomeArq[])
{
  Treinador *treinadores = (Treinador *)malloc(2 * sizeof(Treinador));
  Treinador *treinador1 = &treinadores[0];
  Treinador *treinador2 = &treinadores[1];
  Pokemon *pokemonPtr;

  FILE *arquivoP = fopen(nomeArq, "r");

  if (arquivoP == NULL)
  {
    printf("Falha ao abrir o arquivo, tente novamente.\n");
    exit(1);
  }

  fscanf(arquivoP, "%d %d", &treinador1->PokemonsTotal, &treinador2->PokemonsTotal);

  setupTreinador(treinador1, treinador1->PokemonsTotal);
  setupTreinador(treinador2, treinador2->PokemonsTotal);

  for (int i = 0; i < treinador1->PokemonsTotal; i++)
  {
    pokemonPtr = &treinador1->Pokemons[i];
    getSuperEfetividade(pokemonPtr);
    fscanf(arquivoP, "%s %d %d %d %s", pokemonPtr->Nome, &pokemonPtr->Ataque, &pokemonPtr->Defesa, &pokemonPtr->Vida, pokemonPtr->Tipo);
  }

  for (int i = 0; i < treinador2->PokemonsTotal; i++)
  {
    pokemonPtr = &treinador2->Pokemons[i];
    fscanf(arquivoP, "%s %d %d %d %s", pokemonPtr->Nome, &pokemonPtr->Ataque, &pokemonPtr->Defesa, &pokemonPtr->Vida, pokemonPtr->Tipo);
  }

  fclose(arquivoP);

  return treinadores;
}

int main(int argc, char const *argv[])
{
    Treinador* treinadores = lerTreinadores("treinadores.txt");
    Treinador t1 = treinadores[0];
    for (size_t i = 0; i < t1.PokemonsTotal; i++)
    {
        Pokemon* pP = &t1.Pokemons[i];
        for (int i = 0; pP->Tipo[i] != '\0'; i++)
        {
            pP->Tipo[i] = tolower((int)pP->Tipo);
        }
        

    }
    
    return 0;
}
