/* Your code here! */
#include "maze.h"

using namespace std;

/**
*  This function creates an empty maze.
**/
SquareMaze::SquareMaze() {

}

/**
*  This function makes a new SquareMaze of the given height and width.
**/
void SquareMaze::makeMaze(int width, int height) {
  this->width = width;
  this->height = height;
  for (int i = 0; i < width * height; i++) {
    downWalls.push_back(true);
    rightWalls.push_back(true);
  }

  DisjointSets dsets;
  dsets.addelements(height * width);

  // srand(time(NULL));
  int bound = 0;

  while (bound < width * height - 1) {
    int randX = rand() % width;
    int randY = rand() % height;
    bool randR = rand() % 2; //0 false or 1 true to break right wall

    if (randR) {
      if (randX < width - 1 && rightWalls[randX + randY * width] &&
        dsets.find(randX + randY * width) != dsets.find(randX + 1 + randY * width)) {
          rightWalls[randX + randY * width] = false;
          dsets.setunion(dsets.find(randX + randY * width), dsets.find(randX + 1 + randY * width));
          bound++;
        }
      } else {
        //break down wall
        if (randY < height - 1 && downWalls[randX + randY * width] &&
          dsets.find(randX + randY * width) != dsets.find(randX + (randY + 1) * width)) {
            downWalls[randX + randY * width] = false;
            dsets.setunion(dsets.find(randX + randY * width), dsets.find(randX + (1 + randY) * width));
            bound++;
          }
        }
      }
    }

    /**
    * This function uses your representation of the maze to determine whether
    * it is possible to travel in the given direction from the square at coordinates (x,y).
    * dir = 0 represents a rightward step (+1 to the x coordinate)
    * dir = 1 represents a downward step (+1 to the y coordinate)
    * dir = 2 represents a leftward step (-1 to the x coordinate)
    * dir = 3 represents an upward step (-1 to the y coordinate)
    **/
    bool SquareMaze::canTravel(int x, int y, int dir) const {
      // if (x < 0 || x >= width || y < 0 || y >= height) return false;
      if (dir == 0) return !(rightWalls[x + y * width]);
      if (dir == 1) return !(downWalls[x + y * width]);
      if (dir == 2) {
        if (x == 0) return false;
        else return !(rightWalls[x - 1 + y * width]);
      }
      if (dir == 3) {
        if (y == 0) return false;
        else return !(downWalls[x + (y - 1) * width]);
      }
      return false;
    }

    /**
    * This function sets whether or not the specified wall exists.
    **/
    void SquareMaze::setWall(int x, int y, int dir, bool exists) {
      // if (x < 0 || x >= width || y < 0 || y >= height ) return;
      if (dir == 0) {
        rightWalls[x + y * width] = exists;
      } else if (dir == 1) {
        downWalls[x + y * width] = exists;
      }
    }

    /**
    * This function solves this SquareMaze.
    * dir = 0 represents a rightward step (+1 to the x coordinate)
    * dir = 1 represents a downward step (+1 to the y coordinate)
    * dir = 2 represents a leftward step (-1 to the x coordinate)
    * dir = 3 represents an upward step (-1 to the y coordinate)
    **/
    vector<int> SquareMaze::solveMaze() {
      vector<int> lastRows;

      map<int, int> steps;
      vector<bool> visited;
      for(int i = 0; i < width*height; i++) visited.push_back(false);

      queue<int> q;
      q.push(0);
      visited[0] = true;

      while(!q.empty()) {
        int v = q.front();
        q.pop();
        int x = v % width;
        int y = v / width;
        if (y == height - 1) {
          lastRows.push_back(v);
          // if (lastRows.size() == (unsigned) width) break;
        }

        if (canTravel(x, y, 0) && !visited[v + 1]) {
          steps.insert(pair<int, int> (v + 1, v));
          visited[v + 1] = true;
          q.push(v + 1);
        }
        if (canTravel(x, y, 1) && !visited[v + width]) {
          steps.insert(pair<int, int> (v + width, v));
          visited[v + width] = true;
          q.push(v + width);
        }
        if (canTravel(x, y, 2) && !visited[v - 1]) {
          steps.insert(pair<int, int> (v - 1, v));
          visited[v - 1] = true;
          q.push(v - 1);
        }
        if (canTravel(x, y, 3) && !visited[v - width]) {
          steps.insert(pair<int, int> (v - width, v));
          visited[v - width] = true;
          q.push(v - width);
        }
      }

      vector<int> dirs;
      int last = width - 1;
      while(lastRows[last] == lastRows[last - 1]) last -= 1;
// cout<<"last"<<last<<endl;
      int start = lastRows[last];
      while (start != 0) {
        int former = steps[start];
// cout<<former<<endl;
        if (start == former + 1) dirs.push_back(0);
        else if (start == former - 1) dirs.push_back(2);
        else if (start == former + width) dirs.push_back(1);
        else if (start == former - width) dirs.push_back(3);
        start = former;
      }
      reverse(dirs.begin(),dirs.end());
// for (int dir : dirs) cout<<dir<<endl;
// cout<<"size: "<<dirs.size()<<endl;
      return dirs;
    }

    /**
    * This function draws the maze without the solution.
    * black hsla: 0, 0, 0, 1
    **/
    PNG * SquareMaze::drawMaze() const {
      int pH = height * 10 + 1;
      int pW = width * 10 + 1;
      PNG* unsolved = new PNG(pW, pH);
      for (int i = 0; i < pH; i++) {
        HSLAPixel* pixel = unsolved->getPixel(0, i);
        // pixel->h = 0.0;
        pixel->l = 0.0;
        // pixel->s = 0.0;
        // pixel->a = 1.0;
      }
      for (int i = 10; i < pW; i++) {
        HSLAPixel* pixel = unsolved->getPixel(i, 0);
        pixel->l = 0.0;
      }
      for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
          if (rightWalls[x + y * width]) {
            for (int i = 0; i < 11; i++) {
              HSLAPixel* pixel = unsolved->getPixel(10 * x + 10, 10 * y + i);
              pixel->l = 0.0;
            }
          }
          if (downWalls[x + y * width]) {
            for (int i = 0; i < 11; i++) {
              HSLAPixel* pixel = unsolved->getPixel(10 * x + i, 10 * y + 10);
              pixel->l = 0.0;
            }
          }
        }
      }
      return unsolved;
    }

    /**
    * This function calls drawMaze, then solveMaze;
    * it modifies the PNG from drawMaze to show the solution vector and the exit.
    **/
    PNG * SquareMaze::drawMazeWithSolution() {
      PNG* unsolved = drawMaze();
      vector<int> dirs = solveMaze();
      int x = 5;
      int y = 5;
      for (unsigned i = 0; i < dirs.size(); i++) {
        if (dirs[i] == 0) {
          for (int i = 0; i < 10; i++) {
            HSLAPixel* pixel = unsolved->getPixel(x, y);
            pixel->h = 0;
            pixel->s = 1;
            pixel->l = 0.5;
            x += 1;
          }
        } else if (dirs[i] == 1) {
          for (int i = 0; i < 10; i++) {
            HSLAPixel* pixel = unsolved->getPixel(x, y);
            pixel->h = 0;
            pixel->s = 1;
            pixel->l = 0.5;
            y += 1;
          }
        } else if (dirs[i] == 2) {
          for (int i = 0; i < 10; i++) {
            HSLAPixel* pixel = unsolved->getPixel(x, y);
            pixel->h = 0;
            pixel->s = 1;
            pixel->l = 0.5;
            x -= 1;
          }
        } else if (dirs[i] == 3) {
          for (int i = 0; i < 10; i++) {
            HSLAPixel* pixel = unsolved->getPixel(x, y);
            pixel->h = 0;
            pixel->s = 1;
            pixel->l = 0.5;
            y -= 1;
          }
        }
      }
      HSLAPixel* p = unsolved->getPixel(x, y);
      p->h = 0.0;
      p->s = 1.0;
      p->l = 0.5;
      p->a = 1.0;
      x -= 4;
      y += 5;
      for (int i = 0; i < 9; i++) {
        HSLAPixel* pixel = unsolved->getPixel(x, y);
        // pixel->h = 0.0;
        // pixel->s = 0.0;
        pixel->l = 1.0;
        pixel->a = 1.0;
        x += 1;
      }
      return unsolved;
    }
