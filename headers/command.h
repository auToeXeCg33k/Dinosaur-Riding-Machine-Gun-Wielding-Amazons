#pragma once
#include "gamedata.h"
#include "map.h"

namespace commands
{
	typedef std::string (*command)(const std::vector<std::string>&, Map&, GameData&);
	
	std::string New(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Select(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Move(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Help(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Lookaround(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Attack(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Pickup(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Drop(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Equip(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string End(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Tame(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Geton(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Getoff(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string List(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Status(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
	std::string Steps(const std::vector<std::string>& v, Map& map, GameData& data) noexcept;
}