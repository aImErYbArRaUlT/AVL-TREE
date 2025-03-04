#pragma once

// Node.h

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    int bf = 0; // Balance factor

    Node(int value) : data(value) {}
};