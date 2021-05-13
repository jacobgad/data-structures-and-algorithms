#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;
template <typename T>
class Node {
    public:
        string data;
        T weight;
        Node<T>* parent = nullptr;
        Node<T>* left = nullptr;
        Node<T>* right = nullptr;
};

template <typename T> // the template allows the weight of vertex to take any numeric data type (denoted by T).
class BST {

	public:
        /* define your data structure to represent a binary search tree (bst) */
        Node<T>* root = nullptr;
        T total_weight;
        vector<Node<T>*> nodes;
        vector<pair<string, string>> edges;
        
        vector<string> v_postorder;
        
        /* test1 */
		BST(); // the contructor function.
		~BST(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the bst.
		size_t num_edges(); // returns the total number of edges in the bst.
        T sum_weight(); // return the total weight of all the vertices in the bst.

        /* test2 */
        void add_vertex(const string&, const T&); // adds a vertex, which has a weight, to the tree -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the bst -- returns true if the bst contains the given vertex; otherwise, returns false.
        void recursive_add_vertex(Node<T>*, Node<T>*);

        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the bst.
        vector<string> get_leaves(); // returns a vector of all the leaves in the bst.
                                     //     Leaves are the vertices that do not have any children in the bst.

        /* test4 */
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the bst -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the bst -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex via an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		vector<string> preorder_traversal(); // returns a vector of all the vertices in the visiting order of a preorder traversal over the bst.
		
        /* test8 */
        vector<string> inorder_traversal(); // returns a vector of all the vertices in the visiting order of an inorder traversal over the bst.
        
        /* test9 */
        vector<string> postorder_traversal(); // returns a vector of all the vertices in the visiting order of a postorder traversal over the bst.
        void recursive_postorder_traversal(Node<T>*);

        /* test10 */
        vector<string> breadth_first_traversal(); // returns a vector of all the vertices in the visiting order of a breadth first traversal over the bst.
		
        /* test11 */
        vector<string> path(const string&, const string&); // returns a vector of all the vertices in the path from the first vertex to the second vertex.
                                                           //     A path should include the source and destination vertices at the begining and the end, respectively.

        /* test12 */
        vector<string> path_with_largest_weight(); // returns a path that has the largest weight in the bst.
        int path_weight(vector<Node<T>*>);         //    The weight of a path is the sum of the weights of all the vertices (including the source and destination vertices) in the path.
        vector<Node<T>*>vector_converter(vector<string>);

        /* test13 */
        size_t height(); // returns the height of bst. Height of a tree is the number of edges that form the longest path from root to any leaf.

        /* test14 */
        void remove_vertex(const string&); // delete the given vertex from bst -- note that, all incident edges of the vertex should be deleted as well.
        void remove_edges(const string&);
};

/* test1 */

template <typename T>
BST<T>::BST() {
    total_weight = 0;
}

template <typename T>
BST<T>::~BST() {}


template <typename T>
size_t BST<T>::num_vertices() {
    return nodes.size();
}

template <typename T>
size_t BST<T>::num_edges() {
    if (nodes.size() == 0) return 0;
    return nodes.size()-1;
}

template <typename T>
T BST<T>::sum_weight() {
    return total_weight;
}

/* test2 */

template <typename T>
void BST<T>::add_vertex(const string& u, const T& w) {
    Node<T>* newNode = new Node<T>();
    newNode->data = u;
    newNode->weight = w;
    newNode->left = nullptr;
    newNode->right = nullptr;

    recursive_add_vertex(newNode, root);
    nodes.push_back(newNode);  
    total_weight += w;        
}

template <typename T>
void BST<T>::recursive_add_vertex(Node<T>* newNode, Node<T>* currentNode) {
    if (root == nullptr) {
        newNode->parent = nullptr;
        root = newNode; 
      return;
    }
    if (newNode->weight < currentNode->weight) {
        if (currentNode->left == nullptr) {
            newNode->parent = currentNode;
            currentNode->left = newNode;
            edges.push_back(make_pair(currentNode->data, newNode->data));
            return;
        }
        currentNode = currentNode->left;
        recursive_add_vertex(newNode, currentNode);
    } else {
        if (currentNode->right == nullptr) {
            newNode->parent = currentNode;
            currentNode->right = newNode;
            edges.push_back(make_pair(currentNode->data, newNode->data));
            return;
        }
        currentNode = currentNode->right;
        recursive_add_vertex(newNode, currentNode);
    }
}

template <typename T>
bool BST<T>::contains(const string& u) {
    for (auto& node : nodes) {
        if (node->data == u) return true;
    } 
    return false;
}

/* test3 */

template <typename T>
vector<string> BST<T>::get_vertices() {
    vector<string> v;
    for (auto& node : nodes) {
        v.push_back(node->data);
    }
    return v;
}

template <typename T>
vector<string> BST<T>::get_leaves() {
    vector<string> v;
    for (auto& node : nodes) {
        if(node->left == nullptr && node->right == nullptr) {
            v.push_back(node->data);
        }
    }
    return v;
}

/* test4 */

template <typename T>
bool BST<T>::adjacent(const string& u, const string& v) {
    for (auto& node : nodes) {
        if (node->data == u) {
            if (node->parent) {
                if (node->parent->data == v) return true;
            }
            if (node->left) {
                if (node->left->data == v) return true;
            }
            if (node->right) {
                if (node->right->data == v) return true;
            }     
        }
    }
    return false;
}

/* test5 */

template <typename T>
vector<pair<string,string>> BST<T>::get_edges() {
    return edges;
}

/* test6 */

template <typename T>
vector<string> BST<T>::get_neighbours(const string& u) {
    vector<string> v;
    for (auto node : nodes) {
        if (node-> data == u) {
            if (node->parent) v.push_back(node->parent->data);
            if (node->left) v.push_back(node->left->data);
            if (node->right) v.push_back(node->right->data);
        }
    }
    return v;
}

template <typename T>
size_t BST<T>::degree(const string& u) {
    return get_neighbours(u).size();
}

/* test7 */

template <typename T>
vector<string> BST<T>::preorder_traversal() {
    vector<string> v;
    stack<Node<T>*> stack;
    if (!root) return v;
    stack.push(root);
    while (!stack.empty()) {
        Node<T>* currentNode = stack.top();
        stack.pop();
        v.push_back(currentNode->data);
        if (currentNode->right) stack.push(currentNode->right);
        if (currentNode->left) stack.push(currentNode->left);
    }
    return v;
}

/* test8 */

template <typename T>
vector<string> BST<T>::inorder_traversal() {
    vector<string> v;
    stack<Node<T>*> stack;
    Node<T>* currentNode = root;
    while (currentNode != NULL || stack.empty() == false) {
        while (currentNode != NULL) {
            stack.push(currentNode);
            currentNode = currentNode->left;
        }
        currentNode = stack.top();
        stack.pop();
        v.push_back(currentNode->data);
        currentNode = currentNode->right;
    }
    return v;
}

/* test9 */

template <typename T>
vector<string> BST<T>::postorder_traversal() {
    v_postorder.clear();
    recursive_postorder_traversal(root);
    return v_postorder;
}

template <typename T>
void BST<T>::recursive_postorder_traversal(Node<T>* node) {
    if (node == NULL) return;
    recursive_postorder_traversal(node->left);
    recursive_postorder_traversal(node->right);
    v_postorder.push_back(node->data);
}

/* test10 */

template <typename T>
vector<string> BST<T>::breadth_first_traversal() {
    vector<string> v;
    queue<Node<T>*> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node<T>* currentNode = queue.front();
        queue.pop();
        v.push_back(currentNode->data);
        if (currentNode->left) queue.push(currentNode->left);
        if (currentNode->right) queue.push(currentNode->right);
    }
    return v;
}

