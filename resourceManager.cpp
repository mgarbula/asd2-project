#include "resourceManager.h"
#include <random>
#include <iostream>

std::vector<resource> resourceManager::resources;

void resourceManager::init(std::vector<resource> _resources)
{
    resources = _resources;
}

/// <summary>
/// Returns resource randomly
/// </summary>
/// <returns>Type Resource</returns>
resource resourceManager::selectRes()
{
    double value = randomDouble();
    int resSize = 2;//(sizeof(resources) / sizeof(resources[0]));
    int i, j;
    for (i = 0; i < resSize; i++)
        resources[i].tick();
    if (value <= 0.15) // cheapest res
    {
        j = 0;
        unsigned int minVal = resources[j].getPrice();
        for (i = 1; i < resSize; i++)
        {
            if (minVal > resources[i].getPrice())
            {
                minVal = resources[i].getPrice();
                j = i;
            }
        }
        // DEBUGING
#ifdef DEBUG
        std::cout << "\tCheapest res : " << j << " at " << minVal << "\n";
#endif
        // DEBUGING

    }
    else if (value <= 0.30) // fastest res
    {
        j = 0;
        unsigned int minVal = resources[j].getTime();
        for (int i = 1; i < resSize; i++)
        {
            if (minVal > resources[i].getTime())
            {
                minVal = resources[i].getTime();
                j = i;
            }
        }
        // DEBUGING
#ifdef DEBUG
        std::cout << "\tFastest res : " << j << " at " << minVal << "\n";
#endif
        // DEBUGING

    }
    else if (value <= 0.60) // Min(czas*koszt)
    {
        j = 0;
        unsigned int minVal = resources[j].getTime() * resources[j].getPrice();
        for (int i = 1; i < resSize; i++)
        {
            if (minVal > resources[i].getTime() * resources[i].getPrice())
            {
                minVal = resources[i].getTime() * resources[i].getPrice();
                j = i;
            }
        }
        // DEBUGING
#ifdef DEBUG
        std::cout << "\tMin(czas*koszt) res : " << j << " at " << minVal << "\n";
#endif
        // DEBUGING

    }
    else if (value <= 0.80) // Najdluzej bezczyny zasob
    {
        j = 0;
        unsigned int maxVal = resources[j].getLastUsedTimer();
        for (int i = 1; i < resSize; i++)
        {
            if (maxVal > resources[j].getLastUsedTimer())
            {
                maxVal = resources[j].getLastUsedTimer();
                j = i;
            }
        }
        // DEBUGING
#ifdef DEBUG
        std::cout << "\tNajdluzej bezczyny res : " << j << " at " << maxVal << "\n";
#endif
        // DEBUGING

    }
    else // Najrzadziej alokowany
    {
        j = 0;
        unsigned int minVal = resources[j].getCount();
        for (int i = 1; i < resSize; i++)
        {
            if (minVal > resources[i].getCount())
            {
                minVal = resources[i].getCount();
                j = i;
            }
        }
        // DEBUGING
#ifdef DEBUG
        std::cout << "\tNajrzadziej alokowany res : " << j << " at " << minVal << "\n";
#endif
        // DEBUGING

    }
    return resources[j];
}
/// <summary>
/// Returns random double between 0 and max
/// </summary>
/// <param name="max"></param>
/// <returns>Random double <0, max)</returns>
double resourceManager::randomDouble(double max)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    double min = 0.0;
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}
