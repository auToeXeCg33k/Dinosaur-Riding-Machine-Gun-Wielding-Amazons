#include "dino.h"

Dino::Dino() : hp(100.0) {}


double& Dino::get_hp()
{
	return hp;
}