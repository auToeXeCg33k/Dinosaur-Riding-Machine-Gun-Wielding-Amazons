#pragma once

class Dino
{
private:
	double hp;
	bool bTamed;

public:
	Dino() noexcept;
	Dino(const Dino& other) noexcept = delete;
	Dino(Dino&& other) noexcept;

	double health() const noexcept;
	void health(double const hp) noexcept;

	bool tamed() const noexcept;
	void tamed(bool const tmd) noexcept;
};