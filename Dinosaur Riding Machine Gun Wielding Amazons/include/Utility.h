#pragma once

#include <string>
#include <vector>

#include "GameData.h"

int ReadGameMode() noexcept;

int CheckWin(GameData& data) noexcept;

std::string toLower(const std::string& input) noexcept;

void ProcessInput(const std::string& input, std::vector<std::string>& words) noexcept;
