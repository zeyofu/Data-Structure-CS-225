#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "catchlib.h"

#include "../graph.h"
#include "../edge.h"
#include "../NimLearner.h"

#include <iostream>

/*
TEST_CASE("The graph class creates directed edges", "[weight=5][part=1]") {
  Graph g(false);

  Vertex u = g.insertVertex();
  Vertex v = g.insertVertex();

  g.insertEdge(u, v);

  REQUIRE( g.getAdjacent(u).size() == 1 );
  REQUIRE( g.getAdjacent(v).size() == 0 );
}
*/

bool vertexExists(const Graph & g, const std::string & label) {
  for (const Vertex & v : g.getVertices()) {
    if (g.getVertexLabel(v) == label)
      return true;
  }

  return false;
}

bool edgeExists(const Graph & g, const std::string & label1, const std::string & label2) {
  for (const Vertex & v : g.getVertices()) {
    if (g.getVertexLabel(v) == label1) {
      // found vertex v for label1, check getAdjacent
      for (const Vertex & u : g.getAdjacent(v)) {
        if (g.getVertexLabel(u) == label2) {
          return true;
        }
      }

      // Found label1, did not find an adjacent label2
      return false;
    }
  }

  return false;
}



TEST_CASE("NimLearner(10) constructor creates a starting vertex \"p1-10\"", "[weight=1][part=1]") {
  NimLearner nim(10);

  const Graph & g = nim.getGraph();
  REQUIRE( vertexExists(g, "p1-10") );
}


TEST_CASE("NimLearner(3) constructor creates the correct vertices", "[weight=1][part=1]") {
  NimLearner nim(3);

  const Graph & g = nim.getGraph();

  REQUIRE( vertexExists(g, "p1-3") );
  //REQUIRE( findVertexLabel(g, "p2-3") ); okay but not required, never reached
  REQUIRE( vertexExists(g, "p1-2") );
  REQUIRE( vertexExists(g, "p2-2") );
  REQUIRE( vertexExists(g, "p1-1") );
  REQUIRE( vertexExists(g, "p2-1") );
  REQUIRE( vertexExists(g, "p1-0") );
  REQUIRE( vertexExists(g, "p2-0") );
}


TEST_CASE("NimLearner(3) constructor creates the correct edges", "[weight=1][part=1]") {
  NimLearner nim(3);

  const Graph & g = nim.getGraph();

  //
  // A minimum of 8 edges are required (p2-3 edges are not required);
  // 10 edges may be present with p2-3 edges
  //
  REQUIRE(g.getEdges().size() >= 8);
  REQUIRE(g.getEdges().size() <= 10);

  if (g.getEdges().size() >= 8) {
    // always required edges
    REQUIRE( edgeExists(g, "p1-3", "p2-2") );
    REQUIRE( edgeExists(g, "p1-3", "p2-1") );

    REQUIRE( edgeExists(g, "p1-2", "p2-1") );
    REQUIRE( edgeExists(g, "p1-2", "p2-0") );

    REQUIRE( edgeExists(g, "p1-1", "p2-0") );

    REQUIRE( edgeExists(g, "p2-2", "p1-1") );
    REQUIRE( edgeExists(g, "p2-2", "p1-0") );

    REQUIRE( edgeExists(g, "p2-1", "p1-0") );
  }

  if (g.getEdges().size() > 8) {
    // optional edges
    REQUIRE( edgeExists(g, "p2-3", "p1-2") );
    REQUIRE( edgeExists(g, "p2-3", "p1-1") );
  }
}


TEST_CASE("NimLearner(1) plays a trivial random game", "[weight=1][part=2]") {
  NimLearner nim(1);

  std::vector<Edge> path = nim.playRandomGame();
  REQUIRE( path.size() == 1 );
}

TEST_CASE("NimLearner(10) plays random game", "[weight=1][part=2]") {
  NimLearner nim(10);

  std::vector<Edge> path = nim.playRandomGame();
  REQUIRE( path.size() >= 5 );
  REQUIRE( path.size() <= 10 );
}

