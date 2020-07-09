#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <forward_list>
#include <memory>
#include <random>

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
	inline static const unordered_map<ItemType, vector<string>> types
	{
		{ItemType::gun, {"pistol", "shotgun", "katana", "minigun", "rocket"}}
	};


	inline static const unordered_map<ItemType, int> typeLimits
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
	unordered_map<ItemType, vector<unique_ptr<Item>>> inventory;
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
	unordered_map<ItemType, vector<unique_ptr<Item>>> items;


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


	//lots of copying. needs a rework
	forward_list<Amazon*> amazon_list() const
	{
		forward_list<Amazon*> ret;

		for (auto x : amazons)
			ret.push_front(x);

		return ret;
	}

	
	forward_list<Dino*> dino_list() const
	{
		forward_list<Dino*> ret;

		for (auto& x : dinos)
			ret.push_front(x.get());

		return ret;
	}


	forward_list<Item*> item_list() const
	{
		forward_list<Item*> ret;;

		for (auto& x : items)
			for (auto& y : x.second)
				ret.push_front(y.get());

		return ret;
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
	unordered_map<string, unique_ptr<Amazon>> amazon_map;
	Amazon* pSelected;
	int nActions;
	int nAlive;


public:
	Player(string_view name) : sName(name), pSelected(nullptr), nActions(0), nAlive(0) {}


	const string& name()
	{
		return sName;
	}


	int& actions()
	{
		return nActions;
	}


	int& alive()
	{
		return nAlive;
	}


	int spawns()
	{
		return amazon_map.size();
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
	const int nMaxSpawns;
	const int nMaxAlive;


public:
	GameData(int i) : p1("Player 1"), p2("Player 2"), active(false), nMaxActions(i == 1 ? 3 : 3), nMaxSpawns(i == 1 ? 6 : 6), nMaxAlive(i == 1 ? 3 : 3) {}


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


	int MaxSpawns()
	{
		return nMaxSpawns;
	}


	int MaxAlive()
	{
		return nMaxAlive;
	}


	void turn()
	{
		active = !active;
		p1.actions() = 0;
		p2.actions() = 0;
	}
};





class Command
{
public:
	virtual string exec(const vector<string>& v, Map& map, GameData& data) const noexcept = 0;
};





class New : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data) const noexcept
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
};





class Select : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data) const noexcept
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
	string exec(const vector<string>& v, Map& map, GameData& data) const noexcept
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
};





class Help : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data) const noexcept
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
			"\"end\"\n"
			"\"exit\"\n";
	}
};





class Lookaround : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data) const noexcept
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
		
		/*for (const auto& x : map.tile(loc.y, loc.x).amazon_list())
			if (x != data.CurrentPlayer().selected())
				temp += x->get_name() + ", ";

		for (const auto& x : map.tile(loc.y, loc.x).dino_list())
			temp += "dino(" + to_string(x->get_hp()) + "), ";

		for (const auto& x : map.tile(loc.y, loc.x).item_list())
				temp += x->get_name() + ", ";

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
				temp += x->get_name() + ", ";

			for (const auto& x : map.tile(loc.y + 1, loc.x).dino_list())
				temp += "dino(" + to_string(x->get_hp()) + "), ";

			for (const auto& x : map.tile(loc.y + 1, loc.x).item_list())
				temp += x->get_name() + ", ";

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
				temp += x->get_name() + ", ";

			for (const auto& x : map.tile(loc.y + 1, loc.x + 1).dino_list())
				temp += "dino(" + to_string(x->get_hp()) + "), ";

			for (const auto& x : map.tile(loc.y + 1, loc.x + 1).item_list())
				temp += x->get_name() + ", ";

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
				temp += x->get_name() + ", ";

			for (const auto& x : map.tile(loc.y, loc.x + 1).dino_list())
				temp += "dino(" + to_string(x->get_hp()) + "), ";

			for (const auto& x : map.tile(loc.y, loc.x + 1).item_list())
				temp += x->get_name() + ", ";

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
				temp += x->get_name() + ", ";

			for (const auto& x : map.tile(loc.y - 1, loc.x + 1).dino_list())
				temp += "dino(" + to_string(x->get_hp()) + "), ";

			for (const auto& x : map.tile(loc.y - 1, loc.x + 1).item_list())
					temp += x->get_name() + ", ";

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
				temp += x->get_name() + ", ";

			for (const auto& x : map.tile(loc.y - 1, loc.x).dino_list())
				temp += "dino(" + to_string(x->get_hp()) + "), ";

			for (const auto& x : map.tile(loc.y - 1, loc.x).item_list())
				temp += x->get_name() + ", ";

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
				temp += x->get_name() + ", ";

			for (const auto& x : map.tile(loc.y - 1, loc.x - 1).dino_list())
				temp += "dino(" + to_string(x->get_hp()) + "), ";

			for (const auto& x : map.tile(loc.y - 1, loc.x - 1).item_list())
				temp += x->get_name() + ", ";

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
				temp += x->get_name() + ", ";

			for (const auto& x : map.tile(loc.y, loc.x - 1).dino_list())
				temp += "dino(" + to_string(x->get_hp()) + "), ";

			for (const auto& x : map.tile(loc.y, loc.x - 1).item_list())
				temp += x->get_name() + ", ";

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
				temp += x->get_name() + ", ";

			for (const auto& x : map.tile(loc.y + 1, loc.x - 1).dino_list())
				temp += "dino(" + to_string(x->get_hp()) + "), ";

			for (const auto& x : map.tile(loc.y + 1, loc.x - 1).item_list())
				temp += x->get_name() + ", ";

			if (temp.empty())
				ret.append("Northwestern tile empty.\n");

			else
			{
				ret.append("North West: " + temp.substr(0, temp.length() - 2) + ".\n");
				temp.clear();
			}
		}*/
		return ret;
	}
};





