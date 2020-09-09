#include "Command.h"

#include "GameData.h"
#include "Utility.h"

#include <stdexcept>
#include <random>

CommandHandler::CommandHandler() noexcept
{
    m_Commands.emplace("new", &CommandHandler::New);
    m_Commands.emplace("select", &CommandHandler::Select);
    m_Commands.emplace("move", &CommandHandler::Move);
    m_Commands.emplace("help", &CommandHandler::Help);
    m_Commands.emplace("lookaround", &CommandHandler::Lookaround);
    m_Commands.emplace("attack", &CommandHandler::Attack);
    m_Commands.emplace("pickup", &CommandHandler::Pickup);
    m_Commands.emplace("drop", &CommandHandler::Drop);
    m_Commands.emplace("equip", &CommandHandler::Equip);
    m_Commands.emplace("end", &CommandHandler::End);
    m_Commands.emplace("tame", &CommandHandler::Tame);
    m_Commands.emplace("geton", &CommandHandler::Geton);
    m_Commands.emplace("getoff", &CommandHandler::Getoff);
    m_Commands.emplace("list", &CommandHandler::List);
    m_Commands.emplace("status", &CommandHandler::Status);
    m_Commands.emplace("steps", &CommandHandler::Steps);
}

CommandHandler& CommandHandler::Instance() noexcept
{
	static CommandHandler inst;
	return inst;
}

