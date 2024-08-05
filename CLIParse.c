#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "Pokemon.h"
#include "CLIParse.h"

struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"exemplo", no_argument, 0, 'e'},
    {"custom", required_argument, 0, 'c'},
    {"print", no_argument, 0, 'p'},
    {"instruct", no_argument, 0, 'i'},
    {0, 0, 0, 0}
};


void help(const char nomeArquivo[]) {
    printf("Modo de uso: %s [OPTION]\n", nomeArquivo);
    printf("Options:\n");
    printf("  --help                %-30s\n", "Mostra essa mensagem e sai do programa.");
    printf("  --print               %-30s\n", "Imprime os treinadores e sai do programa.");
    printf("  --custom [arquivo]    %-30s\n", "Lê de um arquivo .txt com um nome da sua escolha.");
    printf("  --exemplo             %-30s\n", "Roda a batalha de exemplo. Funciona como --custom exemplo.txt");
    printf("  --instruct            %-30s\n", "Imprime as instruções de uso do programa e sai do programa.");

    exit(0);
}

void printTreinadores(Treinador treinadores[2])
{

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
}

void printInstruct(const char nomeArquivo[]) {
    setlocale(LC_ALL, ""); // Configuração para suportar UTF-8

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) { // Ler linha por linha
        printf("%s", buffer); 
    }

    fclose(arquivo);
}


