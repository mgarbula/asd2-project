#ifndef __TASK__
#define __TASK__

#include <vector>
#include <ostream>
#include "resource.h"

class task {
private:
	const unsigned int taskNumber;
	std::vector<resource> resources;
public:
	task() : taskNumber{ INT_MAX } {}
	task(const task&);
	task(unsigned int, std::vector<resource>);
	std::vector<resource> getResources();
	unsigned int getTaskNumber();
	friend std::ostream& operator<<(std::ostream& os, const task& ts);
	friend bool operator==(const task&, const task&);
	task& operator = (const task& other);
};

#endif