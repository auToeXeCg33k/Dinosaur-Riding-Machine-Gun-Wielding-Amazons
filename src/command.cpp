#include "command.h"
#include <stdexcept>
#include <cmath>
#include <random>

using namespace std;


string commands::New(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (data.CurrentPlayer().spawns() == data.MaxSpawns())
		return "Maximum number of spawns reached.\n";

	if (data.CurrentPlayer().alive() == data.MaxAlive())
		return "Maximum number of living amazons reached.\n";

	if (data.CurrentPlayer().existsAmazon(v[1]))
		return v[1] + " already exists.\n";

	data.CurrentPlayer().createAmazon(v[1]);

	if (data.CurrentPlayer().id())
		map.tile(Point(map.size() - 1, map.size() - 1)).add(&data.CurrentPlayer().getAmazon(v.at(1)));
	else
		map.tile(Point(0, 0)).add(&data.CurrentPlayer().getAmazon(v.at(1)));

	data.CurrentPlayer().incAlive();
	data.CurrentPlayer().action();

	return v[1] + " created.\n";
}


string commands::Select(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().existsAmazon(v[1]))
		return v[1] + " does not exist.\n";

	if (data.CurrentPlayer().selected() && data.CurrentPlayer().selected()->name() == v[1])
		return v[1] + " is already selected.\n";

	data.CurrentPlayer().selected(&data.CurrentPlayer().getAmazon(v[1]));

	return v[1] + " selected.\n";
}


string commands::Move(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 3)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	try
	{
		Point target(stoi(v.at(1)) - 1, stoi(v.at(2)) - 1);
		Point current(map.find(data.CurrentPlayer().selected()));

		if (target.x() < 0 || target.y() < 0 || target.x() >= map.size() || target.y() >= map.size())
			return "Target tile does not exist.\n";

		if (current.x() + 1 < target.x() || current.x() - 1 > target.x() || current.y() + 1 < target.y() || current.y() - 1 > target.y())
			return "Target tile is too far.\n";

		if (current == target)
			return "Target tile matches the current one.\n";

		map.tile(current).remove(data.CurrentPlayer().selected());
		map.tile(target).add(data.CurrentPlayer().selected());

		data.CurrentPlayer().action();

		string ret(data.CurrentPlayer().selected()->name() + " moved to " + v.at(1) + ";" + v.at(2) + ".\n");

		if (map.tile(target).braindrainer())
		{
			ret.append(map.tile(target).braindrainer()->attack(*data.CurrentPlayer().selected()));

			if (data.CurrentPlayer().selected()->riding() && !data.CurrentPlayer().selected()->dino()->health())
				map.tile(target).add(move(data.CurrentPlayer().selected()->riding()));

			else if(!data.CurrentPlayer().selected()->health())
				data.CurrentPlayer().decAlive();
		}

		return ret;
	}

	catch (invalid_argument&)
	{
		return "Invalid arguments.\n";
	}
}


