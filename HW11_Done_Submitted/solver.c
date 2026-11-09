// ***
// *** You MUST modify this file
// ***

#include "solver.h"
#include "list.h"
#include "mazehelper.h"
#include "path.h"

PathLL* solveMaze(Maze* m) {

    PathLL* successPaths = buildPaths();
    char* retval = malloc(((m->height * m->width) + 1) * sizeof(char));

    MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
    depthFirstSolve(m, mp, retval, 0, successPaths);

    free(retval);

    return successPaths;
}

void depthFirstSolve(Maze* m, MazePos curpos, char* path, int step,
                     PathLL* successPaths) {

    // TODO (Your best bet is to modify a working implementation from HW9)
    if (atEnd(curpos, m)) // base case: end of maze, checked path as successed
	{
		path[step] = '\0'; // end of path
        addNode(successPaths, path);
		return; 
	}
	if(!squareOK(curpos, m)) // base case: check for valid square
	{
		return;
	}
	m->maze[curpos.ypos][curpos.xpos].visited = true;
	
    // Explore all four directions, should have done this for the previous hw to make my life easier :)
	MazePos north = {.xpos = curpos.xpos, .ypos = curpos.ypos - 1};
    MazePos south = {.xpos = curpos.xpos, .ypos = curpos.ypos + 1};
    MazePos east = {.xpos = curpos.xpos + 1, .ypos = curpos.ypos};
    MazePos west = {.xpos = curpos.xpos - 1, .ypos = curpos.ypos};
 
    path[step] = 'N';
    depthFirstSolve(m, north, path, step + 1, successPaths);
 
    path[step] = 'S';
    depthFirstSolve(m, south, path, step + 1, successPaths);
 
    path[step] = 'E';
    depthFirstSolve(m, east, path, step + 1, successPaths);
 
    path[step] = 'W';
    depthFirstSolve(m, west, path, step + 1, successPaths);
 
    m->maze[curpos.ypos][curpos.xpos].visited = false;
}
