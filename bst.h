#pragma once

#include <iostream>
#include "node.cpp"
using namespace std;

template<class T>
class BST
{
public:
    BST();
    ~BST();
    void insert(T item);
    Node<T>* find(T item);
    void deleteNode(Node<T> *z);
    void traverse();
    void isComplete(Node<T> *bruh);
    int completeness = 1; //defaulted to being a near-complete tree
    Node<T>* getRoot() {return root;};
    int height(Node<T> *p);
private:
    Node<T>* treeSearch(Node<T> *p, T item);
    void inOrder(Node<T> *p);
    Node<T>* successor(Node<T> *p);
    void transplant(Node<T> *u, Node<T> *v);
    Node<T> *root;
};
