#include <list>
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <assert.h>

/*
##ifndef NDEBUG
#define NDEBUG value
#endif
*/
namespace Graph
{
  template <class T, class G>
  class graph
  {
  public :
    explicit graph(const std::vector<std::pair<T, T> > &vertices);
    /*Prefixing the explicit keyword to the constructor prevents the compiler from using that constructor for implicit conversions. */
    ~graph()
    {}
    void insert_vertex_pair_by_keys(T key1, T key2);
    void remove_edge_by_keys(T key1, T key2);
    void print_entering();
    void print_exiting();
    void print();

  // Private contained classes
  private:
   // Forward Definition of vertex
    class vertex;

    struct edge
    {
      edge(vertex *edge, G weight) :
        m_Edge(edge),
        m_Weight(weight)
      {}//this notation create a contructor called edge that assign m_Edge:=edge, ecc..
      vertex *m_Edge;
      G m_Weight;
    }; // END EDGE

    class vertex
    {
    public:
      vertex(T key):
        m_Key(key)
      {}
      void connect_edge(vertex *adjacent);
      void connect_enteringedge(vertex *adjacent);
      void remove_edge(vertex *adjacent);
      void remove_enteringedge(vertex *adjacent);

      const T key() const {return m_Key;}
      std::list<edge> &edges() {return m_Edges;}
      std::list<edge> &enteringedges() {return m_EnteringEdges;}
    private:
      std::list<edge> m_Edges;
      std::list<edge> m_EnteringEdges;
      T m_Key;
      bool contains_edge_to_vertex_with_key(const T key);
      bool contains_enteringedge_to_vertex_with_key(const T key);
      edge *find_in_adjacent_list(const T key);
    }; // END VERTEX

   // Private methods and member variables
   private:
     std::list<vertex> m_Vertices;
     vertex *contains_vertex(const T key);
  };
}

/*!
 * Constructor of graph: Take a pair of vertices as connection, attempt 
 * to insert if not already in graph. Then connect them in edge list
 */
template <class T, class G>
Graph::graph<T,G>::graph(const std::vector<std::pair<T, T> > &vertices_relation)
{
#ifndef NDEBUG
  std::cout << "Inserting pairs: " << std::endl;
#endif

  typename std::vector<std::pair<T, T> >::const_iterator insert_it = vertices_relation.begin();

  for(; insert_it != vertices_relation.end(); ++insert_it) {
  #ifndef NDEBUG
    std::cout << insert_it->first << " -- > " << insert_it->second << std::endl;
  #endif
    insert_vertex_pair_by_keys(insert_it->first, insert_it->second);
  }
}

template <class T, class G>
void Graph::graph<T,G>::print()
{ 
  #ifndef NDEBUG
  this->print_exiting();
  this->print_entering();
  #endif
}

template <class T, class G>
void Graph::graph<T,G>::print_exiting()
{
  std::cout << "Printing exiting edges: " << std::endl;
  
  typename std::list<vertex>::iterator print_it = m_Vertices.begin();
  
  for(; print_it != m_Vertices.end(); ++print_it) {
  
    std::cout << print_it->key() << "-->";
  
    typename std::list<edge>::const_iterator edge_it = print_it->edges().begin();
  
    for(; edge_it != print_it->edges().end(); ++edge_it) {
      std::cout << edge_it->m_Edge->key() << " ";
    }
    std::cout << std::endl;
  }
}

template <class T, class G>
void Graph::graph<T, G>::print_entering()
{
  std::cout << "Printing entering edges: " << std::endl;
  
  typename std::list<vertex>::iterator print_it = m_Vertices.begin();
  
  for(; print_it != m_Vertices.end(); ++print_it) {
  
    std::cout << print_it->key() << "<--";
  
    typename std::list<edge>::const_iterator edge_it = print_it->enteringedges().begin();
  
    for(; edge_it != print_it->enteringedges().end(); ++edge_it) {
      std::cout << edge_it->m_Edge->key() << " ";
    }
  
    std::cout << std::endl;
  }
}

/*!
 * Takes in a value of type T as a key and 
 * inserts it into graph data structure if 
 * key not already present
 */
template <typename T, typename G>
void Graph::graph<T, G>::insert_vertex_pair_by_keys(T key1, T key2)
{
  /*!
   * Check if vertices already in Graph
   */
  Graph::graph<T,G>::vertex *insert1 = contains_vertex(key1);
  Graph::graph<T,G>::vertex *insert2 = contains_vertex(key2);
  /*!
   * If not in graph then insert it and get a pointer to it
   * to pass into edge. See () for information on how
   * to build graph
   */ 
  if (insert1 == NULL) {
    std::cout << "Warning: vertex with key " << key1 << " was NULL" << std::endl;
    m_Vertices.push_back(vertex(key1));
    insert1 = contains_vertex(key1);
  }
  if (insert2 == NULL) {
    std::cout << "Warning: vertex with key " << key2 << " was NULL" << std::endl;
    m_Vertices.push_back(vertex(key2));
    insert2 = contains_vertex(key2);
  }

#ifndef NDEBUG
  assert(insert1 != NULL && "Failed to insert first vertex");
  assert(insert2 != NULL && "Failed to insert second vertex");
#endif

  /*!
   * At this point we should have a vertex to insert an edge on
   * if not throw an error.
   */ 
  if (insert1 != NULL && insert2 != NULL) {
    insert1->connect_edge(insert2);
    insert2->connect_enteringedge(insert1);
  } else {
    throw std::runtime_error("Unknown");
  }
}

