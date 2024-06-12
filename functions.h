#pragma once
#include <stdbool.h>
#include "dataStructures.h"

// Constant variables
#define BOARD_SIZE 5
#define MIN_CHESS_POS_SIZE 2 // minimum possible movements (board corners)
#define MAX_CHESS_POS_SIZE 8 // maximum possible movements (middle of board)

// Makros
#define LETTER_TO_ROW(x) x - 'A'; // Convert letter to row index
#define NUMBER_TO_COL(x) x - '1'; // Convert number to column index

// ------------------------------- ex1 ----------------------------------
chessPosArray* createEmptyChessPosArray();
chessPosArray*** createBoard();
void checkMovesFromPosition(chessPosArray* arr, int row, int col);
bool isValidMove(chessPos move);
chessPosArray*** validKnightMoves();

// ------------------------------- ex2 ----------------------------------
chessPosCell* createCell(chessPos position, chessPosCell* next);
void removeCell(chessPosList* lst, chessPosCell* toRemove);
bool arePositionsSame(chessPos pos1, chessPos pos2);
void removeDuplicates(chessPosList* lst);
void printBoard(chessPosList* lst);
void display(chessPosList* lst);

// ------------------------------- ex3 ----------------------------------
void makeEmptyTreeNodeList(treeNodeList* lst);
treeNode* createNewNode(chessPos position);
void insertTreeNode(treeNodeList* lst, treeNode* newNode);
void findAllPossibleKnightPathsHelper(treeNode* node, chessPosArray*** posList, bool visited[BOARD_SIZE][BOARD_SIZE]);
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);

// ------------------------------- ex4 ----------------------------------
void removeLastCell(chessPosList* lst);
bool isValidPosition(chessPos position);
bool isVisited(bool visited[BOARD_SIZE][BOARD_SIZE], chessPos position);
void markVisited(bool visited[BOARD_SIZE][BOARD_SIZE], chessPos position);
void unmarkVisited(bool visited[BOARD_SIZE][BOARD_SIZE], chessPos position);
bool findPathHelper(treeNode* node, bool visited[BOARD_SIZE][BOARD_SIZE], chessPosList* path, int* count);
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);

// ------------------------- helper functions ----------------------------
void makeEmptyList(chessPosList* lst);
void insertCell(chessPosList* lst, chessPosCell* newCell);
void insertDataToEndList(chessPosList* lst, chessPos position);
void getInput(chessPos* startingPosition);
void checkInput(chessPos startingPosition, char ch);
void freeChessPosList(chessPosList* lst);
void freeChessPosArray(chessPosArray* arr);
void freeBoard(chessPosArray*** board);
void freeTreeNodeList(treeNodeList* lst);
void freeTreeNode(treeNode* node);
void freePathTree(pathTree* tree);
void freeMemory(pathTree* allPossiblePaths, chessPosList* knightPath);
void checkAllocation(void* ptr);
