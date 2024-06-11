#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.h"
#include "functions.h"

// Function to initialize an empty chessPosList
void makeEmptyList(chessPosList* lst) {

	lst->head = lst->tail = NULL;
}

// Function to insert a new cell into the list
void insertCell(chessPosList* lst, chessPosCell* newCell) {
    // If the list or newCell is NULL, return
    if (lst == NULL || newCell == NULL) {
        return;
    }

    // If the list is empty, newCell becomes the head and tail
    if (lst->head == NULL) {
        lst->head = newCell;
        lst->tail = newCell;
    }
    else {
        // Otherwise, append newCell to the end of the list
        lst->tail->next = newCell;
        lst->tail = newCell;
    }
}

// Function to insert a chess position at the end of the list
void insertDataToEndList(chessPosList* lst, chessPos position) {
    // Create a new cell for the position
    chessPosCell* newCell = (chessPosCell*)malloc(sizeof(chessPosCell));
    checkAllocation((chessPosCell*)newCell);

    newCell->position[0] = position[0];
    newCell->position[1] = position[1];
    newCell->next = NULL;
    
    // Insert the new cell into the list
    insertCell(lst, newCell);
}

void getInput(chessPos* startingPosition) {

    char input[3];
    scanf("%s", input);
    startingPosition[0][0] = input[0];
    startingPosition[0][1] = input[1];
    checkInput(startingPosition, input[2]);

}

// Function to check if the starting position is valid
void checkInput(chessPos startingPosition, char ch) {

	if (!isValidPosition(startingPosition) || ch != '\0') {
		printf("Invalid input");	
		exit(1);
	}
}

// Function to free memory allocated for a chessPosList
void freeChessPosList(chessPosList* lst) {
    chessPosCell* current = lst->head;
    while (current != NULL) {
        chessPosCell* temp = current; // Store current cell
        current = current->next; // Move to next cell
        free(temp); // Free the current cell
    }
    // After freeing all cells, reset head and tail pointers
    lst->head = lst->tail = NULL;
}

// Function to free memory allocated for a chessPosArray
void freeChessPosArray(chessPosArray* arr) {

    free(arr->positions); // Free the positions array
    free(arr); // Free the chessPosArray structure itself
}

// Function to free memory allocated for a 2D array of chessPosArray
void freeBoard(chessPosArray*** board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            freeChessPosArray(board[row][col]); // Free each chessPosArray
        }
        free(board[row]); // Free the row
    }
    free(board); // Free the board itself
}

// Function to free memory allocated for a treeNodeList
void freeTreeNodeList(treeNodeList* lst) {
    treeNodeListCell* current = lst->head;
    while (current != NULL) {
        treeNodeListCell* temp = current; // Store current cell
        current = current->next; // Move to next cell
        free(temp); // Free the current cell
    }
    // After freeing all cells, reset head and tail pointers
    lst->head = lst->tail = NULL;
}

// Recursive helper function to free memory allocated for tree nodes
void freeTreeNode(treeNode* node) {
    if (node == NULL) return;
    freeTreeNodeList(&(node->next_possible_positions)); // Free the list of next possible positions 
    free(node); // Free the node itself
}

// Function to free memory allocated for a path tree
void freePathTree(pathTree* tree) {
    freeTreeNode(tree->root); // Free the tree nodes recursively starting from the root
}

// Function to free all dynamically allocated memory in the program
void freeMemory(pathTree* allPossiblePaths, chessPosList* knightPath) {

    freePathTree(allPossiblePaths); // Free the tree of all possible paths
    freeChessPosList(knightPath); // Free the knight's path covering all board squares
}

// Function to check if memory allocation was successful
void checkAllocation(void* ptr) {

	if (ptr == NULL) {
		printf("Memory allocation error!");
		exit(1);
	}
}