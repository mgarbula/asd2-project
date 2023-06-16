#include "spanning_tree.h"
#include "resourceManager.h"
#include <queue>
#include<random>
#include <algorithm>

spanning_tree::spanning_tree(task_graph graph) {
	this->vertices = graph.getVertices();
	edges = graph.breadthFirstSearch();
	howManyResources = graph.getHowManyResources();
	//totalCost = graph.getTotalCost();
	mapToFenotype();
	for (task t : this->vertices) {
		for (resource v : t.getResources()) {
			//std::cout << "el: " << v.getPrice() <<  " a price: to " << t.getTheResource().getPrice() << std::endl;
		}
		//std::cout << "price: " << t.getTheResource().getPrice() << std::endl;
	}
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
		std::pair<std::pair<task, task>, int > edge_copy = tree1.edges[i];
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
	//tree.vertices[cross_point].setResource(resourceManager::selectRes(vertices[cross_point].getResources()));
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
	for (int i = 0; i < this->vertices.size(); i++) {
		//fenotype f(v);
		//v.setResource(f.getResource());
		this->vertices[i].setResource(resourceManager::selectRes(this->vertices[i].getResources()));
		this->totalCost += this->vertices[i].getTheResource().getPrice();
		//std::cout << "Resource wybrany i jest to " << this->vertices[i].getTheResource().getPrice() << std::endl;
		//currentFenotype.push_back(f);
	}
}