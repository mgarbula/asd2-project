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
	task(unsigned int, std::vector<resource>);
	std::vector<resource> getResources();
	unsigned int getTaskNumber();
	/*friend std::ostream& operator<<(std::ostream& os, const task& ts) {
		os << "Task number: " << ts.getTaskNumber() << std::endl;
		for (int i = 0; i < ts.getResources.size(); i++) {
			os << i << ": Time: " << ts.getResources()[i].getTime() << ", cost: " << ts.getResources()[i].getPrice() << std::endl;
		}
		return os;
	}*/
};

#endif 

