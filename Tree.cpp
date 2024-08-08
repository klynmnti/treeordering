#include "Tree.h"
/* Default Constructor */
// assigns root as nullptr
Tree::Tree() { root = nullptr; }
/* Destructor */
// deletes left, middle and right subtrees as well as root
Tree::~Tree() {
    delete root->left;
    delete root->middle;
    delete root->right;
    delete root;
    root = nullptr;
}
/* Order functions */
// each function calls its recursive helper below
void Tree::preOrder() const { preOrder(root); }
void Tree::inOrder() const { inOrder(root); }
void Tree::postOrder() const { postOrder(root); }
/* Preorder Recursive Helper */
// checks if n has one or two values, and recursively outputs nodes accordingly
// follows the order small, left subtree, large, middle subtree and right subtree
void Tree::preOrder(Node* n) const {
    if (n != 0) {
        if (n->large == "") {
            cout << n->small << ", ";
            preOrder(n->left);
            preOrder(n->right);
        }
        else {
            cout << n->small << ", ";
            preOrder(n->left);
            cout << n->large << ", ";
            preOrder(n->middle);
            preOrder(n->right);
        }
    }
}
/* Inorder Recursive Helper */
// follows the order left subtree, small, middle subtree, large and right subtree
void Tree::inOrder(Node* n) const {
    if (n != 0) {
        if (n->large == "") {
            inOrder(n->left);
            cout << n->small << ", ";
            inOrder(n->right);
        }
        else {
            inOrder(n->left);
            cout << n->small << ", ";
            inOrder(n->middle);
            cout << n->large << ", ";
            inOrder(n->right);
        }
    }
}
/* Postorder Recursive Helper */
// follows the order left subtree, middle subtree, small, right subtree and large
void Tree::postOrder(Node* n) const {
    if (n != 0) {
        if (n->large == "") {
            postOrder(n->left);
            postOrder(n->right);
            cout << n->small << ", ";
        }
        else {
            postOrder(n->left);
            postOrder(n->middle);
            cout << n->small << ", "; 
            postOrder(n->right);
            cout << n->large << ", "; 
        }
    }
}
/* Search function (bool) */
// calls the recursive search helper function
// if the node returned is not null, the node exists so return true
bool Tree::search(const string& entry) const {
    if (search(root, entry) != nullptr) { return true; }
    return false;
}
/* Search Recursive Helper (Node*) */
// if the string input is smaller than current node's small string, left subtree is searched
// if it's between current node small and large, middle subtree is searched
// if it's larger than current node large, right subtree is searched
// node is returned if found, otherwise null is returned
Node* Tree::search(Node* n, const string& entry) const {
    if (n == nullptr) { return nullptr; }
    if (n->small == entry || n->large == entry) { return n; }
    if (entry < n->small) { return search(n->left, entry); }
    else if (entry < n->large) { return search(n->middle, entry); }
    else { return search(n->right, entry); }
}
/* Insert Function (iterative) */
void Tree::insert(const string& entry) { 
    // Case 1: if the entry already exists, duplicates cannot be inserted so exit
    if (search(entry)) { return; }
    // Case 2: if tree is empty, the root is assigned with the input value
    if (root == nullptr) { root = new Node(entry); }
    // Case 3: the tree has at least one node 
    else {
        Node* r = root;
        // find the appropriate leaf node where entry can be inserted
        while (r->left != nullptr) {
            if (entry < r->small) { r = r->left; }
            else if (entry < r->large) { r = r->middle; }
            else { r = r->right; }
        }
        // if leaf node has an empty space, add entry into the existing leaf node 
        if (r->large == "") {
            if (entry < r->small) {
                r->large = r->small;
                r->small = entry;
            }
            else if (entry >= r->small) { r->large = entry; }
        }
        // otherwise if the leaf node is full continue
        else {
            // find the middle value of leaf node small, large, and entry
            // & adjust the leaf node's data accordingly
            string middle;
            if (entry < r->small) {
                middle = r->small;
                r->small = entry;
            }
            else if (entry >= r->small && entry <= r->large) { middle = entry; }
            else if (entry > r->large) {
                middle = r->large;
                r->large = entry;
            }
            // since the node is full it needs to be split, so create three new nodes
            // also create a node to find the parent of the leaf node
            Node* rnode = new Node(r->large);
            Node* lnode = new Node(r->small);
            Node* midnode = new Node(middle);
            Node* parnode = r->parent;
            // if the leaf node is not the root, determine if it is full or has an empty space
            if (parnode != nullptr) {
                // if it has an empty space, add the middle value to the parent node
                // and adjust parent node's pointers to point to the right and left value nodes
                if (parnode->large == "") {
                    parnode->large = middle; parnode->middle = lnode; parnode->right = rnode;
                    lnode->parent = parnode; rnode->parent = parnode;
                }
                // otherwise if the parent node is full, 
                // adjust the parent node's pointers to point to middle
                // then adjust the middle node's pointers to point to left and right nodes
                else {
                    if (parnode->left == r) { parnode->left = midnode; }
                    else if (parnode->right == r) { parnode->right = midnode; }
                    else { parnode->middle = midnode; }
                    midnode->left = lnode; midnode->right = rnode; midnode->parent = parnode;
                    lnode->parent = midnode; rnode->parent = midnode;
                }
            }
            // if the leaf node is the root, then the middle node becomes the root
            // and pointers are adjusted accordingly
            else {
                root = midnode;
                midnode->right = rnode; midnode->left = lnode;
                rnode->parent = midnode; lnode->parent = midnode;
            }
            // finally r is deallocated and set to null
            delete r;
            r = nullptr;
        }
    }
}
/* Remove function (iterative) */
void Tree::remove(const string& entry) { 
    Node* r = root;
    // search for a node in the tree whose data matches entry
    while (r->left != nullptr) {
        if (r->small == entry || r->large == entry) { break; }
        else if (entry < r->small) { r = r->left; }
        else if (entry < r->large) { r = r->middle; }
        else { r = r->right; }
    }
    // Case 1: Node is full
    // if the node is full and the large value is entry,
    // then simply remove the value from r large and make it empty
    if (r->large != "") {
        if (entry == r->large) { r->large = ""; }
    }
    // Case 2: Node to be removed is root (3 Nodes)
    else if (r == root) {
        // if the root is the only value in the tree, simply deallocate memory and set to null
        if (r->left == nullptr && r->right == nullptr && r->middle == nullptr) {
            delete r;
            r = nullptr;
            root = nullptr;
        }
        // otherwise, swap root's values with its left and right values and set the left and right to null
        else { 
            r->small = r->left->small;
            r->large = r->right->small;
            r->right = nullptr;
            r->left = nullptr;
        }
    }
    // Case 3: Node to be removed is a leaf
    else if (r->left == nullptr && r->right == nullptr && r->middle == nullptr) {
        Node* p = r->parent;
        // determine if the parent pointer has an empty value, and swap values if so
        // then set parent's left/right pointers to null
        if (p->right == r) {
            p->right = nullptr;
            if (p->large == "") {
                p->large = p->small;
                p->small = p->left->small;
                p->left = nullptr;
            }
        }
        else if (p->left == r) {
            p->left = nullptr;
            if (p->large == "") {
                p->large = p->right->small;
                p->right = nullptr;
            }
        }
        // finally deallocate memory and set r to null
        delete r;
        r = nullptr;
    }
}