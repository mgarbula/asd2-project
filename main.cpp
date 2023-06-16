#include <iostream>
#include <string>
#include <algorithm>
#include "resourceManager.h"
#include "resource.h"
#include "task_graph.h"
#include "spanning_tree.h"

std::vector<spanning_tree> createGeneration(task_graph tgraph, int generationSize, int howManyRes) {
	std::vector<spanning_tree> generation;
	for (int i = 0; i < tgraph.getVertices().size() * generationSize * howManyRes; i++) {
		spanning_tree stree(tgraph);
		generation.push_back(stree);
	}
	return generation;
}

bool mySort(spanning_tree first, spanning_tree second) {
	return first.countCost() < second.countCost();
}

std::vector<spanning_tree> selection(std::vector<spanning_tree> generation, int howMany) {
	std::sort(generation.begin(), generation.end(), mySort);
	std::vector<spanning_tree> nextGeneration(generation.begin(), generation.begin() + howMany);
	return nextGeneration;
}

int main(){

	resourceManager::reset();

	int generationSize;
	int howManyLoops;

	/*std::cout << "Podaj wielkosc pokolenia poczatkowego\n";
	std::cin >> generationSize;
	std::string fileName;
	std::cout << "Podaj nazwe grafu\n";
	std::cin >> fileName;
	std::cout << "Podaj ilosc petli\n";
	std::cin >> howManyLoops;*/

	int currentLoops = 0;
	float clone, cross, mutation;

	/*std::cout << "Podaj ile klonowan\n";
	std::cin >> clone;
	std::cout << "Podaj ile krzyzowan\n";
	std::cin >> cross;
	std::cout << "Podaj ile mutacji\n";
	std::cin >> mutation;*/
	generationSize = 100;
	std::string fileName = "graf30.txt";
	howManyLoops = 7;
	clone = 0.3;
	cross = 0.4;
	mutation = 0.3;

	task_graph tgraph(fileName);

	spanning_tree stree(tgraph);

	std::vector<spanning_tree> generation = createGeneration(tgraph, generationSize, tgraph.getHowManyResources());

	std::vector<spanning_tree> newGeneartion;
	spanning_tree bestFromGeneration = generation[12];
	unsigned int bestCost = bestFromGeneration.totalCost;

	while (currentLoops < howManyLoops) {
		int i = 0;
		int clones = clone * generation.size();
		int crosses = cross * generation.size();
		int mutations = mutation * generation.size();

		newGeneartion = selection(generation, clones + crosses + mutations);
		
		//std::cout << "Best of new gen: " << newGeneartion[0].totalCost << std::endl;

		/*for (auto g : newGeneartion) {
			std::cout << "cost of that: " << g.totalCost << std::endl;
		}*/

		std::cout << "============================" << newGeneartion[0].totalCost << std::endl;

		if (newGeneartion[0].totalCost < bestCost ) {
			currentLoops = 0;
			bestFromGeneration = newGeneartion[0];
			bestCost = bestFromGeneration.totalCost;
			std::cout << "nowy najlepszy koszt: " << bestCost << std::endl;
		}
		else {
			currentLoops++;
		}

		std::vector<spanning_tree> modifiedGeneration;
		
		for (std::vector<spanning_tree>::iterator it = newGeneartion.begin(); it != newGeneartion.end(); ++it) {
			if (i++ < clones) {
				//std::cout << "klonowanie\n";
				modifiedGeneration.push_back((*it).clonning());
			}
			else if (i++ < crosses + clones) {
				//std::cout << "krzyzowanie\n";
				std::pair<spanning_tree, spanning_tree> pair = (*it).crossing(*(it + 1));
				modifiedGeneration.push_back(pair.first);
				modifiedGeneration.push_back(pair.second);
				it++;
			}
			else if (i++ < mutations + crosses + clones) {
				//std::cout << "mutacja\n";
				modifiedGeneration.push_back((*it).mutation());
			}
		}


		/*for (auto tree : modifiedGeneration) {
			tree.mapToFenotype();
		}*/
		for (int i = 0; i < modifiedGeneration.size(); i++) {
			modifiedGeneration[i].mapToFenotype();
		}
		//std::cout << "modifiedGeneration " << modifiedGeneration[0].vertices[0].getTheResource().getPrice() << std::endl;
		//std::cout << "before " << generation[0].vertices[0].getTheResource().getPrice() << std::endl;
		generation = modifiedGeneration;
		//std::cout << "after " << generation[0].vertices[0].getTheResource().getPrice() << std::endl;
	}
	system("pause");
    return 0;
}
