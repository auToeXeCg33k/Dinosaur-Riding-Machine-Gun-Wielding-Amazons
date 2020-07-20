#pragma once
#include "amazon.h"

class BrainDrainer
{
private:
    const double min;
    const double max;

    double damage() const noexcept;

public:
    BrainDrainer() noexcept;
    BrainDrainer(const BrainDrainer& other) noexcept = delete;
    BrainDrainer(BrainDrainer&& other) noexcept;

    std::string attack(Amazon& amazon) const noexcept;
};