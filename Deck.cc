#include <vector>
#include <iostream>
#include <cstdlib>
#include "CardPile.h"
#include "Card.h"
#include "Deck.h"

// deck constructor
Deck::Deck(): CardPile() {}

// deck destructor
Deck::~Deck() {}

// generate a default deck
void Deck::generate()
{
  // create a new card starting from the lowest to the highest value and push it into the deck
  for(int i = 0; i <= Card::Hearts; i++)
    {
      for(int j = 0; j <= Card::Ace; j++)
	{
	  Card *newCard = new Card((Card::Rank)j, (Card::Suit)i);
	  push_back(newCard);
	}
    }
}

// input operator for deck
istream& operator>> (istream& in, Deck& deck)
{
  // create a new deck
  Deck newDeck;

  // loop 52 times
  for(int i = 0; i < 52; i++)
    {
      // create a temporary card
      Card tempCard;

      // get the input of the temporary card
      in >> tempCard;

      // create a new card with the temporary card's rank and suit
      Card *newCard = new Card(tempCard.getRank(), tempCard.getSuit());

      // insert the new card into the deck
      deck.push_back(newCard);
    }

  // check if the given deck is a full deck
  if( !deck.playingWithAFullDeck() )
    {
      // output error message
      cerr << "Error, incomplete deck.  Aborting." << endl;
      cout << "    ";

      // output the given deck
      deck.print();
      cout << endl;

      // terminate program
      exit(1);
    }

  // return the in stream
  return in;
}

// check if the deck is a full deck
bool Deck::playingWithAFullDeck() const
{
  // if the size is not 52 then return false
  if ( size() != 52 )
    return false;

  // create a boolean with array value [4][13] and intially set it to false
  bool exist[4][13] = {false};

  // loop 52 times
  for(int i = 0; i < 52; i++)
    {
      // set the array element at the rank and suit to true for each card in the deck
      exist[at(i)->getSuit()][at(i)->getRank()] = true;
    }

  // if their is a card that has not been seen in the deck then return false
  for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 13; j++)
	{
	  if ( !exist[i][j] )
	    return false;
	}
    }

  // return true
  return true;

}
