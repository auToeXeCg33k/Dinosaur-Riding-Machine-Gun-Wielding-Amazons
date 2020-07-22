#include "dino.h"
#include <utility>

Dino::Dino() noexcept : hp(100.0), bTamed(false) {}


double Dino::health() const noexcept
{
	return hp;
}


void Dino::health(double const hp) noexcept
{
	this->hp = hp;
}


bool Dino::tamed() const noexcept
{
	return bTamed;
}

void Dino::tamed(bool const tmd) noexcept
{
	bTamed = tmd;
}
