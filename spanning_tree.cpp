#include "spanning_tree.h"
#include "resourceManager.h"
#include <queue>
#include<random>
#include <algorithm>

spanning_tree::spanning_tree(task_graph graph) {
	this->vertices = graph.getVertices();
	this->helpEdges = graph.getHelpEdges();
	createEdges(helpEdges);
	this->edges = breadthFirstSearch();
	this->howManyResources = graph.getHowManyResources();
	this->broadcast = graph.getBroadcast();
	mapToFenotype();
	countCost();
#ifdef DEBUG
	std::for_each(edges.begin(), edges.end(), [](std::pair<std::pair<task, task>, int> edge) { std::cout << edge.first.first << " - " << edge.first.second << ": " << edge.second << std::endl });
#endif // DEBUG

}
/*spanning_tree& spanning_tree::operator = (spanning_tree& other) {
	this->vertices = other.vertices;
	this->edges = other.edges;
	return *this;
}*/

void spanning_tree::createEdges(std::vector<std::pair<std::pair<int, int>, int>> help) {
	for (std::vector<std::pair<std::pair<int, int>, int>>::iterator it = help.begin(); it != help.end(); ++it) {
		std::pair<std::pair<int, int>, int> fullPair = *it;
		std::pair<task*, task*> taskEdge(&(vertices[fullPair.first.first]), &(vertices[fullPair.first.second]));
		std::pair<std::pair<task*, task*>, int> edgeWithWeight(taskEdge, fullPair.second);
		edges.push_back(edgeWithWeight);
	}
}

std::vector<std::pair<std::pair<task*, task*>, int>> spanning_tree::breadthFirstSearch() {
	std::queue<task*> queue;
	std::vector<task*> visited;
	std::vector<std::pair<std::pair<task*, task*>, int>> treeEdges;

	queue.push(&(vertices[0]));

	while (!queue.empty()) {
		task* elem = queue.front();
		visited.push_back(elem);
		queue.pop();

		std::vector<std::pair<std::pair<task*, task*>, int>> help;

		for (std::vector<std::pair<std::pair<task*, task*>, int>>::iterator it = edges.begin(); it != edges.end(); ++it) {
			if (*elem == *((*it).first.first)) {
				help.push_back(*it);
			}
		}

		std::for_each(help.begin(), help.end(), [&treeEdges, &queue, &visited](std::pair<std::pair<task*, task*>, int> pair) {
			if (std::find(visited.begin(), visited.end(), pair.first.second) == visited.end()) {
				queue.push(pair.first.second);
				treeEdges.push_back(pair);
			}
		});
	}

	return treeEdges;
}


spanning_tree::spanning_tree(const spanning_tree& other) {
	this->edges = other.edges;
	this->vertices = other.vertices;
	this->totalCost = other.totalCost;
	this->howManyResources = other.howManyResources;
	
}
spanning_tree& spanning_tree::operator=(const spanning_tree& other)
{
	if (this == &other)
		return *this;
	this->vertices = other.vertices;
	this->edges = other.edges;
	this->totalCost = other.totalCost;
	this->howManyResources = other.howManyResources;
	return *this;
}

std::pair<spanning_tree, spanning_tree> spanning_tree::crossing(spanning_tree tree) {
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	std::uniform_real_distribution<> dist(min, vertices.size() - 1);
	int cross_point =  dist(gen);
	spanning_tree tree1 = *this;
	spanning_tree tree2 = tree;
	for (int i = cross_point; i < vertices.size(); ++i) {
		task copy = tree1.vertices[i];
		tree1.vertices[i] = tree2.vertices[i];
		tree2.vertices[i] = copy;
	}
	for (int i = cross_point; i < edges.size(); ++i) {
		std::pair<std::pair<task*, task*>, int> edge_copy = tree1.edges[i];
		tree1.edges[i] = tree2.edges[i];
		tree2.edges[i] = edge_copy;
	}
	std::pair<spanning_tree, spanning_tree> new_pair(tree1, tree2);
	return new_pair;
	
}

unsigned int spanning_tree::countCost() {
	totalCost = 0;
	for (auto t : vertices) {
		int price = t.getTheResource().getPrice();
		totalCost += price;
		//std::cout << "zwiekszony koszt: " << price << std::endl;
	}
	return totalCost;
}

unsigned int spanning_tree::getHowManyResources() {
	return howManyResources;
}

spanning_tree spanning_tree::mutation() {
	//resourceManager res;
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	std::uniform_real_distribution<> dist(min, vertices.size() - 1);
	int cross_point = dist(gen);
	spanning_tree tree = *this;
	tree.vertices[cross_point].setResource(resourceManager::selectRes(vertices[cross_point].getResources()));
	return tree;

}
spanning_tree spanning_tree::clonning() {
	spanning_tree tree = *this;
	return tree;
}

void spanning_tree::mapToFenotype() {
	//currentFenotype.clear();
	//for (auto v : vertices) {
	this->totalCost = 0;
	for (int i = 0; i < vertices.size(); i++) {
		//fenotype f(v);
		//v.setResource(f.getResource());
		this->vertices[i].setResource(resourceManager::selectRes(this->vertices[i].getResources()));
		this->totalCost += this->vertices[i].getTheResource().getPrice();
		//std::cout << "Resource wybrany i jest to " << this->vertices[i].getTheResourceNumber() << std::endl;
		//currentFenotype.push_back(f);
	}
	countTime();
}

double spanning_tree::countTime() {
	std::vector<double> timesOfResources(this->howManyResources);
	for (int i = 0; i < edges.size(); i++) {
		task* parentTask = edges[i].first.first;
		task* childTask = edges[i].first.second;
		int weight = edges[i].second;
		int parentTaskResourceNumber = (*parentTask).getTheResourceNumber();
		int childTaskResourceNumber = (*childTask).getTheResourceNumber();
		if (parentTaskResourceNumber == childTaskResourceNumber) {
			std::cout << "przed if\n";
			std::cout << "timesSize " << timesOfResources.size() << std::endl;
			std::cout << "parentTaskResourceNumber " << parentTaskResourceNumber << std::endl;
			timesOfResources[parentTaskResourceNumber] += ((*parentTask).getTheResource().getTime() + (*childTask).getTheResource().getTime());
			std::cout << "po if\n";
		}
		else {
			std::cout << "przed else\n";
			timesOfResources[parentTaskResourceNumber] += (*parentTask).getTheResource().getTime();
			std::cout << "po else 1\n";
			timesOfResources[childTaskResourceNumber] += (timesOfResources[parentTaskResourceNumber] + weight/broadcast + (*childTask).getTheResource().getTime());
			std::cout << "po else 2\n";
		}
	}
	totalTime = *std::max_element(timesOfResources.begin(), timesOfResources.end());

	return totalTime;
}