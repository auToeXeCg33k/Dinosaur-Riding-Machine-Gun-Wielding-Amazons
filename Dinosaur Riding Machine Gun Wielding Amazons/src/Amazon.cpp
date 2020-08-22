#include "Amazon.h"

Amazon::Amazon(std::string_view name) noexcept
	: m_Name{ name }, m_HP{ 100.0 }, m_Hand{ nullptr }, m_Dino{ nullptr }, m_Ridden{ nullptr }
{ m_Inventory.emplace(std::make_pair(ItemType::gun, std::vector<std::unique_ptr<Item>>{})); }

bool Amazon::hasFreeSlot(ItemType type) const noexcept { return m_Inventory.at(type).size() < ItemFactory::LimitOf(type); }

bool Amazon::hasItem(std::string_view name) const noexcept
{
	for (const auto& x : m_Inventory.at(ItemFactory::TypeOf(name)))
		if (x->Name() == name)
			return true;

	return false;
}

void Amazon::take(std::unique_ptr<Item>&& item) noexcept { m_Inventory.at(ItemFactory::TypeOf(item->Name())).emplace_back(move(item)); }

std::unique_ptr<Item> Amazon::drop(std::string_view name) noexcept
{
	long long pos{ -1 };

	for (size_t i = 0; i < m_Inventory.at(ItemFactory::TypeOf(name)).size(); i++)
		if (m_Inventory.at(ItemFactory::TypeOf(name)).at(i)->Name() == name)
		{
			pos = i;

			if (m_Inventory.at(ItemFactory::TypeOf(name)).at(i).get() != m_Hand)
				break;
		}

	if (pos == -1)
		return nullptr;

	std::unique_ptr<Item> ret{ move(m_Inventory.at(ItemFactory::TypeOf(name)).at(pos)) };

	m_Inventory.at(ItemFactory::TypeOf(name)).erase(m_Inventory.at(ItemFactory::TypeOf(name)).begin() + pos);

	return ret;
}

Item* Amazon::item(std::string_view name) const noexcept
{
	for (const auto& x : m_Inventory.at(ItemFactory::TypeOf(name)))
		if (x->Name() == name)
			return x.get();
}

const std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>>& Amazon::inventory() const noexcept {	return m_Inventory; }

const std::string& Amazon::name() const noexcept { return m_Name; }

double Amazon::health() const noexcept { return m_HP; }

void Amazon::health(double const hp) noexcept { this->m_HP = hp; }

Gun* Amazon::hand() const noexcept { return m_Hand; }

void Amazon::hand(Gun* const gun) noexcept { m_Hand = gun; }

Dino* Amazon::dino() const noexcept { return m_Dino; }

void Amazon::dino(Dino* const dino) noexcept { m_Dino = dino; }

std::unique_ptr<Dino>& Amazon::riding() noexcept { return m_Ridden; }

void Amazon::riding(std::unique_ptr<Dino>&& dino) noexcept { m_Ridden = move(dino); }