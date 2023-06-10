#include <iostream>
#include <string>
#include "graph.h"
#include "resource.h"
#include "task_graph.h"
#include "spanning_tree.h"

int main(){
    
    /*resource specialistic{400, 10};
    resource universal{50, 210};

    resource res[2] {specialistic, universal};

    graph graph(10, res);*/
	std::string fileName = "graf10.txt";
	task_graph tgraph(fileName);
	spanning_tree stree(tgraph);

    return 0;
}