#pragma once
#include "functions.h"

chessPosArray* createEmptyChessPosArray();
chessPosArray*** createBoard();
void checkMovesFromPosition(chessPosArray* arr, int row, int col);
bool isValidMove(chessPos move);
chessPosArray*** validKnightMoves();