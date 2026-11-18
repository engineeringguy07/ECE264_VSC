// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// DO NOT MODIFY FROM HERE --->>>
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

static void preOrderTraversal(TreeNode * tn, FILE * fptr)
{
  if (tn == NULL)
    {
      return;
    }
  fprintf(fptr, "%d\n", tn -> value);
  preOrderTraversal(tn -> left, fptr);
  preOrderTraversal(tn -> right, fptr);
}

void preOrderToFile(Tree * tr, char * filename)
{
  if (tr == NULL)
    {
      return;
    }
  FILE * fptr = fopen(filename, "w");
  preOrderTraversal(tr -> root, fptr);
  fclose (fptr);
}
// <<<--- UNTIL HERE

// ***
// *** You MUST modify the follow function
// ***

#ifdef TEST_BUILDTREE
// Consider the algorithm posted on
// https://www.geeksforgeeks.org/construct-a-binary-tree-from-postorder-and-inorder/
// Feel free to add helper functions
// inArray: an integer array containing the in-order traversal output
// postArray: an integer array containing the post-order traversal output
// size: number of integers in inArray or postArray
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

