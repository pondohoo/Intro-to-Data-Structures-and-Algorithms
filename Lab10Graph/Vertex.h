#ifndef VERTEX_H_
#define VERTEX_H_

#include <string>
#include <list>
#include <map>
#include <climits>

using namespace std;

class Vertex {
public:
  // pair consists of int index of neighbor and int edge weight
  list<pair<int, int> > neighbors;
  string label;
  int distance;
  string color;
  Vertex* prev;
  
  Vertex():label(""),distance(INT_MAX),color("WHITE"),prev(0){}
  void setDistance(int d)
  {
    distance = d;
  }
  ~Vertex(){}
};

#endif /* VERTEX_H_ */
