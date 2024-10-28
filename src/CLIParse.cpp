#include <array>
#include <fstream>
#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>

#include "pokemon.hpp"
#include "treinador.hpp"
#include "utils.hpp"

struct option long_options[] = {{"help", no_argument, nullptr, 'h'},
                                {"exemplo", no_argument, nullptr, 'e'},
                                {"custom", required_argument, nullptr, 'c'},
                                {"print", no_argument, nullptr, 'p'},
                                {"instruct", no_argument, nullptr, 'i'},
                                {nullptr, 0, nullptr, 0}};

void help(const std::string nomeArquivo) {
  std::cout << "Modo de uso: " << nomeArquivo << " [OPTION]\n"
            << "Options:\n"
            << std::left << std::setw(25) << "  --help"
            << "Mostra essa mensagem e sai do programa.\n"
            << std::left << std::setw(25) << "  --print"
            << "Imprime os treinadores e sai do programa.\n"
            << std::left << std::setw(25) << "  --custom [arquivo]"
            << "Lê de um arquivo .txt com um nome da sua escolha.\n"
            << std::left << std::setw(25) << "  --exemplo"
            << "Roda a batalha de exemplo. Funciona como --custom exemplo.txt\n"
            << std::left << std::setw(25) << "  --instruct"
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
      std::cout << pokemon << std::endl;
      std::cout << "-----------------" << std::endl;
    }
  }

  std::cout << "\033[0m";
}

void printInstruct(const std::string nomeArquivo) {
  std::locale::global(std::locale(""));

  std::ifstream arquivo(nomeArquivo);
  if (!arquivo.is_open()) {
    perror("Erro ao abrir o arquivo");
    exit(1);
  }

  std::string buffer;
  while (std::getline(arquivo, buffer)) {
    std::cout << buffer << '\n';
  }

  arquivo.close();
}

void parseArgs(int argc, char *argv[]) {
  int opt;
  int opt_index = 0;
  std::string arquivo = "treinadores.txt";

  bool printFlag = false, batalhaFlag = true;

  while ((opt = getopt_long(argc, argv, "hec:p", long_options, &opt_index)) !=
         -1) {
    switch (opt) {
    case 'h':
      help(argv[0]);
      break;
    case 'e':
      arquivo = "exemplo.txt";
      break;
    case 'c':
      arquivo = optarg;
      break;
    case 'p':
      printFlag = true;
      batalhaFlag = false;
      break;
    case 'i':
      printInstruct("instrucoes.txt");
      return;
    default:
      break;
    }
  }

  auto treinadores = lerTreinadores(arquivo);

  if (printFlag)
    printTreinadores(treinadores);

  if (batalhaFlag)
    Batalha(treinadores);
}
