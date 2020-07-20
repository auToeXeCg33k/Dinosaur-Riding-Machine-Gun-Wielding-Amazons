#include "player.h"

using namespace std;


Player::Player(string_view name) noexcept : sName(name), pSelected(nullptr), nActions(0), nAlive(0) {}


Player::Player(Player&& other) noexcept : sName(move(other.sName)), pSelected(move(other.pSelected)), nActions(move(other.nActions)), nAlive(move(other.nAlive)) {}


const string& Player::name() const noexcept
{
	return sName;
}


int Player::actions() const noexcept
{
	return nActions;
}


void Player::action() noexcept
{
	nActions++;
}


void Player::resetActions() noexcept
{
	nActions = 0;
}


int Player::alive() const noexcept
{
	return nAlive;
}


void Player::incAlive() noexcept
{
	nAlive++;
}


void Player::decAlive() noexcept
{
	nAlive--;
}


int Player::spawns() const noexcept
{
	return amazon_map.size();
}


bool Player::existsAmazon(std::string_view name) const noexcept
{
	return amazon_map.find(static_cast<string>(name)) != amazon_map.end();
}


void Player::createAmazon(string_view name) noexcept
{
	amazon_map.emplace(name, make_unique<Amazon>(name));
}


Amazon& Player::getAmazon(std::string_view name) const noexcept
{
	return *amazon_map.at(static_cast<string>(name));
}


Amazon* Player::selected() const noexcept
{
	return pSelected;
}


void Player::selected(Amazon* const amazon) noexcept
{
	pSelected = amazon;
}