TEST_CASE("Path from playRandomGame of NimLearner(10) source vertex is labeled \"p1-10\"", "[weight=1][part=2]") {
  NimLearner nim(10);

  std::vector<Edge> path = nim.playRandomGame();

  const Graph & g = nim.getGraph();
  REQUIRE( g.getVertexLabel(path[0].source) == "p1-10" );
}

TEST_CASE("Path from playRandomGame of NimLearner(10) final vertex is labeled \"p1-0\" or \"p2-0\"", "[weight=1][part=2]") {
  NimLearner nim(10);

  std::vector<Edge> path = nim.playRandomGame();

  const Graph & g = nim.getGraph();
  REQUIRE( g.getVertexLabel(path[path.size() - 1].dest).substr(2, 2) == "-0" );
}

TEST_CASE("A NimLearner(1) random path contains one edge", "[weight=1][part=3]") {
  NimLearner nim(1);

  std::vector<Edge> path = nim.playRandomGame();
  REQUIRE( path.size() == 1 );
}

TEST_CASE("NimLearner(1) updates the edge weight correctly", "[weight=1][part=3]") {
  NimLearner nim(1);
  std::vector<Edge> path = nim.playRandomGame();
  Edge e = path[0];
  nim.updateEdgeWeights(path);

  const Graph & g = nim.getGraph();
  REQUIRE( g.getEdgeWeight(e.source, e.dest) == 1);
}

TEST_CASE("NimLearner(3) learns that (p1-3, p2-2) and (p1-3, p2-1) are losing edges", "[weight=1][part=3]") {
  NimLearner nim(3);

  for (int i = 0; i < 10000; i++) {
    std::vector<Edge> path = nim.playRandomGame();
    nim.updateEdgeWeights(path);
  }

  const Graph & g = nim.getGraph();
  REQUIRE( g.getEdgeWeight( g.getVertexByLabel("p1-3"), g.getVertexByLabel("p2-2")) < 0 );
  REQUIRE( g.getEdgeWeight( g.getVertexByLabel("p1-3"), g.getVertexByLabel("p2-1")) < 0 );
}

TEST_CASE("NimLearner(4) learns that (p1-4, p2-3) is a better edge than (p1-4, p2-2)", "[weight=1][part=3]") {
  NimLearner nim(4);

  for (int i = 0; i < 10000; i++) {
    std::vector<Edge> path = nim.playRandomGame();
    nim.updateEdgeWeights(path);
  }

  const Graph & g = nim.getGraph();
  REQUIRE(
    g.getEdgeWeight( g.getVertexByLabel("p1-4"), g.getVertexByLabel("p2-3")) >
    g.getEdgeWeight( g.getVertexByLabel("p1-4"), g.getVertexByLabel("p2-2"))
  );
}

TEST_CASE("NimLearner(10) has ending edge weights summing to the random games played", "[weight=1][part=3]") {
  NimLearner nim(4);

  for (int i = 0; i < 100; i++) {
    std::vector<Edge> path = nim.playRandomGame();
    nim.updateEdgeWeights(path);
  }

  const Graph & g = nim.getGraph();

  Vertex p1_2 = g.getVertexByLabel("p1-2");
  Vertex p1_1 = g.getVertexByLabel("p1-1");
  Vertex p1_0 = g.getVertexByLabel("p1-0");

  Vertex p2_2 = g.getVertexByLabel("p2-2");
  Vertex p2_1 = g.getVertexByLabel("p2-1");
  Vertex p2_0 = g.getVertexByLabel("p2-0");

  REQUIRE( g.getEdgeWeight( p1_2, p2_0 ) +
           g.getEdgeWeight( p1_1, p2_0 ) +
           g.getEdgeWeight( p2_2, p1_0 ) +
           g.getEdgeWeight( p2_1, p1_0 ) == 100 );
}
