#pragma once
#include "functions.h"

void insertCell(chessPosList* lst, chessPosCell* newCell);
void insertDataToEndList(chessPosList* lst, chessPos position);
void removeLastCell(chessPosList* lst);
bool isValidPosition(chessPos position);
bool isVisited(bool visited[BOARD_SIZE][BOARD_SIZE], chessPos position);
void markVisited(bool visited[BOARD_SIZE][BOARD_SIZE], chessPos position);
void unmarkVisited(bool visited[BOARD_SIZE][BOARD_SIZE], chessPos position);
bool findPathHelper(int row, int col, int count, bool visited[BOARD_SIZE][BOARD_SIZE], chessPosList* path);
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
