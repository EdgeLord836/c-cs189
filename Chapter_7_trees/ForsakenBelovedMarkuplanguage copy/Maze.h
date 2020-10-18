#pragma once
#include <stack>
#include <list>
#include <string> 

class Maze
{
public:
	class Cell
	{
		friend Maze;

		Cell* mNorth = nullptr; // While this "hardcodes" four directions, it is hella easier and 99% of mazes are flat and square
		Cell* mSouth = nullptr;
		Cell* mEast = nullptr;
		Cell* mWest = nullptr;

		bool mIsExit = false;
		bool mProcessed = false;// Prevent loops  Treat finding a processed cell as just not there.  Like a dead end.
	};

private:
  void freeMaze(Cell *);
	bool MazeRecursive( Cell* tCurrent, std::stack<std::string>* tPath );
	Cell* mStart;

public:
	Maze();// Making a constructor with a file name would be cool for the extra credit.
	~Maze();
	std::stack<std::string> SolveMaze();
};
