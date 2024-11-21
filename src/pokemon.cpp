#include "pokemon.hpp"

#include <iostream>
#include <string>

// Public Methods

void Pokemon::Attack(Pokemon &other) const {
  float multiplier = getAttackMultiplier(other);
  float dmg = m_attack * multiplier - other.m_defense;

  if (dmg <= 0)
    dmg = 1;

  other.m_HP -= dmg;
}

std::string Pokemon::getName() const { return m_name; }
float Pokemon::getAttack() const { return m_attack; }
float Pokemon::getDefense() const { return m_defense; }
float Pokemon::getHP() const { return m_HP; }
std::string Pokemon::getType() const { return m_type; }
std::string Pokemon::getSuperEffective() const { return m_superEffective; }

// Private Methods

std::string Pokemon::defineSuperEffective(void) const {
  std::string types[] = {"electric", "water", "fire", "ice", "rock"};
  std::string counterTypes[] = {"water", "fire", "ice", "rock", "electric"};

  for (int i = 0; i < 5; i++) {
    if (m_type == types[i])
      return counterTypes[i];
  }
  std::cerr << "Type '" << m_type << "' not found, leaving program."
            << std::endl;
  exit(1);
}

float Pokemon::getAttackMultiplier(const Pokemon &outro) const {
  float multiplier = 1;

  if (this->m_superEffective == outro.m_type)
    multiplier = 1.2;

  if (outro.m_superEffective == this->m_type)
    multiplier = 0.8;

  return multiplier;
}
