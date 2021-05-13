#include "tree.hpp"

int main(){

	BST<int> t;

    t.add_vertex("C", 5);
    t.add_vertex("A", 1);
    t.add_vertex("D", 3);
    t.add_vertex("H", 10);
    t.add_vertex("G", 20);
    t.add_vertex("F", 15);
    t.add_vertex("B", 30);
    t.add_vertex("E", 17);
    
    cout << "Number of Vertices: " << t.num_vertices() << endl;
    cout << "Number of Edges: " << t.num_edges() << endl;
    cout << "Sum Weight: " << t.sum_weight() << endl;

    cout << "leaves: ";
    for (auto n : t.get_leaves()) {
        cout << n;
    }
    cout << endl;

    cout << "preorder traversal: ";
    for (auto n : t.preorder_traversal()) {
        cout << n;
    }
    cout << endl;

    cout << "inorder traversal: ";
    for (auto n : t.inorder_traversal()) {
        cout << n;
    }
    cout << endl;

    cout << "postorder traversal: ";
    for (auto n : t.postorder_traversal()) {
        cout << n;
    }
    cout << endl;

    cout << "breadth first traversal: ";
    for (auto n : t.breadth_first_traversal()) {
        cout << n;
    }
    cout << endl;
    
    cout << "Path Between C and H: ";
    for (auto n : t.path("C", "H")) {
        cout << n;
    }
    cout << endl;

    cout << "Path Between D and F: ";
    for (auto n : t.path("D", "F")) {
        cout << n;
    }
    cout << endl;
    
    cout << "Path Between C and B: ";
    for (auto n : t.path("C", "B")) {
        cout << n;
    }
    cout << endl;

    cout << "path with largest weight: ";
    for (auto n : t.path_with_largest_weight()) {
        cout << n;
    }
    cout << endl;

    cout<< "Height: " << t.height() << endl;

    //Test for remove leaf D
    cout << endl << "remove leaf D:" << endl;
    t.remove_vertex("D");

    cout << "breadth first traversal: ";
    for (auto n : t.breadth_first_traversal()) {
        cout << n;
    }
    cout << endl;

    cout << "get edges: ";
    for (auto n: t.get_edges()) {
        cout << "(" << n.first << "," << n.second << ")";
    }
    cout << endl;

    t.add_vertex("D", 3);

    //Test for remove Node F
    cout << endl << "remove node F:" << endl;
    t.remove_vertex("F");
    cout << "breadth first traversal: ";
    for (auto n : t.breadth_first_traversal()) {
        cout << n;
    }
    cout << endl;

    cout << "get edges: ";
    for (auto n: t.get_edges()) {
        cout << "(" << n.first << "," << n.second << ")";
    }
    cout << endl;
    
    //Test for remove Node G
    cout << endl << "remove node C:" << endl;
    t.remove_vertex("C");
    cout << "breadth first traversal: ";
    for (auto n : t.nodes) {
        cout << " (D:" << n->data; 
        if (n->parent) cout << " P:" << n->parent->data;
        if (n->left) cout << " L:" << n->left->data;
        if (n->right) cout << " R:" << n->right->data;
        cout << ")";
    }
    cout << endl;

    cout << "get edges: ";
    for (auto n: t.get_edges()) {
        cout << "(" << n.first << "," << n.second << ")";
    }
    cout << endl;
}