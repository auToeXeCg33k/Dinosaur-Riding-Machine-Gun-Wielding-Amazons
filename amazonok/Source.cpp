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

	Point(char x, char y) : x(x), y(y) {}

	bool operator==(Point p) const
	{
		return x == p.x && y == p.y;
	}

	bool operator!=(Point p) const
	{
		return x != p.x || y != p.y;
	}
};



enum class ItemType { gun };




class Item
{
protected:
	string name;

	Item(string name) : name(name) {}

public:
	string get_name()
	{
		return name;
	}
};




class Gun : public Item
{
private:
	double min;
	double max;
	char rate;

public:
	Gun(string name, double min, double max, int rate) : Item(name), min(min), max(max), rate(rate) {}

	double get_dmg()
	{
		std::random_device rd;
		std::mt19937_64 mt(rd());
		std::uniform_real_distribution<> dist(0, 1);

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
	static ItemType lookUp(string name)
	{
		for (auto x : types)
			for (auto y : x.second)
				if (y == name)
					return x.first;
	}

	static bool isValid(string name)
	{
		for (auto x : types)
			for (auto y : x.second)
				if (y == name)
					return true;
		return false;
	}

	static int typeLimit(ItemType type)
	{
		return typeLimits.at(type);
	}

	static unique_ptr<Item> CreateGun(string name)
	{
		if (name == "pistol")
			return unique_ptr<Item>(new Gun("pistol", 15.0, 20.0, 2));

		if (name == "shotgun")
			return unique_ptr<Item>(new Gun("shotgun", 50.0, 75.0, 1));

		if (name == "katana")
			return unique_ptr<Item>(new Gun("katana", 20.0, 30.0, 3));

		if (name == "minigun")
			return unique_ptr<Item>(new Gun("minigun", 1.5, 5.0, 30));

		if (name == "rocket")
			return unique_ptr<Item>(new Gun("rocket", 90.0, 120.0, 1));
	}
};




class Dino
{
private:
	double hp;

public:
	double& get_hp()
	{
		return hp;
	}
};




class Amazon
{
private:
	string name;
	double hp;

	map<ItemType, vector<unique_ptr<Item>>> inventory;
	Gun* held;

	unique_ptr<Dino> dino;
	
	
public:
	Amazon(string name) : name(name), hp(100.0), dino(nullptr), held(nullptr)
	{
		inventory.emplace(pair<ItemType, vector<unique_ptr<Item>>>(ItemType::gun, vector<unique_ptr<Item>>()));
	}


	bool hasFreeSlot(ItemType type)
	{
		return inventory.at(type).size() < ItemFactory::typeLimit(type);
	}


	bool hasItem(string name)
	{
		for (auto& x : inventory.at(ItemFactory::lookUp(name)))
			if (x->get_name() == name)
				return true;
		return false;
	}


	void take(unique_ptr<Item> item)
	{
		inventory.at(ItemFactory::lookUp(item->get_name())).push_back(move(item));
	}


	unique_ptr<Item> remove(string name)
	{
		for (int i = 0; i < inventory.at(ItemFactory::lookUp(name)).size(); i++)
			if (inventory.at(ItemFactory::lookUp(name)).at(i)->get_name() == name)
			{
				unique_ptr<Item> ret(move(inventory.at(ItemFactory::lookUp(name)).at(i)));
				inventory.at(ItemFactory::lookUp(name)).erase(inventory.at(ItemFactory::lookUp(name)).begin() + i);
				return ret;
			}
	}


	Item* item(string name)
	{
		for (auto& x : inventory.at(ItemFactory::lookUp(name)))
			if (x->get_name() == name)
				return x.get();
	}
	
	
	string get_name()
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
		items.emplace(pair<ItemType, vector<unique_ptr<Item>>>(ItemType::gun, vector<unique_ptr<Item>>()));
	}


	bool has(string name)
	{
		for (auto& x : items.at(ItemFactory::lookUp(name)))
			if (x->get_name() == name)
				return true;
		return false;
	}


	void add(unique_ptr<Item> item)
	{
		items.at(ItemFactory::lookUp(item->get_name())).push_back(move(item));
	}


