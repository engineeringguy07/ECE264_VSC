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

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {
	if (atEnd(curpos, m)) // base case: end of maze
	{
		path[step] = '\0'; // end of path
		return true; 
	}
	if(!squareOK(curpos, m)) // base case: check for valid square
	{
		return false;
	}
	else
	{
		m->maze[curpos.ypos][curpos.xpos].visited = true;
	}

	// Go north first
	curpos.ypos--;
	if (depthFirstSolve(m, curpos , path, step+1))
	{
		path[step]='N';
		return true;
	}
	else // Go east
	{
		curpos.ypos++;
		curpos.xpos++;
		if (depthFirstSolve(m, curpos , path, step+1))
		{
			path[step] = 'E';
			return true;
		}
		else // Go west
		{
			curpos.xpos--;
			curpos.xpos--;
			if (depthFirstSolve(m, curpos , path, step+1))
			{
				path[step]='W';		
				return true;	
			}
			else // Go south
			{
				curpos.xpos++;
				curpos.ypos++;

				if (depthFirstSolve(m, curpos , path, step+1))
				{
					path[step] = 'S';
					return true;
				}
			}
		}
	}

	//FILL IN YOUR CODE HERE
	
	return false;
}

