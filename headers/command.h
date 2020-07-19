#pragma once
#include "gamedata.h"
#include "map.h"


class Command
{
public:
	virtual std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept = 0;
	virtual ~Command();
};


class New : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Select : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Move : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Help : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Lookaround : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Attack : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Pickup : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Drop : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Equip : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class End : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Tame : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Geton : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};


class Getoff : public Command
{
public:
	std::string exec(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept;
};