	unique_ptr<Item> remove(string name)
	{
		for (int i = 0; i < items.at(ItemFactory::lookUp(name)).size(); i++)
			if (items.at(ItemFactory::lookUp(name)).at(i)->get_name() == name)
			{
				unique_ptr<Item> ret(move(items.at(ItemFactory::lookUp(name)).at(i)));
				items.at(ItemFactory::lookUp(name)).erase(items.at(ItemFactory::lookUp(name)).begin() + i);
				return ret;
			}
	}


	bool spawn(unique_ptr<Dino> dino)
	{
		if (dinos.size() != 0)
			return false;

		dinos.insert(move(dino));
		return true;
	}
	


	bool spawn(unique_ptr<Item> item)
	{
		if (items.at(ItemFactory::lookUp(item->get_name())).size() != 0)
			return false;

		items.at(ItemFactory::lookUp(item->get_name())).emplace_back(unique_ptr<Item>(move(item)));
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
	unordered_map<string, unique_ptr<Amazon>> amazons;
	vector<vector<unique_ptr<Tile>>> tiles;
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
			for (int i = 0; i < 5; i++)
			{
				tiles.emplace_back(vector<unique_ptr<Tile>>());
				for (int j = 0; j < 5; j++)
					tiles.at(i).emplace_back(unique_ptr<Tile>(new Tile()));
			}
			
			std::random_device rd;
			std::mt19937_64 mt(rd());

			std::uniform_int_distribution<> dist1(0, 4);
			
			for (int i = 0; i < 5; i++)
				while (!tiles.at(dist1(mt)).at(dist1(mt))->spawn(unique_ptr<Dino>(new Dino())));

			for (int i = 0; i < 2; i++)
			{
				while (!tiles.at(0).at(dist1(mt))->spawn(ItemFactory::CreateGun("pistol")));
				while (!tiles.at(4).at(dist1(mt))->spawn(ItemFactory::CreateGun("pistol")));
			}

			std::uniform_int_distribution<> dist2(0, 1);

			while (!tiles.at(dist2(mt)).at(dist1(mt))->spawn(ItemFactory::CreateGun("shotgun")));
			while (!tiles.at(4 - dist2(mt)).at(dist1(mt))->spawn(ItemFactory::CreateGun("shotgun")));
			while (!tiles.at(dist1(mt)).at(dist1(mt))->spawn(ItemFactory::CreateGun("katana")));
			while (!tiles.at(2).at(dist1(mt))->spawn(ItemFactory::CreateGun("minigun")));
			return;
		}

		default:
			throw std::invalid_argument("Invalid gamemode.");
		}
	}

	Tile& get_tile(char y, char x)
	{
		return *tiles.at(y).at(x);
	}

	int get_size()
	{
		return size;
	}

	Amazon* get_amazon(string name)
	{
		if (amazons.find(name) != amazons.end())
			return amazons.at(name).get();
		return nullptr;
	}

	Amazon*& get_selected()
	{
		return selected;
	}

	void new_amazon(string name)
	{
		amazons.emplace(name, new Amazon(name));
	}

	Point location(Amazon* amazon)
	{
		for (int i = 0; i < this->size; i++)
			for (int j = 0; j < this->size; j++)
				if (this->tiles[i][j]->is_here(amazon))
					return Point(j, i);
	}
};




class Command
{
public:
	virtual string exec(vector<string> vec, Map& map) = 0;
};




class New : public Command
{
public:
	string exec(vector<string> vec, Map& map)
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
	string exec(vector<string> vec, Map& map)
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
	string exec(vector<string> vec, Map& map)
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
			Point p = map.location(map.get_selected());

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
	string exec(vector<string> vec, Map& map)
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
	string exec(vector<string> vec, Map& map)
	{
		if (vec.size() != 1)
			return "Incorrect arguments.\n";
		if (!map.get_selected())
			return "Select an amazon first!\n";
		if (map.get_selected()->get_hp() == 0.0f)
			return map.get_selected()->get_name() + " is dead.\n";
		Point loc = map.location(map.get_selected());
		string ret;
		string temp;
		/*
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
		return ret;*/
	}
};




