#include "Pokemon.h"

#ifndef UTILS_H
#define UTILS_H

Treinador* lerTreinadores(const char nomeArq[]);

void limparTreinadores(Treinador treinadores[2]);

void printTreinadores();

#endif // UTILS_H