std::string CommandHandler::HandleCommand(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
{
	if (m_Commands.find(toLower(v.at(0))) == m_Commands.end())
		return "Invalid command.\n";

	return (this->*m_Commands.at(toLower(v.at(0))))(v, map, data);
}

std::string CommandHandler::New(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
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
		map.tile(Point{ map.size() - 1, map.size() - 1 }).add(&data.CurrentPlayer().getAmazon(v.at(1)));
	else
		map.tile(Point{ 0, 0 }).add(&data.CurrentPlayer().getAmazon(v.at(1)));

	data.CurrentPlayer().incAlive();
	data.CurrentPlayer().action();

	return v[1] + " created.\n";
}

std::string CommandHandler::Select(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
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

std::string CommandHandler::Move(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
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
		Point target{ stoi(v.at(1)) - 1, stoi(v.at(2)) - 1 };
		Point current{ map.find(data.CurrentPlayer().selected()) };

		if (target.x() < 0 || target.y() < 0 || target.x() >= map.size() || target.y() >= map.size())
			return "Target tile does not exist.\n";

		if (current.x() + 1 < target.x() || current.x() - 1 > target.x() || current.y() + 1 < target.y() || current.y() - 1 > target.y())
			return "Target tile is too far.\n";

		if (current == target)
			return "Target tile matches the current one.\n";

		map.tile(current).remove(data.CurrentPlayer().selected());
		map.tile(target).add(data.CurrentPlayer().selected());

		data.CurrentPlayer().action();

		std::string ret{ data.CurrentPlayer().selected()->name() + " moved to (" + v.at(1) + ", " + v.at(2) + ").\n" };

		if (map.tile(target).braindrainer())
			ret.append(map.tile(target).braindrainer()->Attack(*data.CurrentPlayer().selected(), map.tile(target), data));

		return ret;
	}

	catch (const std::invalid_argument&)
	{
		return "Invalid arguments.\n";
	}
}

std::string CommandHandler::Help(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
{
	return "### About The Game ###\n\n"

	"The game is turn and tile based, and played by 2 players.\n"
	"Players create and control \"amazons\", who can tame \"dinos\", pick \"items\" up, and use them around the map.\n"
	"There are multiple gamemodes (currently only 1 is implemented).\n"
	"A gamemode defines the size of the map, the maximum number of spawned and living amazons and actions per turn per player.\n"
	"Items and dinos spawn in random locations, their number and these locations also depend on the played gamemode.\n"
	"Dinos can be tamed and ridden. This provides amazons with an additional layer of health, a shield, so to speak.\n"
	"To attack, amazons need weapons. More on these later.\n"
	"Players have common enemies: the braindrainers. The braindrainers attack anyone on their tiles. They move around and spawn randomly.\n"


	"\n\n### Entities ###\n\n"

	"	Amazon:			they have a max HP of 100, start without a dino and any items. Amazons can currently carry a maximum of 2 weapons at a time.\n"
	"	Dino: 			they also have a max HP of 100.\n"
	"	Braindrainer: 		they are unkillable, and deal a random amount of damage between 60 and 90. Every turn they either move to a surrounding tile, or stay where they are, and attack all amazons on their tile.\n"
	

	"\n\n### Items ###\n\n"

	"*Weapons*\n"
	"Weapons deal a random amount of damage between a minimum, and a maximum value. They have a rate of fire. The total damage is the sum of rate of fire number of random damage values.\n\n"
	"	Pistol:			min damage: 15, max damage: 20, rate of fire: 2.\n\n"
	"	Shotgun:		min damage: 50, max damage: 75, rate of fire: 1.\n\n"
	"	Katana:			min damage: 20, max damage: 30, rate of fire: 3.\n\n"
	"	Minigun:		min damage: 1.5, max damage: 5.0, rate of fire: 30.\n\n"
	"	Rocket Launcher:	min damage: 90, max damage: 120, rate of fire: 1.\n"


	"\n\n### Commands ### \n\n"

	"	new <name>:		creates an amazon with the given name. The 2 players can have amazons with the same name. The starting player's amazons spawn in the bottom left, the other player's amazons spawn in the upper right corner of the map.\n\n"
	"	select <name>:		selects a created amazon. Amazons have to be selected in order to command them.\n\n"
	"	move <x> <y>:		moves the selected amazon to the given tile. Amazons can only move to surrounding tiles.\n\n"
	"	help:			opens this menu.\n\n"
	"	attack <name>:		the selected amazon attacks the enemy amazon with the given name. Only amazons on the same tile can attack each other. If the target is riding a dino, the dino is attacked.\n\n"
	"	lookaround:		the selected amazon looks around and tells the player what it sees.\n\n"
	"	pickup <name>:		the selected amazon picks up an item with the given name and puts it in their inventory. Only items on the selected amazon's tile can be picked up. In order to use a picked up item, it has to equipped first.\n\n"
	"	drop <name>:		the selected amazon drops an item with the given name to the tile they are standing on. Prioritizes items not held by the amazon.\n\n"
	"	equip <name>:		the selected amazon takes an item with the given name from their inventory into their hands.\n\n"
	"	end:			players can end their turn with this command.\n\n"
	"	tame:			the selected amazon tames the highest HP dino on their current tile. Amazons can only have one tamed dino at a time, and can only ride ones tamed by them.\n\n"
	"	geton:			the selected amazon gets on their tamed dino. The dino and the amazon have to on the same tile. Only living dinos can be ridden.\n\n"
	"	getoff:			the selected amazon gets off of their tamed dino. If the tamed dino dies while their amazon is riding it, the amazon automatically gets off of it.\n\n"
	"	list:			lists the current player's amazons.\n\n"
	"	status:			provides vital information about the selected amazon, such as health, location, items, dino status.\n\n"
	"	steps:			provides information about the possible steps the current player can take at the time.\n";
}

std::string CommandHandler::Lookaround(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	static const Point offsets[]
	{
		{0, 0},
		{0, 1},
		{1, 1},
		{1, 0},
		{1, -1},
		{0, -1},
		{-1, -1},
		{-1, 0},
		{-1, 1}
	};

	Point p{ map.find(data.CurrentPlayer().selected()) };
	std::string ret;
	std::string temp;

	for (const auto& offset : offsets)
		if (p.x() + offset.x() >= 0 && p.x() + offset.x() < map.size() && p.y() + offset.y() >= 0 && p.y() + offset.y() < map.size())
		{
			ret.append("(" + std::to_string(p.x() + offset.x() + 1) + ", " + std::to_string(p.y() + offset.y() + 1) + "): ");

			for (const auto& x : map.tile(Point{ p.x() + offset.x(), p.y() + offset.y() }).AmazonContainer())
				if (x != data.CurrentPlayer().selected())
					temp.append(x->name() + "(" + (data.OtherPlayer().existsAmazon(x->name()) && &data.OtherPlayer().getAmazon(x->name()) == x ? "enemy" : "friendly") + ", " + std::to_string(static_cast<int>(round(x->health()))) + " HP), ");

			for (const auto& x : map.tile(Point{ p.x() + offset.x(), p.y() + offset.y() }).DinoContainer())
				temp.append((x->Tamed() ? "Tamed" : "Untamed") + static_cast<std::string>(" Dino (") +  std::to_string(static_cast<int>(round(x->Health()))) + " HP), ");

			for (const auto& x : map.tile(Point{ p.x() + offset.x(), p.y() + offset.y() }).ItemContainer())
				for (const auto& y : x.second)
					temp.append(y->Name() + ", ");

			if (map.tile(Point{ p.x() + offset.x(), p.y() + offset.y() }).braindrainer())
				temp.append("BRAINDRAINER, ");

			if (temp.empty())
				ret.append("empty.\n");
			else
			{
				ret.append(temp.substr(0, temp.length() - 2) + ".\n");
				temp.clear();
			}
		}

	return ret;
}

std::string CommandHandler::Attack(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
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

	double dmg{ data.CurrentPlayer().selected()->hand()->Damage() };

	data.CurrentPlayer().action();

	if (data.OtherPlayer().getAmazon(v[1]).riding())
	{
		if (data.OtherPlayer().getAmazon(v[1]).dino()->Health() - dmg <= 0.0)
		{
			data.OtherPlayer().getAmazon(v[1]).dino()->Health(0.0);
			map.tile(map.find(&data.OtherPlayer().getAmazon(v[1]))).add(move(data.OtherPlayer().getAmazon(v[1]).riding()));
			return v[1] + "'s dino died.\n";
		}

		data.OtherPlayer().getAmazon(v[1]).dino()->Health(data.OtherPlayer().getAmazon(v[1]).dino()->Health() - dmg);
		return v[1] + "'s dino suffered " + std::to_string(static_cast<int>(round(dmg))) + " points of damage.\n";
	}
		

	if (data.OtherPlayer().getAmazon(v[1]).health() - dmg <= 0.0)
	{
		data.OtherPlayer().getAmazon(v[1]).health(0.0);
		data.OtherPlayer().decAlive();
		return v[1] + " died.\n";
	}

	data.OtherPlayer().getAmazon(v[1]).health(data.OtherPlayer().getAmazon(v[1]).health() - dmg);
	return v[1] + " suffered " + std::to_string(static_cast<int>(round(dmg))) + " points of damage.\n";
}

std::string CommandHandler::Pickup(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!ItemFactory::IsValid(v[1]))
		return "Invalid item type.\n";

	Point p{ map.find(data.CurrentPlayer().selected()) };

	if (!map.tile(p).has(v[1]))
		return v[1] + " cannot be found on the current tile.\n";

	if (!data.CurrentPlayer().selected()->hasFreeSlot(ItemFactory::TypeOf(v[1])))
		return "Can't pick up " + v[1] + ". " + data.CurrentPlayer().selected()->name() + "'s inventory is full.\n";

	data.CurrentPlayer().selected()->take(map.tile(p).remove(v[1]));

	data.CurrentPlayer().action();

	return "Picked up " + v[1] + ".\n";
}

std::string CommandHandler::Drop(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!ItemFactory::IsValid(v[1]))
		return "Invalid item type.\n";

	if (!data.CurrentPlayer().selected()->hasItem(v[1]))
		return v[1] + " cannot be found in " + data.CurrentPlayer().selected()->name() + "'s inventory.\n";

	Point p{ map.find(data.CurrentPlayer().selected()) };

	std::unique_ptr<Item> item{ data.CurrentPlayer().selected()->drop(v[1]) };

	if (item.get() == data.CurrentPlayer().selected()->hand())
		data.CurrentPlayer().selected()->hand(nullptr);

	map.tile(p).add(move(item));

	data.CurrentPlayer().action();

	return v[1] + " dropped.\n";
}

