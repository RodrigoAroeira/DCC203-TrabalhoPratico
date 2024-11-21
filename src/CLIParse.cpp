#include <array>
#include <fstream>
#include <getopt.h>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>

#include "CLIParse.hpp"
#include "pokemon.hpp"
#include "treinador.hpp"
#include "utils.hpp"

template <size_t size>
std::string createShortOpts(const std::array<option, size> long_options) {
  std::string shortOpts;
  for (const option &opt : long_options) {
    if (!opt.name)
      continue;
    shortOpts += opt.val;
    shortOpts += std::string(opt.has_arg, ':');
  }

  return shortOpts;
}

[[noreturn]] void help(const std::string &nomeArquivo) {
  std::cout << "Modo de uso: " << nomeArquivo << " [OPTION]\n"
            << "Options:\n"
            << std::left << std::setw(25) << "  --help, -h"
            << "Mostra essa mensagem e sai do programa.\n"
            << std::left << std::setw(25) << "  --print, -p"
            << "Imprime os treinadores e sai do programa.\n"
            << std::left << std::setw(25) << "  --custom, -c [arquivo]"
            << "Lê de um arquivo .txt com um nome da sua escolha.\n"
            << std::left << std::setw(25) << "  --exemplo, -e"
            << "Roda a batalha de exemplo. Funciona como --custom exemplo.txt\n"
            << std::left << std::setw(25) << "  --instruct, -i "
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

[[noreturn]] void printInstruct(const std::string &nomeArquivo) {
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

  exit(0);
}

auto long_options =
    std::to_array<option>({{"help", no_argument, nullptr, 'h'},
                           {"exemplo", no_argument, nullptr, 'e'},
                           {"custom", required_argument, nullptr, 'c'},
                           {"print", no_argument, nullptr, 'p'},
                           {"instruct", no_argument, nullptr, 'i'},
                           {nullptr, 0, nullptr, 0}});

void parseArgs(int argc, char *argv[]) {
  int opt;
  int opt_index = 0;
  std::string arquivo = "treinadores.txt";

  bool printFlag = false, batalhaFlag = true;
  std::string shortOpts = createShortOpts(long_options);

  while ((opt = getopt_long(argc, argv, shortOpts.c_str(), long_options.data(),
                            &opt_index)) != -1) {
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
      break;
    default:
      help(argv[0]);
      break;
    }
  }

  auto treinadores = lerTreinadores(arquivo);

  if (printFlag)
    printTreinadores(treinadores);

  if (batalhaFlag)
    Batalha(treinadores);
}
