#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <random>
#include <memory>




using namespace std;




struct Point
{
	const char x;
	const char y;


	Point(const char x, const char y) : x(x), y(y) {}


	bool operator==(const Point p) const
	{
		return x == p.x && y == p.y;
	}


	bool operator!=(const Point p) const
	{
		return x != p.x || y != p.y;
	}
};




enum class ItemType { gun };




class Item
{
protected:
	const string name;
	Item(string_view name) : name(name) {}


public:
	const string& get_name()
	{
		return name;
	}
};




class Gun : public Item
{
private:
	const double min;
	const double max;
	const char rate;


public:
	Gun(string_view name, const double min, const double max, const int rate) : Item(name), min(min), max(max), rate(rate) {}

	double get_dmg()
	{
		random_device rd;
		mt19937_64 mt(rd());
		uniform_real_distribution<> dist(0, 1);

		double dmg = 0.0;

		for (int i = 0; i < rate; i++)
			dmg += (max - min) * dist(mt) + min;

		return dmg;
	}
};




class ItemFactory
{
private:
	inline static const map<ItemType, vector<string>> types
	{
		{ItemType::gun, {"pistol", "shotgun", "katana", "minigun", "rocket"}}
	};


	inline static const map<ItemType, int> typeLimits
	{
		{ItemType::gun, 2}
	};


public:
	static ItemType lookUp(string_view name)
	{
		for (auto x : types)
			for (auto y : x.second)
				if (y == name)
					return x.first;
	}


	static bool isValid(string_view name)
	{
		for (auto x : types)
			for (auto y : x.second)
				if (y == name)
					return true;
		return false;
	}


	static int typeLimit(const ItemType type)
	{
		return typeLimits.at(type);
	}


	static unique_ptr<Item> CreateItem(string_view name)
	{
		if (name == "pistol")
			return make_unique<Gun>("pistol", 15.0, 20.0, 2);

		if (name == "shotgun")
			return make_unique<Gun>("shotgun", 50.0, 75.0, 1);

		if (name == "katana")
			return make_unique<Gun>("katana", 20.0, 30.0, 3);

		if (name == "minigun")
			return make_unique<Gun>("minigun", 1.5, 5.0, 30);

		if (name == "rocket")
			return make_unique<Gun>("rocket", 90.0, 120.0, 1);
	}
};




class Dino
{
private:
	double hp;


public:
	Dino() : hp(100.0) {}


	double& get_hp()
	{
		return hp;
	}
};




class Amazon
{
private:
	const string name;
	double hp;
	map<ItemType, vector<unique_ptr<Item>>> inventory;
	Gun* held;
	unique_ptr<Dino> dino;
	
	
public:
	Amazon(string_view name) : name(name), hp(100.0), dino(nullptr), held(nullptr)
	{
		inventory.emplace(ItemType::gun, vector<unique_ptr<Item>>());
	}


	bool hasFreeSlot(ItemType type)
	{
		return inventory.at(type).size() < ItemFactory::typeLimit(type);
	}


	bool hasItem(string_view name)
	{
		for (auto& x : inventory.at(ItemFactory::lookUp(name)))
			if (x->get_name() == name)
				return true;
		return false;
	}


	void take(unique_ptr<Item>&& item)
	{
		inventory.at(ItemFactory::lookUp(item->get_name())).emplace_back(move(item));
	}


	unique_ptr<Item> remove(string_view name)
	{
		unique_ptr<Item> ret;
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


	Item* item(string_view name)
	{
		for (auto& x : inventory.at(ItemFactory::lookUp(name)))
			if (x->get_name() == name)
				return x.get();
	}
	
	
	const string& get_name()
	{
		return name;
	}


	double& get_hp()
	{
		return hp;
	}


	Gun*& hand()
	{
		return held;
	}


	Dino* get_dino()
	{
		return dino.get();
	}
};




class Tile
{
private:
	unordered_set<Amazon*> amazons;
	unordered_set<unique_ptr<Dino>> dinos;
	map<ItemType, vector<unique_ptr<Item>>> items;


public:
	Tile()
	{
		items.emplace(ItemType::gun, vector<unique_ptr<Item>>());
	}


