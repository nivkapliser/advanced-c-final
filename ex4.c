#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.h"
#include "functions.h"

// Function to remove the last cell from the list
void removeLastCell(chessPosList* lst) {
    // If the list is empty, return
    if (lst->head == NULL) {
        return;
    }

    // If there's only one cell in the list, free it and update pointers
    if (lst->head == lst->tail) {
        free(lst->head);
        lst->head = NULL;
        lst->tail = NULL;
    }
    else {
        // Find the second-to-last cell and free the last cell
        chessPosCell* curr = lst->head;
        while (curr->next != lst->tail) {
            curr = curr->next;
        }
        free(lst->tail);
        curr->next = NULL;
        lst->tail = curr;
    }
}

// Function to check if a position is within the board boundaries
bool isValidPosition(chessPos position) {
    return position[0] >= 'A' && position[0] <= 'E' && position[1] >= '1' && position[1] <= '5';
}

// Function to check if a position has been visited
bool isVisited(bool visited[BOARD_SIZE][BOARD_SIZE], chessPos position) {
    int row = LETTER_TO_ROW(position[0]);
    int col = NUMBER_TO_COL(position[1]);
    return visited[row][col];
}

// Function to mark a position as visited
void markVisited(bool visited[BOARD_SIZE][BOARD_SIZE], chessPos position) {
    int row = LETTER_TO_ROW(position[0]); 
    int col = NUMBER_TO_COL(position[1]);
    visited[row][col] = true;
}

// Function to mark a position as unvisited
void unmarkVisited(bool visited[BOARD_SIZE][BOARD_SIZE], chessPos position) {
    int row = LETTER_TO_ROW(position[0]);
    int col = NUMBER_TO_COL(position[1]);
    visited[row][col] = false;
}

// Recursive helper function to find a path covering all squares on the board
bool findPathHelper(treeNode* node, bool visited[BOARD_SIZE][BOARD_SIZE], chessPosList* path, int* count) {
    // Base case: if the position is not valid or already visited, return false
    if (!isValidPosition(node->position) || isVisited(visited, node->position)) {
        return false;
    }

    // Add current position to the path and mark it as visited
    insertDataToEndList(path, node->position);
    markVisited(visited, node->position);
    (*count)++;// Increment count of visited positions

    // If all positions on the board are visited, return true
    if (*count == BOARD_SIZE * BOARD_SIZE) {
        return true;
    }

    // Recursively explore next possible positions
    treeNodeListCell* curr = node->next_possible_positions.head;
    while (curr != NULL) {
        if (findPathHelper(curr->node, visited, path, count)) {
            return true;// If a complete path is found, return true
        }
        curr = curr->next;
    }

    // Backtrack: remove last position from the path and unmark it as visited
    removeLastCell(path);
    unmarkVisited(visited, node->position);
    (*count)--; // Decrement count of visited positions

    return false;// No complete path found from this node
}

// Function to find a knight path covering all squares on the board
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) {

    int count = 0; // Count of visited positions
    bool visited[BOARD_SIZE][BOARD_SIZE] = { false }; // Initialize visited array
    chessPosList* allBoardPath = (chessPosList*)malloc(sizeof(chessPosList)); // Allocate memory for the path
    checkAllocation((chessPosList*)allBoardPath);

    makeEmptyList(allBoardPath); // Initialize the path list

    // Find a path covering all squares on the board starting from the root node
    bool found = findPathHelper(path_tree->root, visited, allBoardPath, &count);

    // If a path is found, return it; otherwise, free memory and return NULL
    if (found) {
        return allBoardPath;
    }
    else {
        freeChessPosList(allBoardPath);  
        return NULL;
    }
}
