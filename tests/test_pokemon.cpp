// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "pokemon.hpp"

TEST_CASE("Pokemon construtor") {
  Pokemon p("Charmander", 1, 1, 1, "water");
  CHECK(p.getName() == "Charmander");
  CHECK(p.getAttack() == 1);
  CHECK(p.getDefense() == 1);
  CHECK(p.getHP() == 1);
  CHECK(p.getType() == "water");
  CHECK(p.getSuperEffective() == "fire");
}

TEST_CASE("Pokemon attack") {
  Pokemon p1("P1", 2, 1, 10, "water");
  Pokemon p2("P2", 1, 5, 4, "fire");

  p1.Attack(p2);
  CHECK(p2.getHP() == 3);
  p2.Attack(p1);

  CHECK(p1.getHP() == 9);
}
