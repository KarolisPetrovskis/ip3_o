#pragma once

#include <vector>
#include "PowerPlant.h"

/**
 * @class GridStrategy
 * @brief Abstract base class for grid computation strategies.
 */
class GridStrategy
{
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~GridStrategy();

    /**
     * @brief Executes the strategy on a collection of power plants.
     * @param plants A vector of pointers to PowerPlant objects.
     * @return The computed value based on the strategy.
     */
    virtual double execute(const std::vector<PowerPlant *> &plants) const = 0;
};

/**
 * @class TotalOutputStrategy
 * @brief Strategy that computes the total output of all power plants.
 */
class TotalOutputStrategy : public GridStrategy
{
public:
    /**
     * @brief Executes the total output strategy.
     * @param plants A vector of pointers to PowerPlant objects.
     * @return The sum of outputs from all plants.
     */
    double execute(const std::vector<PowerPlant *> &plants) const override;
};

/**
 * @class AverageOutputStrategy
 * @brief Strategy that computes the average output of all power plants.
 */
class AverageOutputStrategy : public GridStrategy
{
public:
    /**
     * @brief Executes the average output strategy.
     * @param plants A vector of pointers to PowerPlant objects.
     * @return The average output of all plants.
     */
    double execute(const std::vector<PowerPlant *> &plants) const override;
};

/**
 * @class MinOutputStrategy
 * @brief Strategy that computes the minimum output among all power plants.
 */
class MinOutputStrategy : public GridStrategy
{
public:
    /**
     * @brief Executes the minimum output strategy.
     * @param plants A vector of pointers to PowerPlant objects.
     * @return The minimum output among all plants.
     */
    double execute(const std::vector<PowerPlant *> &plants) const override;
};