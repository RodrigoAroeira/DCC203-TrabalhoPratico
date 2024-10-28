#include "pokemon.hpp"
#include <string>

// Public Methods

void Pokemon::Atacar(Pokemon &outro) const {
  float multiplier = getAtaqueMultiplier(outro);
  float dano = m_ataque * multiplier - outro.m_defesa;

  if (dano <= 0)
    dano = 1;

  outro.m_vida -= dano;
}

std::string Pokemon::getNome() const { return m_nome; }
float Pokemon::getAtaque() const { return m_ataque; }
float Pokemon::getDefesa() const { return m_defesa; }
float Pokemon::getVida() const { return m_vida; }
std::string Pokemon::getTipo() const { return m_tipo; }
std::string Pokemon::getSuperEfetivo() const { return m_superEfetivo; }

// Private Methods

std::string Pokemon::getSuperEfetividade(void) const {
  std::string tipos[] = {"eletrico", "agua", "fogo", "gelo", "pedra"};
  std::string contraTipos[] = {"agua", "fogo", "gelo", "pedra", "eletrico"};

  std::string selected;
  for (int i = 0; i < 5; i++) {
    if (m_tipo == tipos[i])
      return contraTipos[i];
  }
  printf("Tipo '%s' não encontrado, saindo do programa.\n",
         m_tipo.c_str()); // No caso do tipo não ser encontrado.
  exit(1);
}

float Pokemon::getAtaqueMultiplier(const Pokemon &outro) const {
  float multiplier = 1;

  if (this->m_superEfetivo == outro.m_tipo)
    multiplier = 1.2;

  if (outro.m_superEfetivo == this->m_tipo)
    multiplier = 0.8;

  return multiplier;
}
