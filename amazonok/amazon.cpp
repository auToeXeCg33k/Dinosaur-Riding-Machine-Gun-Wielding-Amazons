#include "amazon.h"

using namespace std;


Amazon::Amazon(string_view name) : name(name), hp(100.0), dino(nullptr), held(nullptr)
{
	inventory.emplace(ItemType::gun, std::vector<std::unique_ptr<Item>>());
}


bool Amazon::hasFreeSlot(ItemType type)
{
	return inventory.at(type).size() < ItemFactory::typeLimit(type);
}


bool Amazon::hasItem(string_view name)
{
	for (auto& x : inventory.at(ItemFactory::lookUp(name)))
		if (x->get_name() == name)
			return true;
	return false;
}


void Amazon::take(unique_ptr<Item>&& item)
{
	inventory.at(ItemFactory::lookUp(item->get_name())).emplace_back(move(item));
}


unique_ptr<Item> Amazon::remove(string_view name)
{
	std::unique_ptr<Item> ret;
	int pos;

	for (int i = 0; i < inventory.at(ItemFactory::lookUp(name)).size(); i++)
		if (inventory.at(ItemFactory::lookUp(name)).at(i)->get_name() == name)
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


Item* Amazon::item(string_view name)
{
	for (auto& x : inventory.at(ItemFactory::lookUp(name)))
		if (x->get_name() == name)
			return x.get();
}


const string& Amazon::get_name()
{
	return name;
}


double& Amazon::get_hp()
{
	return hp;
}


Gun*& Amazon::hand()
{
	return held;
}


Dino* Amazon::get_dino()
{
	return dino.get();
}