std::string CommandHandler::Equip(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->health() == 0.0)
		return data.CurrentPlayer().selected()->name() + " is dead.\n";

	if (!ItemFactory::IsValid(v[1]) || ItemFactory::TypeOf(v[1]) != ItemType::gun)
		return "Invalid weapon type.\n";

	if (!data.CurrentPlayer().selected()->hasItem(v[1]))
		return v[1] + " cannot be found in " + data.CurrentPlayer().selected()->name() + "'s inventory.\n";

	data.CurrentPlayer().selected()->hand(static_cast<Gun*>(data.CurrentPlayer().selected()->item(v[1])));

	return v[1] + " equipped.\n";
}

std::string CommandHandler::End(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	data.turn();

	std::vector<std::pair<Point, std::unique_ptr<BrainDrainer>>> drainers;

	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map.size(); j++)
			if (map.tile(Point{ j, i }).braindrainer())
				drainers.emplace_back(make_pair(Point{ j, i }, map.tile(Point{ j, i }).remove()));

	std::vector<Point> offsets;
	offsets.reserve(9);

	std::mt19937_64 mt{ std::random_device{}() };

	std::string ret;

	for (auto& pair : drainers)
	{
		offsets.clear();
		
		for (int i = -1; i != 2; i++)
			for (int j = -1; j != 2; j++)
				offsets.emplace_back(Point{ i, j });
		
		while(true)
		{
			std::uniform_int_distribution<size_t> dist{ 0, offsets.size() - 1 };
			size_t rnd{ dist(mt) };

			if (pair.first.x() + offsets.at(rnd).x() >= 0 && pair.first.x() + offsets.at(rnd).x() < map.size() && pair.first.y() + offsets.at(rnd).y() >= 0 && pair.first.y() + offsets.at(rnd).y() < map.size() && !map.tile(Point(pair.first.x() + offsets.at(rnd).x(), pair.first.y() + offsets.at(rnd).y())).braindrainer())
			{
				map.tile(Point{ pair.first.x() + offsets.at(rnd).x(), pair.first.y() + offsets.at(rnd).y() }).add(move(pair.second));
				for (auto& x : map.tile(Point{ pair.first.x() + offsets.at(rnd).x(), pair.first.y() + offsets.at(rnd).y() }).AmazonContainer())
					if (x->health())
						ret.append(map.tile(Point{ pair.first.x() + offsets.at(rnd).x(), pair.first.y() + offsets.at(rnd).y() }).braindrainer()->Attack(*x, map.tile(Point{ pair.first.x() + offsets.at(rnd).x(), pair.first.y() + offsets.at(rnd).y() }), data));
				break;
			}

			offsets.erase(offsets.begin() + rnd);
		}

	}

	return ret.append("\n### END OF TURN ###\n");
}

