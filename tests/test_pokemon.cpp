// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "pokemon.hpp"

TEST_CASE("Pokemon construtor") {
  Pokemon p("Charmander", 1, 1, 1, "agua");
  CHECK(p.getNome() == "Charmander");
  CHECK(p.getAtaque() == 1);
  CHECK(p.getDefesa() == 1);
  CHECK(p.getVida() == 1);
  CHECK(p.getTipo() == "agua");
  CHECK(p.getSuperEfetivo() == "fogo");
}

TEST_CASE("Pokemon atacar") {
  Pokemon p1("P1", 2, 1, 10, "agua");
  Pokemon p2("P2", 1, 5, 4, "fogo");

  p1.Atacar(p2);
  CHECK(p2.getVida() == 3);
  p2.Atacar(p1);

  CHECK(p1.getVida() == 9);
}
