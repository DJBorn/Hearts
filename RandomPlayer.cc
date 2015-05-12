
#include <iostream>
#include "Card.h"
#include "Player.h"
#include "Trick.h"
#include "PRNG.h"
#include "RandomPlayer.h"

// random player constructor calls player constructor with r appended to the name
RandomPlayer::RandomPlayer(string name, int seed): Player("r" + name)
{
  // set the seed of the random player to the given seed
  prng(seed);
}

// random player's lead algorithm
Card RandomPlayer::lead()
{
  // the player chooses a random card in their hand
  int choice = prng((int)hand.size() - 1);

  // create a new card that is the same as the player's choice
  Card play(hand.at(choice)->getRank(), hand.at(choice)->getSuit());

  // remove that card from their hand
  hand.removeCard(play);

  // output their name and the card they played
  cout << "  " << showName() << " led " << play << endl;

  // return the card they played
  return play;
}

// random player's throwOff algorithm
Card RandomPlayer::throwOff()
{
  // the player chooses a random card in their hand
  int choice = prng((int)hand.size() - 1);

  // create a new card that is the same as the player's choice
  Card play(hand.at(choice)->getRank(), hand.at(choice)->getSuit());

  // remove that card from their hand
  hand.removeCard(play);

  // output their name and the card they played
  cout << "  " << showName() << " threw off " << play << endl;

  // return the card they played
  return play;
}

// random player's followSuit algorithm
Card RandomPlayer::followSuit(Trick &trick)
{
  // create a suit equivalent to the trick's leading card suit
  Card::Suit suit = trick.getLeadingCard().getSuit();

  // create a suitCount integer set to 0
  int suitCount = 0;

  // loop through the player's hand
  for(int i = 0; i < (int)hand.size(); i++)
    {
      // if the suit of the current hand is the same as the leading card's suit then increase the suitCount by 1
      if(hand.at(i)->getSuit() == suit)
	suitCount++;
    }

  // set the player's choice to be a random number from 0 to the number of suit's in their hand - 1
  int choice = prng(suitCount - 1);

  // loop through the player's hand
  for(int i = 0; i < (int)hand.size(); i++)
    {
      // check if the current card's suit is the same as the leading card's suit
      if(hand.at(i)->getSuit() == suit)
	{
	  // check if choice is 0
	  if ( choice == 0 )
	    {
	      // create a new card with the current card's rank and suit
	      Card play(hand.at(i)->getRank(), hand.at(i)->getSuit());

	      // remove that card from the player's hand
	      hand.removeCard(play);

	      // output the player's name and the card they played
	      cout << "  " << showName() << " followed suit with " << play << endl;

	      // return the card they played
	      return play;
	    }
	  // decrease the choice by 1
	  choice--;
	}
    }
}
