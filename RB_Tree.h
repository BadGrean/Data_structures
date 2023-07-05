#pragma once
#include "Node.h"
#include <string>
#include <vector>

template <class T>
class RB_Tree
{
public:
    using Node_p = Node<T>*;
private:
    typedef Node<T> *Node_p; // creating node pointer to prevent too much usage of memory

    Node_p warden;
    Node_p root;

    int size = 0;

    void initWarden(); // creating node that is NULL for every leaf
    void insertFixUp(Node_p node);
    void rotateRight(Node_p node); // O(1)
    void rotateLeft(Node_p node);

public:
    RB_Tree();

    int depth = 0;

    int getSize() { return size; }
    void insert(T data); // O(log n)
    void show_helper(Node_p root, std::string tabulator, bool visited_last);
    void show();
    std::vector<Node_p> find_helper(Node_p node, int value, std::vector<Node_p> result);
    std::vector<Node_p> find(int value);
    int height_helper(Node_p node);
    int height();
    //std::vector<Node_p> findElementsOnDepth(int depth);
    Node_p getRoot();
};

#include "RB_Tree.cpp"