string commands::Help(const vector<string>& v, Map& map, GameData& data) noexcept
{
	return "### About The Game ###\n\n"
	"The game is turn and tile based, and played by 2 players.\n"
	"Players create and control \"amazons\", who can tame \"dinos\", pick \"items\" up, and use them around the map.\n"
	"There are multiple gamemodes (currently only 1 is implemented).\n"
	"A gamemode defines the size of the map, the maximum number of spawned and living amazons and actions per turn per player.\n"
	"Items and dinos spawn in random locations, their number and these locations also depend on the played gamemode.\n"
	"Dinos can be tamed and ridden. This provides amazons with an additional layer of health, a shield, so to speak.\n"
	"To attack, amazons need weapons. More on these later.\n"
	"Players have common enemies: the braindrainers. The braindrainers attack anyone on their tiles. They move around and spawn randomly."
	"\n\n### Entities ###\n\n"
	"Amazon: they have a max HP of 100, start without a dino and any items. Amazons can currently carry a maximum of 2 weapons at a time.\n"
	"Dino: they also have a max HP of 100.\n"
	"Braindrainer: they are unkillable, and deal a random amount of damage between 60 and 90. Every turn they either move to a surrounding tile, or stay where they are.\n"
	"\n\n### Items ###\n\n"
	"*Weapons*\n"
	"Weapons deal a random amount of damage between a minimum, and a maximum value. They have a rate of fire. The total damage is the sum of rate of fire number of random damage values.\n"
	"Pistol: min damage: 15, max damage: 20, rate of fire: 2.\n"
	"Shotgun: min damage: 50, max damage: 75, rate of fire: 1.\n"
	"Katana: min damage: 20, max damage: 30, rate of fire: 3.\n"
	"Minigun: min damage: 1.5, max damage: 5.0, rate of fire: 30.\n"
	"Rocket Launcher: min damage: 90, max damage: 120, rate of fire: 1.\n"
	"\n\n### Commands ### \n\n"
	"new <name>: creates an amazon with the given name. The 2 players can have amazons with the same name. The starting player's amazons spawn in the bottom left, the other player's amazons spawn in the upper right corner of the map.\n"
	"select <name>: selects a created amazon. Amazons have to be selected in order to command them.\n"
	"move <x> <y>: moves the selected amazon to the given tile. Amazons can only move to surrounding tiles.\n"
	"help: opens this menu.\n"
	"attack <name>: the selected amazon attacks an enemy amazon with the given name. Only amazons on the same tile can attack each other. If the target is riding a dino, the dino is attacked.\n"
	"lookaround: the selected amazon looks around and tells the player what it sees.\n"
	"pickup <name>: the selected amazon picks up an item with the given name and puts it in their inventory. Only items on the selected amazon's tile can be picked up. In order to use a picked up item, it has to equipped first.\n"
	"drop <name>: the selected amazon drops an item with the given name to the tile they are standing on. Prioritizes items not held by the amazon.\n"
	"equip <name>: the selected amazon takes the item with the given name from their inventory into their hands.\n"
	"end: players can end their turn with this command.\n"
	"tame: the selected amazon tames the highest HP dino on their current tile. Amazons can only have one tamed dino at a time, and can only ride ones tamed by them.\n"
	"geton: the selected amazon gets on their tamed dino. The dino and the amazon have to on the same tile. Only living dinos can be ridden.\n"
	"getoff: the selected amazon gets off their tamed dino. If the tamed dino dies while their amazon is riding it, the amazon automatically gets off it.\n"
	"list: lists the current player's amazons.\n"
	"status: provides vital information about the selected amazon, such as health, location, items, dino status.\n"
	"steps: provides information about the possible steps the current player can take at the time.\n";
}


string commands::Lookaround(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	static const struct Offset : public Point
	{
		string adj;
		string noun;

		Offset(const char x, const char y, string_view adj, string_view noun) : Point(x, y), adj(adj), noun(noun) {}
	} offsets[]
	{
		{0, 0, "Current", "Current tile"},
		{0, 1,"Northern", "North"},
		{1, 1, "Northeastern", "North East"},
		{1, 0, "Eastern", "East"},
		{1, -1, "Southeastern", "South East:"},
		{0, -1, "Southern", "South"},
		{-1, -1,"Southwestern", "South West"},
		{-1, 0, "Western", "West"},
		{-1, 1, "Northwestern", "North West"}
	};

	Point p(map.find(data.CurrentPlayer().selected()));
	string ret;
	string temp;

	for (const auto& offset : offsets)
		if (p.x() + offset.x() >= 0 && p.x() + offset.x() < map.size() && p.y() + offset.y() >= 0 && p.y() + offset.y() < map.size())
		{
			for (const auto& x : map.tile(Point(p.x() + offset.x(), p.y() + offset.y())).AmazonContainer())
				if (x != data.CurrentPlayer().selected())
					temp.append(x->name() + "(" + (data.OtherPlayer().existsAmazon(x->name()) && &data.OtherPlayer().getAmazon(x->name()) == x ? "enemy" : "friendly") + ", " + to_string(static_cast<int>(round(x->health()))) + " HP), ");

			for (const auto& x : map.tile(Point(p.x() + offset.x(), p.y() + offset.y())).DinoContainer())
				temp.append((x->tamed() ? "Tamed" : "Untamed") + static_cast<string>(" Dino (") +  to_string(static_cast<int>(round(x->health()))) + " HP), ");

			for (const auto& x : map.tile(Point(p.x() + offset.x(), p.y() + offset.y())).ItemContainer())
				for (const auto& y : x.second)
					temp.append(y->name() + ", ");

			if (map.tile(Point(p.x() + offset.x(), p.y() + offset.y())).braindrainer())
				temp.append("BRAINDRAINER, ");

			if (temp.empty())
				ret.append(offset.adj + " tile empty.\n");

			else
			{
				ret.append(offset.noun + ": " + temp.substr(0, temp.length() - 2) + ".\n");
				temp.clear();
			}
		}

	return ret;
}


