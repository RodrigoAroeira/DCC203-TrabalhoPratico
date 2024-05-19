#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CLIParse.h"

void help(const char progname[]) {
    printf("Modo de uso: %s [OPTION] [FILE]\n", progname);
    printf("Options:\n");
    printf("  --help                %-30s\n", "Mostra essa mensagem e sai do programa.");
    printf("  --print               %-30s\n", "Imprime os treinadores e sai do programa.");
    printf("  --custom [arquivo]    %-30s\n", "Lê de um arquivo .txt com um nome da sua escolha.");
    printf("  --exemplo             %-30s\n", "Roda a batalha de exemplo");
    
    exit(0);
}