/* test11 */

template <typename T>
vector<string> BST<T>::path(const string& u, const string& v){
    Node<T>* uNode;
    Node<T>* vNode;
    vector<string> uPath;
    vector<string> vPath;
    vector<string> path;
    int breakpoint;

    for (Node<T>* node : nodes) {
        if (node->data == u) uNode = node;
    }
    for (Node<T>* node : nodes) {
        if (node->data == v) vNode = node;
    }

    Node<T>* currentNode = uNode;
    uPath.push_back(uNode->data);
    while (currentNode != root) {
        uPath.push_back(currentNode->parent->data);
        currentNode = currentNode->parent;
    }
    currentNode = vNode;
    vPath.push_back(vNode->data);
    while (currentNode != root) {
        vPath.push_back(currentNode->parent->data);
        currentNode = currentNode->parent;
    }

    reverse(uPath.begin(), uPath.end());
    reverse(vPath.begin(), vPath.end());
    for (int i = 0; i != uPath.size()-1; i++) {
        if (uPath[i] == vPath[i] ) breakpoint = i;
    }
    int cppIsStupid = uPath.size();
    for (int i = cppIsStupid-1; i > breakpoint; i--) path.push_back(uPath[i]);
    for (int i = breakpoint; i < vPath.size(); i++) path.push_back(vPath[i]);
    
    return path;
}

/* test12 */

template <typename T>
vector<string> BST<T>::path_with_largest_weight(){
    vector<Node<T>*> leaves;
    vector<Node<T>*> heaviestPathNodes;
    vector<string> heaviestPath;

    leaves.push_back(root);
    for (auto& node : nodes) {
        if(node->left == nullptr && node->right == nullptr) leaves.push_back(node);
    }

    for (Node<T>* uleaf : leaves) {
        int weight = 0;
        for (Node<T>* vleaf : leaves) {
            if (uleaf != vleaf) {
                vector<Node<T>*> v = vector_converter(path(uleaf->data, vleaf->data));
                if (path_weight(v) > path_weight(heaviestPathNodes)) {
                    heaviestPathNodes = v;
                }
            } 
        }
    }
    for (Node<T>* node : heaviestPathNodes) {
        heaviestPath.push_back(node->data);
    }
    return heaviestPath;
}

