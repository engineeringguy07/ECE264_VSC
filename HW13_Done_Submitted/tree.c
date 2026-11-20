// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

// DO NOT MODIFY FROM HERE --->>>
Tree * newTree(void)
{
  Tree * t = malloc(sizeof(Tree));
  t -> root = NULL;
  return t;
}

void deleteTreeNode(TreeNode * tr)
{
  if (tr == NULL)
    {
      return;
    }
  deleteTreeNode (tr -> left);
  deleteTreeNode (tr -> right);
  free (tr);
}

void freeTree(Tree * tr)
{
  if (tr == NULL)
    {
      // nothing to delete
      return;
    }
  deleteTreeNode (tr -> root);
  free (tr);
}


// <<<--- UNTIL HERE

// ***
// *** You MUST modify the follow function
// ***
#ifdef TEST_BUILDTREE // taken from HW12
static TreeNode * buildTreeHelper(int * inArray, int * postArray, int inStart, int inEnd, int postStart, int postEnd)
{
  // Base case
  if (inStart > inEnd || postStart > postEnd)
  {
    return NULL;
  }

  TreeNode * root = (TreeNode *) malloc(sizeof(TreeNode));
  root -> value = postArray[postEnd];

  // Recursive step
  int i;
  for (i = inStart; i <= inEnd; i++)
  {
    if (inArray[i] == root -> value)
    {
      root -> left = buildTreeHelper(inArray, postArray, inStart, i - 1, postStart, postStart + (i - inStart) - 1);
      root -> right = buildTreeHelper(inArray, postArray, i + 1, inEnd, postStart + (i - inStart), postEnd - 1);
      break;
    }
  }
  return root;
}

Tree * buildTree(int * inArray, int * postArray, int size)
{
  Tree * tr = (Tree *) malloc(sizeof(Tree));
  tr -> root = buildTreeHelper(inArray, postArray, 0, size - 1, 0, size - 1);
  return tr;
}
#endif

#ifdef TEST_PRINTPATH
static bool printPathHelper(TreeNode * node, int val)
{
  // Base case
  if (node == NULL) // no node found
  {
    return false;
  }
  if (node -> value == val) // node found
  {
    printf("%d ", node -> value);
    return true;
  }

  // Recursive step
  // if val is a left or right subtree of the node above
  if (printPathHelper(node -> left, val) || printPathHelper(node -> right, val)) 
  {
    printf("%d ", node -> value); // print the node that contains val
    return true; 
  }
  return false;
}
void printPath(Tree * tr, int val)
{
  if (tr == NULL || tr -> root == NULL)
  {
    return;
  }
  printPathHelper(tr -> root, val);
  printf("\n");
  return;
}
#endif
