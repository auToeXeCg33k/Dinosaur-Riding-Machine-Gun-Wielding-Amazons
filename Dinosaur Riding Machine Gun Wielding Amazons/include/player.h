#pragma once

#include "Amazon.h"

class Player
{
private:
	const std::string m_Name;
	std::unordered_map<std::string, Amazon> m_Amazons;
	Amazon* m_Selected;
	unsigned m_Actions;
	unsigned m_Alive;
	char m_ID;

	inline static char m_NextID{ 0 };
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