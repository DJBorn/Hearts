#include <iostream>
#include <string>
#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "CardPile.h"


#ifndef __Trick_H__
#define __Trick_H__

// a Trick is a CardPile that holds extra information
// a Trick will hold the leadingCard, the trumpCard, and the player who
// played the trumpCard
class Trick : public CardPile {
 private:
  // contain the leading card
  Card leadingCard;

  // contain the trump card
  Card trumpCard;

  // contain the trump player (index)
  int trumpPlayer;

 public:

  // create insert Card function
  void insertCard(const Card &card, int &player);

  // Trick constructor
  Trick();

  // get the leading card
  Card getLeadingCard();

  // get the trump card
  Card getTrumpCard();

  // get the trump player
  int getTrumpPlayer();
};

#endif
