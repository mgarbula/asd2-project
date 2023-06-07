#ifndef __SPANNING_TREE__
#define __SPANNING_TREE__

#include <vector>
#include "task.h"
#include "task_graph.h"

class spanning_tree {
private:
	std::vector<task> vertices;
	std::vector<std::pair<std::pair<task, task>, int>> edges;
public:
	spanning_tree(task_graph);
};

#endif 
