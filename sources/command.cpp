#include "command.h"
#include <stdexcept>
#include <array>
#include <cmath>

using namespace std;


Command::~Command() {}


string New::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (data.CurrentPlayer().spawns() == data.MaxSpawns())
		return "Maximum number of spawns reached.\n";

	if (data.CurrentPlayer().alive() == data.MaxAlive())
		return "Maximum number of living amazons reached.\n";

	if (data.CurrentPlayer().ExistsAmazon(v[1]))
		return v[1] + " already exists.\n";

	data.CurrentPlayer().CreateAmazon(v[1]);

	map.tile(0, 0).add(&data.CurrentPlayer().GetAmazon(v[1]));

	data.CurrentPlayer().alive()++;
	data.CurrentPlayer().actions()++;

	return v[1] + " created.\n";
}


string Select::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().ExistsAmazon(v[1]))
		return v[1] + " does not exist.\n";

	if (data.CurrentPlayer().selected() && data.CurrentPlayer().selected()->get_name() == v[1])
		return v[1] + " is already selected.\n";

	data.CurrentPlayer().selected() = &data.CurrentPlayer().GetAmazon(v[1]);

	return v[1] + " selected.\n";
}


string Move::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 3)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->get_hp() == 0.0)
		return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

	try
	{
		int x = stoi(v[1]) - 1;
		int y = stoi(v[2]) - 1;
		Point p = map.location(data.CurrentPlayer().selected());

		if (x < 0 || y < 0 || x >= map.get_size() || y >= map.get_size())
			return "Target tile does not exist.\n";

		if (p.x + 1 < x || p.x - 1 > x || p.y + 1 < y || p.y - 1 > y)
			return "Target tile is too far.\n";

		if (p.x == x && p.y == y)
			return "Target tile matches the current one.\n";

		map.tile(p.y, p.x).remove(data.CurrentPlayer().selected());
		map.tile(y, x).add(data.CurrentPlayer().selected());

		data.CurrentPlayer().actions()++;

		return data.CurrentPlayer().selected()->get_name() + " moved to " + v[1] + ";" + v[2] + ".\n";
	}

	catch (invalid_argument&)
	{
		return "Invalid arguments.\n";
	}
}


string Help::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	return "Available commands:\n"
		"\"new <name>\"\n"
		"\"select <name>\"\n"
		"\"move <x> <y>\"\n"
		"\"lookaround\"\n"
		"\"tame\"\n"
		"\"geton\"\n"
		"\"getoff\"\n"
		"\"pickup <item>\"\n"
		"\"drop <item>\"\n"
		"\"equip <item>\"\n"
		"\"attack <name>\"\n"
		"\"help\"\n"
		"\"end\"\n"
		"\"exit\"\n";
}


string Lookaround::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->get_hp() == 0.0)
		return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

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

	Point p(map.location(data.CurrentPlayer().selected()));
	string ret;
	string temp;

	for (const auto& offset : offsets)
		if (p.x + offset.x >= 0 && p.x + offset.x < map.get_size() && p.y + offset.y >= 0 && p.y + offset.y < map.get_size())
		{
			for (const auto& x : map.tile(Point(p.x + offset.x, p.y + offset.y)).AmazonContainer())
				if (x != data.CurrentPlayer().selected())
					temp.append(x->get_name() + ", ");

			for (const auto& x : map.tile(Point(p.x + offset.x, p.y + offset.y)).DinoContainer())
				temp.append((x->tamed() ? "Tamed" : "Untamed") + static_cast<string>(" Dino (") +  to_string(static_cast<int>(round(x->get_hp()))) + " HP), ");

			for (const auto& x : map.tile(Point(p.x + offset.x, p.y + offset.y)).ItemContainer())
				for (const auto& y : x.second)
					temp.append(y->get_name() + ", ");

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


string Attack::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->get_hp() == 0.0)
		return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

	if (!data.CurrentPlayer().selected()->hand())
		return data.CurrentPlayer().selected()->get_name() + " is not holding any weapon.\n";

	if (!data.OtherPlayer().ExistsAmazon(v[1]))
		return "Enemy " + v[1] + " does not exist.\n";

	if (map.location(data.CurrentPlayer().selected()) != map.location(&data.OtherPlayer().GetAmazon(v[1])))
		return v[1] + " is out of range.\n";

	if (data.OtherPlayer().GetAmazon(v[1]).get_hp() == 0.0)
		return v[1] + " is already dead.\n";

	double dmg = data.CurrentPlayer().selected()->hand()->get_dmg();

	data.CurrentPlayer().actions()++;

	if (data.OtherPlayer().GetAmazon(v[1]).GetRiding())
	{
		if (data.OtherPlayer().GetAmazon(v[1]).GetDino()->get_hp() - dmg < 0.0)
			data.OtherPlayer().GetAmazon(v[1]).GetDino()->get_hp() = 0.0;
		else
			data.OtherPlayer().GetAmazon(v[1]).GetDino()->get_hp() -= dmg;

		if (data.OtherPlayer().GetAmazon(v[1]).GetDino()->get_hp() == 0.0)
		{
			map.tile(map.location(&data.OtherPlayer().GetAmazon(v[1]))).add(move(data.OtherPlayer().GetAmazon(v[1]).GetRiding()));
			return v[1] + "'s dino died.\n";
		}

		return v[1] + "'s dino suffered " + to_string(static_cast<int>(round(dmg))) + " points of damage.\n";
	}
		
		

	if (data.OtherPlayer().GetAmazon(v[1]).get_hp() - dmg < 0.0)
		data.OtherPlayer().GetAmazon(v[1]).get_hp() = 0.0;
	else
		data.OtherPlayer().GetAmazon(v[1]).get_hp() -= dmg;

	if (data.OtherPlayer().GetAmazon(v[1]).get_hp() == 0.0)
	{
		data.OtherPlayer().alive()--;
		return v[1] + " died.\n";
	}

	return v[1] + " suffered " + to_string(static_cast<int>(round(dmg))) + " points of damage.\n";
}


