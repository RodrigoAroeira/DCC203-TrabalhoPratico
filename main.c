#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "CLIParse.h"
#include "Pokemon.h"
#include "utils.h"




static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"exemplo", no_argument, 0, 'e'},
    {"custom", required_argument, 0, 'c'},
    {"print", no_argument, 0, 'p'},
    {0, 0, 0, 0}
};




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
