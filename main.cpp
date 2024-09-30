#include <getopt.h>
#include <string>

#include "CLIParse.hpp"
#include "treinador.hpp"
#include "utils.hpp"

extern struct option long_options[];

int main(int argc, char *argv[]) {

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
      return 0;
    default:
      break;
    }
  }

  auto treinadores = lerTreinadores(arquivo);

  if (printFlag)
    printTreinadores(treinadores);

  if (batalhaFlag)
    Batalha(treinadores);

  return 0;
}