template <typename T , typename G>
void Graph::graph<T,G>::remove_edge_by_keys(T key1, T key2)
{
  Graph::graph<T,G>::vertex *insert1 = contains_vertex(key1);
  Graph::graph<T,G>::vertex *insert2 = contains_vertex(key2);
  if (insert1 == NULL || insert2 == NULL)
    throw "Failed to remove edge";
  
  insert1->remove_edge(insert2);
  insert2->remove_enteringedge(insert1);
}

/*!
 * Search the std::list of vertices for key
 * if present return the vertex to indicate
 * already in graph else return NULL to indicate
 * new node
 */
template <typename T, typename G>
typename Graph::graph<T,G>::vertex *Graph::graph<T,G>::contains_vertex(T key)
{
  typename std::list<vertex >::iterator find_it = m_Vertices.begin();
  for(; find_it != m_Vertices.end(); ++find_it) {
    if (find_it->key() == key) {
      return &(*find_it);
    }
  }
  return NULL;
}

/*!
 * Take the oposing vertex from input and insert it
 * into adjacent list, you can have multiple edges
 * between vertices
 */
template <class T, class G>
void Graph::graph<T,G>::vertex::connect_edge(Graph::graph<T,G>::vertex *adjacent)
{
  //this is a vertex
  if (adjacent == NULL)
    return;

  std::cout << "Connecting edge from " << this->key() << " to " << adjacent->key() << std::endl;
  if (!contains_edge_to_vertex_with_key(adjacent->key())) {
    //Graph::graph<T>::  = find_in_adjacent_list(adjacent->key());
    Graph::graph<T,G>::edge e(adjacent, 1);
    m_Edges.push_back(e);
  }
}

template <class T, class G>
void Graph::graph<T,G>::vertex::connect_enteringedge(Graph::graph<T,G>::vertex *adjacent)
{
  //this is a vertex
  if (adjacent == NULL)
    return;

  std::cout << "Connecting (entering) edge from " << adjacent->key() << " to " << this->key() << std::endl;
  if (!contains_enteringedge_to_vertex_with_key(adjacent->key())) {
    //Graph::graph<T>::  = find_in_adjacent_list(adjacent->key());
    Graph::graph<T,G>::edge e(adjacent, 1);
    m_EnteringEdges.push_back(e);
  }
}

template <class T, class G>
void Graph::graph<T,G>::vertex::remove_edge(Graph::graph<T,G>::vertex *adjacent)
{
  //this is a vertex
  if (adjacent == NULL)
    throw std::runtime_error ("remove_edge NULL");

  std::cout << "Removing edge from " << this->key() << " to " << adjacent->key() << " ... ";
 
  typename std::list<edge>::iterator del_it = (this->edges()).begin();
  for(; del_it != this->edges().end(); ++del_it) {
    if (del_it->m_Edge->key() == adjacent->key())
    {
      (this->edges()).erase(del_it);
      break;
    }
  }
  
  // check 
  bool failed = false;
  del_it = (this->edges()).begin();
  for(; del_it != (this->edges()).end(); ++del_it) {
    if (del_it->m_Edge->key() == adjacent->key())
    {
      std::cout << "Failed" << std::endl;
      failed = true;
      break;
    }
  }
  if (! failed) std::cout << "Done" << std::endl;
}

template <class T, class G>
void Graph::graph<T,G>::vertex::remove_enteringedge(Graph::graph<T,G>::vertex *adjacent)
{
  //this is a vertex
  if (adjacent == NULL)
    throw std::runtime_error ("remove_edge NULL");

  std::cout << "Removing (entering) edge from " << adjacent->key() << " to " << this->key() << " ... ";
 
  typename std::list<edge>::iterator del_it = (this->enteringedges()).begin();
  for(; del_it != this->enteringedges().end(); ++del_it) {
    if (del_it->m_Edge->key() == adjacent->key())
    {
      (this->enteringedges()).erase(del_it);
      break;
    }
  }
  
  // check 
  bool failed = false;
  del_it = (this->enteringedges()).begin();
  for(; del_it != (this->enteringedges()).end(); ++del_it) {
    if (del_it->m_Edge->key() == adjacent->key())
    {
      std::cout << "Failed" << std::endl;
      failed = true;
      break;
    }
  }
  if (! failed) std::cout << "Done" << std::endl;
}

template <typename T , typename G>
typename Graph::graph<T,G>::edge *Graph::graph<T,G>::vertex::find_in_adjacent_list(const T key){

  //this is a vertex
  typename std::list<edge>::iterator find_it = m_Edges.begin();

  for(; find_it != m_Edges.end(); ++find_it) {
    if (find_it->m_Edge->key() == key) {
      return find_it->m_Edge;
    }   
  }
  return NULL;

}

/*!
 * Private member function that check if there is already
 * an edge between the two vertices
 */
template <class T, class G>
bool Graph::graph<T,G>::vertex::contains_edge_to_vertex_with_key(const T key)
{
  //this is a vertex
  typename std::list<edge>::iterator find_it = m_Edges.begin();

  for(; find_it != m_Edges.end(); ++find_it) {
    if (find_it->m_Edge->key() == key) {
      return true;
    }   
  }
  return false;
}

template <class T, class G>
bool Graph::graph<T,G>::vertex::contains_enteringedge_to_vertex_with_key(const T key)
{
  //this is a vertex
  typename std::list<edge>::iterator find_it = m_EnteringEdges.begin();

  for(; find_it != m_EnteringEdges.end(); ++find_it) {
    if (find_it->m_Edge->key() == key) {
      return true;
    }   
  }
  return false;
}
