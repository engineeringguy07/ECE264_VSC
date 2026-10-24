// ***
// *** You MUST modify this file
// ***

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "path.h"
#include "mazehelper.h"
#include "maze.h"

char * solveMaze(Maze * m) {
    //An obvious upper bound on the size of the solution path is the number
    //of squares in the maze + 1 (to account for the '\0'). You could make
    //this a tighter bound by accounting for how many walls there are, but
    //this approach is good enough!
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	if (!depthFirstSolve(m, mp, retval, 0)) {
		free(retval);
		return NULL;
		fprintf(stderr, "No solution found!\n");
	} else {
		printf("Solution found: %s\n", retval);
	}
	
	return retval;
}
// Maze *m: The maze structure that contains the maze data, including its dimensions, the 2D array of squares, and the start and end positions.
// MazePos curpos: The current position in the maze that the algorithm is exploring. It is represented as a structure containing x and y coordinates.
// char *path: A character array that will store the path taken to reach the end of the maze. Each character in the array represents a direction
bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {
	
	//FILL IN YOUR CODE HERE
	
	return false;
}