string Pickup::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->get_hp() == 0.0)
		return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

	if (!ItemFactory::isValid(v[1]))
		return "Invalid item type.\n";

	Point p = map.location(data.CurrentPlayer().selected());

	if (!map.tile(p.y, p.x).has(v[1]))
		return v[1] + " cannot be found on the current tile.\n";

	if (!data.CurrentPlayer().selected()->hasFreeSlot(ItemFactory::lookUp(v[1])))
		return "Can't pick up " + v[1] + ". " + data.CurrentPlayer().selected()->get_name() + "'s inventory is full.\n";

	data.CurrentPlayer().selected()->take(map.tile(p.y, p.x).remove(v[1]));

	data.CurrentPlayer().actions()++;

	return "Picked up " + v[1] + ".\n";
}


string Drop::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->get_hp() == 0.0)
		return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

	if (!ItemFactory::isValid(v[1]))
		return "Invalid item type.\n";

	if (!data.CurrentPlayer().selected()->hasItem(v[1]))
		return v[1] + " cannot be found in " + data.CurrentPlayer().selected()->get_name() + "'s inventory.\n";

	Point p = map.location(data.CurrentPlayer().selected());

	unique_ptr<Item> item(data.CurrentPlayer().selected()->remove(v[1]));

	if (item.get() == data.CurrentPlayer().selected()->hand())
		data.CurrentPlayer().selected()->hand() = nullptr;

	map.tile(p.y, p.x).add(move(item));

	data.CurrentPlayer().actions()++;

	return v[1] + " dropped.\n";
}


string Equip::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 2)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->get_hp() == 0.0)
		return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

	if (!ItemFactory::isValid(v[1]) || ItemFactory::lookUp(v[1]) != ItemType::gun)
		return "Invalid weapon type.\n";

	if (!data.CurrentPlayer().selected()->hasItem(v[1]))
		return v[1] + " cannot be found in " + data.CurrentPlayer().selected()->get_name() + "'s inventory.\n";

	data.CurrentPlayer().selected()->hand() = static_cast<Gun*>(data.CurrentPlayer().selected()->item(v[1]));

	return v[1] + " equipped.\n";
}


string End::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 1)
		return "Ivalid arguments.\n";

	data.turn();

	return "\n### END OF TURN ###\n";
}


string Tame::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 1)
		return "Ivalid arguments.\n";

	if (data.CurrentPlayer().actions() == data.MaxActions())
		return "Maximum number of actions reached.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->get_hp() == 0.0)
		return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

	if (data.CurrentPlayer().selected()->GetDino())
		return data.CurrentPlayer().selected()->get_name() + " already has a dino.\n";

	const auto& dinos(map.tile(map.location(data.CurrentPlayer().selected())).DinoContainer());

	if (dinos.empty())
		return "There are no dinos nearby.\n";

	Dino* temp(dinos.front().get());

	for (const auto& x : dinos)
		if (x->get_hp() >= temp->get_hp() && !x->tamed())
			temp = x.get();

	if (temp->tamed())
		return "There are no free dinos nearby.\n";

	data.CurrentPlayer().selected()->GetDino() = temp;
	temp->tamed() = !temp->tamed();

	return "Dino (" + to_string(static_cast<int>(round(temp->get_hp()))) + " HP) tamed.\n";
}


string Geton::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";

	if (data.CurrentPlayer().selected()->get_hp() == 0.0)
		return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

	if (!data.CurrentPlayer().selected()->GetDino())
		return data.CurrentPlayer().selected()->get_name() + " does not have a dino. Tame one first!\n";

	if (data.CurrentPlayer().selected()->GetRiding())
		return data.CurrentPlayer().selected()->get_name() + " is already riding their dino.\n";

	const auto point(map.location(data.CurrentPlayer().selected()));

	if (!map.tile(point).is_here(data.CurrentPlayer().selected()->GetDino()))
		return data.CurrentPlayer().selected()->get_name() + "'s dino is not nearby.\n";

	if (data.CurrentPlayer().selected()->GetDino()->get_hp() == 0.0)
		return data.CurrentPlayer().selected()->get_name() + "'s dino is dead.\n";

	data.CurrentPlayer().selected()->GetRiding() = map.tile(point).remove(data.CurrentPlayer().selected()->GetDino());
	return data.CurrentPlayer().selected()->get_name() + " got on their dino.\n";
}


string Getoff::exec(const vector<string>& v, Map& map, GameData& data) const noexcept
{
	if (v.size() != 1)
		return "Invalid arguments.\n";

	if (!data.CurrentPlayer().selected())
		return "Select an amazon first!\n";
	
	if (data.CurrentPlayer().selected()->get_hp() == 0.0)
		return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

	if (!data.CurrentPlayer().selected()->GetDino())
		return data.CurrentPlayer().selected()->get_name() + " does not have a dino. Tame one first!\n";

	if (!data.CurrentPlayer().selected()->GetRiding())
		return data.CurrentPlayer().selected()->get_name() + " is currently not riding their dino.\n";

	map.tile(map.location(data.CurrentPlayer().selected())).add(move(data.CurrentPlayer().selected()->GetRiding()));

	return data.CurrentPlayer().selected()->get_name() + " got off their dino.\n";
}