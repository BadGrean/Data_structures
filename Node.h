#pragma once
template <class T> class Node
{
public:
	T data;

	Node(const T& value) : data(value), parent(nullptr), left(nullptr), right(nullptr), color(0) {};

	Node* parent;
	Node* left;
	Node* right;
	int color; // color attribute of a tree: 0 - black, 1 - red
};