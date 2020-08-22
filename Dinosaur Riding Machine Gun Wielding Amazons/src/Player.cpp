#include "Player.h"


Player::Player(std::string_view name) noexcept
	: m_Name{ name }, m_Selected{ nullptr }, m_Actions{ 0 }, m_Alive{ 0 }, m_ID{ m_NextID }
{ m_NextID++; }

Player::~Player() noexcept { m_NextID--; }

const std::string& Player::name() const noexcept { return m_Name; }

unsigned Player::actions() const noexcept { return m_Actions; }

void Player::action() noexcept { m_Actions++; }

void Player::resetActions() noexcept { m_Actions = 0; }

unsigned Player::alive() const noexcept { return m_Alive; }

void Player::incAlive() noexcept { m_Alive++; }

void Player::decAlive() noexcept { m_Alive--; }

size_t Player::spawns() const noexcept { return m_Amazons.size(); }

bool Player::existsAmazon(const std::string& name) const noexcept { return m_Amazons.find(name) != m_Amazons.end(); }

void Player::createAmazon(const std::string& name) noexcept { m_Amazons.emplace(name, name); }

Amazon& Player::getAmazon(const std::string& name) noexcept { return m_Amazons.at(name); }

const std::unordered_map<std::string, Amazon>& Player::AmazonContainer() const noexcept { return m_Amazons; }

char Player::id() const noexcept { return m_ID; }

Amazon* Player::selected() const noexcept { return m_Selected; }

void Player::selected(Amazon* const amazon) noexcept { m_Selected = amazon; }