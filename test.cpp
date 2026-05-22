#include <cassert>
#include <iostream>
#include "PowerGrid.h"

int main()
{
    // Test CoalPlant
    CoalPlant coal("Coal A", 0.35, 500.0, 1000.0);
    assert(coal.getName() == "Coal A");
    assert(coal.getEfficiency() == 0.35);
    assert(coal.getBurnRate() == 500.0);
    assert(coal.getSupply() == 1000.0);
    assert(coal.calculateOutput() == 0.35 * 500.0);
    coal.addSupply(200.0);
    assert(coal.getSupply() == 1200.0);

    // Test SolarPlant
    SolarPlant solar("Solar B", 0.22, 15000.0);
    assert(solar.getName() == "Solar B");
    assert(solar.getEfficiency() == 0.22);
    assert(solar.getArea() == 15000.0);
    assert(solar.calculateOutput() == 0.22 * 15000.0);

    // Test clone (Prototype pattern)
    PowerPlant *clonedCoal = coal.clone();
    assert(clonedCoal->getName() == "Coal A");
    assert(clonedCoal->getEfficiency() == 0.35);
    assert(dynamic_cast<CoalPlant *>(clonedCoal)->getBurnRate() == 500.0);
    delete clonedCoal;

    PowerPlant *clonedSolar = solar.clone();
    assert(clonedSolar->getName() == "Solar B");
    delete clonedSolar;

    // Test PowerGrid container
    PowerGrid grid;
    assert(grid.size() == 0);

    grid.addPlant(coal);
    grid.addPlant(solar);
    grid.addPlant(CoalPlant("Coal C", 0.40, 620.0, 2000.0));
    assert(grid.size() == 3);

    // Test getPlant
    PowerPlant *p = grid.getPlant(0);
    assert(p->getName() == "Coal A");
    p = grid.getPlant(2);
    assert(p->getName() == "Coal C");

    // Test removePlant
    grid.removePlant(1);
    assert(grid.size() == 2);
    assert(grid.getPlant(1)->getName() == "Coal C");

    // Test deep copy (copy constructor)
    PowerGrid gridCopy = grid;
    assert(gridCopy.size() == 2);
    assert(gridCopy.getPlant(0)->getName() == "Coal A");
    assert(gridCopy.getPlant(1)->getName() == "Coal C");
    grid.removePlant(0);
    assert(grid.size() == 1);
    assert(gridCopy.size() == 2);

    // Test assignment operator deep copy
    PowerGrid gridAssigned;
    gridAssigned = gridCopy;
    assert(gridAssigned.size() == 2);
    gridCopy.removePlant(0);
    assert(gridAssigned.size() == 2);

    // Test iterator
    gridAssigned.addPlant(SolarPlant("Solar D", 0.30, 10000.0));
    int count = 0;
    for (PowerGrid::ForwardIterator it = gridAssigned.begin(); it != gridAssigned.end(); ++it)
    {
        ++count;
    }
    assert(count == 3);
    // test prefix and postfix increment
    PowerGrid::ForwardIterator it = gridAssigned.begin();
    PowerGrid::ForwardIterator it2 = it++;
    assert(it2 != it);
    it2 = ++it;
    assert(it2 == it);

    // Test sortPlants with callback
    gridAssigned.sortPlants([](const PowerPlant *a, const PowerPlant *b)
                            { return a->getEfficiency() < b->getEfficiency(); });
    // After sort, first should have lowest efficiency
    double firstEff = gridAssigned.getPlant(0)->getEfficiency();
    double secondEff = gridAssigned.getPlant(1)->getEfficiency();
    double thirdEff = gridAssigned.getPlant(2)->getEfficiency();
    assert(firstEff <= secondEff && secondEff <= thirdEff);

    // Test strategy - TotalOutputStrategy
    gridAssigned.setStrategy(new TotalOutputStrategy());
    double total = gridAssigned.compute();
    double expectedTotal = 0.0;
    for (size_t i = 0; i < gridAssigned.size(); ++i)
    {
        expectedTotal += gridAssigned.getPlant(i)->calculateOutput();
    }
    assert(total == expectedTotal);

    // Test AverageOutputStrategy
    gridAssigned.setStrategy(new AverageOutputStrategy());
    double avg = gridAssigned.compute();
    assert(avg == expectedTotal / gridAssigned.size());

    // Test MinOutputStrategy
    gridAssigned.setStrategy(new MinOutputStrategy());
    double minVal = gridAssigned.compute();
    double expectedMin = gridAssigned.getPlant(0)->calculateOutput();
    for (size_t i = 1; i < gridAssigned.size(); ++i)
    {
        double out = gridAssigned.getPlant(i)->calculateOutput();
        if (out < expectedMin)
            expectedMin = out;
    }
    assert(minVal == expectedMin);

    // Test StrategyNotSetException
    PowerGrid emptyGrid;
    bool strategyException = false;
    try
    {
        emptyGrid.compute();
    }
    catch (const StrategyNotSetException &)
    {
        strategyException = true;
    }
    assert(strategyException);

    // Test for third class (WindPlant) - to be implemented
    WindPlant wind("Sea Breeze", 0.45, 80.0);
    assert(wind.getName() == "Sea Breeze");
    assert(wind.getEfficiency() == 0.45);
    assert(wind.calculateOutput() == 0.45 * 80.0);
    PowerPlant *windClone = wind.clone();
    assert(windClone->getName() == "Sea Breeze");
    delete windClone;

    PowerGrid windGrid;
    windGrid.addPlant(wind);
    assert(windGrid.size() == 1);
    windGrid.setStrategy(new TotalOutputStrategy());
    assert(windGrid.compute() == 36.0);

    std::cout << "All tests passed." << std::endl;
    return 0;
}