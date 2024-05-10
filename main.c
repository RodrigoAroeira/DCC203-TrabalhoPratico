#include "Pokemon.h"
#include "func.h"

int main(int argc, char const *argv[])
{
    Treinador *treinadores;
    treinadores = lerTreinadores("treinadores.txt");
    Batalha(treinadores);
    limparTreinadores(treinadores);
    return 0;
}
