#ifndef __NODE_H
#define __NODE_H

#include <string>
#include <iostream>
using namespace std;
#pragma once

class Node {
    friend class Tree; // class Tree is able to access Node's data members
    private:
        string small;
        string large;
        Node *left;
        Node *middle;
        Node *right;
        Node *parent;
    public:
        // two constructors: one parameter vs two parameters
        Node(string s) : small(s), large(""), left(0), middle(0), right(0), parent(0) {}
        Node(string& s, string& l) : small(s), large(l), left(0), middle(0), right(0), parent(0) {}
};

#endif