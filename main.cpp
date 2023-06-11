#include <iostream>
#include <string>
#include "resourceManager.h"
#include "resource.h"
#include "task_graph.h"
#include "spanning_tree.h"

//std::vector<spanning_tree> createGeneration(task_graph tgraph, int generationSize) {
//	for (int i = 0; i < )
//}

int main(){
    
    /*
    JAK UZYWAC bo sam nie wiedzia³em

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
	std::cout << "resources: " << tgraph.getHowManyResources();
	//spanning_tree stree(tgraph);

	//std::vector<spanning_tree> generation = createGeneration(tgraph, generationSize);

    return 0;
}