#include "interpreter.h"

using namespace std;


Interpreter::Interpreter() noexcept
{
	commands.emplace("new", commands::New);
	commands.emplace("select", commands::Select);
	commands.emplace("move", commands::Move);
	commands.emplace("help", commands::Help);
	commands.emplace("attack", commands::Attack);
	commands.emplace("lookaround", commands::Lookaround);
	commands.emplace("pickup", commands::Pickup);
	commands.emplace("drop", commands::Drop);
	commands.emplace("equip", commands::Equip);
	commands.emplace("end", commands::End);
	commands.emplace("tame", commands::Tame);
	commands.emplace("geton", commands::Geton);
	commands.emplace("getoff", commands::Getoff);
}


Interpreter::Interpreter(Interpreter&& other) noexcept : commands(move(other.commands)) {}


string Interpreter::interpret(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (commands.find(v.at(0)) == commands.end())
		return "Invalid command.\n";

	return commands.at(v.at(0))(v, map, data);
}