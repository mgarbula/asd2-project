#include "fenotype.h"
#include "resourceManager.h"

fenotype::fenotype(task task) : taskNumber{ task.getTaskNumber() } {
	resourceManager::init(task.getResources());
	res = resourceManager::selectRes();
}

resource fenotype::getResource() {
	return res;
}