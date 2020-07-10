#pragma once
#include "command.h"


class Interpreter
{
private:
	std::unordered_map<std::string, const std::unique_ptr<const Command>> commands;

public:
	Interpreter();
	std::string interpret(const std::vector<std::string>& vec, Map& map, GameData& data) const noexcept;
};