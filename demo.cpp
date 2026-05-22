#include <iostream>
#include <algorithm>
#include "PowerGrid.h"

bool sortByEfficiencyDesc(const PowerPlant *a, const PowerPlant *b)
{
    return a->getEfficiency() > b->getEfficiency();
}

bool sortByNameDesc(const PowerPlant *a, const PowerPlant *b)
{
    return a->getName() > b->getName();
}

int main()
{
    PowerGrid grid;
    grid.addPlant(CoalPlant("Zeta Coal", 0.35, 500.0, 1000.0));
    grid.addPlant(SolarPlant("Alpha Solar", 0.22, 15000.0));
    grid.addPlant(CoalPlant("Beta Coal", 0.40, 620.0, 2000.0));

    PowerPlant *testPlant = grid.getPlant(0);
    // polymorphism
    std::cout << "Test plant output: " << testPlant->calculateOutput() << "\n";

    std::cout << "Total output before supply change: " << grid.sumOutputs() << "\n";

    // dynamic_cast
    for (size_t i = 0; i < grid.size(); ++i)
    {
        if (auto *coal = dynamic_cast<CoalPlant *>(grid.getPlant(i)))
        {
            std::cout << coal->getName() << " supply: " << coal->getSupply() << "\n";
            coal->addSupply(500.0);
            std::cout << "After adding 500, supply: " << coal->getSupply() << "\n";
        }
    }

    // deep copy
    PowerGrid backupGrid = grid;

    // strategy
    grid.setStrategy(new TotalOutputStrategy());
    backupGrid.setStrategy(new MinOutputStrategy());

    std::cout << "Total output: " << grid.compute() << "\n";
    std::cout << "Min output: " << backupGrid.compute() << "\n";

    // callback
    grid.sortPlants(sortByEfficiencyDesc);
    std::cout << "Plants sorted by efficiency (descending):\n";
    // iterator
    std::for_each(grid.begin(), grid.end(), [](PowerPlant *p)
                  { std::cout << p->getName() << " (Efficiency: " << p->getEfficiency() << ")\n"; });

    grid.sortPlants(sortByNameDesc);
    std::cout << "\nPlants sorted by name (descending):\n";
    std::for_each(grid.begin(), grid.end(), [](PowerPlant *p)
                  { std::cout << p->getName() << "\n"; });

    return 0;
}