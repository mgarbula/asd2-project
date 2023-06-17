#ifndef __TASK_GRAPH__
#define __TASK_GRAPH__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "task.h"

class task_graph {
private:
    std::vector<task> vertices;
	unsigned int howManyResources;
	unsigned int broadcast;
	//std::vector<std::pair<std::pair<task, task>, int>> edges; // wektor par, ka¿da para sk³ada siê z pary (wierzcholek od, wierzcholek do) oraz wagi
	//std::vector<std::pair<std::pair<task*, task*>, int>> edges;
	std::vector<std::pair<std::pair<int, int>, int>> helpEdges; // krawêdzie z numerami zadañ
	std::vector<std::string> readFromFile(std::string, std::string);
	void createTasksAndHelpEdges(std::vector<std::string>, std::vector<std::string>, std::vector<std::string>);
	unsigned int getNumber(std::string);
	std::vector<resource> getResources(std::string, std::string);
	void readHowManyRes(std::string);
	void getHelpEdgesFromFile(unsigned int, std::string);
	//void createEdges(std::vector<std::pair<std::pair<int, int>, int>>);
	void setBroadcast(std::string);
	void calcPerf();
	unsigned int totalCost;
	unsigned int totalTime;
public:
	unsigned int getTotalCost() { return totalCost; }
	unsigned int getTotalTime() { return totalTime; }
	unsigned int getBroadcast() { return broadcast; }
	std::vector<std::pair<std::pair<int, int>, int>> getHelpEdges() { return helpEdges; }
	task_graph(std::string);
	std::vector<task> getVertices();
	unsigned int getHowManyResources();
};

#endif