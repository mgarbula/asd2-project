#include "resourceManager.h"
#include <random>
#include <vector>
#include <iostream>

unsigned int resourceManager::size = 0;
int resourceManager::prevRes = -1;
int resourceManager::recordedTime = 0;
record* resourceManager::resources = NULL;

void resourceManager::init(unsigned int _size)
{
    size = _size;
    resources = new record[size];
    for (int i = 0; i < size; i++)
        resources[i] = record();
}
void resourceManager::reset()
{
    for (int i = 0; i < size; i++)
        resources[i] = record();

}

void resourceManager::startRecTransition()
{
    prevRes = 0;
    recordedTime = 0;
}
int resourceManager::getRecTransition()
{
    return recordedTime;
}


/// <summary>
/// Returns resource randomly
/// </summary>
/// <returns>Type Resource</returns>
resource resourceManager::selectRes(std::vector<resource> _resources)
{
    double value = randomDouble();
    int resSize = _resources.size();
    int i, j;
    for (i = 0; i < resSize; i++)
        resources[i].lastTime++;
    if (value <= 0.15) // cheapest res
    {
        j = 0;
        unsigned int minVal = _resources[j].getPrice();
        for (i = 1; i < resSize; i++)
        {
            if (minVal > _resources[i].getPrice())
            {
                minVal = _resources[i].getPrice();
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
        unsigned int minVal = _resources[j].getTime();
        for (int i = 1; i < resSize; i++)
        {
            if (minVal > _resources[i].getTime())
            {
                minVal = _resources[i].getTime();
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
        unsigned int minVal = _resources[j].getTime() * _resources[j].getPrice();
        for (int i = 1; i < resSize; i++)
        {
            if (minVal > _resources[i].getTime() * _resources[i].getPrice())
            {
                minVal = _resources[i].getTime() * _resources[i].getPrice();
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
        unsigned int maxVal = resources[j].lastTime;
        for (int i = 1; i < resSize; i++)
        {
            if (maxVal > resources[j].lastTime)
            {
                maxVal = resources[j].lastTime;
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
        unsigned int minVal = resources[j].allocTimes;
        for (int i = 1; i < resSize; i++)
        {
            if (minVal > resources[i].allocTimes)
            {
                minVal = resources[i].allocTimes;
                j = i;
            }
        }
        // DEBUGING
#ifdef DEBUG
        std::cout << "\tNajrzadziej alokowany res : " << j << " at " << minVal << "\n";
#endif
        // DEBUGING

    }
    resources[j].lastTime = 0;
    resources[j].allocTimes++;
    return _resources[j];
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
