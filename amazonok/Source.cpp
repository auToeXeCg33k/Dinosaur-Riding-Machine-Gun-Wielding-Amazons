#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <memory>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::unique_ptr;
using std::move;




constexpr char G_TYPE_NUMBER = 1;




enum TYPE : bool
{
	GUN
};




const unordered_map<string, TYPE> G_GET_TYPE
{
	{"pistol", TYPE::GUN},
	{"shotgun", TYPE::GUN},
	{"katana", TYPE::GUN},
	{"minigun", TYPE::GUN},
	{"rocketlauncher", TYPE::GUN}
};




const unordered_map<TYPE, char> G_TYPE_SIZE
{
	{TYPE::GUN, 2}
};




struct point
{
	const char x;
	const char y;
	point(char x, char y) noexcept : x(x), y(y) {}
	bool operator==(const point& p) const noexcept
	{
		return x == p.x && y == p.y;
	}
	bool operator!=(const point& p) const noexcept
	{
		return x != p.x || y != p.y;
	}
};




class Item
{
protected:
	const string name;
	Item(const string& name) noexcept : name(name) {}

public:
	const string& get_name() const noexcept
	{
		return name;
	}
};




class Gun : public Item
{
protected:
	const double min;
	const double max;
	const char rate;
	Gun(const string& name, const double& min, const double& max, const int& rate) noexcept : Item(name), min(min), max(max), rate(rate) {}

public:
	const double get_dmg() const noexcept
	{
		std::random_device rd;
		std::mt19937_64 mt(rd());
		std::uniform_real_distribution<> dist(0, 1);
		double dmg = 0.0;
		char i = 0;
		while (i++ < rate)
			dmg += (max - min) * dist(mt) + min;
		return dmg;
	}
};




class Pistol : public Gun
{
public:
	Pistol() noexcept : Gun("pistol", 15.0f, 20.0f, 2) {}
};




class Shotgun : public Gun
{
public:
	Shotgun() noexcept : Gun("shotgun", 50.0f, 75.0f, 1) {}
};




class Gepkatana : public Gun
{
public:
	Gepkatana() noexcept : Gun("katana", 20.0f, 30.0f, 3) {}
};




class Minigun : public Gun
{
public:
	Minigun() noexcept : Gun("minigun", 1.5f, 5.0f, 30) {}
};




class Rocketlauncher : public Gun
{
public:
	Rocketlauncher() noexcept : Gun("rocket", 90.0f, 120.0f, 1) {}
};




class Dino
{
private:
	double hp;
public:
	double& get_hp() noexcept
	{
		return hp;
	}
};




class Amazon
{
private:
	const string name;
	unique_ptr<Dino> dino;
	const unique_ptr<vector<unique_ptr<const Item>>[]> inventory;
	const Gun* held;
	double hp;

public:
	Amazon(const string& name) noexcept : name(name), hp(100.0f), inventory(new vector<unique_ptr<const Item>>[G_TYPE_NUMBER]), dino(nullptr), held(nullptr) {}

	const string& get_name() const noexcept
	{
		return name;
	}

	double& get_hp() noexcept
	{
		return hp;
	}

	const Gun*& get_gun() noexcept
	{
		return held;
	}

	Dino* get_dino() noexcept
	{
		return dino.get();
	}

	bool inventory_put(const TYPE& type, unique_ptr<const Item>& item) const noexcept
	{
		if (inventory[type].size() < G_TYPE_SIZE.at(type))
		{
			inventory[type].push_back(move(item));
			return true;
		}
		return false;
	}

	unique_ptr<const Item> inventory_drop(const TYPE& type, const string& name) const noexcept
	{
		for (auto i = 0; i < inventory[type].size(); i++)
			if (inventory[type][i]->get_name() == name)
			{
				unique_ptr<const Item> item(move(inventory[type][i]));
				inventory[type].erase(inventory[type].begin() + i);
				return item;
			}
		return nullptr;
	}

	const Item* inventory_retrieve(const TYPE& type, const string& name) const noexcept
	{
		for (auto i = 0; i < inventory[type].size(); i++)
			if (inventory[type][i]->get_name() == name)
				return inventory[type][i].get();
		return nullptr;
	}
};




