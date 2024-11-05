#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN


#include "doctest.h"
#include "utils.hpp"
#include "treinador.hpp"
#include <iostream>

TEST_CASE("Batalha") {
    auto old_buffer = std::cout.rdbuf(nullptr);
    auto treinadores = lerTreinadores("exemplo.txt");
    Batalha(treinadores);
    CHECK(treinadores[0].isVencedor());
    std::cout.rdbuf(old_buffer);
}