std::string CommandHandler::Tame(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
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

	const auto& dinos = map.tile(map.find(data.CurrentPlayer().selected())).DinoContainer();

	if (dinos.empty())
		return "There are no dinos nearby.\n";

	Dino* temp{ dinos.front().get() };

	for (const auto& x : dinos)
		if (x->Health() >= temp->Health() && !x->Tamed())
			temp = x.get();

	if (temp->Tamed())
		return "There are no free dinos nearby.\n";

	data.CurrentPlayer().selected()->dino(temp);
	temp->Tamed(!temp->Tamed());

	return "Dino (" + std::to_string(static_cast<int>(round(temp->Health()))) + " HP) tamed.\n";
}

std::string CommandHandler::Geton(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
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

	const Point point{ map.find(data.CurrentPlayer().selected()) };

	if (!map.tile(point).has(data.CurrentPlayer().selected()->dino()))
		return data.CurrentPlayer().selected()->name() + "'s dino is not nearby.\n";

	if (data.CurrentPlayer().selected()->dino()->Health() == 0.0)
		return data.CurrentPlayer().selected()->name() + "'s dino is dead.\n";

	data.CurrentPlayer().selected()->riding(map.tile(point).remove(data.CurrentPlayer().selected()->dino()));
	return data.CurrentPlayer().selected()->name() + " got on their dino.\n";
}

std::string CommandHandler::Getoff(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
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

	return data.CurrentPlayer().selected()->name() + " got off of their dino.\n";
}

std::string CommandHandler::List(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	std::string ret;

	for (const auto& x : data.CurrentPlayer().AmazonContainer())
		ret.append(x.first + ", ");

	if (ret.empty())
		return "You don't have amazons.\n";

	return "Your amazons: " + ret.substr(0, ret.size() - 2) + ".\n";
}

std::string CommandHandler::Status(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";
	
	Amazon* selected{ data.CurrentPlayer().selected() };

	std::string ret{ selected->name() + ".\n" };
	ret.append(std::to_string(static_cast<int>(round(selected->health()))) + " HP.\n");

	Point location{ map.find(selected) };

	ret.append("On (" + std::to_string(location.x() + 1) + ", " + std::to_string(location.y() + 1) + ").\n");
	ret.append("Holding: " + (selected->hand() ? "a " + selected->hand()->Name() : "nothing") + ".\n");
	ret.append("Inventory: ");

	std::string temp;
	
	for (const auto& x : selected->inventory())
		for (const auto& y : x.second)
			temp.append(y->Name() + ", ");

	if (temp.empty())
		ret.append("empty.\n");
	else
		ret.append(temp.substr(0, temp.size() - 2) + ".\n");

	ret.append("Dino: " + (selected->dino() ? std::to_string(static_cast<int>(round(selected->dino()->Health()))) + " HP" : "none") + ".\n");
	return ret.append(selected->riding() ? "Riding.\n" : "Not riding.\n");
}

std::string CommandHandler::Steps(const std::vector<std::string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	return "Remaining actions: " + std::to_string(data.MaxActions() - data.CurrentPlayer().actions()) + ".\n"
	"Living amazons: " + std::to_string(data.CurrentPlayer().alive()) + ".\n"
	"Spawns: " + std::to_string(data.CurrentPlayer().spawns()) + ".\n"
	"Possible spawns: " + std::to_string(std::min<size_t>(data.MaxSpawns() - data.CurrentPlayer().spawns(), data.MaxAlive() - data.CurrentPlayer().alive())) + ".\n";
}