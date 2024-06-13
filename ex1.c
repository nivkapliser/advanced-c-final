#include "dataStructures.h"
#include "functions.h"
#include <stdbool.h>
#include <stdlib.h>

// This function creates an empty chessPosArray
chessPosArray* createEmptyChessPosArray() {

	// Allocate memory for the result chessPosArray
	chessPosArray* res = (chessPosArray*)malloc(sizeof(chessPosArray));
	checkAllocation((chessPosArray*)res);

	// Initialize size of chessPosArray
	res->size = 0; // physical size	

	// Allocate memory for the positions array
	// initialized with the minimum number of moves possible (2)
	res->positions = (chessPos*)malloc(MIN_CHESS_POS_SIZE * sizeof(chessPos));
	checkAllocation((chessPos*)res->positions);

	return res;
}

// This function creates the chess board
chessPosArray*** createBoard() {

	int row, col;
	chessPosArray*** board;

	// Allocate memory for the chess board array 
	board = (chessPosArray***)malloc(BOARD_SIZE * sizeof(chessPosArray**));
	checkAllocation((chessPosArray***)board);	

	for (row = 0; row < BOARD_SIZE; row++) {
		board[row] = (chessPosArray**)malloc(BOARD_SIZE * sizeof(chessPosArray*));
		checkAllocation((chessPosArray**)board[row]);
		for (col = 0; col < BOARD_SIZE; col++) {
			// Create an empty chessPosArray for each position on the board
			board[row][col] = createEmptyChessPosArray();
		}
	}

	return board;
}

// This function checks for each possible move if is valid
void checkMovesFromPosition(chessPosArray* arr, int row, int col) {

	int i = 0;

	// Define possible knight's moves
	chessPos moves[MAX_CHESS_POS_SIZE] = {
		{row - 2, col + 1}, {row + 1, col + 2},
		{row - 1, col + 2}, {row + 2, col + 1},
		{row + 2, col - 1}, {row + 1, col - 2},
		{row - 1, col - 2}, {row - 2, col - 1}
	};

	for (i = 0; i < MAX_CHESS_POS_SIZE; i++) {
		// Check if the move is valid
		if (isValidMove(moves[i])) {		
			// Check if the array needs to be resized
			if (arr->size >= MIN_CHESS_POS_SIZE && arr->size % MIN_CHESS_POS_SIZE == 0) {
				arr->positions = (chessPos*)realloc(arr->positions, (arr->size + MIN_CHESS_POS_SIZE) * sizeof(chessPos));
				checkAllocation((chessPos*)arr->positions);
			}
			// Store the valid move in the array
			arr->positions[arr->size][0] = moves[i][0] + 'A';
			arr->positions[arr->size][1] = moves[i][1] + '1';
			arr->size++;
		}
	}
}

// This function checks if a specific move is valid
bool isValidMove(chessPos move) {

	int newRow = move[0];
	int newCol = move[1];

	// Check if the new position is within the board boundaries
	if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
		return true; // Valid move
	}
	return false; // Invalid move
}

// This function creates a 2D array of pointers to chessPosArray
// each contain the possible move of the knight from this position
chessPosArray*** validKnightMoves() {

	int i, j;
	chessPosArray*** board = createBoard();

	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			// Populate each position on the board with valid knight moves
			checkMovesFromPosition(board[i][j], i, j);
		}
	}

	return board;
}

