#pragma once

#include <ostream>
#include <string>

class Pokemon {
public:
  Pokemon(const Pokemon &) = delete;
  Pokemon(Pokemon &&) = delete;
  Pokemon &operator=(const Pokemon &) = delete;
  Pokemon &operator=(Pokemon &&) = delete;
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
  std::string nome;
  float ataque;
  float defesa;
  float vida;
  std::string tipo;
  std::string superEfetivo;

private:
  float getAtaqueMultiplier(const Pokemon &outro);
  std::string getSuperEfetividade();
};
