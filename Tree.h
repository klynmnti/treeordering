#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
    private:
        Node *root;
        /* Private helper functions */
        Node* search(Node* n, const string& entry) const;
        void preOrder(Node* n) const;
        void inOrder(Node* n) const;
        void postOrder(Node* n) const;
    public:
        Tree();
        ~Tree();
        void insert(const string &entry);
        void preOrder() const;
        void inOrder() const;
        void postOrder() const;
        void remove(const string &entry);
        bool search (const string &entry) const;
};

#endif