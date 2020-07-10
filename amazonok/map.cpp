#include "map.h"
#include <random>

using namespace std;


Map::Map(const int i)
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


Tile& Map::tile(const char y, const char x)
{
	return tiles.at(y).at(x);
}


Tile& Map::tile(const Point p)
{
	return tiles.at(p.y).at(p.x);
}


int Map::get_size()
{
	return size;
}


Point Map::location(Amazon* amazon)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (tiles.at(i).at(j).is_here(amazon))
				return Point(j, i);
}