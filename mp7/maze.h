/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>
#include <queue>
#include <map>
#include <cstdlib>
#include <algorithm>

#include "cs225/PNG.h"
#include "dsets.h"

using namespace cs225;
using namespace std;

/**
 * This class creates a SquareMaze object which represents a randomly-generated
 * square maze and its solution
 **/
class SquareMaze{

private:

  vector<bool> downWalls; //dir 1

  vector<bool> rightWalls; //dir 0

  int width;

  int height;

public:

  /**
   *  This function creates an empty maze.
   **/
   SquareMaze();

  /**
   *  This function makes a new SquareMaze of the given height and width.
   **/
   void makeMaze(int width, int height);

   /**
    * This function uses your representation of the maze to determine whether
    * it is possible to travel in the given direction from the square at coordinates (x,y).
    **/
   bool canTravel(int x, int y, int dir) const;

   /**
    * This function sets whether or not the specified wall exists.
    **/
   void setWall(int x, int y, int dir, bool exists);

   /**
    * This function solves this SquareMaze.
    **/
   vector<int> solveMaze();

   /**
    * This function draws the maze without the solution.
    **/
   cs225::PNG * drawMaze() const;

   /**
    * This function calls drawMaze, then solveMaze;
    * it modifies the PNG from drawMaze to show the solution vector and the exit.
    **/
   cs225::PNG * drawMazeWithSolution();
};

#endif
