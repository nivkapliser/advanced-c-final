#include "dataStructures.h"
#include "functions.h"
#include "Ex2_H.h"

// This function creates new chessPosCell with a position and next cell
chessPosCell* createCell(chessPos position, chessPosCell* next) {
	
	// Allocate memory for the new cell
	chessPosCell* res = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkAllocation((chessPosCell*)res);
	
	// Assign position and next pointer to the new cell
	res->position[0] = position[0];
	res->position[1] = position[1];
	res->next = next;

	return res;
}

// This function remove a cell from the list
void removeCell(chessPosList* lst, chessPosCell* toRemove) {
	
	// If toRemove is the head of the list
	if (toRemove == lst->head) {
		lst->head = toRemove->next;
		// If the removed cell was the only cell in the list
		if (lst->head == NULL) {
			lst->tail = NULL;
		}
	}
	else {
		// Find the previous cell of toRemove
		chessPosCell* prev = lst->head;
		while (prev->next != toRemove) {
			prev = prev->next;
		}
		// Update next pointer of the previous cell
		prev->next = toRemove->next;
		// If toRemove was the tail of the list
		if (prev->next == NULL) {
			lst->tail = prev;
		}
	}
	// Free memory allocated for the removed cell
	free(toRemove);
	
}

// This function check if two positions are the same
bool arePositionsSame(chessPos pos1, chessPos pos2) {

	return pos1[0] == pos2[0] && pos1[1] == pos2[1];
}

// Function to remove duplicates from the list
void removeDuplicates(chessPosList* lst) {
	
	// If the list is empty
	if (lst->head == lst->tail)// if list is empty
	{
		return;
	}

	// Iterate through the list
	chessPosCell* current = lst->head;
	while (current != NULL) {
		// Compare current position with positions of subsequent cells
		chessPosCell* runner = current->next;
		while (runner != NULL) {
			if (arePositionsSame(current->position, runner->position)) {
				// If a duplicate is found, remove it
				chessPosCell* duplicate = runner;
				runner = runner->next;
				removeCell(lst, duplicate);
			}
			else {
				runner = runner->next;
			}
		}
		current = current->next;
	}
}

// Function to print the chess board with cell positions
void printBoard(chessPosList* lst) {
printf("   1  2  3  4  5\n");
	for (int i = 0; i < BOARD_SIZE; i++) {
		printf("%c|", 'A' + i);
		for (int j = 0; j < BOARD_SIZE; j++) {
			chessPosCell* current = lst->head;
			int pos = 1;
			// Find and print the position of each cell on the board
			while (current != NULL) {
				if (current->position[1] - '1' == j && current->position[0] - 'A' == i) {
					printf("%2d|", pos);
					break;
				}
				current = current->next;
				pos++;
			}
			// If no cell is found at the position, print a dot
			if (current == NULL) {
				printf(" .|");
			}
		}
		printf("\n");
	}
}

// Function to display the chess board with unique cell positions
void display(chessPosList* lst) {
	
	if (lst == NULL) {
		printf("No knight's tour\n");
		return;
	}

	removeDuplicates(lst);// Remove duplicate positions	
	printBoard(lst);// Print the board with unique positions

}

