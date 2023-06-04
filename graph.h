/*
Klasa grafu zadań.
W węzłach znajdują się sposoby przydziału zasobów dla poszczególnych zadań.
*/

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "resource.h"

class graph
{
private:
    /* data */
    int size;
    int* arr;
    resource* resources;
    int selectRes(); //Random pick the next res
    double randomDouble(double=1.0); //Returns random double from 0 to 1
public:
    graph(unsigned int, resource[]);
    void connect(unsigned int source, unsigned int destiny, unsigned int edgeWeight);
    ~graph();
};


#endif