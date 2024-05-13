#include "Pokemon.h"
#include <string.h>
#include <stdio.h>

float ataqueMultiplier(Pokemon *ataque, Pokemon *defesa)
{
  float multiplier = 1;
  // Primeiro checar casos que o ataque é super efetivo
  // Os elementos são {eletrico, agua, fogo, gelo, pedra}
  // Eletrico ganha de agua, agua ganha de fogo, fogo ganha de gelo, gelo ganha de pedra, pedra ganha de eletrico
  // Multiplicador de efetividade é 1.2 e de nao efetividade é 0.8

  if(strcmp(ataque->SuperEfetivo, defesa->Tipo) == 0)
    multiplier = 1.2;
  
  if(strcmp(defesa->SuperEfetivo, ataque->Tipo) == 0)
    multiplier = 0.8;

  // Efetividade efetividades[] = {
  //     {"eletrico", "agua", "pedra"},
  //     {"agua", "fogo", "eletrico"},
  //     {"fogo", "gelo", "agua"},
  //     {"gelo", "pedra", "fogo"},
  //     {"pedra", "eletrico", "gelo"}};

  // for (int i = 0; i < sizeof(efetividades) / sizeof(efetividades[0]); i++)
  // {
  //   {
  //     if (strcmp(ataque->Tipo, efetividades[i].tipo) == 0)
  //     {
  //       if (strcmp(defesa->Tipo, efetividades[i].fraqueza) == 0)
  //       {
  //         multiplier = 1.2;
  //       }
  //       else if (strcmp(defesa->Tipo, efetividades[i].resistencia) == 0)
  //       {
  //         multiplier = 0.8;
  //       }
  //     }
  //   }
  // }

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

int acharVencedor(Treinador *treinador1, Treinador *treinador2)
{
  int vencedor;
  if (treinador1->PokemonsVivos == 0)
  {
    treinador2->vencedor = true;
    vencedor = 2;
  }
  else if (treinador2->PokemonsVivos == 0)
  {
    treinador1->vencedor = true;
    vencedor = 1;
  }
  return vencedor;
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
  for (int i = 0; i < 2; i++)
  {
    if (treinadores[i].vencedor)
    {
      printf("Jogador %d venceu\n", i + 1);
      printf("Pokemons sobreviventes:\n");
      for (int j = 0; j < treinadores[i].PokemonsTotal; j++)
      {
        if (treinadores[i].Pokemons[j].Vida > 0)
        {
          printf("%s\n", treinadores[i].Pokemons[j].Nome);
        }
      }
    }
  }
  printf("Pokemons derrotados:\n");
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < treinadores[i].PokemonsTotal; j++)
    {
      if (treinadores[i].Pokemons[j].Vida <= 0)
      {
        printf("%s\n", treinadores[i].Pokemons[j].Nome);
      }
    }
  }
}

void Batalha(Treinador treinadores[2])
{
  // Nº de pokemons não necessariamente é igual
  Treinador *treinador1 = &treinadores[0];
  Treinador *treinador2 = &treinadores[1];
  Treinador *vencedorT;

  Pokemon *pokemonPtr1, *pokemonPtr2;

  int vencedorI, i = 0, j = 0;

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
    if (treinador2->Pokemons[j].Vida <= 0)
    {
      printf("%s venceu %s\n", treinador1->Pokemons[i].Nome, treinador2->Pokemons[j].Nome);
      j++;
      treinador2->PokemonsVivos--;
    }
  }

  vencedorI = acharVencedor(treinador1, treinador2);
  vencedorT = vencedorI == 1 ? treinador1 : treinador2;

  printf("Jogador %d venceu\n", vencedorI);
  printSobreviventes(vencedorT);
  printDerrotados(treinadores);
}