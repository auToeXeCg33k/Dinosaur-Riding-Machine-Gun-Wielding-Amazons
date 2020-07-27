#include "amazon.h"

using namespace std;


Amazon::Amazon(string_view name) noexcept : sName(name), hp(100.0), held(nullptr), pDino(nullptr), pRiding(nullptr)
{
	inv.emplace(ItemType::gun, std::vector<std::unique_ptr<Item>>());
}


bool Amazon::hasFreeSlot(ItemType type) const noexcept
{
	return inv.at(type).size() < ItemFactory::typeLimit(type);
}


bool Amazon::hasItem(string_view name) const noexcept
{
	for (auto& x : inv.at(ItemFactory::lookUp(name)))
		if (x->name() == name)
			return true;
	return false;
}


void Amazon::take(unique_ptr<Item>&& item) noexcept
{
	inv.at(ItemFactory::lookUp(item->name())).emplace_back(move(item));
}


unique_ptr<Item> Amazon::drop(string_view name) noexcept
{
	long long pos(-1);

	for (size_t i = 0; i < inv.at(ItemFactory::lookUp(name)).size(); i++)
		if (inv.at(ItemFactory::lookUp(name)).at(i)->name() == name)
		{
			pos = i;

			if (inv.at(ItemFactory::lookUp(name)).at(i).get() != held)
				break;
		}

	if (pos == -1)
		return nullptr;

	std::unique_ptr<Item> ret(move(inv.at(ItemFactory::lookUp(name)).at(pos)));

	inv.at(ItemFactory::lookUp(name)).erase(inv.at(ItemFactory::lookUp(name)).begin() + pos);

	return ret;
}


Item* Amazon::item(string_view name) const noexcept
{
	for (auto& x : inv.at(ItemFactory::lookUp(name)))
		if (x->name() == name)
			return x.get();
}


const unordered_map<ItemType, vector<unique_ptr<Item>>>& Amazon::inventory() const noexcept
{
	return inv;
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