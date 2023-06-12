#include <iostream>
#include <string>
#include "resourceManager.h"
#include "resource.h"
#include "task_graph.h"
#include "spanning_tree.h"

std::vector<spanning_tree> createGeneration(task_graph tgraph, int generationSize, int howManyRes) {
	std::vector<spanning_tree> generation;

	for (int i = 0; i < tgraph.getVertices().size() * generationSize * howManyRes; i++) {
		spanning_tree stree(tgraph);
		stree.mapToFenotype();
		generation.push_back(stree);
	}
	return generation;
}

int main(){
    
    /*
    JAK UZYWAC bo sam nie wiedzia�em

    resource specialistic{400, 10};
    resource universal{50, 210};

    resource res[2] {specialistic, universal};

    resourceManager::init(res);
    std::cout << resourceManager::selectRes().getTime() << "\n";*/

	int generationSize;
	std::cout << "Podaj wielkosc pokolenia poczatkowego\n";
	std::cin >> generationSize;

	std::string fileName = "graf10.txt";
	task_graph tgraph(fileName);
	spanning_tree stree(tgraph);

	std::vector<spanning_tree> generation = createGeneration(tgraph, generationSize, tgraph.getHowManyResources());

    return 0;
}