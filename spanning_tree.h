#ifndef __SPANNING_TREE__
#define __SPANNING_TREE__

#include <vector>
#include "task.h"
#include "task_graph.h"

class spanning_tree {
public:
	std::vector<task> vertices;
	std::vector<std::pair<std::pair<task, task>, int>> edges;
	unsigned int howManyResources;
public:
	spanning_tree(task_graph);
	std::pair<spanning_tree, spanning_tree> crossing(spanning_tree);//funckja przyjmuje jako argument przyjmuje drzewo i po skrzyzowaniu zwraca pare drzew tego z argumentu i tego biezacego
	spanning_tree mutation();
	unsigned int countCost();
	unsigned int getHowManyResources();
};


#endif 
