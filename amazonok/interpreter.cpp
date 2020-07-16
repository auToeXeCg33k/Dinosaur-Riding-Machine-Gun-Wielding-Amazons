#include "interpreter.h"

using namespace std;


Interpreter::Interpreter()
{
	commands.emplace("new", make_unique<const New>());
	commands.emplace("select", make_unique<const Select>());
	commands.emplace("move", make_unique<const Move>());
	commands.emplace("help", make_unique<const Help>());
	commands.emplace("attack", make_unique<const Attack>());
	commands.emplace("lookaround", make_unique<const Lookaround>());
	commands.emplace("pickup", make_unique<const Pickup>());
	commands.emplace("drop", make_unique<const Drop>());
	commands.emplace("equip", make_unique<const Equip>());
	commands.emplace("end", make_unique<const End>());
	commands.emplace("tame", make_unique<const Tame>());
}


string Interpreter::interpret(const vector<string>& vec, Map& map, GameData& data) const noexcept
{
	if (commands.find(vec[0]) == commands.end())
		return "Invalid command.\n";

	return commands.at(vec[0])->exec(vec, map, data);
}