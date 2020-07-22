#include "braindrainer.h"
#include <random>

using namespace std;

BrainDrainer::BrainDrainer() noexcept : min(60.0), max(90.0) {}

double BrainDrainer::damage() const noexcept
{
    random_device rd;
    mt19937_64 mt(rd());
    uniform_real_distribution<> dist(0, 1);

    return (max-min) * dist(mt) + min;
}

string BrainDrainer::attack(Amazon& amazon) const noexcept
{
    auto dmg(damage());

    if (amazon.riding())
    {
        if (amazon.dino()->health() - dmg < 0.0)
            amazon.dino()->health(0.0);
        else
            amazon.dino()->health(amazon.dino()->health() - dmg);

        if (!amazon.dino()->health())
        {
            return amazon.name() + "'s dino was killed by a Braindrainer.\n";
        }

        return amazon.name() + "'s dino suffered " + to_string(static_cast<int>(round(dmg))) + " points of damage from a Braindrainer.\n";
    }

    if (amazon.health() - dmg < 0.0)
        amazon.health(0.0);
    else
        amazon.health(amazon.health() - dmg);

    if (!amazon.health())
        return amazon.name() + " was killed by a Braindrainer.\n";
    
    return amazon.name() + " suffered " + to_string(static_cast<int>(round(dmg))) + " points of damage from a Braindrainer.\n";
}