	Tile(Tile&& other) noexcept : amazons(move(other.amazons)), dinos(move(other.dinos)), items(move(other.items)) {}


	bool has(string_view name)
	{
		for (auto& x : items.at(ItemFactory::lookUp(name)))
			if (x->get_name() == name)
				return true;
		return false;
	}


	void add(unique_ptr<Item>&& item)
	{
		items.at(ItemFactory::lookUp(item->get_name())).emplace_back(move(item));
	}


	unique_ptr<Item> remove(string_view name)
	{
		for (int i = 0; i < items.at(ItemFactory::lookUp(name)).size(); i++)
			if (items.at(ItemFactory::lookUp(name)).at(i)->get_name() == name)
			{
				unique_ptr<Item> ret(move(items.at(ItemFactory::lookUp(name)).at(i)));
				items.at(ItemFactory::lookUp(name)).erase(items.at(ItemFactory::lookUp(name)).begin() + i);
				return ret;
			}
	}


	bool spawnDino()
	{
		if (dinos.size() != 0)
			return false;

		dinos.emplace();
		return true;
	}
	


	bool spawnItem(string_view name)
	{
		if (items.at(ItemFactory::lookUp(name)).size() != 0)
			return false;

		items.at(ItemFactory::lookUp(name)).emplace_back(ItemFactory::CreateItem(name));
		return true;
	}


	void place(Amazon* amazon)
	{
		amazons.insert(amazon);
	}


	void remove(Amazon* amazon)
	{
		amazons.erase(amazon);
	}


	bool is_here(Amazon* amazon)
	{
		if (amazons.find(amazon) != amazons.end())
			return true;
		return false;
	}
};




class Map
{
private:
	vector<vector<Tile>> tiles;
	int size;


public:
	Map(const int i)
	{
		switch (i)
		{
		case 1:
		{
			size = 5;
			for (int i = 0; i < 5; i++)
			{
				tiles.emplace_back();
				for (int j = 0; j < 5; j++)
					tiles.at(i).emplace_back();
			}
			
			random_device rd;
			mt19937_64 mt(rd());

			uniform_int_distribution<> dist1(0, 4);
			
			for (int i = 0; i < 5; i++)
				while (!tiles.at(dist1(mt)).at(dist1(mt)).spawnDino());

			for (int i = 0; i < 2; i++)
			{
				while (!tiles.at(0).at(dist1(mt)).spawnItem("pistol"));
				while (!tiles.at(4).at(dist1(mt)).spawnItem("pistol"));
			}

			uniform_int_distribution<> dist2(0, 1);

			while (!tiles.at(dist2(mt)).at(dist1(mt)).spawnItem("shotgun"));
			while (!tiles.at(4 - dist2(mt)).at(dist1(mt)).spawnItem("shotgun"));
			while (!tiles.at(dist1(mt)).at(dist1(mt)).spawnItem("katana"));
			while (!tiles.at(2).at(dist1(mt)).spawnItem("minigun"));
			return;
		}

		default:
			throw invalid_argument("Invalid gamemode.");
		}
	}


	Tile& tile(const char y, const char x)
	{
		return tiles.at(y).at(x);
	}


	int get_size()
	{
		return size;
	}


	Point location(Amazon* amazon)
	{
		for (int i = 0; i < this->size; i++)
			for (int j = 0; j < this->size; j++)
				if (this->tiles.at(i).at(j).is_here(amazon))
					return Point(j, i);
	}
};




class Player
{
private:
	const string sName;
	int nActions;
	unordered_map<string, unique_ptr<Amazon>> amazon_map;
	Amazon* pSelected;


public:
	Player(string_view name) : sName(name), nActions(0), pSelected(nullptr) {}


	const string& name()
	{
		return sName;
	}


	int& actions()
	{
		return nActions;
	}


	bool ExistsAmazon(const string& name)
	{
		return amazon_map.find(name) != amazon_map.end();
	}


	void CreateAmazon(string_view name)
	{
		amazon_map.emplace(name, make_unique<Amazon>(name));
	}


	Amazon& GetAmazon(const string& name)
	{
		return *amazon_map.at(name);
	}


