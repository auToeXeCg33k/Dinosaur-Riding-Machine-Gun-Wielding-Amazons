#include "dino.h"

Dino::Dino() : hp(100.0), bTamed(false) {}


double& Dino::get_hp()
{
	return hp;
}


bool& Dino::tamed()
{
	return bTamed;
}