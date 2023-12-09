#include <iostream>
#include "bst.h"
using namespace std;

template<class T>
BST<T>::BST() : root(nullptr)
{
}

template<class T>
BST<T>::~BST()
{
    cout << endl << "destroying..." <<endl;
    if (root == nullptr){
        return;
    }
    else{
        //there are four paths from here on
        //the first is when both the left and right nodes exist
        //the second is when left exists only
        //the third is when right exists only
        //the fourth is when we come across a leaf
        Node<T> *temp = root;
        while (root->getLeft() != nullptr || root->getRight() != nullptr){ //only go until we have deleted all children of the root
            
            if (temp->getLeft() != nullptr && temp->getRight() != nullptr){
                //case 1: we will default to going leftwards always
                temp = temp->getLeft();
            }
            else if (temp->getLeft() != nullptr){
                //case 2: only left exists
                temp = temp->getLeft();
            }
            else if (temp->getRight() != nullptr){
                //case 3: only right exists
                temp = temp->getRight();
            }
        
            else{
                //case 4; leaf

                //there are really only 3 cases
                //the first two is where the leaf exists without a brother/sister (left or right)
                //the third is when he has a brother or sister
                //in the case that he has a brother or sister, we should traverse leftwards just because
                
                if (temp->getParent()->getLeft() == nullptr){
                    //case 1: right is a leaf and no sibling
                    cout << "deleting node " << temp->getItem() << endl;
                    temp = temp->getParent();
                    deleteNode(temp->getRight());
                    temp->setRight(nullptr);
                    
                }
                else if (temp->getParent()->getRight() == nullptr){
                    //case 2: left is a leaf and no sibling
                    cout << "deleting node " << temp->getItem() << endl;
                    temp = temp->getParent();
                    deleteNode(temp->getLeft());
                    temp->setLeft(nullptr);
                }
                else{
                    //case 3: here, the child has a sibling
                    temp = temp->getParent();
                    //this one is going to look convoluted and annoying but basically, we have no way to know which node is the leaf, so we need two cases to check
                    
                    //ok, 3 cases again.
                    //case 1: both children are in fact leaves
                    //case 2: left side is a leaf, the right side is not
                    //case 3: right side is a leaf, the left side is not
                    if (((temp->getLeft())->getRight() == nullptr && (temp->getLeft())->getLeft() == nullptr) && ((temp->getRight())->getRight() == nullptr && (temp->getRight())->getLeft() == nullptr)){
                        //case 1: they're both leaves lol
                        cout << "deleting nodes " << temp->getLeft()->getItem();
                        cout << " and " << temp->getRight()->getItem() << endl;
                        deleteNode(temp->getLeft());
                        temp->setLeft(nullptr);
                        deleteNode(temp->getRight());
                        temp->setRight(nullptr);
                    }
                    else if ((temp->getLeft())->getRight() == nullptr && (temp->getLeft())->getLeft() == nullptr){
                        //case 2: only left is a leaf
                        cout << "deleting node " << temp->getLeft()->getItem() << endl;
                        deleteNode(temp->getLeft());
                        temp->setLeft(nullptr);
                    }
                    else if ((temp->getRight())->getRight() == nullptr && (temp->getRight())->getLeft() == nullptr){
                        //case 3: only right is a leaf
                        cout << "deleting node " << temp->getRight()->getItem() << endl;
                        deleteNode(temp->getRight());
                        temp->setRight(nullptr);
                    }
                }
            }
        }
    }
    //at this point, we have only the root left
    cout << "deleting root node " << root->getItem() << endl;
    cout << "deleted list: " << endl;
    deleteNode(root);
    cout << endl;
}

