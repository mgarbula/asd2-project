/*
Menadżer zasobów

*/

#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "resource.h"
#include <vector>

struct record {
    int lastTime = 0;
    int allocTimes = 0;
};

class resourceManager
{
private:
    /* data */
    static unsigned int size;
    static int prevRes;
    static int recordedTime;
    static record* resources;
public:
    static void reset();
    static void init(unsigned int);
    static std::pair<resource, int> selectRes(std::vector<resource>); //Random pick the next res
    static double randomDouble(double = 1.0); //Returns random double from 0 to 1
    static void startRecTransition(); 
    static int getRecTransition();
    static void del();
};


#endif