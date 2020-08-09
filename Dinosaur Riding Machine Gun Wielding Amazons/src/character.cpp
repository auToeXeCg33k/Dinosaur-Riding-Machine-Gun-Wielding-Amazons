#include <random>

#include "character.h"

using std::string;
using std::string_view;
using std::unique_ptr;
using std::move;


Dino::Dino() noexcept : hp{ 100.0 }, is_tamed{ false } {}


double Dino::health() const noexcept
{
	return hp;
}


void Dino::health(double const hp) noexcept
{
	this->hp = hp;
}


bool Dino::tamed() const noexcept
{
	return is_tamed;
}


void Dino::tamed(bool const tmd) noexcept
{
	is_tamed = tmd;
}




Amazon::Amazon(string_view name) noexcept : nm{ name }, hp{ 100.0 }, held{ nullptr }, owned_dino{ nullptr }, ridden_dino{ nullptr }
{
	inv.emplace(std::make_pair(ItemType::gun, std::vector<std::unique_ptr<Item>>{}));
}


bool Amazon::hasFreeSlot(ItemType type) const noexcept
{
	return inv.at(type).size() < ItemFactory::LimitOf(type);
}


bool Amazon::hasItem(string_view name) const noexcept
{
	for (const auto& x : inv.at(ItemFactory::TypeOf(name)))
		if (x->name() == name)
			return true;

	return false;
}


void Amazon::take(unique_ptr<Item>&& item) noexcept
{
	inv.at(ItemFactory::TypeOf(item->name())).emplace_back(move(item));
}


unique_ptr<Item> Amazon::drop(string_view name) noexcept
{
	long long pos{ -1 };

	for (size_t i = 0; i < inv.at(ItemFactory::TypeOf(name)).size(); i++)
		if (inv.at(ItemFactory::TypeOf(name)).at(i)->name() == name)
		{
			pos = i;

			if (inv.at(ItemFactory::TypeOf(name)).at(i).get() != held)
				break;
		}

	if (pos == -1)
		return nullptr;

	std::unique_ptr<Item> ret{ move(inv.at(ItemFactory::TypeOf(name)).at(pos)) };

	inv.at(ItemFactory::TypeOf(name)).erase(inv.at(ItemFactory::TypeOf(name)).begin() + pos);

	return ret;
}


Item* Amazon::item(string_view name) const noexcept
{
	for (const auto& x : inv.at(ItemFactory::TypeOf(name)))
		if (x->name() == name)
			return x.get();
}


const std::unordered_map<ItemType, std::vector<unique_ptr<Item>>>& Amazon::inventory() const noexcept
{
	return inv;
}


const string& Amazon::name() const noexcept
{
	return nm;
}


double Amazon::health() const noexcept
{
	return hp;
}


void Amazon::health(double const hp) noexcept
{
	this->hp = hp;
}


Gun* Amazon::hand() const noexcept
{
	return held;
}


void Amazon::hand(Gun* const gun) noexcept
{
	held = gun;
}


Dino* Amazon::dino() const noexcept
{
	return owned_dino;
}


void Amazon::dino(Dino* const dino) noexcept
{
	owned_dino = dino;
}


unique_ptr<Dino>& Amazon::riding() noexcept
{
	return ridden_dino;
}


void Amazon::riding(unique_ptr<Dino>&& dino) noexcept
{
	ridden_dino = move(dino);
}




BrainDrainer::BrainDrainer() noexcept : min{ 60.0 }, max{ 90.0 } {}


double BrainDrainer::damage() const noexcept
{
	std::mt19937_64 mt{ std::random_device{}() };
	std::uniform_real_distribution<> dist{ 0, 1 };

	return (max - min) * dist(mt) + min;
}


string BrainDrainer::attack(Amazon& amazon) const noexcept
{
	auto dmg{ damage() };

	if (amazon.riding())
	{
		if (amazon.dino()->health() - dmg < 0.0)
			amazon.dino()->health(0.0);
		else
			amazon.dino()->health(amazon.dino()->health() - dmg);

		if (!amazon.dino()->health())
			return amazon.name() + "'s dino was killed by a Braindrainer.\n";

		return amazon.name() + "'s dino suffered " + std::to_string(static_cast<int>(round(dmg))) + " points of damage from a Braindrainer.\n";
	}

	if (amazon.health() - dmg < 0.0)
		amazon.health(0.0);
	else
		amazon.health(amazon.health() - dmg);

	if (!amazon.health())
		return amazon.name() + " was killed by a Braindrainer.\n";

	return amazon.name() + " suffered " + std::to_string(static_cast<int>(round(dmg))) + " points of damage from a Braindrainer.\n";
}