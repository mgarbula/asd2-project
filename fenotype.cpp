#include "fenotype.h"
#include "resourceManager.h"

fenotype::fenotype(task task) : taskNumber{ task.getTaskNumber() } {
	resourceManager::init(task.getResources().size());
	res = resourceManager::selectRes(task.getResources());
}

resource fenotype::getResource() {
	return res;
}