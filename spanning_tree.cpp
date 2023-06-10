#include "spanning_tree.h"
#include <queue>
#include <algorithm>

spanning_tree::spanning_tree(task_graph graph) {
	vertices = graph.getVertices();
	edges = graph.breadthFirstSearch();

#ifdef DEBUG
	std::for_each(edges.begin(), edges.end(), [](std::pair<std::pair<task, task>, int> edge) { std::cout << edge.first.first << " - " << edge.first.second << ": " << edge.second << std::endl });
#endif // DEBUG

}