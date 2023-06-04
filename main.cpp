#include <iostream>
#include "graph.h"
#include "resource.h"

int main(){
    
    resource specialistic{400, 10};
    resource universal{50, 210};

    resource res[2] {specialistic, universal};

    graph graph(10, res);
    return 0;
}