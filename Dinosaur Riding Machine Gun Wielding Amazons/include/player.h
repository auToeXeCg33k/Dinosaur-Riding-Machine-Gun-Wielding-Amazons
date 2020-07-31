#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"


class Player
{
private:
	const std::string sName;
	std::unordered_map<std::string, Amazon> amazon_map;
	Amazon* pSelected;
	unsigned nActions;
	unsigned nAlive;
	char nID;

	static char nextID;

public:
	Player(std::string_view name) noexcept;
	Player(Player&& other) noexcept = delete;

	~Player() noexcept;

	const std::string& name() const noexcept;

	unsigned actions() const noexcept;
	void action() noexcept;
	void resetActions() noexcept;

	unsigned alive() const noexcept;
	void incAlive() noexcept;
	void decAlive() noexcept;
	
	size_t spawns() const noexcept;

	bool existsAmazon(std::string_view name) const noexcept;
	void createAmazon(std::string_view name) noexcept;
	Amazon& getAmazon(std::string_view name) noexcept;
	const std::unordered_map<std::string, Amazon>& amazons() const noexcept;

	char id() const noexcept;

	Amazon* selected() const noexcept;
	void selected(Amazon* const amazon) noexcept;
};


class GameData
{
private:
	Player p1;
	Player p2;
	bool active;
	const unsigned nMaxActions;
	const unsigned nMaxSpawns;
	const unsigned nMaxAlive;

public:
	GameData(int i) noexcept;
	GameData(GameData&& other) noexcept = delete;

	Player& CurrentPlayer() noexcept;
	Player& OtherPlayer() noexcept;

	unsigned MaxActions() const noexcept;
	unsigned MaxSpawns() const noexcept;
	unsigned MaxAlive() const noexcept;

	void turn() noexcept;
};

#endif