#include "fenotype.h"
#include "resourceManager.h"

fenotype::fenotype(task task) : taskNumber{ task.getTaskNumber() } {
	res = task.getTheResource();
}

resource fenotype::getResource() {
	return res;
}