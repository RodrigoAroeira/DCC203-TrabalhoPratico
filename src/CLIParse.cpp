#include "pokemon.hpp"
#include "treinador.hpp"
#include <array>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <locale>
#include <string>

struct option long_options[] = {{"help", no_argument, nullptr, 'h'},
                                {"exemplo", no_argument, nullptr, 'e'},
                                {"custom", required_argument, nullptr, 'c'},
                                {"print", no_argument, nullptr, 'p'},
                                {"instruct", no_argument, nullptr, 'i'},
                                {nullptr, 0, nullptr, 0}};

void help(const std::string nomeArquivo) {
  std::cout << "Modo de uso: " << nomeArquivo << " [OPTION]\n";
  std::cout << "Options:\n";
  std::cout << "  --help                "
            << "Mostra essa mensagem e sai do programa.\n";
  std::cout << "  --print               "
            << "Imprime os treinadores e sai do programa.\n";
  std::cout << "  --custom [arquivo]    "
            << "Lê de um arquivo .txt com um nome da sua escolha.\n";
  std::cout
      << "  --exemplo             "
      << "Roda a batalha de exemplo. Funciona como --custom exemplo.txt\n";
  std::cout << "  --instruct            "
            << "Imprime as instruções de uso do programa e sai do programa.\n";

  exit(0);
}

void printTreinadores(const std::array<Treinador, 2> &treinadores) {
  const std::string colors[] = {"\033[32m", "\033[31m"};

  for (size_t i = 0; i < treinadores.size(); ++i) {
    std::cout << colors[i];
    std::cout << "Treinador " << (i + 1) << "\n";
    const Treinador &treinador = treinadores[i];
    for (auto &pokemon : treinador.pokemons) {
      std::cout << "-----------------\n";
      std::cout << "Nome: " << pokemon.getNome() << "\n";
      std::cout << "Ataque: " << pokemon.getAtaque() << "\n";
      std::cout << "Defesa: " << pokemon.getDefesa() << "\n";
      std::cout << "Vida: " << pokemon.getVida() << "\n";
      std::cout << "Tipo: " << pokemon.getTipo() << "\n";
      std::cout << "Super Efetivo contra: " << pokemon.getSuperEfetivo()
                << "\n";
      std::cout << "-----------------" << std::endl;
    }
  }

  std::cout << "\033[0m";
}

void printInstruct(const std::string nomeArquivo) {
  std::locale::global(std::locale("")); // Configuração para suportar UTF-8

  std::ifstream arquivo(nomeArquivo);
  if (!arquivo.is_open()) {
    perror("Erro ao abrir o arquivo");
    exit(1);
  }

  std::string buffer;
  while (std::getline(arquivo, buffer)) { // Ler linha por linha
    std::cout << buffer << '\n';
  }

  arquivo.close();
}

void parseArgs() {}
