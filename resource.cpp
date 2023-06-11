#include "resource.h"


void resource::tick()
{
    lastUsed++;
}

unsigned int resource::getTime()
{
    return time;
}

unsigned int resource::getPrice()
{
    return price;
}

unsigned int resource::getCount()
{
    return counter;
}
void resource::use()
{
    lastUsed = 0;
    counter++;
}

unsigned int resource::getLastUsedTimer()
{
    return lastUsed;
}

resource::resource(unsigned int _time, unsigned int _price) : time{_time}, price{_price}
{
    counter = 0;
}
resource& resource::operator = (const resource& other) {
    this->counter = other.counter;
    this->lastUsed = other.lastUsed;
    return *this;
}

resource::~resource()
{
}