class Tile
{
private:
	unordered_set<Amazon*> amazons;
	unordered_set<unique_ptr<Dino>> dinos;
	const unique_ptr<vector<unique_ptr<const Item>>[]> items;

public:
	Tile() noexcept : items(new vector<unique_ptr<const Item>>[G_TYPE_NUMBER]) {}

	const unordered_set<Amazon*>& get_amazons() const noexcept
	{
		return amazons;
	}

	const unordered_set<unique_ptr<Dino>>& get_dinos() const noexcept
	{
		return dinos;
	}

	const unique_ptr<vector<unique_ptr<const Item>>[]>& get_items() const noexcept
	{
		return items;
	}

	bool spawn(unique_ptr<Dino>& dino) noexcept
	{
		if (dinos.size() != 0)
			return true;
		dinos.insert(move(dino));
		return false;
	}

	bool spawn(const TYPE& type, unique_ptr<const Item>& item) const noexcept
	{
		if (items[type].size() != 0)
			return true;
		items[type].push_back(move(item));
		return false;
	}

	void place(Amazon* const& amazon) noexcept
	{
		amazons.insert(amazon);
	}

	void place(const TYPE& type, unique_ptr<const Item>& item) const noexcept
	{
		items[type].push_back(move(item));
	}

	void remove(Amazon* const& amazon)
	{
		amazons.erase(amazon);
	}

	unique_ptr<const Item> remove(const TYPE& type, const string& name) const noexcept
	{
		for (auto i = 0; i < items[type].size(); i++)
			if (items[type][i]->get_name() == name)
			{
				unique_ptr<const Item> temp(move(items[type][i]));
				items[type].erase(items[type].begin() + i);
				return temp;
			}
		return nullptr;
	}

	bool is_here(Amazon* const& amazon) const noexcept
	{
		if (amazons.find(amazon) != amazons.end())
			return true;
		return false;
	}
};




class Map
{
private:
	std::unordered_map<string, const unique_ptr<Amazon>> amazons;
	unique_ptr<unique_ptr<Tile[]>[]> tiles;
	Amazon* selected;
	int size;

public:
	Map(const int& i) : selected(nullptr)
	{
		switch (i)
		{
		case 1:
		{
			size = 5;
			tiles = unique_ptr<unique_ptr<Tile[]>[]>(new unique_ptr<Tile[]>[5]);
			for (auto i = 0; i < 5; i++)
				tiles[i] = unique_ptr<Tile[]>(new Tile[5]);
			std::random_device rd;
			std::mt19937_64 mt(rd());
			std::uniform_int_distribution<> dist1(0, 4);
			int i = 5;
			unique_ptr<Dino> dino;
			while (i--)
			{
				dino = unique_ptr<Dino>(new Dino());
				while (tiles[dist1(mt)][dist1(mt)].spawn(dino));
			}

			i = 2;
			unique_ptr<Item const> item;
			while (i--)
			{
				item = unique_ptr<const Item>(new Pistol());
				while (tiles[0][dist1(mt)].spawn(TYPE::GUN, item));
				item = unique_ptr<const Item>(new Pistol());
				while (tiles[4][dist1(mt)].spawn(TYPE::GUN, item));
			}
			std::uniform_int_distribution<> dist2(0, 1);
			item = unique_ptr<const Item>(new Shotgun());
			while (tiles[dist2(mt)][dist1(mt)].spawn(TYPE::GUN, item));
			item = unique_ptr<const Item>(new Shotgun());
			while (tiles[4 - dist2(mt)][dist1(mt)].spawn(TYPE::GUN, item));
			item = unique_ptr<const Item>(new Gepkatana());
			while (tiles[dist1(mt)][dist1(mt)].spawn(TYPE::GUN, item));
			item = unique_ptr<const Item>(new Minigun());
			while (tiles[2][dist1(mt)].spawn(TYPE::GUN, item));
			break;
		}

		default:
			throw std::invalid_argument("Unknown gamemode.");
		}
	}

	Tile& get_tile(const char& y, const char& x) const noexcept
	{
		return tiles[y][x];
	}

	int const& get_size() const noexcept
	{
		return size;
	}

	Amazon* get_amazon(string name) const noexcept
	{
		if (amazons.find(name) != amazons.end())
			return amazons.at(name).get();
		return nullptr;
	}

