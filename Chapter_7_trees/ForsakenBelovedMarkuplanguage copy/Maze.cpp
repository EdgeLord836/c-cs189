#include "Maze.h"

#include <iostream>
using namespace std;

Maze::Maze() {
	// Making a test maze by hand to make testing easy without giving away the extra credit of the maze maker.

	// mStart = new Cell;
	// mStart->mNorth = new Cell;
	// mStart->mNorth->mNorth = new Cell;
	// mStart->mEast = new Cell;
	// mStart->mEast->mEast = new Cell;
	// mStart->mEast->mEast->mNorth = new Cell;
	// mStart->mEast->mEast->mNorth->mNorth = new Cell;
	// mStart->mEast->mEast->mNorth->mNorth->mIsExit = true;
	// // This is a big U 

  mStart = new Cell;
	mStart->mNorth = new Cell;
	mStart->mNorth->mNorth = new Cell;
  mStart->mNorth->mNorth->mNorth = new Cell;
  mStart->mNorth->mNorth->mEast = new Cell;
  mStart->mNorth->mNorth->mEast->mEast = new Cell;
  mStart->mNorth->mNorth->mEast->mEast->mNorth = new Cell;
  mStart->mNorth->mNorth->mEast->mEast->mEast = new Cell;
  mStart->mNorth->mNorth->mEast->mEast->mEast->mSouth = new Cell;
  mStart->mNorth->mNorth->mEast->mEast->mEast->mSouth->mEast = new Cell;
  mStart->mNorth->mNorth->mEast->mEast->mEast->mSouth->mEast->mEast = new Cell;
  mStart->mNorth->mNorth->mEast->mEast->mEast->mSouth->mEast->mEast->mNorth = new Cell;
  mStart->mNorth->mNorth->mEast->mEast->mEast->mSouth->mEast->mEast->mNorth->mNorth = new Cell;
  mStart->mNorth->mNorth->mEast->mEast->mEast->mSouth->mEast->mEast->mNorth->mNorth->mWest = new Cell;
  mStart->mNorth->mNorth->mEast->mEast->mEast->mSouth->mEast->mEast->mNorth->mNorth->mWest->mIsExit = true;
}

/*

XXXXXXX
X.X.XE.
X....X.
X.XX...
XSXXXXX
XXXXXXX

*/











void Maze::freeMaze(Maze::Cell* tCurrent) {
  if (tCurrent->mNorth)
    freeMaze(tCurrent->mNorth);
  if (tCurrent->mEast)
    freeMaze(tCurrent->mEast);
  if (tCurrent->mSouth)
    freeMaze(tCurrent->mSouth);
  if (tCurrent->mWest)
    freeMaze(tCurrent->mWest);
  
  if (tCurrent) delete tCurrent;
}

Maze::~Maze() {
	// Totally leaks
  freeMaze(mStart);
}

bool Maze::MazeRecursive( Maze::Cell* tCurrent, std::stack<std::string>* tPath ) {
	// This is the main part.  Just keep in mind the single sentence recursive definition:

	// "To exit a maze, I take a step and if I'm not done I exit the maze."

	// Use Processed to prevent loops.  The last cell is marked IsExit.  
	// "tPath" is there for you to push the path as you move.  If
	// it turns out you didn't find the exit that direction then pop it back off.  The return value
	// of true-false is how you communicate success backwards.

  if (tCurrent->mIsExit) return true;

  bool is_path_found = false;

  if (tCurrent->mNorth && !tCurrent->mNorth->mProcessed) {
    tPath->push("North");
    // cout << "N" << endl;
    is_path_found = MazeRecursive(tCurrent->mNorth, tPath);
  }
  if (tCurrent->mEast && !tCurrent->mEast->mProcessed) {
    tPath->push("East");
    // cout << "E" << endl;
    is_path_found = MazeRecursive(tCurrent->mEast, tPath);
  }
  if (tCurrent->mSouth && !tCurrent->mSouth->mProcessed) {
    tPath->push("South");
    // cout << "S" << endl;
    is_path_found = MazeRecursive(tCurrent->mSouth, tPath);
  }
  if (tCurrent->mWest && !tCurrent->mWest->mProcessed) {
    tPath->push("West");
    // cout << "W" << endl;
    is_path_found = MazeRecursive(tCurrent->mWest, tPath);
  }
  
  if (is_path_found) return true;

  if (!tCurrent->mNorth &&\
      !tCurrent->mEast &&\
      !tCurrent->mSouth &&\
      !tCurrent->mWest) {
    tCurrent->mProcessed = true;
    tPath->pop();
    // cout << "backtracking" << endl;
    return false;
  } else if (
      (tCurrent->mNorth && tCurrent->mNorth->mProcessed) ||\
      (tCurrent->mEast && tCurrent->mEast->mProcessed) ||\
      (tCurrent->mSouth && tCurrent->mSouth->mProcessed) ||\
      (tCurrent->mWest && tCurrent->mWest->mProcessed)) {
    tCurrent->mProcessed = true;
    tPath->pop();
    // cout << "backtracking" << endl;
    return false;
  }
	return false;
}

std::stack<std::string> Maze::SolveMaze()// Driver
{
	// No need to change this.
	std::stack<std::string> tAnswer;
	MazeRecursive( mStart, &tAnswer );
	return tAnswer;
}