#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataStructures.h"
#include "functions.h"

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


bool findPathHelper(int row, int col, int count, bool visited[BOARD_SIZE][BOARD_SIZE], chessPosList* path) {
    
    // If all positions on the board are visited, return true
    if (count == BOARD_SIZE * BOARD_SIZE) {
        return true;
    }

    // Iterate through all possible moves of the knight
    for (int i = 0; i < MAX_CHESS_POS_SIZE; i++) {
        int nextRow = row + rowMoves[i];
        int nextCol = col + colMoves[i];
        chessPos newPos = { nextRow + 'A', nextCol + '1' }; // Convert the row and column indices to chess notation
        // Check if the new position is valid and not visited
        if (isValidPosition(newPos) && !visited[nextRow][nextCol]) {
            visited[nextRow][nextCol] = true; // Mark the new position as visited
            insertDataToEndList(path, newPos); // Add the new position to the path

            // Recursively search for the next position
            if (findPathHelper(nextRow, nextCol, count + 1, visited, path)) {
                return true; // If a complete path is found, return true
            }
            // If no complete path is found, backtrack by removing the last position from the path
            else { 
                visited[nextRow][nextCol] = false;
                removeLastCell(path);
            }
        }
    }

    return false; // No complete path found from this node
}

// Function to find a knight's path covering all squares on the board
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) {
    
    bool visited[BOARD_SIZE][BOARD_SIZE] = { false }; // Initialize visited array
    int row = LETTER_TO_ROW(path_tree->root->position[0]); // Convert the letter to row index
    int col = NUMBER_TO_COL(path_tree->root->position[1]); // Convert the number to column index

    // Allocate memory for the path list
    chessPosList* allBoardPath = (chessPosList*)malloc(sizeof(chessPosList)); // Allocate memory for the path
    checkAllocation((chessPosList*)allBoardPath);

    makeEmptyList(allBoardPath); // Initialize the path list;

    visited[row][col] = true; // Mark the starting position as visited
    insertDataToEndList(allBoardPath, path_tree->root->position); // Add the starting position to the path
    int count = 1; // Initialize the count of visited positions

    // Find a path covering all squares on the board starting from the root node
    bool found = findPathHelper(row, col, count, visited, allBoardPath);

    // If a path is found, return it; otherwise, free memory and return NULL
    if (found) {
        return allBoardPath;
    }
    else {
        freeChessPosList(allBoardPath);
        return NULL;
    }
}