	Amazon*& selected()
	{
		return pSelected;
	}
};




class GameData
{
private:
	Player p1;
	Player p2;
	bool active;
	const int nMaxActions;


public:
	GameData() : p1("Player 1"), p2("Player 2"), active(false), nMaxActions(3) {}


	Player& CurrentPlayer()
	{
		return active ? p2 : p1;
	}


	Player& OtherPlayer()
	{
		return active ? p1 : p2;
	}


	int MaxActions()
	{
		return nMaxActions;
	}


	void turn()
	{
		active = !active;
	}
};





class Command
{
public:
	virtual string exec(const vector<string>& v, Map& map, GameData& data) = 0;
};




class New : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data)
	{
		if (v.size() != 2)
			return "Invalid arguments.\n";

		if (data.CurrentPlayer().ExistsAmazon(v[1]))
			return v[1] + " already exists.\n";

		data.CurrentPlayer().CreateAmazon(v[1]);

		map.tile(0, 0).place(&data.CurrentPlayer().GetAmazon(v[1]));

		data.CurrentPlayer().actions()++;

		return v[1] + " created.\n";
	}
};




class Select : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data)
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
};




class Move : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data)
	{
		if (v.size() != 3)
			return "Invalid arguments.\n";

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
			return "Incorrect arguments.\n";
		}
	}
};




class Help : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data)
	{
		return "Available commands:\n"
			"\"new <name>\"\n"
			"\"select <name>\"\n"
			"\"move <x> <y>\"\n"
			"\"look\"\n"
			"\"pickup <item>\"\n"
			"\"drop <item>\"\n"
			"\"equip <item>\"\n"
			"\"attack <name>\"\n"
			"\"help\"\n"
			"\"exit\"\n";
	}
};




class Look : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data)
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
		/*
		for (const auto& am : map.tile(loc.y, loc.x).get_amazons())
			if (am != data.CurrentPlayer().selected())
				temp += am->get_name() + ", ";
		for (const auto& din : map.tile(loc.y, loc.x).get_dinos())
			temp += "dino, ";
		for (auto i = 0; i < G_TYPE_NUMBER; i++)
			for (const auto& item : map.tile(loc.y, loc.x).get_items()[i])
				temp += item->get_name() + ", ";
		if (temp == "")
			ret += "Current tile empty.\n";
		else
		{
			ret += "Current tile: " + temp.substr(0, temp.length() - 2) + ".\n";
			temp = "";
		}

		if (loc.y + 1 < map.get_size())
		{
			for (const auto& am : map.tile(loc.y + 1, loc.x).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.tile(loc.y + 1, loc.x).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.tile(loc.y + 1, loc.x).get_items()[i])
					temp += item->get_name() + ", ";
			if (temp == "")
				ret += "Northern tile empty.\n";
			else
			{
				ret += "North: " + temp.substr(0, temp.length() - 2) + ".\n";
				temp = "";
			}
		}

		if (loc.y + 1 < map.get_size() && loc.x + 1 < map.get_size())
		{
			for (const auto& am : map.tile(loc.y + 1, loc.x + 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.tile(loc.y + 1, loc.x + 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.tile(loc.y + 1, loc.x + 1).get_items()[i])
					temp += item->get_name() + ", ";
			if (temp == "")
				ret += "Northeastern tile empty.\n";
			else
			{
				ret += "North East: " + temp.substr(0, temp.length() - 2) + ".\n";
				temp = "";
			}
		}

		if (loc.x + 1 < map.get_size())
		{
			for (const auto& am : map.tile(loc.y, loc.x + 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.tile(loc.y, loc.x + 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.tile(loc.y, loc.x + 1).get_items()[i])
					temp += item->get_name() + ", ";
			if (temp == "")
				ret += "Eastern tile empty.\n";
			else
			{
				ret += "East: " + temp.substr(0, temp.length() - 2) + ".\n";
				temp = "";
			}
		}

		if (loc.x + 1 < map.get_size() && loc.y - 1 >= 0)
		{
			for (const auto& am : map.tile(loc.y - 1, loc.x + 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.tile(loc.y - 1, loc.x + 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.tile(loc.y - 1, loc.x + 1).get_items()[i])
					temp += item->get_name() + ", ";
			if (temp == "")
				ret += "Southeastern tile empty.\n";
			else
			{
				ret += "South East: " + temp.substr(0, temp.length() - 2) + ".\n";
				temp = "";
			}
		}

		if (loc.y - 1 >= 0)
		{
			for (const auto am : map.tile(loc.y - 1, loc.x).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.tile(loc.y - 1, loc.x).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.tile(loc.y - 1, loc.x).get_items()[i])
					temp += item->get_name() + ", ";
			if (temp == "")
				ret += "Southern tile empty.\n";
			else
			{
				ret += "South: " + temp.substr(0, temp.length() - 2) + ".\n";
				temp = "";
			}
		}

		if (loc.y - 1 >= 0 && loc.x - 1 >= 0)
		{
			for (const auto& am : map.tile(loc.y - 1, loc.x - 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.tile(loc.y - 1, loc.x - 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.tile(loc.y - 1, loc.x - 1).get_items()[i])
					temp += item->get_name() + ", ";
			if (temp == "")
				ret += "Southwestern tile empty.\n";
			else
			{
				ret += "South West: " + temp.substr(0, temp.length() - 2) + ".\n";
				temp = "";
			}
		}

		if (loc.x - 1 >= 0)
		{
			for (const auto& am : map.tile(loc.y, loc.x - 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.tile(loc.y, loc.x - 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.tile(loc.y, loc.x - 1).get_items()[i])
					temp += item->get_name() + ", ";
			if (temp == "")
				ret += "Western tile empty.\n";
			else
			{
				ret += "West: " + temp.substr(0, temp.length() - 2) + ".\n";
				temp = "";
			}
		}

		if (loc.y + 1 < map.get_size() && loc.x - 1 >= 0)
		{
			for (const auto& am : map.tile(loc.y + 1, loc.x - 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.tile(loc.y + 1, loc.x - 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.tile(loc.y + 1, loc.x - 1).get_items()[i])
					temp += item->get_name() + ", ";
			if (temp == "")
				ret += "Northwestern tile empty.\n";
			else
			{
				ret += "North West: " + temp.substr(0, temp.length() - 2) + ".\n";
				temp = "";
			}
		}
		return ret;*/
	}
};




