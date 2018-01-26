#include "NimLearner.h"
#include <vector>
#include "edge.h"

int main() {
  NimLearner nim(10);

  for (int i = 0; i < 100000; i++) {
    vector<Edge> path = nim.playRandomGame();
    nim.updateEdgeWeights(path);
  }

  nim.getGraph().print();

  return 0;
}
