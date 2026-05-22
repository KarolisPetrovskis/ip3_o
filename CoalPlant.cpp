#include "PowerPlant.h"
#include <iostream>

CoalPlant::CoalPlant(std::string plantName, double plantEfficiency, double plantBurnRate, double plantSupply)
    : PowerPlant(std::move(plantName), plantEfficiency), burnRate(plantBurnRate), supply(plantSupply) {}

PowerPlant *CoalPlant::clone() const
{
    return new CoalPlant(name, efficiency, burnRate, supply);
}

double CoalPlant::calculateOutput() const
{
    return efficiency * burnRate;
}

void CoalPlant::addSupply(double amount)
{
    supply += amount;
}

double CoalPlant::getSupply() const
{
    return supply;
}

double CoalPlant::getBurnRate() const
{
    return burnRate;
}