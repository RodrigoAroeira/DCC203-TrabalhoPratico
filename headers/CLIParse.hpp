#pragma once

#include "treinador.hpp"
#include <array>
#include <string>

void help(const std::string nomeArquivo);

void printTreinadores(const std::array<Treinador, 2> &treinadores);

void printInstruct(const std::string nomeArquivo);
