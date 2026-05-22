#pragma once

#include <string>
#include <stdexcept>

/**
 * @class NotImplementedException
 * @brief Thrown when a method is not implemented.
 */
class NotImplementedException : public std::logic_error
{
public:
    /**
     * @brief Constructs the exception with a default message.
     */
    NotImplementedException();
};

/**
 * @class StrategyNotSetException
 * @brief Thrown when a strategy is not set.
 */
class StrategyNotSetException : public std::logic_error
{
public:
    /**
     * @brief Constructs the exception with a default message.
     */
    StrategyNotSetException();
};

/**
 * @class PowerPlant
 * @brief Abstract base class for different types of power plants.
 */
class PowerPlant
{
protected:
    /** @brief The name of the power plant. */
    std::string name;
    /** @brief The efficiency of the power plant. */
    double efficiency;

public:
    /**
     * @brief Constructs a power plant with name and efficiency.
     * @param plantName The name of the plant.
     * @param plantEfficiency The efficiency of the plant.
     */
    PowerPlant(std::string plantName, double plantEfficiency);

    /**
     * @brief Copy constructor deleted to prevent slicing.
     */
    PowerPlant(const PowerPlant &other) = delete;

    /**
     * @brief Assignment operator deleted to prevent slicing.
     * @return Reference to this power plant.
     */
    PowerPlant &operator=(const PowerPlant &other) = delete;

    /**
     * @brief Creates a clone of this power plant.
     * @return A pointer to the cloned power plant.
     */
    virtual PowerPlant *clone() const = 0;

    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~PowerPlant();

    /**
     * @brief Calculates the output of the power plant.
     * @return The calculated output.
     */
    virtual double calculateOutput() const;

    /**
     * @brief Gets the name of the power plant.
     * @return The name as a string.
     */
    std::string getName() const;

    /**
     * @brief Gets the efficiency of the power plant.
     * @return The efficiency as a double.
     */
    double getEfficiency() const;

    /**
     * @brief Less-than operator for comparing power plants.
     * @param other The power plant to compare with.
     * @return True if this plant is less than the other.
     */
    bool operator<(const PowerPlant &other) const;
};

/**
 * @class CoalPlant
 * @brief Represents a coal-fired power plant.
 */
class CoalPlant : public PowerPlant
{
private:
    /** @brief The burn rate of the coal plant. */
    double burnRate;
    /** @brief The current supply of coal. */
    double supply;

public:
    /**
     * @brief Constructs a coal plant with name, efficiency, burn rate, and optional supply.
     * @param plantName The name of the plant.
     * @param plantEfficiency The efficiency of the plant.
     * @param plantBurnRate The burn rate of the plant.
     * @param plantSupply The initial supply (default 0.0).
     */
    CoalPlant(std::string plantName, double plantEfficiency, double plantBurnRate, double plantSupply = 0.0);

    /**
     * @brief Copy constructor deleted to prevent slicing.
     */
    CoalPlant(const CoalPlant &other) = delete;

    /**
     * @brief Assignment operator deleted to prevent slicing.
     * @return Reference to this coal plant.
     */
    CoalPlant &operator=(const CoalPlant &other) = delete;

    /**
     * @brief Creates a clone of this coal plant.
     * @return A pointer to the cloned coal plant.
     */
    PowerPlant *clone() const override;

    /**
     * @brief Virtual destructor.
     */
    virtual ~CoalPlant() = default;

    /**
     * @brief Calculates the output of the coal plant.
     * @return The calculated output.
     */
    double calculateOutput() const override;

    /**
     * @brief Adds supply to the coal plant.
     * @param amount The amount to add.
     */
    void addSupply(double amount);

    /**
     * @brief Gets the current supply.
     * @return The supply as a double.
     */
    double getSupply() const;

    /**
     * @brief Gets the burn rate.
     * @return The burn rate as a double.
     */
    double getBurnRate() const;
};

/**
 * @class SolarPlant
 * @brief Represents a solar power plant.
 */
class SolarPlant : public PowerPlant
{
private:
    /** @brief The area of the solar panels. */
    double area;

public:
    /**
     * @brief Constructs a solar plant with name, efficiency, and area.
     * @param plantName The name of the plant.
     * @param plantEfficiency The efficiency of the plant.
     * @param plantArea The area of the solar panels.
     */
    SolarPlant(std::string plantName, double plantEfficiency, double plantArea);

    /**
     * @brief Copy constructor deleted to prevent slicing.
     */
    SolarPlant(const SolarPlant &other) = delete;

    /**
     * @brief Assignment operator deleted to prevent slicing.
     * @return Reference to this solar plant.
     */
    SolarPlant &operator=(const SolarPlant &other) = delete;

    /**
     * @brief Creates a clone of this solar plant.
     * @return A pointer to the cloned solar plant.
     */
    PowerPlant *clone() const override;

    /**
     * @brief Virtual destructor.
     */
    virtual ~SolarPlant() = default;

    /**
     * @brief Calculates the output of the solar plant.
     * @return The calculated output.
     */
    double calculateOutput() const override;

    /**
     * @brief Gets the area of the solar panels.
     * @return The area as a double.
     */
    double getArea() const;
};