# AVL Tree Implementation

## Overview

This project implements an **AVL Tree**, a self-balancing binary search tree where the heights of the left and right subtrees differ by at most one. This ensures operations like insertion, deletion, and searching remain efficient with O(log n) time complexity.

## Features

- **Insertion (AddItem)**: Adds a node to the tree while maintaining AVL balance.
- **Balanced Insertion (AVLAddItem)**: Inserts elements while ensuring balance with rotations.
- **Search**: Checks if an item exists in the tree.
- **Deletion**: Removes a node from the tree while maintaining AVL properties.
- **Balancing**: Rebalances the tree for optimal performance.
- **File Operations**:
  - **Save**: Saves the tree structure to a file.
  - **Load**: Loads the tree from a file.
- **Display Operations**:
  - **In-Order Traversal**: Prints the tree in sorted order.
  - **Graphical Representation**: Draws the tree structure in the console.

## File Structure

- `Btree.h`: Header file defining the AVL Tree class.
- `Btree.cpp`: Implementation of the AVL Tree.
- `Node.h`: Header file defining the tree node structure.
- `Node.cpp`: Implementation of the Node class.

## How to Use

### Compilation

To compile the project, use a C++ compiler such as `g++` (for Linux/macOS) or `cl` (for Windows).

```sh
 g++ -o AVLTree Btree.cpp Node.cpp -std=c++11
```

### Running

```sh
 ./AVLTree
```

### Menu Options

Once the program runs, you will see the following menu:

```
|||||||||||||AVL TREE MENU|||||||||||||||||
|| OPTION  1: ADD ITEM                   ||
|| OPTION  2: AVLADD ITEM                ||
|| OPTION  3: CLEAR TREE                 ||
|| OPTION  4: SEARCH FOR ITEM IN TREE    ||
|| OPTION  5: PRINT CURRENT TREE IN ORDER||
|| OPTION  6: SAVE CURRENT TREE          ||
|| OPTION  7: LOAD TREE FROM FILE        ||
|| OPTION  8: DELETE ITEM FROM TREE      ||
|| OPTION  9: DRAW AVL TREE              ||
|| OPTION 10: QUIT                       ||
|||||||||||||||||||||||||||||||||||||||||||
```

Enter the corresponding option number to perform the desired action.

## Important Functions

### Insertion

```cpp
void Btree::AddItem(int item);
void Btree::AVLAddItem(int item);
```

- `AddItem` inserts an element without AVL balancing.
- `AVLAddItem` inserts and balances the tree with rotations.

### Deletion

```cpp
bool Btree::deleteNode(int value);
```

- Deletes a node and maintains balance.

### Search

```cpp
bool Btree::Search(int item);
```

- Returns `true` if the item is found, `false` otherwise.

### Tree Balancing

```cpp
void Btree::Balance();
```

- Balances the tree for optimal performance.

### File Operations

```cpp
void Btree::Save();  // Saves tree to a file
void Btree::Load();  // Loads tree from a file
```

### Traversal

```cpp
void Btree::InOrder(); // Prints elements in ascending order
```

## Additional Information

- The project uses **Windows-specific functions**, such as `SetConsoleCursorPosition`, meaning some functions may not work on Linux/macOS.
- Uses **AVL rotations** (single and double) for balancing.
- The implementation supports **graphical visualization** of the tree.

## Future Improvements

- Make the project cross-platform.
- Implement GUI-based tree visualization.
- Extend functionalities with additional tree traversal methods (preorder, postorder).

## Author

Aimery Barrault

## License

This project is open-source and can be modified or distributed under the MIT license.


