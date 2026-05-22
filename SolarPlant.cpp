#include "PowerPlant.h"

SolarPlant::SolarPlant(std::string plantName, double plantEfficiency, double plantArea)
    : PowerPlant(std::move(plantName), plantEfficiency), area(plantArea) {}

PowerPlant *SolarPlant::clone() const
{
    return new SolarPlant(name, efficiency, area);
}

double SolarPlant::calculateOutput() const
{
    return efficiency * area;
}

double SolarPlant::getArea() const
{
    return area;
}