class Attack : public Command
{
public:
	string exec(vector<string> vec, Map& map)
	{
		if (vec.size() != 2)
			return "Incorrect arguments.\n";
		if (!map.get_selected())
			return "Select an amazon first!\n";
		if (map.get_selected()->get_hp() == 0.0f)
			return map.get_selected()->get_name() + " is dead.\n";
		if (!map.get_selected()->hand())
			return map.get_selected()->get_name() + " is not holding any weapon.\n";
		if (!map.get_amazon(vec[1]))
			return vec[1] + " does not exist.\n";
		if (map.get_amazon(vec[1]) == map.get_selected())
			return vec[1] + " cannot attack themselves.\n";

		Point selected = map.location(map.get_selected());
		Point found = map.location(map.get_amazon(vec[1]));
		if (selected != found)
		if (map.location(map.get_selected()) != map.location(map.get_amazon(vec[1])))
			return vec[1] + " is out of range.\n";
		if (map.get_amazon(vec[1])->get_hp() == 0.0f)
			return vec[1] + " is already dead.\n";

		double dmg = map.get_selected()->hand()->get_dmg();

		Dino* dino(map.get_amazon(vec[1])->get_dino());
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
	string exec(vector<string> vec, Map& map) 
	{
		if (vec.size() != 2)
			return "Invalid arguments.\n";

		if (!map.get_selected())
			return "Select an amazon first!\n";

		if (map.get_selected()->get_hp() == 0.0)
			return map.get_selected()->get_name() + " is dead.\n";

		if (!ItemFactory::isValid(vec[1]))
			return "Unknown item.\n";

		Point p = map.location(map.get_selected());
		
		if (!map.get_tile(p.y, p.x).has(vec[1]))
			return vec[1] + " cannot be found on the current tile.\n";

		if (!map.get_selected()->hasFreeSlot(ItemFactory::lookUp(vec[1])))
			return "Can't pick up " + vec[1] + ". " + map.get_selected()->get_name() + "'s inventory is full.\n";
		
		map.get_selected()->take(map.get_tile(p.y, p.x).remove(vec[1]));

		return "Picked up " + vec[1] + ".\n";
	}
};




class Drop : public Command
{
public:
	string exec(vector<string> vec, Map& map)
	{
		if (vec.size() != 2)
			return "Invalid arguments.\n";

		if (!map.get_selected())
			return "Select an amazon first!\n";

		if (map.get_selected()->get_hp() == 0.0)
			return map.get_selected()->get_name() + " is dead.\n";

		if (!ItemFactory::isValid(vec[1]))
			return "Unknown item.\n";

		if (!map.get_selected()->hasItem(vec[1]))
			return vec[1] + " cannot be found in " + map.get_selected()->get_name() + "'s inventory.\n";

		Point p = map.location(map.get_selected());

		map.get_tile(p.y, p.x).add(map.get_selected()->remove(vec[1]));

		return vec[1] + " dropped.\n";
	}
};




class Equip : public Command
{
public:
	string exec(vector<string> vec, Map& map)
	{
		if (vec.size() != 2)
			return "Invalid arguments.\n";

		if (!map.get_selected())
			return "Select an amazon first!\n";

		if (map.get_selected()->get_hp() == 0.0)
			return map.get_selected()->get_name() + " is dead.\n";

		if (!ItemFactory::isValid(vec[1]) || ItemFactory::lookUp(vec[1]) != ItemType::gun)
			return "Unknown weapon type.\n";

		if (!map.get_selected()->hasItem(vec[1]))
			return vec[1] + " cannot be found in " + map.get_selected()->get_name() + "'s inventory.\n";

		map.get_selected()->hand() = static_cast<Gun*>(map.get_selected()->item(vec[1]));

		return vec[1] + " equipped.\n";
	}
};




class Interpreter
{
private:
	unordered_map<string, unique_ptr<Command>> commands;

public:
	Interpreter()
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


	string interpret(vector<string> vec, Map& map)
	{
		if (commands.find(vec[0]) == commands.end())
			return "Unknown command.\n";

		return commands.at(vec[0])->exec(vec, map);
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
}




int main()
{
	Map map = InitMap();
	Interpreter interpreter;
	string input;

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
			return 0;

		cout << interpreter.interpret(words, map) << endl;
	}
}