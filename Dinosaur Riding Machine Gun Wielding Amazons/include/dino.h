#pragma once

class Dino
{
private:
	double hp;
	bool bTamed;

public:
	Dino() noexcept;
	Dino(Dino&& other) noexcept = delete;

	double health() const noexcept;
	void health(double const hp) noexcept;

	bool tamed() const noexcept;
	void tamed(bool const tmd) noexcept;
};