class Attack : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data)
	{
		if (v.size() != 2)
			return "Invalid arguments.\n";

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

			return v[1] + "'s dino suffered " + to_string(dmg) + " points of damage.\n";
		}

		if (data.OtherPlayer().GetAmazon(v[1]).get_hp() - dmg < 0.0)
			data.OtherPlayer().GetAmazon(v[1]).get_hp() = 0.0;
		else
			data.OtherPlayer().GetAmazon(v[1]).get_hp() -= dmg;

		if (data.OtherPlayer().GetAmazon(v[1]).get_hp() == 0.0)
			return v[1] + " died.\n";

		return v[1] + " suffered " + to_string(dmg) + " points of damage.\n";
	}
};




class Pickup : public Command
{
public:
	string exec(const vector<string>& vec, Map& map, GameData& data)
	{
		if (vec.size() != 2)
			return "Invalid arguments.\n";

		if (!data.CurrentPlayer().selected())
			return "Select an amazon first!\n";

		if (data.CurrentPlayer().selected()->get_hp() == 0.0)
			return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

		if (!ItemFactory::isValid(vec[1]))
			return "Invalid item type.\n";

		Point p = map.location(data.CurrentPlayer().selected());
		
		if (!map.tile(p.y, p.x).has(vec[1]))
			return vec[1] + " cannot be found on the current tile.\n";

		if (!data.CurrentPlayer().selected()->hasFreeSlot(ItemFactory::lookUp(vec[1])))
			return "Can't pick up " + vec[1] + ". " + data.CurrentPlayer().selected()->get_name() + "'s inventory is full.\n";
		
		data.CurrentPlayer().selected()->take(map.tile(p.y, p.x).remove(vec[1]));

		data.CurrentPlayer().actions()++;

		return "Picked up " + vec[1] + ".\n";
	}
};




