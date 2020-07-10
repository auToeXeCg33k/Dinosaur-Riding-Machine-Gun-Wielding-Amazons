#include "command.h"
#include <stdexcept>

using namespace std;


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

	map.tile(0, 0).place(&data.CurrentPlayer().GetAmazon(v[1]));

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
		map.tile(y, x).place(data.CurrentPlayer().selected());

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

	Point loc = map.location(data.CurrentPlayer().selected());
	string ret;
	string temp;

	for (const auto& x : map.tile(loc.y, loc.x).amazon_list())
		if (x != data.CurrentPlayer().selected())
			temp.append(x->get_name() + ", ");

	for (const auto& x : map.tile(loc.y, loc.x).dino_list())
		temp.append("dino(" + to_string(static_cast<int>(round(x->get_hp()))) + " HP), ");

	for (const auto& x : map.tile(loc.y, loc.x).item_list())
		temp.append(x->get_name() + ", ");

	if (temp.empty())
		ret.append("Current tile empty.\n");

	else
	{
		ret.append("Current tile: " + temp.substr(0, temp.length() - 2) + ".\n");
		temp.clear();
	}


	if (loc.y + 1 < map.get_size())
	{
		for (const auto& x : map.tile(loc.y + 1, loc.x).amazon_list())
			temp.append(x->get_name() + ", ");

		for (const auto& x : map.tile(loc.y + 1, loc.x).dino_list())
			temp.append("dino(" + to_string(static_cast<int>(round(x->get_hp()))) + " HP), ");

		for (const auto& x : map.tile(loc.y + 1, loc.x).item_list())
			temp.append(x->get_name() + ", ");

		if (temp.empty())
			ret.append("Northern tile empty.\n");

		else
		{
			ret.append("North: " + temp.substr(0, temp.length() - 2) + ".\n");
			temp.clear();
		}
	}


	if (loc.y + 1 < map.get_size() && loc.x + 1 < map.get_size())
	{
		for (const auto& x : map.tile(loc.y + 1, loc.x + 1).amazon_list())
			temp.append(x->get_name() + ", ");

		for (const auto& x : map.tile(loc.y + 1, loc.x + 1).dino_list())
			temp.append("dino(" + to_string(static_cast<int>(round(x->get_hp()))) + " HP), ");

		for (const auto& x : map.tile(loc.y + 1, loc.x + 1).item_list())
			temp.append(x->get_name() + ", ");

		if (temp.empty())
			ret.append("Northeastern tile empty.\n");

		else
		{
			ret.append("North East: " + temp.substr(0, temp.length() - 2) + ".\n");
			temp.clear();
		}
	}


	if (loc.x + 1 < map.get_size())
	{
		for (const auto& x : map.tile(loc.y, loc.x + 1).amazon_list())
			temp.append(x->get_name() + ", ");

		for (const auto& x : map.tile(loc.y, loc.x + 1).dino_list())
			temp.append("dino(" + to_string(static_cast<int>(round(x->get_hp()))) + " HP), ");

		for (const auto& x : map.tile(loc.y, loc.x + 1).item_list())
			temp.append(x->get_name() + ", ");

		if (temp.empty())
			ret.append("Eastern tile empty.\n");

		else
		{
			ret.append("East: " + temp.substr(0, temp.length() - 2) + ".\n");
			temp.clear();
		}
	}


	if (loc.x + 1 < map.get_size() && loc.y - 1 >= 0)
	{
		for (const auto& x : map.tile(loc.y - 1, loc.x + 1).amazon_list())
			temp.append(x->get_name() + ", ");

		for (const auto& x : map.tile(loc.y - 1, loc.x + 1).dino_list())
			temp.append("dino(" + to_string(static_cast<int>(round(x->get_hp()))) + " HP), ");

		for (const auto& x : map.tile(loc.y - 1, loc.x + 1).item_list())
			temp.append(x->get_name() + ", ");

		if (temp.empty())
			ret.append("Southeastern tile empty.\n");

		else
		{
			ret.append("South East: " + temp.substr(0, temp.length() - 2) + ".\n");
			temp.clear();
		}
	}


	if (loc.y - 1 >= 0)
	{
		for (const auto& x : map.tile(loc.y - 1, loc.x).amazon_list())
			temp.append(x->get_name() + ", ");

		for (const auto& x : map.tile(loc.y - 1, loc.x).dino_list())
			temp.append("dino(" + to_string(static_cast<int>(round(x->get_hp()))) + " HP), ");

		for (const auto& x : map.tile(loc.y - 1, loc.x).item_list())
			temp.append(x->get_name() + ", ");

		if (temp.empty())
			ret.append("Southern tile empty.\n");

		else
		{
			ret.append("South: " + temp.substr(0, temp.length() - 2) + ".\n");
			temp.clear();
		}
	}


	if (loc.y - 1 >= 0 && loc.x - 1 >= 0)
	{
		for (const auto& x : map.tile(loc.y - 1, loc.x - 1).amazon_list())
			temp.append(x->get_name() + ", ");

		for (const auto& x : map.tile(loc.y - 1, loc.x - 1).dino_list())
			temp.append("dino(" + to_string(static_cast<int>(round(x->get_hp()))) + " HP), ");

		for (const auto& x : map.tile(loc.y - 1, loc.x - 1).item_list())
			temp.append(x->get_name() + ", ");

		if (temp.empty())
			ret.append("Southwestern tile empty.\n");

		else
		{
			ret.append("South West: " + temp.substr(0, temp.length() - 2) + ".\n");
			temp.clear();
		}
	}


	if (loc.x - 1 >= 0)
	{
		for (const auto& x : map.tile(loc.y, loc.x - 1).amazon_list())
			temp.append(x->get_name() + ", ");

		for (const auto& x : map.tile(loc.y, loc.x - 1).dino_list())
			temp.append("dino(" + to_string(static_cast<int>(round(x->get_hp()))) + " HP), ");

		for (const auto& x : map.tile(loc.y, loc.x - 1).item_list())
			temp.append(x->get_name() + ", ");

		if (temp.empty())
			ret.append("Western tile empty.\n");

		else
		{
			ret.append("West: " + temp.substr(0, temp.length() - 2) + ".\n");
			temp.clear();
		}
	}


	if (loc.y + 1 < map.get_size() && loc.x - 1 >= 0)
	{
		for (const auto& x : map.tile(loc.y + 1, loc.x - 1).amazon_list())
			temp.append(x->get_name() + ", ");

		for (const auto& x : map.tile(loc.y + 1, loc.x - 1).dino_list())
			temp.append("dino(" + to_string(static_cast<int>(round(x->get_hp()))) + " HP), ");

		for (const auto& x : map.tile(loc.y + 1, loc.x - 1).item_list())
			temp.append(x->get_name() + ", ");

		if (temp.empty())
			ret.append("Northwestern tile empty.\n");

		else
		{
			ret.append("North West: " + temp.substr(0, temp.length() - 2) + ".\n");
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
	Dino* dino(data.OtherPlayer().GetAmazon(v[1]).get_dino());

	data.CurrentPlayer().actions()++;

	if (dino && dino->get_hp() != 0.0)
	{
		if (dino->get_hp() - dmg < 0.0)
			dino->get_hp() = 0.0;
		else
			dino->get_hp() -= dmg;

		if (dino->get_hp() == 0.0)
			return v[1] + "'s dino died.\n";

		return v[1] + "'s dino suffered " + to_string(static_cast<int>(round(dmg))) + " points of damage.\n";
	}

	if (data.OtherPlayer().GetAmazon(v[1]).get_hp() - dmg < 0.0)
		data.OtherPlayer().GetAmazon(v[1]).get_hp() = 0.0;
	else
		data.OtherPlayer().GetAmazon(v[1]).get_hp() -= dmg;

	if (data.OtherPlayer().GetAmazon(v[1]).get_hp() == 0.0)
	{
		data.CurrentPlayer().alive()--;
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