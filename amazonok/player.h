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

public:
	Player(std::string_view name);
	const std::string& name();
	int& actions();
	int& alive();
	int spawns();
	bool ExistsAmazon(const std::string& name);
	void CreateAmazon(std::string_view name);
	Amazon& GetAmazon(const std::string& name);
	Amazon*& selected();
};