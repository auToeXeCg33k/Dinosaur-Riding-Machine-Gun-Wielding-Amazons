#include "Dino.h"

Dino::Dino() noexcept
	: m_HP{ 100.0 }, m_Tamed{ false } {}

double Dino::Health() const noexcept { return m_HP; }

void Dino::Health(double const hp) noexcept { this->m_HP = hp; }

bool Dino::Tamed() const noexcept { return m_Tamed; }

void Dino::Tamed(bool const tmd) noexcept { m_Tamed = tmd; }