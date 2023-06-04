#include "graph.h"
#include <random>
#include <iostream>

graph::graph(unsigned int size, resource resources[])
{
    this->size = size;
    this->resources = resources;
    arr = new int[size];
    for(int i=0;i<size;i++)
    {
        arr[i] = selectRes();
        resources[arr[i]].use();
    }
}
int graph::selectRes()
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

        return j;
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

        return j;
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

        return j;
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

        return j;
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

        return j;
    }
}
double graph::randomDouble(double max)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    double min = 0.0;
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}

void graph::connect(unsigned int source, unsigned int destiny, unsigned int edgeWeight)
{
    std::cout << source << " -(" << edgeWeight << ")->" << destiny << " : method(" << selectRes() << ")";
}
graph::~graph()
{
    delete[] arr;
}