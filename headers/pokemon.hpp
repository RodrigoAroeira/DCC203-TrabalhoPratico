#pragma once

#include <ostream>
#include <string>

class Pokemon {
public:
  Pokemon(std::string nome, float ataque, float defesa, float vida,
          std::string tipo)
      : nome(std::move(nome)), ataque(ataque), defesa(defesa), vida(vida),
        tipo(std::move(tipo)), superEfetivo(getSuperEfetividade()) {}

  void Atacar(Pokemon &outro);

  std::string getNome() const;
  float getAtaque() const;
  float getDefesa() const;
  float getVida() const;
  std::string getTipo() const;
  std::string getSuperEfetivo() const;

  friend std::ostream &operator<<(std::ostream &os, const Pokemon &pokemon) {
    os << pokemon.nome + " - " << pokemon.getVida();
    return os;
  }

private:
  const std::string nome;
  const float ataque;
  const float defesa;
  float vida;
  const std::string tipo;
  const std::string superEfetivo;

private:
  float getAtaqueMultiplier(const Pokemon &outro);
  std::string getSuperEfetividade();
};
