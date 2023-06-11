#include <iostream>
#include <string>
#include "resourceManager.h"
#include "resource.h"
#include "task_graph.h"
#include "spanning_tree.h"

int main(){
    
    /*
    JAK UZYWAC bo sam nie wiedzia³em

    resource specialistic{400, 10};
    resource universal{50, 210};

    resource res[2] {specialistic, universal};

    resourceManager::init(2, res);
    std::cout << resourceManager::selectRes().getTime() << "\n";*/

	std::string fileName = "graf10.txt";
	task_graph tgraph(fileName);
	spanning_tree stree(tgraph);

    return 0;
}