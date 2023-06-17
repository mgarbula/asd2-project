#ifndef __TASK__
#define __TASK__

#include <vector>
#include <ostream>
#include "resource.h"

class task {
private:
	resource the_resource;
	int theResourceNumber;
	const unsigned int taskNumber;
	std::vector<resource> resources;
public:
	task() : taskNumber{ INT_MAX } {}
	task(const task&);
	task(unsigned int, std::vector<resource>);
	std::vector<resource> getResources();
	resource getTheResource();
	int getTheResourceNumber();
	unsigned int getTaskNumber();
	friend std::ostream& operator<<(std::ostream& os, const task& ts);
	friend bool operator==(const task&, const task&);
	task& operator = (const task& other);
	void setResource(std::pair<resource, int> resource_);
};

#endif