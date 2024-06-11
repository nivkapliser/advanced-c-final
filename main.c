#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dataStructures.h"
#include "functions.h"

int main() {
    
    chessPos startingPosition; 

    // Gets the data from the user
    // Checking if input is valid
    // if input is not valid - prints error messege and exits
    getInput(&startingPosition);

    // Genarates all the possible paths from the inputed position
    pathTree allPossiblePaths = findAllPossibleKnightPaths(&startingPosition);

    // Finds the knight's path covers all board
    chessPosList* knightPath = findKnightPathCoveringAllBoard(&allPossiblePaths);   
        
    // Display the knight's path covering all board squares
    if (knightPath != NULL) {
        display(knightPath);
    }
    else {
        printf("No knight's tour\n");
    }

    // Free all the remaining memory
    freeMemory(&(allPossiblePaths), knightPath);

    return 0;
}









