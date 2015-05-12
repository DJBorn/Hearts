#include <vector>
#include <algorithm>
#include <iostream>
#include "CardPile.h"
#include "Card.h"

const uint32_t CardPile::DefaultRandomSeed = 37;

CardPile::CardPile() : prng(DefaultRandomSeed) {}

// set the cardpile seed
void CardPile::setSeed(uint32_t seed)
{
  prng.seed(seed);
}

// remove all the cards from the cardpile
void CardPile::emptyCardPile()
{
  // for every card in the cardpile, delete the card
  for(int i = 0; i < (int)size(); i++)
    {
      delete(at(i));
    }

  // clear the cardpile vector
  clear();
}

// cardpile destructor
CardPile::~CardPile()
{
  // for every card in the cardpile, delete the card
  for(int i = 0; i < (int)size(); i++)
    {
      delete(at(i));
    }
}

// remove a card from the cardpile
void CardPile::removeCard(Card &card)
{
  // search through the cardpile
  for(int i = 0; i < (int)size(); i++)
    {
      // if the rank and suit of the current card is equal to the given card then delete that card and erase it from the vector
      if( at(i)->getRank() == card.getRank() && at(i)->getSuit() == card.getSuit() )
	{
	  delete(at(i));
	  erase(begin() + i);
	}
    }
}

// print the cardpile
void CardPile::print()
{
  // print each card's rank and suit followed by a space
  for(int i = 0; i < (int)size(); i++)
    {
      cout << Card::RankName.at(at(i)->getRank());
      cout << Card::SuitName.at(at(i)->getSuit());
      cout << " ";
    }
}

// get the hearts value of the cardpile
int CardPile::heartsValue()
{
  // declare the total value as 0
  int totalValue = 0;

  // loop through the cardpile's size
  for (int i = 0 ; i < (int)size(); i++)
    {
      // if the suit is a hearts then increase the total value by 1
      if ( at(i)->getSuit() == Card::Hearts )
	totalValue++;

      // if the card is the queen of spades and increase the total value by 13
      if ( at(i)->getSuit() == Card::Spades && at(i)->getRank() == Card::Queen )
	totalValue += 13;
    }

  // return the total value
  return totalValue;
}

// shuffle the cardpile
void CardPile::shuffle()
{
  // use Fisher-Yates shuffle
  for (int i = size() - 1; i > 0; i--)
    {
      const int j = prng(i);
      Card* tmp = at(j);
      at(j) = at(i);
      at(i) = tmp;
    }
}