string commands::Attack(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!data.CurrentPlayer().selected()->hand())
		return data.CurrentPlayer().selected()->name() + " is not holding any weapon.\n";

	if (!data.OtherPlayer().existsAmazon(v[1]))
		return "Enemy " + v[1] + " does not exist.\n";

	if (map.find(data.CurrentPlayer().selected()) != map.find(&data.OtherPlayer().getAmazon(v[1])))
		return v[1] + " is out of range.\n";

	if (data.OtherPlayer().getAmazon(v[1]).health() == 0.0)
		return v[1] + " is already dead.\n";

	double dmg = data.CurrentPlayer().selected()->hand()->dmg();

	data.CurrentPlayer().action();

	if (data.OtherPlayer().getAmazon(v[1]).riding())
	{
		if (data.OtherPlayer().getAmazon(v[1]).dino()->health() - dmg < 0.0)
			data.OtherPlayer().getAmazon(v[1]).dino()->health(0.0);
		else
			data.OtherPlayer().getAmazon(v[1]).dino()->health(data.OtherPlayer().getAmazon(v[1]).dino()->health() - dmg);

		if (data.OtherPlayer().getAmazon(v[1]).dino()->health() == 0.0)
		{
			map.tile(map.find(&data.OtherPlayer().getAmazon(v[1]))).add(move(data.OtherPlayer().getAmazon(v[1]).riding()));
			return v[1] + "'s dino died.\n";
		}

		return v[1] + "'s dino suffered " + to_string(static_cast<int>(round(dmg))) + " points of damage.\n";
	}
		
		

	if (data.OtherPlayer().getAmazon(v[1]).health() - dmg < 0.0)
		data.OtherPlayer().getAmazon(v[1]).health(0.0);
	else
		data.OtherPlayer().getAmazon(v[1]).health(data.OtherPlayer().getAmazon(v[1]).health() - dmg);

	if (data.OtherPlayer().getAmazon(v[1]).health() == 0.0)
	{
		data.OtherPlayer().decAlive();
		return v[1] + " died.\n";
	}

	return v[1] + " suffered " + to_string(static_cast<int>(round(dmg))) + " points of damage.\n";
}


string commands::Pickup(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!ItemFactory::isValid(v[1]))
		return "Invalid item type.\n";

	Point p = map.find(data.CurrentPlayer().selected());

	if (!map.tile(p).has(v[1]))
		return v[1] + " cannot be found on the current tile.\n";

	if (!data.CurrentPlayer().selected()->hasFreeSlot(ItemFactory::lookUp(v[1])))
		return "Can't pick up " + v[1] + ". " + data.CurrentPlayer().selected()->name() + "'s inventory is full.\n";

	data.CurrentPlayer().selected()->take(map.tile(p).remove(v[1]));

	data.CurrentPlayer().action();

	return "Picked up " + v[1] + ".\n";
}


string commands::Drop(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!ItemFactory::isValid(v[1]))
		return "Invalid item type.\n";

	if (!data.CurrentPlayer().selected()->hasItem(v[1]))
		return v[1] + " cannot be found in " + data.CurrentPlayer().selected()->name() + "'s inventory.\n";

	Point p = map.find(data.CurrentPlayer().selected());

	unique_ptr<Item> item(data.CurrentPlayer().selected()->drop(v[1]));

	if (item.get() == data.CurrentPlayer().selected()->hand())
		data.CurrentPlayer().selected()->hand(nullptr);

	map.tile(p).add(move(item));

	data.CurrentPlayer().action();

	return v[1] + " dropped.\n";
}


string commands::Equip(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!ItemFactory::isValid(v[1]) || ItemFactory::lookUp(v[1]) != ItemType::gun)
		return "Invalid weapon type.\n";

	if (!data.CurrentPlayer().selected()->hasItem(v[1]))
		return v[1] + " cannot be found in " + data.CurrentPlayer().selected()->name() + "'s inventory.\n";

	data.CurrentPlayer().selected()->hand(static_cast<Gun*>(data.CurrentPlayer().selected()->item(v[1])));

	return v[1] + " equipped.\n";
}


string commands::End(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	data.turn();

	vector<pair<Point, unique_ptr<BrainDrainer>>> drainers;

	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map.size(); j++)
			if (map.tile(Point(j, i)).braindrainer())
				drainers.emplace_back(make_pair(Point(j, i), map.tile(Point(j, i)).remove()));

	vector<Point> offsets;
	offsets.reserve(9);

	random_device rd;
	mt19937_64 mt(rd());

	for (auto& pair : drainers)
	{
		offsets.clear();
		
		for (int i = -1; i != 2; i++)
			for (int j = -1; j != 2; j++)
				offsets.emplace_back(Point(i, j));
		
		while(true)
		{
			uniform_int_distribution<> dist(0, offsets.size() - 1);
			int rnd(dist(mt));

			if (pair.first.x() + offsets.at(rnd).x() >= 0 && pair.first.x() + offsets.at(rnd).x() < map.size() && pair.first.y() + offsets.at(rnd).y() >= 0 && pair.first.y() + offsets.at(rnd).y() < map.size() && !map.tile(Point(pair.first.x() + offsets.at(rnd).x(), pair.first.y() + offsets.at(rnd).y())).braindrainer())
			{
				map.tile(Point(pair.first.x() + offsets.at(rnd).x(), pair.first.y() + offsets.at(rnd).y())).add(move(pair.second));
				break;
			}

			offsets.erase(offsets.begin() + rnd);
		}
	}

	return "\n### END OF TURN ###\n";
}