	Amazon*& get_selected() noexcept
	{
		return selected;
	}

	void new_amazon(const string& name) noexcept
	{
		amazons.emplace(name, new Amazon(name));
	}

	point location(Amazon* const& amazon) const noexcept
	{
		for (int i = 0; i < this->size; i++)
			for (int j = 0; j < this->size; j++)
				if (this->tiles[i][j].is_here(amazon))
					return point(j, i);
	}
};




class Command
{
public:
	virtual string exec(const vector<string>& vec, Map& map) noexcept = 0;
};




class New : public Command
{
public:
	string exec(const vector<string>& vec, Map& map) noexcept
	{
		if (vec.size() != 2)
			return "Incorrect arguments.\n";
		if (map.get_amazon(vec[1]))
			return vec[1] + " already exists.\n";
		map.new_amazon(vec[1]);
		map.get_tile(0, 0).place(map.get_amazon(vec[1]));
		return vec[1] + " created.\n";
	}
};




class Select : public Command
{
public:
	string exec(const vector<string>& vec, Map& map) noexcept
	{
		if (vec.size() != 2)
			return "Incorrect arguments.\n";
		if (!map.get_amazon(vec[1]))
			return vec[1] + " does not exist.\n";
		if (map.get_selected() == map.get_amazon(vec[1]))
			return vec[1] + " is already selected.\n";
		map.get_selected() = map.get_amazon(vec[1]);
		return vec[1] + " selected.\n";
	}
};




class Move : public Command
{
public:
	string exec(const vector<string>& vec, Map& map) noexcept
	{
		if (vec.size() != 3)
			return "Incorrect arguments.\n";
		if (!map.get_selected())
			return "Select an amazon first!\n";
		if (map.get_selected()->get_hp() == 0.0)
			return map.get_selected()->get_name() + " is dead.\n";
		try
		{
			int x = std::stoi(vec[1]) - 1;
			int y = std::stoi(vec[2]) - 1;
			point p = map.location(map.get_selected());

			if (x < 0 || y < 0 || x >= map.get_size() || y >= map.get_size())
				return "Target tile does not exist.\n";
			if (p.x + 1 < x || p.x - 1 > x || p.y + 1 < y || p.y - 1 > y)
				return "Target tile is too far.\n";
			if (p.x == x && p.y == y)
				return "Target tile matches the current one.\n";

			map.get_tile(p.y, p.x).remove(map.get_selected());
			map.get_tile(y, x).place(map.get_selected());
			return map.get_selected()->get_name() + " moved to " + vec[1] + ";" + vec[2] + ".\n";
		}
		catch (std::invalid_argument&)
		{
			return "Incorrect arguments.\n";
		}
	}
};




