#pragma once

#include <ostream>
#include <string>

class Pokemon {
public:
  Pokemon(const std::string &nome, float ataque, float defesa, float vida,
          const std::string &tipo)
      : m_nome(std::move(nome)), m_ataque(ataque), m_defesa(defesa),
        m_vida(vida), m_tipo(std::move(tipo)),
        m_superEfetivo(getSuperEfetividade()) {}

  void Atacar(Pokemon &outro) const;

  std::string getNome() const;
  float getAtaque() const;
  float getDefesa() const;
  float getVida() const;
  std::string getTipo() const;
  std::string getSuperEfetivo() const;

  inline friend std::ostream &operator<<(std::ostream &os,
                                         const Pokemon &pokemon) {
    os << "Nome: " << pokemon.getNome() << "\n";
    os << "Ataque: " << pokemon.getAtaque() << "\n";
    os << "Defesa: " << pokemon.getDefesa() << "\n";
    os << "Vida: " << pokemon.getVida() << "\n";
    os << "Tipo: " << pokemon.getTipo() << "\n";
    os << "Super Efetivo contra: " << pokemon.getSuperEfetivo();
    return os;
  }

private:
  const std::string m_nome;
  const float m_ataque;
  const float m_defesa;
  float m_vida;
  const std::string m_tipo;
  const std::string m_superEfetivo;

private:
  float getAtaqueMultiplier(const Pokemon &outro) const;
  std::string getSuperEfetividade() const;
};
