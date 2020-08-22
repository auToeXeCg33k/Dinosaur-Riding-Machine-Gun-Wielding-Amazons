#pragma once

class Dino
{
private:
	double m_HP;
	bool m_Tamed;
public:
	Dino() noexcept;
	Dino(Dino&& other) noexcept = delete;

	double Health() const noexcept;
	void Health(double const hp) noexcept;

	bool Tamed() const noexcept;
	void Tamed(bool const tmd) noexcept;
};