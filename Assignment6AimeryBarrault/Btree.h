#pragma once
//Btree.h

#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>

class Btree {

  
public:
    // Constructor
  Btree();  
    // Destructor
 ~Btree();

 // Adds an item to the binary tree.
    void AddItem(int item);
 // Adds an item to the AVL tree and ensures it remains balanced.
    void AVLAddItem(int item);
 // Deletes an item from the tree.
    void Delete(int item);
 // Searches for an item in the tree and returns the count of its occurrences.
    bool Search(int item);
 // Clears the tree, deleting all nodes.
    void Clear();
 // Balances the tree 
    void Balance();
 // Performs an in-order traversal of the tree and prints each node.
    void InOrder();
 // Saves the current tree structure to a file.
    void Save();
 // Loads a tree structure from a file.
    void Load();
 // Displays the tree structure in a console window.
    void calldraw();
 // Displays cool menu and handles input
    void menu();

private:
    Node* root;
    bool Stop;

 // Private member function declarations
 // Counts the number of nodes in the tree.
    int countNodes(Node* node);
 // Fills an array with the tree's elements in sorted order.
    void fillArray(Node* node, int* array, int& index);
 // Reconstructs a balanced tree from a sorted array of elements.
    Node* balanceArrayToTree(int* array, int start, int end);
 // Positions the console cursor for tree visualization.
    void goTo(int x, int y);
 // Prints the tree structure to the console, used for visualization.
    void printTree(Node* node, int xl = 0, int xh = 118, int y = 0);
 // Helper function for in-order traversal.
    void recinorder(Node* node);
 // Helper function for clearing the tree.
    void clearHelper(Node*& node);
 // Helper function for saving the tree to a file.
    void saveHelper(Node* node, std::ofstream& file);
 // Performs a single right rotation for AVL tree balancing.
    void singlerotateright(Node*& trav);
 // Performs a single left rotation for AVL tree balancing.
    void singlerotateleft(Node*& trav);
 // Performs a double right rotation for AVL tree balancing.
    void doublerotateright(Node*& trav);
 // Performs a double left rotation for AVL tree balancing.
    void doublerotateleft(Node*& trav);
 // AVL tree insertion.
    void AddAvlRec(Node*& trav, int value);
 // Deletes a node from the tree and rebalances if necessary. 
    bool deleteNode(int value);
 // Finds the node with the minimum value in the tree.
    Node* minValueNode(Node* node);
 // Balances the tree after a node deletion.
    void balanceAfterDelete(Node*& node);
 // Updates the balance factor of a node.
    void updateBalanceFactor(Node*& node);
 // Computes the height of a node in the tree.
    int height(Node* node);
};