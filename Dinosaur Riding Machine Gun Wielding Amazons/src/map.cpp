#include "Map.h"

#include <random>

Map::Map(const int i) noexcept
{
	switch (i)
	{
	case 1:
		sz = 5;
		for (int i = 0; i < 5; i++)
		{
			tiles.emplace_back();
			for (int j = 0; j < 5; j++)
				tiles.at(i).emplace_back();
		}

		std::mt19937_64 mt(std::random_device{}());

		std::uniform_int_distribution<> dist1{ 0, 4 };

		for (int i = 0; i < 5; i++)
			while (!tiles.at(dist1(mt)).at(dist1(mt)).spawnDino());

		for (int i = 0; i < 2; i++)
		{
			while (!tiles.at(0).at(dist1(mt)).spawnItem("pistol"));
			while (!tiles.at(4).at(dist1(mt)).spawnItem("pistol"));
		}

		std::uniform_int_distribution<unsigned> dist2{ 0, 1 };

		while (!tiles.at(dist2(mt)).at(dist1(mt)).spawnItem("shotgun"));
		while (!tiles.at(4 - dist2(mt)).at(dist1(mt)).spawnItem("shotgun"));
		while (!tiles.at(dist1(mt)).at(dist1(mt)).spawnItem("katana"));
		while (!tiles.at(2).at(dist1(mt)).spawnItem("minigun"));

		std::uniform_int_distribution<unsigned> dist3{ 0, 2 };

		for (int i = 0; i < 2; i++)
			while (!tiles.at(3 - dist3(mt)).at(dist1(mt)).spawnDrainer());

		return;
	}
}

Tile& Map::tile(const Point p) noexcept { return tiles.at(p.y()).at(p.x()); }

int Map::size() const noexcept { return sz; }

Point Map::find(Amazon* amazon) const noexcept
{
	for (int i = 0; i < sz; i++)
		for (int j = 0; j < sz; j++)
			if (tiles.at(i).at(j).has(amazon))
				return Point{ j, i };
}