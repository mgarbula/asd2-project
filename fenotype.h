#ifndef __FENOTYPE__
#define __FENOTYPE__

#include "resource.h"
#include "task.h"

class fenotype {
private:
	const unsigned int taskNumber;
	resource res;
public:
	fenotype(task);
	resource getResource();
};

#endif // !__FENOTYPE__



