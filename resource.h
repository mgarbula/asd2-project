#ifndef __RESOURCE_H__
#define __RESOURCE_H__

class resource
{
private:
    unsigned int time;
    unsigned int price;
    unsigned int counter;
    unsigned int lastUsed;
public:
    void tick();
    void use();
    unsigned int getTime();
    unsigned int getPrice();
    unsigned int getCount();
    unsigned int getLastUsedTimer();
    resource(unsigned int=0, unsigned int=0);
    resource& operator = (const resource& other);
    ~resource();
};

#endif