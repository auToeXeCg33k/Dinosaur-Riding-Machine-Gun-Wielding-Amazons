#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"


class Player
{
private:
	const std::string nm;
	std::unordered_map<std::string, Amazon> amazons;
	Amazon* slctd;
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

	bool existsAmazon(const std::string& name) const noexcept;
	void createAmazon(const std::string& name) noexcept;
	Amazon& getAmazon(const std::string& name) noexcept;
	const std::unordered_map<std::string, Amazon>& AmazonContainer() const noexcept;

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