#include "Tile.h"

Tile::Tile() noexcept {	m_Items.emplace(std::make_pair(ItemType::gun, std::vector<std::unique_ptr<Item>>{})); }

Tile::Tile(Tile&& other) noexcept
	: m_Amazons{ move(other.m_Amazons) }, m_Dinos{ move(other.m_Dinos) }, m_Items{ move(other.m_Items) }, m_Braindrainer{ move(other.m_Braindrainer) } {}

void Tile::add(Amazon* const amazon) noexcept { m_Amazons.insert(amazon); }

void Tile::add(std::unique_ptr<Dino>&& dino) noexcept { m_Dinos.push_back(move(dino)); }

void Tile::add(std::unique_ptr<Item>&& item) noexcept { m_Items.at(ItemFactory::TypeOf(item->Name())).emplace_back(move(item)); }

void Tile::add(std::unique_ptr<BrainDrainer>&& drainer) noexcept { this->m_Braindrainer = move(drainer); }

void Tile::remove(Amazon* const amazon) noexcept { m_Amazons.erase(amazon); }

std::unique_ptr<Dino> Tile::remove(Dino* dino) noexcept
{
	for (size_t i = 0; i < m_Dinos.size(); i++)
		if (m_Dinos.at(i).get() == dino)
		{
			std::unique_ptr<Dino> ret{ move(m_Dinos.at(i)) };
			m_Dinos.erase(m_Dinos.begin() + i);
			return ret;
		}
}

std::unique_ptr<Item> Tile::remove(std::string_view name) noexcept
{
	for (size_t i = 0; i < m_Items.at(ItemFactory::TypeOf(name)).size(); i++)
		if (m_Items.at(ItemFactory::TypeOf(name)).at(i)->Name() == name)
		{
			std::unique_ptr<Item> ret{ move(m_Items.at(ItemFactory::TypeOf(name)).at(i)) };
			m_Items.at(ItemFactory::TypeOf(name)).erase(m_Items.at(ItemFactory::TypeOf(name)).begin() + i);
			return ret;
		}
}

std::unique_ptr<BrainDrainer> Tile::remove() noexcept { return move(m_Braindrainer); }

bool Tile::has(Amazon* const amazon) const noexcept { return m_Amazons.find(amazon) != m_Amazons.end(); }

bool Tile::has(Dino* const dino) const noexcept
{
	for (const auto& x : m_Dinos)
		if (x.get() == dino)
			return true;

	return false;
}

bool Tile::has(std::string_view name) const noexcept
{
	for (const auto& x : m_Items.at(ItemFactory::TypeOf(name)))
		if (x->Name() == name)
			return true;

	return false;
}

bool Tile::has() const noexcept { return m_Braindrainer.get(); }

bool Tile::spawnDino() noexcept
{
	if (m_Dinos.size())
		return false;

	m_Dinos.emplace_back(std::make_unique<Dino>());
	return true;
}

bool Tile::spawnItem(std::string_view name) noexcept
{
	if (m_Items.at(ItemFactory::TypeOf(name)).size())
		return false;

	m_Items.at(ItemFactory::TypeOf(name)).emplace_back(ItemFactory::CreateItem(name));
	return true;
}

bool Tile::spawnDrainer() noexcept
{
	if (m_Braindrainer)
		return false;

	m_Braindrainer = std::make_unique<BrainDrainer>();
	return true;
}

const std::unordered_set<Amazon*>& Tile::AmazonContainer() const noexcept { return m_Amazons; }

const std::vector<std::unique_ptr<Dino>>& Tile::DinoContainer() const noexcept { return m_Dinos; }

const std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>>& Tile::ItemContainer() const noexcept { return m_Items; }

BrainDrainer* Tile::braindrainer() const noexcept { return m_Braindrainer.get(); }