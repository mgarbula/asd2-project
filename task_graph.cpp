#include "task_graph.h"

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
		timeIndex++; costIndex++;
		resource resource(taskTime, taskCost);
		resources.push_back(resource);
		if (taskTime >= time.size() || taskCost >= cost.size()) {
			break;
		}
	}
	return resources;
}

void task_graph::createTasksAndHelpEdges(std::vector<std::string> tasks, std::vector<std::string> times, std::vector<std::string> costs) {
	for (int i = 0; i < tasks.size(); i++) {
		unsigned int number = getNumber(tasks[i]);
		std::vector<resource> resources = getResources(times[i], costs[i]);
		//std::vector<std::pair<int, int>> edges = getEdges(tasks[i]);
		task task(number, resources);
		vertices.push_back(task);

	}
}

task_graph::task_graph(std::string pathToFile) {
	std::vector<std::string> tasks = readFromFile(pathToFile, "@tasks");
	std::vector<std::string> times = readFromFile(pathToFile, "@times");
	std::vector<std::string> costs = readFromFile(pathToFile, "@cost ");

	createTasksAndHelpEdges(tasks, times, costs);

	/*for (int i = 0; i < vertices.size(); i++) {
		std::cout << vertices[i];
	}*/
}