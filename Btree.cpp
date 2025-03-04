#pragma once

//Btree.cpp

#include "Btree.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <Windows.h>


using namespace std;

Btree::Btree() {
    
    root = nullptr; 
    Stop = false;

}

   

Btree::~Btree() {
    Clear();
 }

void Btree::AddItem(int item) {
    if (root == nullptr) {
        root = new Node(item);
        return;
    }
    else {
        Node* trav = root;

        while (true) {
            if (item < trav->data) {
                if (trav->left != nullptr) {
                    trav = trav->left;
                }
                else {
                    trav->left = new Node(item);
                    trav->left->data = item;
                    break;
                }
            }
            else if (item > trav->data) {
                if (trav->right != nullptr) {
                    trav = trav->right;
                }
                else {
                    trav->right = new Node(item);
                    trav->right->data = item;
                    break;
                }
            }
            else {
                break;
            }
        }
    }
}




    void Btree::AVLAddItem(int item) {
        AddAvlRec(root, item);
        Stop = false; 
    }

    void Btree::Delete(int item) {
        deleteNode(item);
        Stop = false; 
    }

    bool Btree::Search(int item) {
        Node* current = root;
        while (current != nullptr) {
            if (item == current->data) {
                return true;  // Item found
            }
            else if (item < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return false;  
    }


    void Btree::Clear() {
        clearHelper(root);
    }

    void Btree::Balance() {
        int nodeCount = countNodes(root);
        int* balanceArray = new int[nodeCount];
        int index = 0;
        fillArray(root, balanceArray, index);
        root = nullptr; 
        root = balanceArrayToTree(balanceArray, 0, nodeCount - 1);
        delete[] balanceArray; // Clean up the dynamic array
    }

    void Btree::InOrder() {
        recinorder(root);
        std::cout << std::endl;
    }

 

   void Btree::Save() {

       Balance(); // Calling Balance before tree is saved

       ofstream file;
       string filename;
       cout << "Enter file name to save: ";
       cin >> filename;
       file.open(filename);
       saveHelper(root, file);


       file.close();
    }

    void Btree::Load() {
        ifstream file;
        string filename;
        cout << "Enter file name to load: ";
        cin >> filename;
        file.open(filename);

        if (!file.is_open()) {
            cout << "File not found!" << endl;
            return;
        }

        Clear();
        int value;
        while (file >> value) {
            AddItem(value);
        }
        Balance();

       file.close();
    }

    void Btree::calldraw() {
        system("cls");
        printTree(root);
        goTo(0, 20);
        system("pause");
        system("cls");
    }

    void Btree::menu() {

        int OptionNum, item;

        do {
            cout << endl << endl;
            cout << "|||||||||||||AVL TREE MENU|||||||||||||||||" << endl;
            cout << "||OPTION  1: ADD ITEM                    ||" << endl;
            cout << "||OPTION  2: AVLADD ITEM                 ||" << endl;
            cout << "||OPTION  3: CLEAR TREE                  ||" << endl;
            cout << "||OPTION  4: SEARCH FOR ITEM IN TREE     ||" << endl;
            cout << "||OPTION  5: PRINT CURRENT TREE IN ORDER ||" << endl;
            cout << "||OPTION  6: SAVE CURRENT TREE           ||" << endl;
            cout << "||OPTION  7: LOAD TREE FROM FILE         ||" << endl;
            cout << "||OPTION  8: DELETE ITEM FROM TREE       ||" << endl;
            cout << "||OPTION  9: DRAW AVL TREE               ||" << endl;
            cout << "||OPTION 10: QUIT                        ||" << endl;
            cout << "|||||||||||||||||||||||||||||||||||||||||||" << endl;
            cout << "SELECT OPTION # ---> ";
            cin >> OptionNum;

            switch (OptionNum) {
            case 1:
                cout << "Add item -> ";
                cin >> item;
                AddItem(item);
                break;
            case 2:
                cout << "Add item into tree -> ";
                cin >> item;
                AVLAddItem(item);
                break;
            case 3:
                Clear();
                break;
            case 4:
                cout << "Enter item to search -> ";
                cin >> item;
                if (Search(item)) {
                    cout << "Item " << item << "found in the tree." << endl;
                }
                else {
                    cout << "Item not found in the tree." << endl;
                }
                break;
            case 5:
                InOrder();
                break;
            case 6:
                Save();
                break;
            case 7:
                Load();
                break;
            case 8:
                cout << "Enter item to delete -> ";
                cin >> item;
                if (deleteNode(item)) {

                    cout << "Item found in the tree. " << item << " is being deleted from the tree" << endl;
                    ;
                }
                else {
                    cout << "Item not found in the tree." << endl;
                }
                break;
            case 9:
                calldraw();
                break;
            case 10:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "This option does not exist! :(" << endl;
            }

            if (OptionNum != 10) {
                cout << "Press any key to continue...";
                cin.ignore();
                cin.get();
                system("cls");

            }

        } while (OptionNum != 10);
    }
    



    int Btree::countNodes(Node * node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    void Btree::fillArray(Node * node, int* array, int& index) {
        if (node != nullptr) {
            fillArray(node->left, array, index);
            array[index++] = node->data;
            fillArray(node->right, array, index);
        }
    }

    Node * Btree::balanceArrayToTree(int* array, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        int mid = (start + end) / 2;
        Node* node = new Node(array[mid]);
        node->left = balanceArrayToTree(array, start, mid - 1);
        node->right = balanceArrayToTree(array, mid + 1, end);
        updateBalanceFactor(node);
        return node;
    }



    void Btree::goTo(int x, int y)
    {
       

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        pos.X = x; //Column
        pos.Y = y; //Row
        SetConsoleCursorPosition(hConsole, pos);
    }

    void Btree::printTree(Node * node, int xl, int xh, int y) {
        Balance();

        if (node) {
            int xm = (xl + xh) / 2;
            goTo(xm, y);
            cout << node->data;
            printTree(node->left, xl, xm - 1, y + 2);
            printTree(node->right, xm + 1, xh, y + 2);
        }
    }

    void Btree::recinorder(Node * node) {
        if (node != nullptr) {
            recinorder(node->left);
            cout << node->data << " ";
            recinorder(node->right);
        }
    }

    void Btree::clearHelper(Node * &node) {
        if (node) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
            node = nullptr;
        }
    }

    void Btree::saveHelper(Node * node, ofstream & file) {
        if (node) {
            
            saveHelper(node->left, file);
           
            file << node->data << " ";
            
            saveHelper(node->right, file);
        }
    }

    // AVL rotation and insertion functions
    void Btree::singlerotateright(Node*& trav) {
        Node* temp = trav->left;
        trav->left = temp->right;
        temp->right = trav;

        // Update balance factors
        trav->bf = 0;
        temp->bf = 0;

        // Update trav to the new root of the subtree
        trav = temp;
    }

    void Btree::singlerotateleft(Node*& trav) {
        Node* temp = trav->right;
        trav->right = temp->left;
        temp->left = trav;

        // Update balance factors
        trav->bf = 0;
        temp->bf = 0;

        // Update trav to the new root of the subtree
        trav = temp;
    }

    void Btree::doublerotateright(Node*& trav) {
        Node* temp1 = trav->left;
        Node* temp2 = temp1->right;
        temp1->right = temp2->left;
        temp2->left = temp1;

       trav->bf = 0;
        temp1->bf = 0;
        
        trav->left = temp2->right;
        temp2->right = trav;

        trav->bf = 0;
        temp2->bf = 0;

      
        trav = temp2;
    }

    void Btree::doublerotateleft(Node*& trav) {
        Node* temp1 = trav->right;
        Node* temp2 = temp1->left;
        temp1->left = temp2->right;
        temp2->right = temp1;

       
        trav->bf = 0;
        temp1->bf = 0;

        
        trav->right = temp2->left;
        temp2->left = trav;

       
        trav->bf = 0;
        temp1->bf = 0;

        
        trav = temp2;
    }

    void Btree::AddAvlRec(Node*& trav, int value) {
        if (!trav) {
            trav = new Node(value);
        }
        else if (value == trav->data) {
            Stop = true; // Value is already in the tree
        }
        else {
            if (value < trav->data) {
                AddAvlRec(trav->left, value);
                if (!Stop) {
                    trav->bf--;
                }
            }
            else {
                AddAvlRec(trav->right, value);
                if (!Stop) {
                    trav->bf++;
                }
            }

            // Check and perform rotations if necessary
            if (!Stop) {
                if (trav->bf == -2) {
                    if (trav->left->bf == -1) {
                        singlerotateright(trav);
                    }
                    else {
                        doublerotateright(trav);
                    }
                    updateBalanceFactor(trav); // Update balance factors after rotation
                }
                else if (trav->bf == 2) {
                    if (trav->right->bf == 1) {
                        singlerotateleft(trav);
                    }
                    else {
                        doublerotateleft(trav);
                    }
                    updateBalanceFactor(trav); // Update balance factors after rotation
                }

                if (trav->bf == 0) {
                    Stop = true; // Height of the subtree hasn't increased
                }
            }
        }
    }


    bool Btree::deleteNode(int value) {
        Node* parent = nullptr;
        Node* child = root;  
        Node* child2;
        Node* parent2;

        // Find the node to delete and its parent
        while (child != nullptr) {
            if (value < child->data) {
                parent = child;
                child = child->left;
            }
            else if (value > child->data) {
                parent = child;
                child = child->right;
            }
            else {
                // Node found, break from the loop to proceed with deletion
                break;
            }
        }

        // If the node was not found, return false
        if (child == nullptr) return false;

        // Node with two children: Find the in-order successor
        if (child->left != nullptr && child->right != nullptr) {
            child2 = child->right;
            parent2 = child;

            while (child2->left != nullptr) {
                parent2 = child2;
                child2 = child2->left;
            }

            // Replace child's data with child2's data
            child->data = child2->data;
          
            if (parent2 != child) { 
                parent2->left = child2->right;
            }
            else {
                parent2->right = child2->right;
            }
            delete child2; // Delete the in-order successor node from memory
            child2 = nullptr;
        }
        else {
            // Node with only one child or no child
            if (child->right == nullptr) {
                if (parent == nullptr) {
                    root = child->left;
                }
                else if (parent->left == child) {
                    parent->left = child->left;
                }
                else {
                    parent->right = child->left;
                }
            }
            else if (child->left == nullptr) {
                if (parent == nullptr) {
                    root = child->right;
                }
                else if (parent->left == child) {
                    parent->left = child->right;
                }
                else {
                    parent->right = child->right;
                }
            }

            delete child; // Delete the node from memory
            child = nullptr; 

        }

        balanceAfterDelete(parent);
        updateBalanceFactor(parent);
        
        
        return true;
        
    }




    Node * Btree::minValueNode(Node * node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void Btree::balanceAfterDelete(Node * &node) {
        if (node->bf == -2) {
            if (node->left->bf <= 0) {
                singlerotateright(node);
                Stop = true;
            }
            else {
                doublerotateright(node);
            }
        }
        else if (node->bf == 2) {
            if (node->right->bf >= 0) {
                singlerotateleft(node);
                Stop = true;
            }
            else {
                doublerotateleft(node);
            }
        }
        else if (node->bf != 0) {
            Stop = true;
        }
    }

    void Btree::updateBalanceFactor(Node * &node) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        node->bf = leftHeight - rightHeight;
    }


    
    int Btree::height(Node * node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + max(height(node->left), height(node->right));
    }

