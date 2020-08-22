#include "GameData.h"

GameData::GameData(int i) noexcept
	: m_Player1{ "Player 1" }, m_Player2{ "Player 2" }, m_ActivePlayer{ 0 }, m_MaxActions{ i == 1 ? 3u : 3u }, m_MaxSpawns{ i == 1 ? 6u : 6u }, m_MaxAlive{ i == 1 ? 3u : 3u } {}

Player& GameData::CurrentPlayer() noexcept { return m_ActivePlayer ? m_Player2 : m_Player1; }

Player& GameData::OtherPlayer() noexcept { return m_ActivePlayer ? m_Player1 : m_Player2; }

unsigned GameData::MaxActions() const noexcept { return m_MaxActions; }

unsigned GameData::MaxSpawns() const noexcept { return m_MaxSpawns; }

unsigned GameData::MaxAlive() const noexcept { return m_MaxAlive; }

void GameData::turn() noexcept
{
	m_ActivePlayer = !m_ActivePlayer;
	m_Player1.resetActions();
	m_Player2.resetActions();
}