template<class T>
void BST<T>::isComplete(Node<T> * temp)
{
    //this runs recursively until it's found that the tree is not "nearly complete"
    if (temp->getRight() == nullptr && temp->getLeft() == nullptr){
        cout << "node with value: " << temp->getItem() <<  " is a leaf. Is technically complete." << endl;
        
        return;
    }
    int heightL = 0;
    int heightR = 0;
    Node<T>* original = temp;
    while (temp->getLeft() != nullptr){ //find height of left spine
        ++heightL;
        temp = temp->getLeft();
    }
    while (temp->getRight() != nullptr){ //find height of right spine
        ++heightR;
        temp = temp->getRight();
    }
    if ((heightR - heightL) <= 1 && (heightR - heightL) >= -1){
        temp = original;
        cout << "tree with node: " << temp->getItem() << " is at least nearly complete" << endl;
        
        if (temp->getLeft() != nullptr){
            isComplete(temp->getLeft());
        }
        if (temp->getRight() != nullptr){
            isComplete(temp->getRight());
        }
    }


    else{
        temp = original;
        cout << "tree with node: " << temp->getItem() << " is not nearly complete" << endl;
        this->completeness = 0;
        if (temp->getLeft() != nullptr){
            isComplete(temp->getLeft());
        }
        if (temp->getRight() != nullptr){
            isComplete(temp->getRight());
        }
    }
}
template<class T>
int BST<T>::height(Node<T> *p){
    if (p == nullptr){
        cout << "tree is empty " << endl;
        return 0;
    }
    int heightL = 1;
    int heightR = 1;
    //any subtree should continue to compare its longest path and return the bigger one to its parent
    if (p->getLeft() != nullptr){ //basically, we'll stop the recursion once we hit a nullptr
        heightL += height(p->getLeft());
        //at the end this should hold the largest height value of the left subtree of the root
    }
    if (p->getRight() != nullptr){
        heightR += height(p->getRight());
        //and at the end here it should hold the longest path in the right subtree of the root
    }
    
    //this last if-else statement has two purposes. The first purpose is that it returns the recursive value of function calls
    //It's second purpose is to return the greater of the heights at the end, which is the only one we want to be returned to main
    //
    if (heightL >= heightR){
        return heightL;
    }
    else{
        return heightR;
    }
}

// Inserts a new node at the front of the list
template<class T>
void BST<T>::insert(T item)
{
    // First search for the insertion point
    Node<T> *y = nullptr;
    Node<T> *x = root;
    while (x != nullptr)
    {
        y = x;  // Remember previous node
        // Update x to a child pointer
        if (item < x->getItem())
            x = x->getLeft();
        else
            x = x->getRight();
    }
    // At this point, y points to the node where we should
    // insert the new node.
    // Create a new node with the insertion value
    Node<T> *newNode = new Node<T>(item);
    newNode->setParent(y);  // Set parent to Y
    if (y==nullptr)
    {
        root = newNode;  // First node
    }
    else
    {
        // Set new node as left or right child of y
        if (item < y->getItem())
            y->setLeft(newNode);
        else
            y->setRight(newNode);
    }
}

template<class T>
Node<T>* BST<T>::find(T item)
{
    if (root == nullptr)
        return nullptr;
    return treeSearch(root, item);
}

template<class T>
Node<T>* BST<T>::treeSearch(Node<T> *p, T item)
{
    if (p == nullptr)
        return nullptr;
    if (p->getItem() == item)
        return p;
    if (item < p->getItem())
        return treeSearch(p->getLeft(), item);
    else
        return treeSearch(p->getRight(), item);
}

template<class T>
void BST<T>::traverse()
{
    inOrder(root);
}

template<class T>
void BST<T>::inOrder(Node<T> *p)
{
    if (p != nullptr)
    {
        inOrder(p->getLeft());
        cout << p->getItem() << endl;
        inOrder(p->getRight());
    }
}


template<class T>
Node<T>* BST<T>::successor(Node<T> *p)
{
    if (p->getRight() != nullptr)
    {
        p = p->getRight();
        while (p->getLeft() != nullptr)
        {
            p = p->getLeft();
        }
        return p;
    }
    else
    {
        Node<T>* parent = p->getParent();
        while ((parent != nullptr) && (p == parent->getRight()))
        {
            p = parent;
            parent = parent->getParent();
        }
        return parent;
    }
}

template<class T>
void BST<T>::deleteNode(Node<T> *z)
{
    if (z->getLeft() == nullptr)
        transplant(z, z->getRight());
    else if (z->getRight() == nullptr)
        transplant(z, z->getLeft());
    else
    {
        Node<T> *y;
        // Find y as the minimum in z's right subtree
        y = z->getRight();
        while (y->getLeft() != nullptr)
        {
            y = y->getLeft();
        }
        // Y's right subtree to Z's right subtree
        if (y->getParent() != z)
        {
            transplant(y, y->getRight());
            y->setRight(z->getRight());
            y->getRight()->setParent(y);
        }
        // Swap y and z and y's left subtree to z's left subtree
        transplant(z, y);
        y->setLeft(z->getLeft());
        y->getLeft()->setParent(y);
    }
}

template<class T>
void BST<T>::transplant(Node<T> *u, Node<T> *v)
{
    if (u->getParent() == nullptr)
        root = v;
    else if (u == u->getParent()->getLeft())
        u->getParent()->setLeft(v);
    else
        u->getParent()->setRight(v);
    if (v != nullptr)
        v->setParent(u->getParent());
}

