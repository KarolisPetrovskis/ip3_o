#include "PowerGrid.h"
#include <vector>
#include <algorithm>

class PowerGrid::PowerGridImpl
{
private:
    std::vector<PowerPlant *> plants;
    GridStrategy *strategy = nullptr;

    PowerGridImpl() = default;
    PowerGridImpl(const PowerGridImpl &other);
    PowerGridImpl &operator=(const PowerGridImpl &other);
    ~PowerGridImpl();

    void addPlant(const PowerPlant &plant);
    void removePlant(size_t index);
    PowerPlant *getPlant(size_t index) const;
    double sumOutputs() const;
    size_t size() const;
    void setStrategy(GridStrategy *strategy);
    double compute() const;
    void sortPlants(PowerGrid::SortCallback comparator);
    PowerPlant **begin();
    PowerPlant **end();

    friend class PowerGrid;
};

PowerGrid::PowerGridImpl::~PowerGridImpl()
{
    for (auto *p : plants)
        delete p;
    delete strategy;
}

PowerGrid::PowerGridImpl::PowerGridImpl(const PowerGridImpl &other)
    : strategy(nullptr)
{
    plants.reserve(other.plants.size());
    for (const auto *plant : other.plants)
        plants.push_back(plant->clone());
}

PowerGrid::PowerGridImpl &PowerGrid::PowerGridImpl::operator=(const PowerGridImpl &other)
{
    if (this != &other)
    {
        for (auto *p : plants)
            delete p;
        plants.clear();
        plants.reserve(other.plants.size());
        for (const auto *plant : other.plants)
            plants.push_back(plant->clone());

        delete strategy;
        strategy = nullptr;
    }
    return *this;
}

void PowerGrid::PowerGridImpl::addPlant(const PowerPlant &plant)
{
    plants.push_back(plant.clone());
}

void PowerGrid::PowerGridImpl::removePlant(size_t index)
{
    if (index < plants.size())
    {
        delete plants[index];
        plants.erase(plants.begin() + index);
    }
}

PowerPlant *PowerGrid::PowerGridImpl::getPlant(size_t index) const
{
    return (index < plants.size()) ? plants[index] : nullptr;
}

size_t PowerGrid::PowerGridImpl::size() const
{
    return plants.size();
}

double PowerGrid::PowerGridImpl::sumOutputs() const
{
    double total = 0.0;
    for (const auto *plant : plants)
        total += plant->calculateOutput();
    return total;
}

void PowerGrid::PowerGridImpl::setStrategy(GridStrategy *strategy)
{
    delete this->strategy;
    this->strategy = strategy;
}

double PowerGrid::PowerGridImpl::compute() const
{
    if (!strategy)
        throw StrategyNotSetException();
    return strategy->execute(plants);
}

void PowerGrid::PowerGridImpl::sortPlants(PowerGrid::SortCallback comparator)
{
    std::sort(plants.begin(), plants.end(), comparator);
}

PowerPlant **PowerGrid::PowerGridImpl::begin()
{
    return plants.data();
}

PowerPlant **PowerGrid::PowerGridImpl::end()
{
    return plants.data() + plants.size();
}

PowerGrid::PowerGrid() : pimpl(new PowerGridImpl()) {}

PowerGrid::PowerGrid(const PowerGrid &other)
    : pimpl(new PowerGridImpl(*other.pimpl)) {}

PowerGrid &PowerGrid::operator=(const PowerGrid &other)
{
    if (this != &other)
    {
        delete pimpl;
        pimpl = new PowerGridImpl(*other.pimpl);
    }
    return *this;
}

PowerGrid::~PowerGrid()
{
    delete pimpl;
}

void PowerGrid::addPlant(const PowerPlant &plant)
{
    pimpl->addPlant(plant);
}

void PowerGrid::removePlant(size_t index)
{
    pimpl->removePlant(index);
}

PowerPlant *PowerGrid::getPlant(size_t index) const
{
    return pimpl->getPlant(index);
}

size_t PowerGrid::size() const
{
    return pimpl->size();
}

double PowerGrid::sumOutputs() const
{
    return pimpl->sumOutputs();
}

PowerGrid::ForwardIterator PowerGrid::begin()
{
    return ForwardIterator(pimpl->begin());
}

PowerGrid::ForwardIterator PowerGrid::end()
{
    return ForwardIterator(pimpl->end());
}

void PowerGrid::setStrategy(GridStrategy *strategy)
{
    pimpl->setStrategy(strategy);
}

double PowerGrid::compute() const
{
    return pimpl->compute();
}

void PowerGrid::sortPlants(SortCallback comparator)
{
    pimpl->sortPlants(comparator);
}

PowerGrid::ForwardIterator::ForwardIterator() : ptr(nullptr) {}

PowerGrid::ForwardIterator::ForwardIterator(PowerPlant **p) : ptr(p) {}

PowerPlant *&PowerGrid::ForwardIterator::operator*() const
{
    return *ptr;
}

PowerPlant *PowerGrid::ForwardIterator::operator->() const
{
    return *ptr;
}

PowerGrid::ForwardIterator &PowerGrid::ForwardIterator::operator++()
{
    ++ptr;
    return *this;
}

PowerGrid::ForwardIterator PowerGrid::ForwardIterator::operator++(int)
{
    ForwardIterator tmp = *this;
    ++ptr;
    return tmp;
}

bool PowerGrid::ForwardIterator::operator==(const ForwardIterator &other) const
{
    return ptr == other.ptr;
}

bool PowerGrid::ForwardIterator::operator!=(const ForwardIterator &other) const
{
    return ptr != other.ptr;
}