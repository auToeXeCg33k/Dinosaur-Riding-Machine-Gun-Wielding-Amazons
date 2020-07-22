#pragma once
#include <string>
#include <vector>

std::string toLower(std::string_view input) noexcept;

int ReadGameMode() noexcept;

void ProcessInput(std::string_view input, std::vector<std::string>& words) noexcept;