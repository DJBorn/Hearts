#include <vector>
#include <iostream>
#include <string>
#include "CardPile.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Trick.h"

// trick constructor
Trick::Trick() {}

// insert a card into the trick
void Trick::insertCard(const Card &card, int &player)
{
  // check if the size of the trick is 0
  if( (int)size() == 0 )
    {
      // set the leading card to the given card
      leadingCard = card;

      // set the trump card to the given card
      trumpCard = card;

      // set the trump player to the given player
      trumpPlayer = player;
    }

  // if there already exists a card, then check if the given card has the same suit as the leading card
  else if( card.getSuit() == leadingCard.getSuit() )
    {
      // if the given card's rank is greater than the trump cards rank then set that card as the new trump card
      if(card.getRank() > trumpCard.getRank())
	{
	  trumpCard = card;
	  trumpPlayer = player;
	}
    }

  // create a new card with the same rank and suit and insert it into the trick
  Card *insertCard = new Card(card.getRank(), card.getSuit());
  push_back(insertCard);
}

// get the leading card
Card Trick::getLeadingCard()
{
  return leadingCard;
}

// get the trump card
Card Trick::getTrumpCard()
{
  return trumpCard;
}

// get the trump player
int Trick::getTrumpPlayer()
{
  return trumpPlayer;
}