template <typename T>
int BST<T>::path_weight(vector<Node<T>*> nodes) {
    int weight = 0;
    for (Node<T>* node : nodes) {
        weight += node->weight;
    }
    return weight;
}

template <typename T>
vector<Node<T>*> BST<T>::vector_converter(vector<string> nodesData) {
    vector<Node<T>*> v;
    for (string data : nodesData) {
        for (Node<T>* node : nodes) {
            if (data == node->data) v.push_back(node);
        }
    }
    return v;
}

/* test13 */

template <typename T>
size_t BST<T>::height() {
    vector<Node<T>*> leaves;
    int maxHeight = 0;

    for (auto& node : nodes) {
        if(node->left == nullptr && node->right == nullptr) leaves.push_back(node);
    }

    for (Node<T>* leaf : leaves) {
        int height = 0;
        while (leaf->parent != nullptr) {
            height++;
            leaf = leaf->parent;
        }
        if (height > maxHeight) maxHeight = height;
    }
    return maxHeight;
}

/* test14 */

template <typename T>
void BST<T>::remove_vertex(const string& u) {
    //find the node to remove
    Node<T>* nodeToRemove;
    int nodeToRemoveIndex;
    for (int i=0; i<nodes.size(); i++) {
        if (nodes[i]->data == u) {
            nodeToRemove = nodes[i];
            nodeToRemoveIndex = i;
        }
    }
    //remove edges
    remove_edges(u);

    //case 1: nodeToRemove is a leaf
    if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr) {
        if (nodeToRemove->parent->left != nullptr) {
            if (nodeToRemove = nodeToRemove->parent->left) nodeToRemove->parent->left = nullptr;
        }
        if (nodeToRemove->parent->right != nullptr) {
            if (nodeToRemove = nodeToRemove->parent->right) nodeToRemove->parent->right = nullptr;
        } 
        nodes.erase(nodes.begin() + nodeToRemoveIndex);
    }
    //case 2: nodeToRemove has 1 child
    bool hasOneChild;
    if (nodeToRemove->left != nullptr && nodeToRemove->right == nullptr) hasOneChild = true;
    if (nodeToRemove->left == nullptr && nodeToRemove->right != nullptr) hasOneChild = true;
    if (hasOneChild == true) {
        Node<T>* child;
        if (nodeToRemove->left != nullptr) child = nodeToRemove->left;
        if (nodeToRemove->right != nullptr) child = nodeToRemove->right; 
        
        if (nodeToRemove->parent->left != nullptr) {
            if (nodeToRemove == nodeToRemove->parent->left) nodeToRemove->parent->left = child;
        }
        if (nodeToRemove->parent->right != nullptr) {
            if (nodeToRemove == nodeToRemove->parent->right) nodeToRemove->parent->right = child;
        }
        edges.push_back(make_pair(nodeToRemove->parent->data, child->data));
        nodes.erase(nodes.begin() + nodeToRemoveIndex);
    }
    //case 3: nodeToRemove has 2 children
    if (nodeToRemove->left != nullptr && nodeToRemove->right != nullptr) {
        Node<T>* replacementNode = nodeToRemove->left;
        while (replacementNode->right != nullptr) {
            if (replacementNode->right) replacementNode = replacementNode->right;
        }
        //prepair replacement Node
        replacementNode->parent->right = nullptr;
        replacementNode->left = nodeToRemove->left;
        replacementNode->right = nodeToRemove->right;
        remove_edges(replacementNode->data);
        //remove nodeToRemove
        if (nodeToRemove->parent) {
            if (nodeToRemove->parent->left != nullptr) {
                if (nodeToRemove == nodeToRemove->parent->left) nodeToRemove->parent->left = replacementNode;
            }
            if (nodeToRemove->parent->right != nullptr) {
                if (nodeToRemove == nodeToRemove->parent->right) nodeToRemove->parent->right = replacementNode;
            }
        }
        //update parents
        replacementNode->parent = nullptr;
        if (nodeToRemove->parent) replacementNode->parent = nodeToRemove->parent;
        nodeToRemove->left->parent = replacementNode;
        nodeToRemove->right->parent = replacementNode;
        //add edges
        if (nodeToRemove->parent) edges.push_back(make_pair(replacementNode->data, nodeToRemove->parent->data));
        edges.push_back(make_pair(replacementNode->data, replacementNode->left->data));
        edges.push_back(make_pair(replacementNode->data, replacementNode->right->data));
        //delete nodeToRemove
        nodes.erase(nodes.begin() + nodeToRemoveIndex);
    }
}

template <typename T>
void BST<T>::remove_edges(const string& u) {
    for (int i=0; i<edges.size(); i++) {
        if (edges[i].first == u || edges[i].second == u) {
            edges.erase(edges.begin() + i);
            i--;
        } 
    }
}
