/* MODIFY this file */

#include "sort.h"

void ssort(int * arr, int size) {
	/* For step 3, fill this in to perform a selection sort
	   For step 4, add conditional compilation flags to perform an ascending selection sort instead */
	for (int i = 0; i < size - 1; i++) {
		int maxIndex = i;
		for (int j = i + 1; j < size; j++) 
		{
			if (arr[j] > arr[maxIndex]) {
				maxIndex = j;
			}
		}
		if (maxIndex != i) 
		{
			int temp = arr[i];
			arr[i] = arr[maxIndex];
			arr[maxIndex] = temp;
		}
	}
	#ifdef ASCENDING
		// Ascending order selection sort
		for (int i = 0; i < size - 1; i++) {
			int minIndex = i;
			for (int j = i + 1; j < size; j++) 
			{
				if (arr[j] < arr[minIndex]) {
					minIndex = j;
				}
			}
			if (minIndex != i) 
			{
				int temp = arr[i];
				arr[i] = arr[minIndex];
				arr[minIndex] = temp;
			}
		}
	#endif
}
