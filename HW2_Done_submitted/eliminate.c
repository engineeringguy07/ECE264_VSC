/* You MUST modify this file */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 

#ifdef TEST_ELIMINATE
// 100% of the score
void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails, stop
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }
	
  // Note that from here on, you can access elements of the arr with
  // expressions like a[i]
	
  // initialize all elements
  int index = 0;
  int *status = (int *)calloc(n, sizeof(int)); // 0 for alive and 1 for eliminated
  for (int i = 0; i < n; i++)
  {
    arr[i] = i;
  }
  // counting to k,
  // mark the eliminated element
  // print the index of the marked element
  // repeat until only one element is unmarked
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < k; j++)
    {
      if (status[index] == 1) // choosen element is eliminated, skip
      {
        j--;
      }
      else if (j == k - 1 && status[index] == 0) // choosen element is alive
      {
        status[index] = 1; // mark as eliminated
        printf("%d\n", arr[index]);
      }
      index = (index + 1) % n;
    }
  }
  // print the last one
  for (int i = 0; i < n; i++)
  {
    if (status[i] == 0)
    {
      printf("%d\n", arr[i]);
      break;
    }
  }

  // release the memory of the array
  free (status);
  free (arr);
}
#endif
