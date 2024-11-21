#pragma once

#include <ostream>
#include <string>

class Pokemon {
public:
  Pokemon(const std::string &name, float attack, float defense, float hp,
          const std::string &type)
      : m_name(std::move(name)), m_attack(attack), m_defense(defense), m_HP(hp),
        m_type(std::move(type)), m_superEffective(getSuperEffective()) {}

  void Attack(Pokemon &outro) const;

  std::string getName() const;
  float getAttack() const;
  float getDefense() const;
  float getHP() const;
  std::string getType() const;
  std::string getSuperEffective() const;

  friend std::ostream &operator<<(std::ostream &os, const Pokemon &pokemon) {
    os << "Name: " << pokemon.getName() << "\n";
    os << "Attack: " << pokemon.getAttack() << "\n";
    os << "Defense: " << pokemon.getDefense() << "\n";
    os << "HP: " << pokemon.getHP() << "\n";
    os << "Type: " << pokemon.getType() << "\n";
    os << "Super Effective against: " << pokemon.getSuperEffective();
    return os;
  }

private:
  const std::string m_name;
  const float m_attack;
  const float m_defense;
  float m_HP;
  const std::string m_type;
  const std::string m_superEffective;

private:
  float getAttackMultiplier(const Pokemon &outro) const;
  std::string defineSuperEffective() const;
};