class Attack : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data) const noexcept
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

			return v[1] + "'s dino suffered " + to_string(dmg) + " points of damage.\n";
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

		return v[1] + " suffered " + to_string(dmg) + " points of damage.\n";
	}
};





class Pickup : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data) const noexcept
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
};





class Drop : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data) const noexcept
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
};





class Equip : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data) const noexcept
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
};





class End : public Command
{
public:
	string exec(const vector<string>& v, Map& map, GameData& data) const noexcept
	{
		if (v.size() != 1)
			return "Ivalid arguments.\n";

		data.turn();

		return "\n### END OF TURN ###\n";
	}
};





class Interpreter
{
private:
	unordered_map<string, const unique_ptr<const Command>> commands;


public:
	Interpreter()
	{
		commands.emplace("new", make_unique<const New>());
		commands.emplace("select", make_unique<const Select>());
		commands.emplace("move", make_unique<const Move>());
		commands.emplace("help", make_unique<const Help>());
		commands.emplace("attack", make_unique<const Attack>());
		commands.emplace("lookaround", make_unique<const Lookaround>());
		commands.emplace("pickup", make_unique<const Pickup>());
		commands.emplace("drop", make_unique<const Drop>());
		commands.emplace("equip", make_unique<const Equip>());
		commands.emplace("end", make_unique<const End>());
	}


	string interpret(const vector<string>& vec, Map& map, GameData& data) const noexcept
	{
		if (commands.find(vec[0]) == commands.end())
			return "Invalid command.\n";

		return commands.at(vec[0])->exec(vec, map, data);
	}
};





int ReadGameMode()
{
	cout << "Enter gamemode number: ";

	string input;
	int mode;

	while (1)
	{
		getline(cin, input);

		try
		{
			mode = stoi(input);

			if (mode < 1 || mode > 1)
			{
				cout << "Invalid gamemode. Try again: ";
				continue;
			}
				
			return mode;
		}

		catch (const invalid_argument&)
		{
			cout << "Not a number. Try again: ";
		}
	}
}





void ProcessInput(string_view input, vector<string>& words)
{
	string word;

	for (int i = 0; i < input.length(); i++)
	{
		if (input.at(i) != ' ')
			word.push_back(input.at(i));

		if (i == input.length() - 1 && !word.empty())
		{
			words.push_back(word);
			break;
		}

		if (input.at(i) == ' ' && !word.empty())
		{
			words.push_back(word);
			word.clear();
		}
	}
}





int main()
{
	const int gameMode(ReadGameMode());

	const Interpreter interpreter;
	GameData data(gameMode);
	Map map(gameMode);

	cout << "\nMap size is " << map.get_size() << "x" << map.get_size() << ".\n"
		"The maximum number of actions per turn is " << data.MaxActions() << ".\n"
		"The maximum number of spawns is " << data.MaxSpawns() << ".\n"
		"The maximum number of living amazons is " << data.MaxAlive() << ".\n\n";

	string input;
	vector<string> words;

	while (1)
	{
		cout << data.CurrentPlayer().name() << ": ";
		getline(cin, input);

		words.clear();

		ProcessInput(input, words);

		if (words.size() == 0)
			continue;

		if (words.at(0) == "exit")
			return 0;

		cout << interpreter.interpret(words, map, data) << endl;
	}
}