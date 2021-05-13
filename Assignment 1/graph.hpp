#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>
#include <map>

using namespace std;

template <typename T> // the template allows the weight of an edge to take any numeric data type (denoted by T).
class Graph {

	public:
        
        /* define your data structure to represent a weighted undirected graph */
        
        map<string, map<string, T>> m;
        size_t edges = 0;
        
        /* test1 */
		Graph(); // the contructor function.
		~Graph(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the graph.
		size_t num_edges(); // returns the total number of edges in the graph.

        /* test2 */
        void add_vertex(const string&); // adds a vertex to the graph -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the graph -- returns true if the graph contains the given vertex; otherwise, returns false.
        
        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the graph.

        /* test4 */
        void add_edge(const string&, const string&, const T&); // adds a weighted edge to the graph -- the two strings represent the incident vertices; the third parameter represents the edge's weight.
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the graph -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the graph -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex by an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		void remove_edge(const string&, const string&); // removes the edge between two vertices, if it exists.
        
        /* test8 */
        void remove_vertex(const string&); // delete the given vertex from the graph -- note that, all incident edges of the vertex should be deleted as well.

        /* test9 */
		vector<string> depth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a depth-first traversal from the given vertex.
		
        /* test10 */
        vector<string> breadth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a breadth-first traversal from the given vertex.
        
        /* test11 */
		bool contain_cycles(); // check if the graph contains any cycle -- returns true if there exists a path from a vertex to itself; otherwise, return false.
        
        /* test12 */
		Graph<T> minimum_spanning_tree(); // returns a spanning tree of the graph -- the returned tree is preferably a minimum spanning tree.
		
};

/* test1 */

template <typename T>
Graph<T>::Graph() {}

template <typename T>
Graph<T>::~Graph() {}


template <typename T>
size_t Graph<T>::num_vertices() {
    return m.size();
}

template <typename T>
size_t Graph<T>::num_edges() {
    return edges;
}

/* test2 */

template <typename T>
void Graph<T>::add_vertex(const string& u) {
    m[u] = map<string, T>();
}

template <typename T>
bool Graph<T>::contains(const string& u) {
    if (m.find(u) != m.end()) return true; //m.find will return an iterator or m.end otherwise
    return false;
};

/* test3 */

template <typename T>
vector<string> Graph<T>::get_vertices() {
    vector<string> v;
    for (auto it = m.begin(); it != m.end(); it++) {
        v.push_back(it->first); // -> is used to access first through an iterator
    }
    return v;
}

/* test4 */

template <typename T>
void Graph<T>::add_edge(const string& u, const string& v, const T& weight) {
    if(u==v) return; //to prevent an edge that points it itself, user error
    m[u][v]=weight;
    m[v][u]=weight; //as this is an undirected graph we need to make and keep entries in sync
    edges++;
}
template <typename T>
bool Graph<T>::adjacent(const string& u, const string& v) {
    if (m.count(v) > 0) {
        if (m[v].count(u) > 0) return true;
    }
    return false;
}

/* test5 */

template <typename T>
vector<pair<string,string>> Graph<T>::get_edges() {
    vector<pair<string, string>> v;  //assign vector variable v to keep code concise
    for(auto const ent1 : m) {
        for(auto const ent2 : ent1.second) { //loop through entire map On^2
            pair<string, string> p1;
            p1.first = ent1.first; p1.second = ent2.first; //undirected graph means an edge can have two forms
            pair<string, string> p2;
            p2.first = ent2.first; p2.second = ent1.first;
            if(find(v.begin(), v.end(), p1) == v.end() && find(v.begin(), v.end(), p2) == v.end()) v.push_back(p1); //if neither one of the two forms is found add it to the vector
        }
    }
    return v;
}

/* test6 */

template <typename T>
vector<string> Graph<T>::get_neighbours(const string& u) {
    vector<string> v;
    for (auto const k : m[u]) { //loop through the inner map u
        v.push_back(k.first); //add each member to vector v
    }
    return v;
}

template <typename T>
size_t Graph<T>::degree(const string& u) {
    return get_neighbours(u).size(); //get_neighbours already does this, just need size of vector
}

/* test7 */

template <typename T>
void Graph<T>::remove_edge(const string& u, const string& v) {
    m[u].erase(v);
    m[v].erase(u); //need to make sure both records are deleted of undirected graph
    edges--;
}

/* test8 */

template <typename T>
void Graph<T>::remove_vertex(const string& u) {
    if (contains(u)) {
        for (auto& k : m) { //the & is needed to point k to the same place in memory to mutate the actual value in the graph
            if (k.second.find(u) != k.second.end()) { //go through the each sub map an erase any link to U
                k.second.erase(u);
                edges --;
            }
        }
        m.erase(u);
    }
}

/* test9 */

template <typename T>
vector<string> Graph<T>::depth_first_traversal(const string& u) {
    //Create a map of all nodes and initialise them all to false
	map<string, bool> visited;
	for (auto& k : m) visited[k.first] = false; 
    //dfs uses a stack initiase and push u as the root node
    stack<string> s;
	s.push(u);
    //initialise vector ordered as this is the expected return
	vector<string> ordered;
    while (!s.empty()) { //the stack will now only be empty if all nodes are visited
        string n = s.top();
        s.pop();
        if(!visited[n]) {
            visited[n] = true;
            ordered.push_back(n); //add the newly visited node to orderd
            //as this is dfs traverse the graph back up a node and repeat while loop
            for (auto it = m[n].rbegin(); it != m[n].rend(); it++) {
                    s.push(it->first);
            }
        }
    }
    return ordered;
}

/* test10 */

template <typename T>
vector<string> Graph<T>::breadth_first_traversal(const string& u) {
    //Create a map of all nodes and initialise them all to false
    map<string, bool> visited;
	for (auto& k : m) visited[k.first] = false;
    //bfs uses a queue initiase and push u as the root node
    queue<string> q;
	q.push(u);
    //initialise vector ordered as this is the expected return
    vector<string> ordered;
    while (!q.empty()) { //the queue will now only be empty if all nodes are visited
        string n = q.front();
        q.pop();
        if (!visited[n]) {
            visited[n] = true;
            ordered.push_back(n); //add the newly visited node to orderd
            for (auto it = m[n].begin(); it != m[n].end(); it++) {
                q.push(it->first);
            }
        }
    }
    return ordered;
}

/* test11 */

template <typename T>
bool Graph<T>::contain_cycles() {
    // for the graph to contain a cycle the number of edges must be at least equal to the number or vertices
    return num_edges() >= num_vertices();;
}

/* test12 */

template <typename T>
Graph<T> Graph<T>::minimum_spanning_tree() {
    Graph<T> msp;
    //list of nodes that have been visited
    vector<string> visited;
    //add the first node to visited
    visited.push_back(m.begin()->first);
    //while the minimum spaning tree has not reached every node
    while (msp.num_vertices() < m.size()) {
        //initialise the lowest value as type T and the max value of a double
        T lowest_value = 1.79769e+308;
        //link is a pair used to describe an edge
        pair<string, string> link;
        for (string vertex : visited) {
            //loop through all the asjacent vertexs of the visited vertex
            for (auto adjacent : m[vertex]) {
                //if visited doesnt contain adjacent.key and adjacent.value is the lowest value 
                if(find(visited.begin(), visited.end(), adjacent.first) == visited.end() && adjacent.second < lowest_value) {
                    lowest_value = adjacent.second;
                    //create a link pair for the edge with lowest value
                    link = make_pair(vertex, adjacent.first);
                }
            }
        }
        visited.push_back(link.second);
        //add edge to graph msp using add_edge method already defined
        msp.add_edge(link.first, link.second, m[link.first][link.second]);
    }
    return msp;
}