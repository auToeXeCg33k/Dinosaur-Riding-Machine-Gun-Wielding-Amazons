#pragma once
#include "amazon.h"


class Player
{
private:
	const std::string sName;
	std::unordered_map<std::string, std::unique_ptr<Amazon>> amazon_map;
	Amazon* pSelected;
	int nActions;
	int nAlive;
	char nID;

	static char nextID;

public:
	Player(std::string_view name) noexcept;
	Player(const Player& other) noexcept = delete;
	Player(Player&& other) noexcept;

	~Player() noexcept;

	const std::string& name() const noexcept;

	int actions() const noexcept;
	void action() noexcept;
	void resetActions() noexcept;

	int alive() const noexcept;
	void incAlive() noexcept;
	void decAlive() noexcept;
	
	int spawns() const noexcept;

	bool existsAmazon(std::string_view name) const noexcept;
	void createAmazon(std::string_view name) noexcept;
	Amazon& getAmazon(std::string_view name) const noexcept;
	const std::unordered_map<std::string, std::unique_ptr<Amazon>>& amazons() const noexcept;

	char id() const noexcept;

	Amazon* selected() const noexcept;
	void selected(Amazon* const amazon) noexcept;
};