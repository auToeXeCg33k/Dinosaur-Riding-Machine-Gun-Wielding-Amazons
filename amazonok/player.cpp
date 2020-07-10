#include "player.h"

using namespace std;


Player::Player(string_view name) : sName(name), pSelected(nullptr), nActions(0), nAlive(0) {}


const string& Player::name()
{
	return sName;
}


int& Player::actions()
{
	return nActions;
}


int& Player::alive()
{
	return nAlive;
}


int Player::spawns()
{
	return amazon_map.size();
}


bool Player::ExistsAmazon(const string& name)
{
	return amazon_map.find(name) != amazon_map.end();
}


void Player::CreateAmazon(string_view name)
{
	amazon_map.emplace(name, make_unique<Amazon>(name));
}


Amazon& Player::GetAmazon(const string& name)
{
	return *amazon_map.at(name);
}


Amazon*& Player::selected()
{
	return pSelected;
}