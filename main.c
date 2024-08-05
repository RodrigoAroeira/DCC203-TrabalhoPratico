#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "CLIParse.h"
#include "Pokemon.h"
#include "utils.h"

extern struct option long_options[];

int main(int argc, char* const* argv)
{
    int opt;
    int opt_index = 0;
    char arquivo[100] = "treinadores.txt";

    bool printFlag = false, batalhaFlag = true;

    while ((opt = getopt_long(argc, argv, "hec:p", long_options, &opt_index)) != -1)
    {
        switch (opt)
        {
        case 'h':
            help(argv[0]);
            break;
        case 'e':
            strcpy(arquivo, "exemplo.txt");
            break;
        case 'c':
            strcpy(arquivo, optarg);
            break;
        case 'p':
            printFlag = true;
            batalhaFlag = false;
            break;
        case 'i':
            printInstruct("instrucoes.txt");
            return 0;
        default:
            break;
        }
    }

    Treinador *treinadores;
    treinadores = lerTreinadores(arquivo);

    if (printFlag)
        printTreinadores(treinadores);

    if (batalhaFlag)
        Batalha(treinadores);

    limparTreinadores(treinadores);
    return 0;
}
