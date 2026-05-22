#include "GridStrategy.h"

GridStrategy::~GridStrategy() = default;

double TotalOutputStrategy::execute(const std::vector<PowerPlant *> &plants) const
{
    double total = 0.0;
    for (const auto *plant : plants)
    {
        try
        {
            total += plant->calculateOutput();
        }
        catch (const NotImplementedException &)
        {
        }
    }
    return total;
}

double AverageOutputStrategy::execute(const std::vector<PowerPlant *> &plants) const
{
    double total = 0.0;
    int count = 0;
    for (const auto *plant : plants)
    {
        try
        {
            total += plant->calculateOutput();
            count++;
        }
        catch (const NotImplementedException &)
        {
        }
    }
    return count > 0 ? (total / count) : 0.0;
}

double MinOutputStrategy::execute(const std::vector<PowerPlant *> &plants) const
{
    double minOutput = -1.0;
    for (const auto *plant : plants)
    {
        try
        {
            double out = plant->calculateOutput();
            if (minOutput < 0.0 || out < minOutput)
            {
                minOutput = out;
            }
        }
        catch (const NotImplementedException &)
        {
        }
    }
    return minOutput < 0.0 ? 0.0 : minOutput;
}