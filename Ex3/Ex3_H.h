#pragma once
#include "functions.h"

void makeEmptyTreeNodeList(treeNodeList* lst);
treeNode* createNewNode(chessPos position);
void insertTreeNode(treeNodeList* lst, treeNode* newNode);
void findAllPossibleKnightPathsHelper(treeNode* node, chessPosArray*** posList, bool visited[BOARD_SIZE][BOARD_SIZE]);
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
