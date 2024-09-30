#include "pokemon.hpp"
#include <string>

// Public Methods

void Pokemon::Atacar(Pokemon &outro) {
  float multiplier = getAtaqueMultiplier(outro);
  float dano = ataque * multiplier - outro.defesa;

  if (dano <= 0)
    dano = 1;

  outro.vida -= dano;
}

std::string Pokemon::getNome() const { return nome; }
float Pokemon::getAtaque() const { return ataque; }
float Pokemon::getDefesa() const { return defesa; }
float Pokemon::getVida() const { return vida; }
std::string Pokemon::getTipo() const { return tipo; }
std::string Pokemon::getSuperEfetivo() const { return superEfetivo; }

// Private Methods

std::string Pokemon::getSuperEfetividade(void) {
  std::string tipos[] = {"eletrico", "agua", "fogo", "gelo", "pedra"};
  std::string contraTipos[] = {"agua", "fogo", "gelo", "pedra", "eletrico"};

  std::string selected;
  for (int i = 0; i < 5; i++) {
    if (tipo == tipos[i])
      return contraTipos[i];
  }
  printf("Tipo '%s' não encontrado, saindo do programa.\n",
         tipo.c_str()); // No caso do tipo não ser encontrado.
  exit(1);
}

float Pokemon::getAtaqueMultiplier(const Pokemon &outro) {
  float multiplier = 1;

  if (this->superEfetivo == outro.superEfetivo)
    multiplier = 1.2;

  if (outro.superEfetivo == this->superEfetivo)
    multiplier = 0.8;

  return multiplier;
}
