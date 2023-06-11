/*
Menadżer zasobów

*/

#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "resource.h"
#include <vector>

class resourceManager
{
private:
    /* data */
    static std::vector<resource> resources;
public:
    static void init(std::vector<resource>);
    static resource selectRes(); //Random pick the next res
    static double randomDouble(double = 1.0); //Returns random double from 0 to 1
};


#endif