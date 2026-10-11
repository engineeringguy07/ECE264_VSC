// ***
// *** You MUST modify this file
// ***

#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// do NOT modify this function
static void printDeck(CardDeck deck)
{
  int ind;
  for (ind = 0; ind < deck.size; ind ++)
    {
      printf("%c ", deck.cards[ind]);
    }
  printf("\n");
}

#ifdef TEST_DIVIDE
// leftDeck and rightDeck are arrays of CardDeck
// This function creates pairs of left and right decks
// Each pair divides the original deck into two non-overlapping decks and
// together they form the original deck.
//
// You can think of the left deck held by the left hand taking some
// cards (at least one) from the top of the original deck.
//
// The right deck is held by the right hand taking some (at least one)
// cards from the bottom of the original deck.
void divide(CardDeck origDeck, CardDeck * leftDeck, CardDeck * rightDeck)
{
  for(int k = 0; k < origDeck.size - 1; k++)
  {
    int count = 0;
    for(int i = 0; i <= k; i++)
    {
      leftDeck[k].cards[i] = origDeck.cards[i];
      count++;
    }
  
    leftDeck[k].size = count;
    rightDeck[k].size = origDeck.size - count;
    
    for(int i = 0; i < rightDeck[k].size; i++)
    {
      rightDeck[k].cards[i] = origDeck.cards[count++];
    }
  }  
}
#endif

#ifdef TEST_INTERLEAVE

// Interleave two decks to generate all possible results.
//
// If the leftDeck is {'A'} and the right deck is {'2', '3'}, this
// function prints
// A 2 3
// 2 A 3
// 2 3 A
//
// If the leftDeck is {'A', '2'} and the right deck is {'3', '4'}, this
// function prints 
// 3 4 A 2
// 3 A 4 2
// A 3 4 2 
// 3 A 2 4 
// A 3 2 4 
// A 2 3 4 
//
// Please notice the space does not matter because grading will use
// diff -w
//
// How to generate all possible interleaves?

// Understand that a card at a particular position can come from
// either left or right (two options). The following uses left for
// explanation but it is equally applicable to the right.
//
// After taking one card from the left deck, the left deck has one
// fewer card. Now, the problem is the same as the earlier problem
// (thus, this problem can be solved by using recursion), excecpt one
// left card has been taken. Again, the next card can come from left
// or right.
//
// This process continues until either the left deck or the right deck
// runs out of cards. The remaining cards are added to the result.
// 
// It is very likely that you want to create a "helper" function that
// can keep track of some more arguments.  If you create a helper
// function, please keep it inside #ifdef TEST_INTERLEAVE and #endif
// so that the function can be removed for grading other parts of the
// program.
void placing_cards(CardDeck result, CardDeck leftDeck, CardDeck rightDeck, int idx_left, int idx_right, int idx_result)
{
  if (idx_left == leftDeck.size) // base case: when used all of the left deck
  {
    for (int i = idx_right; i < rightDeck.size; i++) // fill the rest of result with the remaining cards in right deck
    {
      result.cards[idx_result] = rightDeck.cards[i];
      idx_result++;
    }
    printDeck(result);
    return;
  }
  else if (idx_right == rightDeck.size) // base case: when used all of right deck
  {
    for (int i = idx_left; i < leftDeck.size; i++) // fill the rest of result with the remaining cards in left deck
    {
      result.cards[idx_result] = leftDeck.cards[i];
      idx_result++;
    } 
    printDeck(result);
    return;
  }
  
  result.cards[idx_result] = leftDeck.cards[idx_left];
  placing_cards(result, leftDeck,rightDeck, idx_left + 1, idx_right, idx_result + 1);

  result.cards[idx_result] = rightDeck.cards[idx_right];
  placing_cards(result, leftDeck,rightDeck, idx_left, idx_right + 1, idx_result + 1);

}

void interleave(CardDeck leftDeck, CardDeck rightDeck)
{
  CardDeck result;
  result.size = leftDeck.size + rightDeck.size;
  int idx_left = 0;
  int idx_right = 0;
  int idx_result = 0;
  placing_cards(result, leftDeck, rightDeck, idx_left, idx_right, idx_result);
}
#endif



#ifdef TEST_SHUFFLE
// The shuffle function has the following steps:

// 1. calculate the number of possible left and right decks. It is
// the number of cards - 1 because the left deck may have 1, 2,...,
// #cards - 1 cards.
//
// 2. allocate memory to store these possible pairs of left and right
// decks.
//
// 3. send each pair to the interleave function
//
// 4. release allocated memory
//
void shuffle(CardDeck origDeck)
{ 
  //Allocate mem
  CardDeck *leftDecks = malloc((origDeck.size - 1) * sizeof(CardDeck));
  CardDeck *rightDecks = malloc((origDeck.size - 1) * sizeof(CardDeck));
  
  divide(origDeck, leftDecks, rightDecks);// Fill allocated mem

  for(int i = 0; i < origDeck.size - 1; i++) // Send each pair to interleave
  {
    interleave(leftDecks[i], rightDecks[i]);
  }

  // Free allocated mem
  free(leftDecks);
  free(rightDecks);
}
#endif
