#pragma once
#include "command.h"


class Interpreter
{
private:
	std::unordered_map<std::string, commands::command > commands;

public:
	Interpreter() noexcept;
	Interpreter(const Interpreter& other) noexcept = delete;
	Interpreter(Interpreter&& other) noexcept;

	std::string interpret(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};