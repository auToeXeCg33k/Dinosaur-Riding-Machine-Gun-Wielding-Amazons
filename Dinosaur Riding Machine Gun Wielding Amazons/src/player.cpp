#include "player.h"

using std::string;
using std::string_view;


char Player::nextID{ 0 };


Player::Player(string_view name) noexcept : nm{ name }, slctd{ nullptr }, nActions{ 0 }, nAlive{ 0 }, nID{ nextID }
{
	nextID++;
}


Player::~Player() noexcept
{
	nextID--;
}


const string& Player::name() const noexcept
{
	return nm;
}


unsigned Player::actions() const noexcept
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


unsigned Player::alive() const noexcept
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


size_t Player::spawns() const noexcept
{
	return amazons.size();
}


bool Player::existsAmazon(const string& name) const noexcept
{
	return amazons.find(name) != amazons.end();
}


void Player::createAmazon(const string& name) noexcept
{
	amazons.emplace(name, name);
}


Amazon& Player::getAmazon(const string& name) noexcept
{
	return amazons.at(name);
}


const std::unordered_map<string, Amazon>& Player::AmazonContainer() const noexcept
{
	return amazons;
}


char Player::id() const noexcept
{
	return nID;
}


Amazon* Player::selected() const noexcept
{
	return slctd;
}


void Player::selected(Amazon* const amazon) noexcept
{
	slctd = amazon;
}




GameData::GameData(int i) noexcept : p1{ "Player 1" }, p2{ "Player 2" }, active{ 0 }, nMaxActions{ i == 1 ? 3u : 3u }, nMaxSpawns{ i == 1 ? 6u : 6u }, nMaxAlive{ i == 1 ? 3u : 3u } {}


Player& GameData::CurrentPlayer() noexcept
{
	return active ? p2 : p1;
}


Player& GameData::OtherPlayer() noexcept
{
	return active ? p1 : p2;
}


unsigned GameData::MaxActions() const noexcept
{
	return nMaxActions;
}


unsigned GameData::MaxSpawns() const noexcept
{
	return nMaxSpawns;
}


unsigned GameData::MaxAlive() const noexcept
{
	return nMaxAlive;
}


void GameData::turn() noexcept
{
	active = !active;
	p1.resetActions();
	p2.resetActions();
}