#include "task_graph.h"
#include "resourceManager.h"
#include <queue>
#include <algorithm>

std::vector<std::string> task_graph::readFromFile(std::string pathToFile, std::string what) {
	std::ifstream myFile(pathToFile);
	std::vector<std::string> text;
	std::string helpText;
	
	while (std::getline(myFile, helpText) && helpText.substr(0, 6) != what);

	while (std::getline(myFile, helpText) && helpText[0] != '@') {
		text.push_back(helpText);
	}

	myFile.close();
	return text;
}

unsigned int task_graph::getNumber(std::string task) {
	int i = 0;
	while (task[i++] != ' ');
	i--;
	return stoi(task.substr(1, i));
}

std::vector<resource> task_graph::getResources(std::string time, std::string cost) {
	int timeIndex = 0;
	int costIndex = 0;
	int lastTime, lastCost;
	std::vector<resource> resources;

	while (1) {
		lastTime = timeIndex;
		lastCost = costIndex;
		while (time[timeIndex++] != ' ');
		while (cost[costIndex++] != ' ');

		int taskTime = stoi(time.substr(lastTime, timeIndex - 1));
		int taskCost = stoi(cost.substr(lastCost, costIndex - 1));
		resource resource(taskTime, taskCost);
		resources.push_back(resource);
		if (timeIndex >= time.size() || costIndex >= cost.size()) {
			break;
		}
	}
	return resources;
}

void task_graph::getHelpEdgesFromFile(unsigned int number, std::string task) {
	std::pair<std::pair<int, int>, int> edgeWithWeight;
	std::pair<int, int> edge;
	int spaces = 0;
	int index = 0;

	while (spaces < 2) {
		if (task[index++] == ' ') {
			spaces++;
		}
	}

	while (index < task.size() - 1) {
		std::string neigbourStr;
		while (task[index] != '(') {
			neigbourStr += task[index++];
		}
		int neighbour = stoi(neigbourStr);
		index++;
		std::string weightStr;
		while (task[index] != ')') {
			weightStr += task[index++];
		}
		int weight = stoi(weightStr);
		index++;
		edge.first = number;
		edge.second = neighbour;
		edgeWithWeight.first = edge;
		edgeWithWeight.second = weight;
		helpEdges.push_back(edgeWithWeight);
	}
}

//void task_graph::createEdges(std::vector<std::pair<std::pair<int, int>, int>> help) {
//	for (std::vector<std::pair<std::pair<int, int>, int>>::iterator it = help.begin(); it != help.end(); ++it) {
//		std::pair<std::pair<int, int>, int> fullPair = *it;
//		std::cout << "nu,mber bez pointera " << vertices[fullPair.first.first].getTheResourceNumber() << std::endl;
//		std::pair<task*, task*> taskEdge(&(vertices[fullPair.first.first]), &(vertices[fullPair.first.second]));
//		std::cout << "number " << (*taskEdge.first).getTheResourceNumber() << std::endl;
//		std::pair<std::pair<task*, task*>, int> edgeWithWeight(taskEdge, fullPair.second);
//		edges.push_back(edgeWithWeight);
//	}
//}

void task_graph::createTasksAndHelpEdges(std::vector<std::string> tasks, std::vector<std::string> times, std::vector<std::string> costs) {
	for (int i = 0; i < tasks.size(); i++) {
		unsigned int number = getNumber(tasks[i]);
		std::vector<resource> resources = getResources(times[i], costs[i]);
		getHelpEdgesFromFile(number, tasks[i]);
		task task(number, resources);
		vertices.push_back(task);
	}
}

unsigned int task_graph::getHowManyResources() {
	return howManyResources;
}

void task_graph::readHowManyRes(std::string pathToFile) {
	std::ifstream myFile(pathToFile);
	std::string helpText;

	while (std::getline(myFile, helpText) && helpText.substr(0, 5) != "@proc");

	int index = 0;
	while (helpText[index++] != ' ');
	howManyResources = stoi(helpText.substr(index, helpText.size() - 1));
}

void task_graph::calcPerf()
{
	resourceManager::reset();
	totalCost = 0;
	totalTime = 0;
	//for (auto v : vertices)
	for (int i = 0; i < vertices.size(); i++)
	{
		std::pair<resource, int> r = resourceManager::selectRes(vertices[i].getResources());
		vertices[i].setResource(r);
		totalCost += r.first.getPrice();
		totalTime += r.first.getTime();
	}

}

void task_graph::setBroadcast(std::string str) {
	int spaces = 0;
	int index = 0;
	while (spaces < 2) {
		if (str[index++] == ' ') {
			spaces++;
		}
	}
	std::string help;
	while (str[index] != ' ') {
		help += str[index++];
	}
	broadcast = stoi(help);
}

task_graph::task_graph(std::string pathToFile) {
	std::vector<std::string> tasks = readFromFile(pathToFile, "@tasks");
	std::vector<std::string> times = readFromFile(pathToFile, "@times");
	std::vector<std::string> costs = readFromFile(pathToFile, "@cost ");
	std::vector<std::string> broadcastStr = readFromFile(pathToFile, "@comm ");

	createTasksAndHelpEdges(tasks, times, costs);
	
	readHowManyRes(pathToFile);
	resourceManager::init(howManyResources);
	calcPerf();
	//createEdges(helpEdges);
	setBroadcast(broadcastStr[0]);
	for (int i = 0; i < vertices.size(); i++) {
		std::cout << vertices[i];
	}
	std::cout << "\n" << totalTime << " <- czas " << totalCost << " <- koszt\n";
}

std::vector<task> task_graph::getVertices() {
	return vertices;
}

//std::vector<std::pair<std::pair<task*, task*>, int>> task_graph::breadthFirstSearch() {
//	std::queue<task*> queue;
//	std::vector<task*> visited;
//	std::vector<std::pair<std::pair<task*, task*>, int>> treeEdges;
//
//	queue.push(&(vertices[0]));
//
//	while (!queue.empty()) {
//		task* elem = queue.front();
//		visited.push_back(elem);
//		queue.pop();
//
//		std::vector<std::pair<std::pair<task*, task*>, int>> help;
//
//		for (std::vector<std::pair<std::pair<task*, task*>, int>>::iterator it = edges.begin(); it != edges.end(); ++it) {
//			if (*elem == *((*it).first.first)) {
//				help.push_back(*it);
//			}
//		}
//
//		std::for_each(help.begin(), help.end(), [&treeEdges, &queue, &visited](std::pair<std::pair<task*, task*>, int> pair) { 
//			if (std::find(visited.begin(), visited.end(), pair.first.second) == visited.end()) {
//				queue.push(pair.first.second);
//				treeEdges.push_back(pair);
//			}
//		});
//	}
//
//	return treeEdges;
//}