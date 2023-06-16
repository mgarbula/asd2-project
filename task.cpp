#include "task.h"

task::task(unsigned int _taskNumber, std::vector<resource> _resources) : taskNumber{ _taskNumber }, resources{ _resources } {}

task::task(const task& t) : taskNumber{ t.taskNumber } { 
	this->resources = t.resources; 
	this->the_resource = t.the_resource; 
}

std::vector<resource> task::getResources() {
	return resources;
}

unsigned int task::getTaskNumber() {
	return taskNumber;
}

std::ostream& operator<<(std::ostream& os, const task& ts) {
	os << "Task number: " << ts.taskNumber << std::endl;
	std::vector<resource> resources = ts.resources;
	for (int i = 0; i < ts.resources.size(); i++) {
		os << i << ": Time: " << resources.at(i).getTime() << ", cost: " << resources[i].getPrice() << std::endl;
	}
	return os;
}

bool operator==(const task& taskL, const task& taskR) {
	return taskL.taskNumber == taskR.taskNumber;
}
task & task::operator = (const task& other) {
	 if (this == &other) {
		 return *this;
	 }
	 this->the_resource = other.the_resource;
	 this->resources = other.resources;
	 return *this;
}
 
 void task::setResource(resource resource_) {
	 this->the_resource = resource_;
 }
 resource task::getTheResource()
 {
	 return the_resource;
 }