#include "dataStructures.h"
#include "functions.h"
#include "Ex1_H.h"
#include "Ex3_H.h"
#include "Ex4_H.h"

// Function to initialize an empty treeNodeList
void makeEmptyTreeNodeList(treeNodeList* lst) { 

	lst->head = lst->tail = NULL;
}

// Function to create a new treeNode with given position
treeNode* createNewNode(chessPos position) {
	treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
	checkAllocation((treeNode*)newNode);

	newNode->position[0] = position[0];
	newNode->position[1] = position[1];
	makeEmptyTreeNodeList(&(newNode->next_possible_positions));// Initialize next_possible_positions list
	return newNode;
}

// Function to insert a treeNode into the treeNodeList
void insertTreeNode(treeNodeList* lst, treeNode* newNode) {
	treeNodeListCell* newCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkAllocation((treeNodeListCell*)newCell);
	newCell->node = newNode;
	newCell->next = NULL;

	// If the list is empty, newNode becomes both head and tail
	if (lst->head == NULL) {
		lst->head = newCell;
		lst->tail = newCell;
	}
	else {
		// Otherwise, append newNode to the end of the list
		lst->tail->next = newCell;
		lst->tail = newCell;
	}
}

// Recursive helper function to find all possible knight paths
void findAllPossibleKnightPathsHelper(treeNode* node, chessPosArray*** posList, bool visited[BOARD_SIZE][BOARD_SIZE]) {
	
	int row = LETTER_TO_ROW(node->position[0]); // Convert letter to row index
	int col = NUMBER_TO_COL(node->position[1]);// Convert number to column index
	int i;
	
	visited[row][col] = true; // Mark current position as visited
	
	chessPosArray nextPosList = *posList[row][col];// Get possible next positions
	int movesSize = nextPosList.size;

	for (i = 0; i < movesSize; i++) {
		int nextRow = LETTER_TO_ROW(nextPosList.positions[i][0]); // Convert letter to row index
		int nextCol = NUMBER_TO_COL(nextPosList.positions[i][1]);// Convert number to column index

		// If the next position is not visited, create a new node and continue exploration
		if (!visited[nextRow][nextCol]) {
			treeNode* newNode = createNewNode(nextPosList.positions[i]);
			insertTreeNode(&(node->next_possible_positions), newNode);
			findAllPossibleKnightPathsHelper(newNode, posList, visited);
		}
	}

	visited[row][col] = false;// Mark current position as unvisited before backtracking
}

// Function to find all possible knight paths from a given starting position
pathTree findAllPossibleKnightPaths(chessPos* startingPosition) {
	
	pathTree tree;

	// Initialize the root node with the starting position
	tree.root = createNewNode(*startingPosition);
	
	// Initialize visited array and mark the starting position as visited
	bool visited[BOARD_SIZE][BOARD_SIZE] = { false };
	int row = LETTER_TO_ROW(tree.root->position[0]);// Convert letter to row index
	int col = NUMBER_TO_COL(tree.root->position[1]);// Convert number to column index	
	visited[row][col] = true;

	// Get valid knight moves
	chessPosArray*** validMoves = validKnightMoves();
	// Find all possible knight paths recursively
	findAllPossibleKnightPathsHelper(tree.root, validMoves, visited);

	// Free the allocated memory for validMoves	
	freeBoard(validMoves);	

	return tree;
}
