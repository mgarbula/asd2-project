#include "task.h"

task::task(unsigned int _taskNumber, std::vector<resource> _resources) : taskNumber{ _taskNumber }, resources{ _resources } {}

std::vector<resource> task::getResources() {
	return resources;
}

unsigned int task::getTaskNumber() {
	return taskNumber;
}

//std::ostream& task::operator<<(std::ostream& os, const task& ts) {
//	os << "Task number: " << ts.taskNumber << std::endl;
//	for (int i = 0; i < ts.resources.size(); i++) {
//		os << i << ": Time: " << ts.resources[i].getTime() << ", cost: " << ts.resources[i].getPrice() << std::endl;
//	}
//	return os;
//}