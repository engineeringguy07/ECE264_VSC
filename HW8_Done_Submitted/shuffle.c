#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
static void printDeck(CardDeck);
void divide(CardDeck, CardDeck *, CardDeck *);
void interleave(CardDeck, CardDeck, int);
void placing_cards(CardDeck, CardDeck, CardDeck, int, int, int, int);
void shuffle_deck(CardDeck, int);

void shuffle(CardDeck origDeck, int round)
{ 
  shuffle_deck(origDeck, round);
}

static void printDeck(CardDeck deck)
{
  int ind;
  for (ind = 0; ind < deck.size; ind ++)
    {
      printf("%c ", deck.cards[ind]);
    }
  printf("\n");
}

void shuffle_deck(CardDeck Deck, int remain_round)
{
  CardDeck *leftDecks = malloc((Deck.size - 1) * sizeof(CardDeck));
  CardDeck *rightDecks = malloc((Deck.size - 1) * sizeof(CardDeck));
  divide(Deck, leftDecks, rightDecks);// Fill allocated mem
  for(int i = 0; i < Deck.size - 1; i++) // Send each pair to interleave
  {
    interleave(leftDecks[i], rightDecks[i], remain_round);
  }
  // Free allocated mem
  free(leftDecks);
  free(rightDecks);
}

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

void interleave(CardDeck leftDeck, CardDeck rightDeck, int remain_round)
{
  CardDeck result;
  result.size = leftDeck.size + rightDeck.size;
  int idx_left = 0;
  int idx_right = 0;
  int idx_result = 0;
  placing_cards(result, leftDeck, rightDeck, idx_left, idx_right, idx_result, remain_round);
}

void placing_cards(CardDeck result, CardDeck leftDeck, CardDeck rightDeck, int idx_left, int idx_right, int idx_result, int remain_round)
{
  if (idx_left == leftDeck.size) // when used all of the left deck
  {
    for (int i = idx_right; i < rightDeck.size; i++) // fill the rest of result with the remaining cards in right deck
    {
      result.cards[idx_result] = rightDeck.cards[i];
      idx_result++;
    }
    if (remain_round == 1) // base case: if this is the last round, print the result
    {
      printDeck(result);
      return;
    }
    else // if not the last round, shuffle the result deck again
    {
      shuffle_deck(result, remain_round - 1);
      return;
    }
  }
  else if (idx_right == rightDeck.size) // when used all of right deck
  {
    for (int i = idx_left; i < leftDeck.size; i++) // fill the rest of result with the remaining cards in left deck
    {
      result.cards[idx_result] = leftDeck.cards[i];
      idx_result++;
    } 
    if (remain_round == 1) // base case: if this is the last round, print the result
    {
      printDeck(result);
      return;
    }
    else // if not the last round, shuffle the result deck again
    {
      shuffle_deck(result, remain_round - 1);
      return;
    }
  }
  
  result.cards[idx_result] = leftDeck.cards[idx_left];
  placing_cards(result, leftDeck,rightDeck, idx_left + 1, idx_right, idx_result + 1, remain_round);

  result.cards[idx_result] = rightDeck.cards[idx_right];
  placing_cards(result, leftDeck,rightDeck, idx_left, idx_right + 1, idx_result + 1, remain_round);

}


