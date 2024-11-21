#pragma once

#include <array>
#include <string>

#include "trainer.hpp"

std::array<Trainer, 2> readTrainers(const std::string &filename);
