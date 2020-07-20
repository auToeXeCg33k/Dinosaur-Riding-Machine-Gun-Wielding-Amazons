#pragma once
#include <string>
#include <vector>

int ReadGameMode() noexcept;

void ProcessInput(std::string_view input, std::vector<std::string>& words) noexcept;