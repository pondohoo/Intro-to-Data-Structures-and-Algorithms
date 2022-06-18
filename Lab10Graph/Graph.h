#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <climits>

#include "Vertex.h"

using namespace std;

class Graph {
public:
  vector<Vertex> vertices;
public:
  // initializes an empty graph
  Graph();
  // initializes a graph read from a file
  Graph(ifstream&);
  //~Graph();
  void output_graph(const string &);
  void bfs();
};

#endif /* GRAPH_H_ */
