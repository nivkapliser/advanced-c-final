#pragma once // Include guard to prevent multiple inclusion of the header file

// Definition of chess position
typedef char chessPos[2];

// Definition of chess positions array structure
typedef struct _chessPosArray {
	unsigned int size; // Size of the array
	chessPos* positions; // Array of chess positions
} chessPosArray;

// Definition of chess position linked list node structure
typedef struct _chessPosCell {
	chessPos position; // Chess position data
	struct _chessPosCell* next; // Pointer to the next cell in the list
} chessPosCell;

// Definition of chess position linked list structure
typedef struct _chessPosList {
	chessPosCell* head; // Pointer to the first cell in the list
	chessPosCell* tail; // Pointer to the last cell in the list
} chessPosList;

// Definition of tree nodes list structure
struct _treeNodeListCell;

typedef struct _treeNodeList {
	struct _treeNodeListCell* head; // Pointer to the first cell in the list 
	struct _treeNodeListCell* tail; // Pointer to the last cell in the list
} treeNodeList;

// Definition of tree node structure
typedef struct _treeNode {
	chessPos position; // Chess position data
	treeNodeList next_possible_positions;  // List of possible next positions
} treeNode;

// Definition of tree node list cell structure
typedef struct _treeNodeListCell {
	treeNode* node; // Pointer to a tree node
	struct _treeNodeListCell* next; // Pointer to the next cell in the list
} treeNodeListCell;

// Definition of path tree structure
typedef struct _pathTree {
	treeNode* root; // Pointer to the root of the tree
} pathTree;