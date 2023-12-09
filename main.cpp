#include "bst.cpp"
#include <iostream>

using namespace std;

int main()
{
    BST<int> bst;
    cout << "creating tree: "<< endl;
    bst.insert(10);
    bst.insert(11);
    bst.insert(9);
    bst.insert(9);
    bst.insert(9);
    bst.insert(8);
    bst.insert(8);
    bst.insert(7);
    bst.insert(6);
    bst.insert(12);
    bst.insert(14);
    bst.insert(13);
    bst.insert(12);
    cout <<"tree height: " << bst.height(bst.getRoot()) << endl << endl;
    bst.traverse();
    bst.isComplete(bst.getRoot());
    if (bst.completeness == 0){
        cout << "--this bst is not nearly complete. "<< endl;
    }
    else{
        cout << "--this bst is at least nearly complete" << endl;
    }
    /*
    Node<int> *temp = bst.find(5);
    bst.deleteNode(temp);
    temp = bst.find(7);
    bst.deleteNode(temp);
    temp = bst.find(5);
    bst.deleteNode(temp);
    */
    cout << endl;
    

    return 0;
}


