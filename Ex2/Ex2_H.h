#pragma once
#include "functions.h"

chessPosCell* createCell(chessPos position, chessPosCell* next);
void removeCell(chessPosList* lst, chessPosCell* toRemove);
bool arePositionsSame(chessPos pos1, chessPos pos2);
void removeDuplicates(chessPosList* lst);
void printBoard(chessPosList* lst);
void display(chessPosList* lst);