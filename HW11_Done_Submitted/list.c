// ***
// *** You MUST modify this file
// ***

#include "list.h"

/** INTERFACE FUNCTIONS **/

PathLL* buildPaths() {
    PathLL* retval = malloc(sizeof(PathLL));
    retval->head = NULL;
    return retval;
}

// Read the comments in list.h to understand what you need to implement
// for each function.
// Remember to check for memory leak.

void freePaths(PathLL* p) {
    // Remove all nodes from a linked list, deallocate the PathLL structure.
    // TODO
    PathNode* curr = p->head;
    while (curr != NULL) {
        PathNode* next = curr->next;
        freeNode(curr);
        curr = next;
    }
    free(p);
}

PathNode* buildNode(char* path) {
    // Allocate a new PathNode with path as its data, return the address.

    // WARNING: don't forget to use strcpy to copy path into the new node.
    // Don't just set them equal, otherwise if the input path changes the node
    // will have the wrong path.

    // TODO
    PathNode* newNode = NULL;
    newNode = malloc(sizeof(PathNode));
    newNode->path = malloc(strlen(path) + 1);
    strcpy(newNode->path, path);
    newNode->next = NULL;
    return newNode;
}

void freeNode(PathNode* p) {
    // Deallocate a pathNode
    // TODO
    free(p->path);
    free(p);
}

// Helper function: count the number of turns in a path
static int countTurns(const char* path) {
    int turns = 0;
    for (int i = 1; path[i] != '\0'; i++) {
        if (path[i] != path[i - 1]) {
            turns++;
        }
    }
    return turns;
}

// Helper function: compare two paths lexicographically
static int comparePaths(const char* path1, const char* path2) {
    if (strlen(path1) != strlen(path2)) 
    {
        if (strlen(path1) < strlen(path2)) 
        {
            return -1; // path1 come before path2
        } 
        else 
        {
            return 1; // path1 come after path2
        }    
    }

    if (countTurns(path1) != countTurns(path2)) 
    {
        if (countTurns(path1) < countTurns(path2)) 
        {
            return -1; // path1 come before path2
        } 
        else 
        {
            return 1; // path1 come after path2
        }    
    }

    return strcmp(path1, path2);
}

bool addNode(PathLL* paths, char* path) {
    // Add a path to the list of paths
    // TODO
    // Insert the new node at the right order in the list
    PathNode* newNode = buildNode(path);
    PathNode* prev = NULL;
    PathNode* curr = paths->head;
    
    while (curr != NULL && comparePaths(curr->path, path) < 0)
    {
        prev = curr;
        curr = curr->next;
    }
    newNode->next = curr;
    if (prev == NULL) 
    {
        paths->head = newNode;
    } 
    else 
    {
        prev->next = newNode;
    }
    return true;
}

bool removeNode(PathLL* paths, char* path) {
    // Remove a node from the list with the specified path
    // TODO
    PathNode* curr = paths->head;
    PathNode* prev = NULL;
    while (curr != NULL)
    {
        if (strcmp(curr->path, path) == 0)
        {
            if (prev == NULL) {
                paths->head = curr->next;
            } else {
                prev->next = curr->next;
            }
            freeNode(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

bool containsNode(PathLL* paths, char* path) {
    // Return true if path exists in the list
    // TODO
    PathNode* curr = paths->head;
    while (curr != NULL)
    {
        if (strcmp(curr->path, path) == 0)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void printPaths(PathLL* paths, FILE* fptr) {
    PathNode* curr = paths->head;
    int i = 0;
    while (curr != NULL) {
        fprintf(fptr, "Path %2d: %s\n", i, curr->path);
        i++;
        curr = curr->next;
    }
}
