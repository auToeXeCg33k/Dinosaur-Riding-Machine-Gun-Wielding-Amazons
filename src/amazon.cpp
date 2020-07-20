#include "amazon.h"

using namespace std;


Amazon::Amazon(string_view name) noexcept : sName(name), hp(100.0), held(nullptr), pDino(nullptr), pRiding(nullptr)
{
	inventory.emplace(ItemType::gun, std::vector<std::unique_ptr<Item>>());
}


Amazon::Amazon(Amazon&& other) noexcept : sName(move(other.sName)), hp(move(other.hp)), inventory(move(other.inventory)), held(move(other.held)), pDino(move(other.pDino)), pRiding(move(other.pRiding)) {} 


bool Amazon::hasFreeSlot(ItemType type) const noexcept
{
	return inventory.at(type).size() < ItemFactory::typeLimit(type);
}


bool Amazon::hasItem(string_view name) const noexcept
{
	for (auto& x : inventory.at(ItemFactory::lookUp(name)))
		if (x->name() == name)
			return true;
	return false;
}


void Amazon::take(unique_ptr<Item>&& item) noexcept
{
	inventory.at(ItemFactory::lookUp(item->name())).emplace_back(move(item));
}


unique_ptr<Item> Amazon::drop(string_view name) noexcept
{
	std::unique_ptr<Item> ret;
	int pos;

	for (int i = 0; i < inventory.at(ItemFactory::lookUp(name)).size(); i++)
		if (inventory.at(ItemFactory::lookUp(name)).at(i)->name() == name)
		{
			ret = move(inventory.at(ItemFactory::lookUp(name)).at(i));

			if (ret.get() == held)
			{
				pos = i;
				continue;
			}

			inventory.at(ItemFactory::lookUp(name)).erase(inventory.at(ItemFactory::lookUp(name)).begin() + i);
			return ret;
		}

	inventory.at(ItemFactory::lookUp(name)).erase(inventory.at(ItemFactory::lookUp(name)).begin() + pos);
	return ret;
}


Item* Amazon::item(string_view name) const noexcept
{
	for (auto& x : inventory.at(ItemFactory::lookUp(name)))
		if (x->name() == name)
			return x.get();
}


const string& Amazon::name() const noexcept
{
	return sName;
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


void Amazon::hand(Gun* const item) noexcept
{
	held = item;
}


Dino* Amazon::dino() const noexcept
{
	return pDino;
}


void Amazon::dino(Dino* const dino) noexcept
{
	pDino = dino;
}


unique_ptr<Dino>& Amazon::riding() noexcept
{
	return pRiding;
}


void Amazon::riding(unique_ptr<Dino>&& dino) noexcept
{
	pRiding = move(dino);
}