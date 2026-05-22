#pragma once

#include <functional>
#include <cstddef>
#include "PowerPlant.h"
#include "GridStrategy.h"

/**
 * @class PowerGrid
 * @brief Manages a collection of power plants using the Pimpl Idiom.
 */
class PowerGrid
{
private:
    /**
     * @struct PowerGridImpl
     * @brief The actual implementation of the PowerGrid, hidden from users.
     */
    struct PowerGridImpl;
    /** @brief Pointer to the private implementation. */
    PowerGridImpl *pimpl;

public:
    /**
     * @brief Default constructor. Initializes an empty power grid.
     */
    PowerGrid();

    /**
     * @brief Copy constructor. Performs a deep copy of the @p other power grid.
     * @param other The power grid to copy from.
     */
    PowerGrid(const PowerGrid &other);

    /**
     * @brief Assignment operator. Performs a deep copy after cleaning existing resources.
     * @param other The power grid to assign from.
     * @return Reference to this power grid.
     */
    PowerGrid &operator=(const PowerGrid &other);

    /**
     * @brief Destructor. Frees the dynamically allocated implementation object.
     */
    ~PowerGrid();

    /**
     * @brief Adds a new power plant to the grid.
     * @param plant The power plant to add.
     */
    void addPlant(const PowerPlant &plant);

    /**
     * @brief Removes a power plant at the specified index.
     * @param index The index of the plant to remove.
     */
    void removePlant(size_t index);

    /**
     * @brief Retrieves a pointer to the power plant at the specified index.
     * @param index The index of the plant to retrieve.
     * @return A pointer to the power plant.
     */
    PowerPlant *getPlant(size_t index) const;

    /**
     * @brief Returns the number of power plants in the grid.
     * @return The current size as a size_t.
     */
    size_t size() const;

    /**
     * @brief Computes the total output of all power plants in the grid.
     * @return The total output as a double.
     */
    double sumOutputs() const;

    /**
     * @class ForwardIterator
     * @brief Iterator for traversing the power plants in the grid.
     */
    class ForwardIterator
    {
    private:
        /** @brief Pointer to the current power plant. */
        PowerPlant **ptr;

    public:
        /**
         * @brief Default constructor. Initializes an invalid iterator.
         */
        ForwardIterator();

        /**
         * @brief Constructs an iterator pointing to a specific power plant.
         * @param p Pointer to the power plant.
         */
        explicit ForwardIterator(PowerPlant **p);

        /**
         * @brief Dereference operator.
         * @return Reference to the power plant pointer.
         */
        PowerPlant *&operator*() const;

        /**
         * @brief Arrow operator.
         * @return Pointer to the power plant.
         */
        PowerPlant *operator->() const;

        /**
         * @brief Prefix increment operator.
         * @return Reference to this iterator.
         */
        ForwardIterator &operator++();

        /**
         * @brief Postfix increment operator.
         * @return A copy of the iterator before increment.
         */
        ForwardIterator operator++(int);

        /**
         * @brief Equality operator.
         * @param other The iterator to compare with.
         * @return True if both iterators point to the same position.
         */
        bool operator==(const ForwardIterator &other) const;

        /**
         * @brief Inequality operator.
         * @param other The iterator to compare with.
         * @return True if iterators point to different positions.
         */
        bool operator!=(const ForwardIterator &other) const;
    };

    /**
     * @brief Returns an iterator to the beginning of the grid.
     * @return ForwardIterator pointing to the first plant.
     */
    ForwardIterator begin();

    /**
     * @brief Returns an iterator to the end of the grid.
     * @return ForwardIterator pointing past the last plant.
     */
    ForwardIterator end();

    /**
     * @brief Sets the computation strategy for the grid.
     * @param strategy Pointer to the strategy to use.
     */
    void setStrategy(GridStrategy *strategy);

    /**
     * @brief Computes a value using the current strategy.
     * @return The computed value.
     */
    double compute() const;

    /**
     * @brief Type alias for a comparator function used in sorting.
     */
    using SortCallback = std::function<bool(const PowerPlant *, const PowerPlant *)>;

    /**
     * @brief Sorts the power plants using the provided comparator.
     * @param comparator The comparison function.
     */
    void sortPlants(SortCallback comparator);
};