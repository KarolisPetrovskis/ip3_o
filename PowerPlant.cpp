#include "PowerPlant.h"

NotImplementedException::NotImplementedException() : std::logic_error("NotImplementedException") {}

StrategyNotSetException::StrategyNotSetException() : std::logic_error("StrategyNotSetException") {}

PowerPlant::PowerPlant(std::string plantName, double plantEfficiency)
    : name(std::move(plantName)), efficiency(plantEfficiency) {}

PowerPlant::~PowerPlant() = default;

double PowerPlant::calculateOutput() const
{
    throw NotImplementedException();
}

bool PowerPlant::operator<(const PowerPlant &other) const
{
    return this->name < other.name;
}

std::string PowerPlant::getName() const
{
    return name;
}

double PowerPlant::getEfficiency() const
{
    return efficiency;
}