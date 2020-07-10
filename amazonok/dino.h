#pragma once

class Dino
{
private:
	double hp;
	bool bTamed;

public:
	Dino();
	double& get_hp();
	bool& tamed();
};