#ifndef __SPANNING_TREE__
#define __SPANNING_TREE__

#include <vector>
#include "task.h"
#include "task_graph.h"
//#include "fenotype.h"

class spanning_tree {
public:
	std::vector<task> vertices;
	//std::vector<std::pair<std::pair<task, task>, int>> edges;
	std::vector<std::pair<std::pair<int, int>, int>> helpEdges;
	std::vector<std::pair<std::pair<task*, task*>, int>> edges;
	//std::vector<fenotype> currentFenotype;
	unsigned int howManyResources;
	unsigned int totalCost;
	double totalTime;
	unsigned int broadcast;
public:
	//spanning_tree() {}
	spanning_tree(task_graph);
	spanning_tree& operator=(const spanning_tree& other);
	//spanning_tree& operator = (spanning_tree& other);
	std::pair<spanning_tree, spanning_tree> crossing(spanning_tree);//funckja przyjmuje jako argument przyjmuje drzewo i po skrzyzowaniu zwraca pare drzew tego z argumentu i tego biezacego
	spanning_tree mutation();
	spanning_tree clonning();
	unsigned int countCost();
	double countTime();
	unsigned int getHowManyResources();
	void mapToFenotype();
	spanning_tree(const spanning_tree& other);
private:
	void createEdges(std::vector<std::pair<std::pair<int, int>, int>>);
	std::vector<std::pair<std::pair<task*, task*>, int>> breadthFirstSearch();
};


#endif 
