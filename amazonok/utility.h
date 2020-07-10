#pragma once
#include <string>
#include <vector>

int ReadGameMode();

void ProcessInput(std::string_view input, std::vector<std::string>& words);