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
    BrainDrainer(BrainDrainer&& other) noexcept = delete;

    std::string attack(Amazon& amazon) const noexcept;
};