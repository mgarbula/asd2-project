/*
Menadżer zasobów

*/

#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "resource.h"

class resourceManager
{
private:
    /* data */
    static int size;
    static resource* resources;
public:
    static void init(unsigned int, resource[]);
    static resource selectRes(); //Random pick the next res
    static double randomDouble(double = 1.0); //Returns random double from 0 to 1
    static void del();
};


#endif