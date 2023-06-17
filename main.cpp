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
	int stopCondition;

	/*std::cout << "Podaj wielkosc pokolenia poczatkowego\n";
	std::cin >> generationSize;
	std::string fileName;
	std::cout << "Podaj nazwe grafu\n";
	std::cin >> fileName;
	std::cout << "Podaj warunek stopu\n";
	std::cin >> stopCondition;*/

	int currentLoops = 0;
	float clone, cross, mutation;
	double time;

	/*std::cout << "Podaj ile klonowan\n";
	std::cin >> clone;
	std::cout << "Podaj ile krzyzowan\n";
	std::cin >> cross;
	std::cout << "Podaj ile mutacji\n";
	std::cin >> mutation;
	std::cout << "Podaj czas nie do przekroczenia\n";
	std::cin >> time;*/
	generationSize = 10;
	std::string fileName = "graf10.txt";
	stopCondition = 5;
	clone = 0.3;
	cross = 0.4;
	mutation = 0.3;
	time = 300;

	task_graph tgraph(fileName);

	spanning_tree stree(tgraph);

	std::vector<spanning_tree> generation = createGeneration(tgraph, generationSize, tgraph.getHowManyResources());

	std::vector<spanning_tree> newGeneartion;
	spanning_tree bestFromGeneration = generation[12];
	unsigned int bestCost = bestFromGeneration.totalCost;

	while (currentLoops < stopCondition) {
		int i = 0;
		int clones = clone * generation.size();
		int crosses = cross * generation.size();
		int mutations = mutation * generation.size();

		newGeneartion = selection(generation, clones + crosses + mutations);

		std::cout << "============================" << newGeneartion[0].totalCost << std::endl;

		if (newGeneartion[0].totalCost < bestCost ) {
			std::cout << "Koszt jest lepszy i wynosi: " << newGeneartion[0].totalCost << std::endl;
			std::cout << "ale czy czas sie zgadza? ";
			if (newGeneartion[0].totalTime <= time) {
				std::cout << "TAK!\n";
				currentLoops = 0;
				bestFromGeneration = newGeneartion[0];
				bestCost = bestFromGeneration.totalCost;
				std::cout << "nowy najlepszy koszt: " << bestCost << std::endl;
			}
			else {
				std::cout << "NIE!";
				currentLoops++;
			}
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

		for (int i = 0; i < modifiedGeneration.size(); i++) {
			modifiedGeneration[i].mapToFenotype();
		}
		generation = modifiedGeneration;
	}
	system("pause");
    return 0;
}