class Help : public Command
{
public:
	string exec(const vector<string>& vec, Map& map) noexcept
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
	string exec(const vector<string>& vec, Map& map) noexcept
	{
		if (vec.size() != 1)
			return "Incorrect arguments.\n";
		if (!map.get_selected())
			return "Select an amazon first!\n";
		if (map.get_selected()->get_hp() == 0.0f)
			return map.get_selected()->get_name() + " is dead.\n";
		point loc = map.location(map.get_selected());
		string ret;
		string temp;

		for (const auto& am : map.get_tile(loc.y, loc.x).get_amazons())
			if (am != map.get_selected())
				temp += am->get_name() + ", ";
		for (const auto& din : map.get_tile(loc.y, loc.x).get_dinos())
			temp += "dino, ";
		for (auto i = 0; i < G_TYPE_NUMBER; i++)
			for (const auto& item : map.get_tile(loc.y, loc.x).get_items()[i])
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
			for (const auto& am : map.get_tile(loc.y + 1, loc.x).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.get_tile(loc.y + 1, loc.x).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.get_tile(loc.y + 1, loc.x).get_items()[i])
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
			for (const auto& am : map.get_tile(loc.y + 1, loc.x + 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.get_tile(loc.y + 1, loc.x + 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.get_tile(loc.y + 1, loc.x + 1).get_items()[i])
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
			for (const auto& am : map.get_tile(loc.y, loc.x + 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.get_tile(loc.y, loc.x + 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.get_tile(loc.y, loc.x + 1).get_items()[i])
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
			for (const auto& am : map.get_tile(loc.y - 1, loc.x + 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.get_tile(loc.y - 1, loc.x + 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.get_tile(loc.y - 1, loc.x + 1).get_items()[i])
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
			for (const auto am : map.get_tile(loc.y - 1, loc.x).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.get_tile(loc.y - 1, loc.x).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.get_tile(loc.y - 1, loc.x).get_items()[i])
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
			for (const auto& am : map.get_tile(loc.y - 1, loc.x - 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.get_tile(loc.y - 1, loc.x - 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.get_tile(loc.y - 1, loc.x - 1).get_items()[i])
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
			for (const auto& am : map.get_tile(loc.y, loc.x - 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.get_tile(loc.y, loc.x - 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.get_tile(loc.y, loc.x - 1).get_items()[i])
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
			for (const auto& am : map.get_tile(loc.y + 1, loc.x - 1).get_amazons())
				temp += am->get_name() + ", ";
			for (const auto& din : map.get_tile(loc.y + 1, loc.x - 1).get_dinos())
				temp += "dino, ";
			for (auto i = 0; i < G_TYPE_NUMBER; i++)
				for (const auto& item : map.get_tile(loc.y + 1, loc.x - 1).get_items()[i])
					temp += item->get_name() + ", ";
			if (temp == "")
				ret += "Northwestern tile empty.\n";
			else
			{
				ret += "North West: " + temp.substr(0, temp.length() - 2) + ".\n";
				temp = "";
			}
		}
		return ret;
	}
};




class Attack : public Command
{
public:
	string exec(const vector<string>& vec, Map& map) noexcept
	{
		if (vec.size() != 2)
			return "Incorrect arguments.\n";
		if (!map.get_selected())
			return "Select an amazon first!\n";
		if (map.get_selected()->get_hp() == 0.0f)
			return map.get_selected()->get_name() + " is dead.\n";
		if (!map.get_selected()->get_gun())
			return map.get_selected()->get_name() + " is not holding any weapon.\n";
		if (!map.get_amazon(vec[1]))
			return vec[1] + " does not exist.\n";
		if (map.get_amazon(vec[1]) == map.get_selected())
			return vec[1] + " cannot attack themselves.\n";

		const point selected = map.location(map.get_selected());
		const point found = map.location(map.get_amazon(vec[1]));
		if (selected != found)
		if (map.location(map.get_selected()) != map.location(map.get_amazon(vec[1])))
			return vec[1] + " is out of range.\n";
		if (map.get_amazon(vec[1])->get_hp() == 0.0f)
			return vec[1] + " is already dead.\n";

		Dino* const dino(map.get_amazon(vec[1])->get_dino());
		const double dmg = map.get_selected()->get_gun()->get_dmg();
		if (dino && dino->get_hp() != 0.0f)
		{
			dino->get_hp() -= dmg;
			if (dino->get_hp() == 0.0f)
				return vec[1] + "'s dino died.\n";
			return vec[1] + "'s dino suffered " + std::to_string(dmg) + " points of damage.\n";
		}

		map.get_amazon(vec[1])->get_hp() -= dmg;
		if (map.get_amazon(vec[1])->get_hp() == 0.0f)
			return vec[1] + " died.\n";
		return vec[1] + " suffered " + std::to_string(dmg) + " points of damage.\n";
	}
};




class Pickup : public Command
{
public:
	string exec(const vector<string>& vec, Map& map) noexcept
	{
		if (vec.size() != 2)
			return "Incorrect arguments.\n";
		if (!map.get_selected())
			return "Select an amazon first!\n";
		if (map.get_selected()->get_hp() == 0.0f)
			return map.get_selected()->get_name() + " is dead.\n";
		if (G_GET_TYPE.find(vec[1]) == G_GET_TYPE.end())
			return "Unknown item.\n";

		const point p = map.location(map.get_selected());
		unique_ptr<const Item> i(map.get_tile(p.y, p.x).remove(G_GET_TYPE.at(vec[1]), vec[1]));
		if (!i)
			return vec[1] + " cannot be found on the current tile.\n";
		if (!map.get_selected()->inventory_put(G_GET_TYPE.at(vec[1]), i))
		{
			map.get_tile(p.y, p.x).place(G_GET_TYPE.at(vec[1]), i);
			return "Can't pick up " + vec[1] + ".\n";
		}
		return "Picked up " + vec[1] + ".\n";
	}
};




class Drop : public Command
{
public:
	string exec(const vector<string>& vec, Map& map) noexcept
	{
		if (vec.size() != 2)
			return "Incorrect arguments.\n";
		if (!map.get_selected())
			return "Select an amazon first!\n";
		if (map.get_selected()->get_hp() == 0.0f)
			return map.get_selected()->get_name() + " is dead.\n";
		if (G_GET_TYPE.find(vec[1]) == G_GET_TYPE.end())
			return "Unknown item.\n";

		const point p = map.location(map.get_selected());
		unique_ptr<const Item> i = map.get_selected()->inventory_drop(G_GET_TYPE.at(vec[1]), vec[1]);
		if (!i)
		{
			if (i.get() == map.get_selected()->get_gun())//tesztelendő hogy szükséges-e
				map.get_selected()->get_gun() = nullptr;
			return vec[1] + " cannot be found in " + map.get_selected()->get_name() + "'s inventory.\n";
		}	
		map.get_tile(p.y, p.x).place(G_GET_TYPE.at(vec[1]), i);
		return vec[1] + " dropped.\n";
	}
};




class Equip : public Command
{
public:
	string exec(const vector<string>& vec, Map& map) noexcept
	{
		if (vec.size() != 2)
			return "Incorrect arguments.\n";
		if (!map.get_selected())
			return "Select an amazon first!\n";
		if (map.get_selected()->get_hp() == 0.0f)
			return map.get_selected()->get_name() + " is dead.\n";
		if (G_GET_TYPE.find(vec[1]) == G_GET_TYPE.end() || G_GET_TYPE.at(vec[1]) != TYPE::GUN)
			return "Unknown weapon type.\n";
		const Item* item = map.get_selected()->inventory_retrieve(G_GET_TYPE.at(vec[1]), vec[1]);
		if (!item)
			return vec[1] + " cannot be found in " + map.get_selected()->get_name() + "'s inventory.\n";
		map.get_selected()->get_gun() = ((Gun*)item);
		return vec[1] + " equipped.\n";
	}
};




class Interpreter
{
private:
	unordered_map<string, const unique_ptr<Command>> commands;

public:
	Interpreter() noexcept
	{
		commands.emplace("new", unique_ptr<Command>(new New()));
		commands.emplace("select", unique_ptr<Command>(new Select()));
		commands.emplace("move", unique_ptr<Command>(new Move()));
		commands.emplace("help", unique_ptr<Command>(new Help()));
		commands.emplace("attack", unique_ptr<Command>(new Attack()));
		commands.emplace("look", unique_ptr<Command>(new Look()));
		commands.emplace("pickup", unique_ptr<Command>(new Pickup()));
		commands.emplace("drop", unique_ptr<Command>(new Drop()));
		commands.emplace("equip", unique_ptr<Command>(new Equip()));
	}

	string interpret(const vector<string>& vec, Map& map) const noexcept
	{
		if (commands.find(vec[0]) == commands.end())
			return "Unknown command.\n";
		return commands.at(vec[0])->exec(vec, map);
	}
};




int main()
{

	cout << "Enter gamemode number: ";


	string input;


	unique_ptr<Map> map;


	while (1)
	{
		getline(cin, input);
		if (input == "exit")
			return 0;


		try
		{
			int i = std::stoi(input);
			try
			{
				map = unique_ptr<Map>(new Map(i));
				cout << "Map of size " << map->get_size() << "x" << map->get_size() << " created." << endl
					<< "Type \"help\" for the list of available commands!\n" << endl;
				break;
			}
			catch (std::invalid_argument& e)
			{
				cout << e.what() << " Try again: ";
			}
		}
		catch (std::invalid_argument&)
		{
			cout << "Not a number. Try again: ";
		}
	}




	const Interpreter interpreter;




	while (1)
	{
		cout << "Command: ";


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
			break;


		cout << interpreter.interpret(words, *map) << endl;
	}




	return 0;
}