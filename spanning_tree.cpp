#include "spanning_tree.h"
#include "resourceManager.h"
#include <queue>
#include<random>
#include <algorithm>

spanning_tree::spanning_tree(task_graph graph) {
	vertices = graph.getVertices();
	edges = graph.breadthFirstSearch();
	howManyResources = graph.getHowManyResources();

#ifdef DEBUG
	std::for_each(edges.begin(), edges.end(), [](std::pair<std::pair<task, task>, int> edge) { std::cout << edge.first.first << " - " << edge.first.second << ": " << edge.second << std::endl });
#endif // DEBUG

}
std::pair<spanning_tree, spanning_tree> spanning_tree::crossing(spanning_tree tree) {
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	std::uniform_real_distribution<> dist(min, vertices.size());
	int cross_point =  dist(gen);
	spanning_tree tree1 = *this;
	spanning_tree tree2 = tree;
	for (int i = cross_point; i < vertices.size(); ++i) {
		task copy = tree1.vertices[i];
		tree1.vertices[i] = tree2.vertices[i];
		tree2.vertices[i] = copy;
	}
	for (int i = cross_point; i < edges.size(); ++i) {
		std::pair<std::pair<task, task>, int > edge_copy = tree1.edges[i];
		tree1.edges[i] = tree2.edges[i];
		tree2.edges[i] = edge_copy;
	}
	std::pair<spanning_tree, spanning_tree> new_pair(tree1, tree2);
	return new_pair;

}
//spanning_tree spanning_tree::mutation() {
//	//code
//	
//}

unsigned int spanning_tree::countCost() {
	unsigned int cost = 0;
	for (auto v : vertices) {
		resourceManager::init(v.getResources());
		cost += resourceManager::selectRes().getPrice();
	}
	return cost;
}

unsigned int spanning_tree::getHowManyResources() {
	return howManyResources;
}