// 189 Recursion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Maze.h"

using namespace std;

int main()
{
	Maze tTestMaze;
	std::stack<std::string> tPath;
	tPath = tTestMaze.SolveMaze();

	//print pathway
	cout << "Exit ";
	while (!tPath.empty())
	{
		cout << " <- " << tPath.top();
		tPath.pop();
	}
	cout << " <- Start\n";
}

