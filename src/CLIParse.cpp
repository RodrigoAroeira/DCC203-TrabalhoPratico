#include "CLIParse.hpp"

#include <getopt.h>

#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>

#include "pokemon.hpp"
#include "trainer.hpp"
#include "utils.hpp"

[[noreturn]] void help(const std::string &filename) {

#define PAD_LEFT std::left << std::setw(25)
  std::cout << "Usage: " << filename << " [OPTION]\n"
            << "Options:\n"
            << PAD_LEFT << "  --help, -h"
            << "Displays this message and exits the program.\n"
            << PAD_LEFT << "  --print, -p"
            << "Prints the trainers and exits the program.\n"
            << PAD_LEFT << "  --custom, -c [file]"
            << "Reads from a .txt file with a name of your choice.\n"
            << PAD_LEFT << "  --example, -e"
            << "Runs the example battle. Works like --custom example.txt\n"
            << PAD_LEFT << "  --instruct, -i "
            << "Prints the program usage instructions and exits the program.\n";
  exit(0);
}

void printTrainers(const std::array<Trainer, 2> &trainers) {
  const std::string colors[] = {"\033[32m", "\033[31m"};

  for (size_t i = 0; i < trainers.size(); ++i) {
    std::cout << colors[i];
    std::cout << "Trainer " << (i + 1) << std::endl;
    const Trainer &trainer = trainers[i];
    for (auto &pokemon : trainer.pokemons) {
      std::cout << "-----------------" << std::endl;
      std::cout << pokemon << std::endl;
      std::cout << "-----------------" << std::endl;
    }
  }

  std::cout << "\033[0m";
}

[[noreturn]] void printInstruct(const std::string &filename) {
  std::locale::global(std::locale(""));

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening the file." << std::endl;
    exit(1);
  }

  std::string buffer;
  while (std::getline(file, buffer)) {
    std::cout << buffer << '\n';
  }

  exit(0);
}

template <size_t size>
std::string generateShortOpts(const std::array<option, size> longOpts) {
  std::string shortOpts;
  for (const option &opt : longOpts) {
    if (!opt.name)
      continue;
    shortOpts += opt.val;
    shortOpts += std::string(opt.has_arg, ':');
  }

  return shortOpts;
}

auto longOpts =
    std::to_array<option>({{"help", no_argument, nullptr, 'h'},
                           {"example", no_argument, nullptr, 'e'},
                           {"custom", required_argument, nullptr, 'c'},
                           {"print", no_argument, nullptr, 'p'},
                           {"instruct", no_argument, nullptr, 'i'},
                           {nullptr, 0, nullptr, 0}});

void parseArgs(int argc, char *argv[]) {
  int opt;
  int optIdx = 0;
  std::string file = "trainers.txt";

  bool printFlag = false, battleFlag = true;
  std::string shortOpts = generateShortOpts(longOpts);

  while ((opt = getopt_long(argc, argv, shortOpts.c_str(), longOpts.data(),
                            &optIdx)) != -1) {
    switch (opt) {
    case 'h':
      help(argv[0]);
      break;
    case 'e':
      file = "example.txt";
      break;
    case 'c':
      file = optarg;
      break;
    case 'p':
      printFlag = true;
      battleFlag = false;
      break;
    case 'i':
      printInstruct("instructions.txt");
      break;
    default:
      help(argv[0]);
      break;
    }
  }

  auto trainers = readTrainers(file);

  if (printFlag)
    printTrainers(trainers);

  if (battleFlag)
    Battle(trainers);
}