string commands::Tame(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (data.CurrentPlayer().selected()->dino())
		return data.CurrentPlayer().selected()->name() + " already has a dino.\n";

	const auto& dinos(map.tile(map.find(data.CurrentPlayer().selected())).DinoContainer());

	if (dinos.empty())
		return "There are no dinos nearby.\n";

	Dino* temp(dinos.front().get());

	for (const auto& x : dinos)
		if (x->health() >= temp->health() && !x->tamed())
			temp = x.get();

	if (temp->tamed())
		return "There are no free dinos nearby.\n";

	data.CurrentPlayer().selected()->dino(temp);
	temp->tamed(!temp->tamed());

	return "Dino (" + to_string(static_cast<int>(round(temp->health()))) + " HP) tamed.\n";
}


string commands::Geton(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!data.CurrentPlayer().selected()->dino())
		return data.CurrentPlayer().selected()->name() + " does not have a dino. Tame one first!\n";

	if (data.CurrentPlayer().selected()->riding())
		return data.CurrentPlayer().selected()->name() + " is already riding their dino.\n";

	const auto point(map.find(data.CurrentPlayer().selected()));

	if (!map.tile(point).has(data.CurrentPlayer().selected()->dino()))
		return data.CurrentPlayer().selected()->name() + "'s dino is not nearby.\n";

	if (data.CurrentPlayer().selected()->dino()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + "'s dino is dead.\n";

	data.CurrentPlayer().selected()->riding(map.tile(point).remove(data.CurrentPlayer().selected()->dino()));
	return data.CurrentPlayer().selected()->name() + " got on their dino.\n";
}


string commands::Getoff(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";
	
	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!data.CurrentPlayer().selected()->dino())
		return data.CurrentPlayer().selected()->name() + " does not have a dino. Tame one first!\n";

	if (!data.CurrentPlayer().selected()->riding())
		return data.CurrentPlayer().selected()->name() + " is currently not riding their dino.\n";

	map.tile(map.find(data.CurrentPlayer().selected())).add(move(data.CurrentPlayer().selected()->riding()));

	return data.CurrentPlayer().selected()->name() + " got off their dino.\n";
}


string commands::List(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	string ret;

	for (const auto& x : data.CurrentPlayer().amazons())
		ret.append(x.first + ", ");

	if (ret.empty())
		return "You don't have amazons.\n";

	return "Your amazons: " + ret.substr(0, ret.size() - 2) + ".\n";
}


string commands::Status(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";
	
	auto selected(data.CurrentPlayer().selected());

	string ret(selected->name() + ".\n");
	ret.append(to_string(static_cast<int>(round(selected->health()))) + " HP.\n");

	auto location(map.find(selected));

	ret.append("On " + to_string(location.x() + 1) + ";" + to_string(location.y() + 1) + ".\n");
	ret.append("Holding: " + (selected->hand() ? "a " + selected->hand()->name() : "nothing") + ".\n");
	ret.append("Inventory: ");

	string temp;
	
	for (const auto& x : selected->inventory())
		for (const auto& y : x.second)
			temp.append(y->name() + ", ");

	if (temp.empty())
		ret.append("empty.\n");
	else
		ret.append(temp.substr(0, temp.size() - 2) + ".\n");

	ret.append("Dino: " + (selected->dino() ? to_string(static_cast<int>(round(selected->dino()->health()))) + " HP" : "none") + ".\n");
	return ret.append(selected->riding() ? "Riding.\n" : "Not riding.\n");
}


string commands::Steps(const vector<string>& v, Map& map, GameData& data) noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	return "Remaining actions: " + to_string(data.MaxActions() - data.CurrentPlayer().actions()) + ".\n"
	"Living amazons: " + to_string(data.CurrentPlayer().alive()) + ".\n"
	"Spawns: " + to_string(data.CurrentPlayer().spawns()) + ".\n"
	"Possible spawns: " + to_string(min(data.MaxSpawns() - data.CurrentPlayer().spawns(), data.MaxAlive() - data.CurrentPlayer().alive())) + ".\n";
}