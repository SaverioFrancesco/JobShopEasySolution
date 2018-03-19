// main.cpp
#include "graph.hh"
#include <cstdlib>

int main(int argc, char *argv[])
{
  std::vector<std::pair<int, int> > graph_vect;
  
  graph_vect.push_back(std::pair<int, int>(1, 2));
  graph_vect.push_back(std::pair<int, int>(2, 3));
  graph_vect.push_back(std::pair<int, int>(3, 1));
  graph_vect.push_back(std::pair<int, int>(2, 1));
  graph_vect.push_back(std::pair<int, int>(3, 4));
  graph_vect.push_back(std::pair<int, int>(4, 1));
  
  
  Graph::graph<int,int> my_graph(graph_vect);
  my_graph.print();
  my_graph.remove_edge_by_keys(2, 3);
  my_graph.print();
  my_graph.remove_edge_by_keys(2, 1);
  my_graph.print();
  my_graph.remove_edge_by_keys(3, 1);
  my_graph.print();
  my_graph.remove_edge_by_keys(3, 4);
  my_graph.print();
  my_graph.remove_edge_by_keys(1, 2);
  my_graph.print();
  my_graph.remove_edge_by_keys(4, 1);
  my_graph.print();
  return 0;
}