class Drop : public Command
{
public:
	string exec(const vector<string>& vec, Map& map, GameData& data)
	{
		if (vec.size() != 2)
			return "Invalid arguments.\n";

		if (!data.CurrentPlayer().selected())
			return "Select an amazon first!\n";

		if (data.CurrentPlayer().selected()->get_hp() == 0.0)
			return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

		if (!ItemFactory::isValid(vec[1]))
			return "Invalid item type.\n";

		if (!data.CurrentPlayer().selected()->hasItem(vec[1]))
			return vec[1] + " cannot be found in " + data.CurrentPlayer().selected()->get_name() + "'s inventory.\n";

		Point p = map.location(data.CurrentPlayer().selected());

		unique_ptr<Item> item(data.CurrentPlayer().selected()->remove(vec[1]));

		if (item.get() == data.CurrentPlayer().selected()->hand())
			data.CurrentPlayer().selected()->hand() = nullptr;

		map.tile(p.y, p.x).add(move(item));

		data.CurrentPlayer().actions()++;

		return vec[1] + " dropped.\n";
	}
};




class Equip : public Command
{
public:
	string exec(const vector<string>& vec, Map& map, GameData& data)
	{
		if (vec.size() != 2)
			return "Invalid arguments.\n";

		if (!data.CurrentPlayer().selected())
			return "Select an amazon first!\n";

		if (data.CurrentPlayer().selected()->get_hp() == 0.0)
			return data.CurrentPlayer().selected()->get_name() + " is dead.\n";

		if (!ItemFactory::isValid(vec[1]) || ItemFactory::lookUp(vec[1]) != ItemType::gun)
			return "Invalid weapon type.\n";

		if (!data.CurrentPlayer().selected()->hasItem(vec[1]))
			return vec[1] + " cannot be found in " + data.CurrentPlayer().selected()->get_name() + "'s inventory.\n";

		data.CurrentPlayer().selected()->hand() = static_cast<Gun*>(data.CurrentPlayer().selected()->item(vec[1]));

		return vec[1] + " equipped.\n";
	}
};




class Interpreter
{
private:
	unordered_map<string, const unique_ptr<Command>> commands;

public:
	Interpreter()
	{
		commands.emplace("new", make_unique<New>());
		commands.emplace("select", make_unique<Select>());
		commands.emplace("move", make_unique<Move>());
		commands.emplace("help", make_unique<Help>());
		commands.emplace("attack", make_unique<Attack>());
		commands.emplace("look", make_unique<Look>());
		commands.emplace("pickup", make_unique<Pickup>());
		commands.emplace("drop", make_unique<Drop>());
		commands.emplace("equip", make_unique<Equip>());
	}


	string interpret(const vector<string>& vec, Map& map, GameData& data)
	{
		if (commands.find(vec[0]) == commands.end())
			return "Invalid command.\n";

		return commands.at(vec[0])->exec(vec, map, data);
	}
};




Map InitMap()
{
	cout << "Enter gamemode number: ";
	string input;

	while (1)
	{
		getline(cin, input);
		try
		{
			int i = stoi(input);
			try
			{
				Map m(i);

				cout << "Map of size " << m.get_size() << "x" << m.get_size() << " created.\n"
					"Type \"help\" for the list of available commands!\n" << endl;

				return m;
			}
			catch (invalid_argument& e)
			{
				cout << e.what() << " Try again: ";
			}
		}
		catch (invalid_argument&)
		{
			cout << "Not a number. Try again: ";
		}
	}
}




int main()
{
	GameData data;
	Map map(InitMap());
	Interpreter interpreter;
	string input;

	while (1)
	{
		cout << data.CurrentPlayer().name() + ": ";
		getline(cin, input);

		string word;
		vector<string> words;

		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] != ' ')
				word += input[i];
			if (i == input.length() - 1 && word != "")
			{
				words.push_back(word);
				break;
			}
			if (input[i] == ' ' && word != "")
			{
				words.push_back(word);
				word = "";
			}
		}

		if (words.size() == 0)
			continue;

		if (words[0] == "exit")
			return 0;

		cout << interpreter.interpret(words, map, data) << endl;
		
		if (data.CurrentPlayer().actions() == data.MaxActions())
			data.turn();
	}
}